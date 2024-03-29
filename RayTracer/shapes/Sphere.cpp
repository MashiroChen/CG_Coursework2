/*
 * Sphere.cpp
 *
 *
 */
#include "iostream"
#include "Sphere.h"
#include "math/geometry.h"


namespace rt{

    Sphere::~Sphere(){};


	/**
	 * Computes whether a ray hit the specific instance of a sphere shape and returns the hit data
	 *
	 * @param ray cast ray to check for intersection with shape
	 *
	 * @return hit struct containing intersection information
	 *
	 */
	Hit Sphere::intersect(Ray ray){

		Hit h;
		//-----------to be implemented -------------
		// We know the center of sphere and its radius.
		// Thus we can construct an equation |ray - center|^2 = radius^2
		// If the equation has answer, then they intersect.

		Vec3f diff = ray.origin - center;
        float a = ray.dir.dotProduct(ray.dir);
        float b = 2 * ray.dir.dotProduct(diff);
        float c = diff.dotProduct(diff) - (radius * radius);

        // origin + t * dir, here dir_parameter is t
        float dir_parameter;

        // Check whether this quatratic has solution
        float discriminant = b * b - 4 * a * c;
        if (discriminant < 0){
            h.intersection = false;
        } else {
            h.intersection = true;

            // Calculate two solutions
            float sol1 = (-b + sqrtf(discriminant))/(2 * a);
            float sol2 = (-b - sqrtf(discriminant)) / (2 * a);

            // The smaller value is more suitable (closer to camera)
            if (sol1 <= sol2){
                dir_parameter = sol1;
            } else {
                dir_parameter = sol2;
            }
            h.point = ray.origin + dir_parameter * ray.dir;
        }
		return h;
	}

	Vec3f Sphere::MapTexture(Hit h){
	    if (hasTexutre) {
            Vec3f normalized_hitpoint = Vec3f((h.point - center)[0] / radius,
                                              (h.point - center)[1] / radius,
                                              (h.point - center)[2] / radius);
            float theta = acos(normalized_hitpoint[1]);
            float phi = atan2(normalized_hitpoint[0], normalized_hitpoint[2]);
            if (phi < 0)
                phi += 2 * M_PI;
            float u = phi / (2 * M_PI);
            float v = theta / (M_PI);
            int width = texture_img.cols;
            int height = texture_img.rows;
            int mapping_x = (int) ((width - 1) * u);
            int mapping_y = (int) ((height - 1) * v);
            Vec3f diffuseColor = Vec3f(texture_img.at<cv::Vec3b>(mapping_y, mapping_x)[2]/255.0,
                                       texture_img.at<cv::Vec3b>(mapping_y, mapping_x)[1]/255.0,
                                       texture_img.at<cv::Vec3b>(mapping_y, mapping_x)[0]/255.0);
            return diffuseColor;
        } else {
	        return material->getDc();
	    }
	}


	Vec3f Sphere::CalculateNorm(Hit h){
        return (h.point - center).normalize();
	}

	// return the aabb, with min and max point.
    void Sphere::CalculateBox() {
        Vec3f radius_list = Vec3f(radius, radius, radius);
	    this->aabbMin = center - radius_list;
	    this->aabbMax = center + radius_list;
    }

    Vec3f Sphere::getAABBMin(){
        return  this->aabbMin;
	}

	Vec3f Sphere::getAABBMax() {
	    return this->aabbMax;
	}





} //namespace rt


