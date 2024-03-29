/*
 * main.cpp
 *
 */

#include <iostream>
#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include "math/geometry.h"
#include "parsers/PPMWriter.h"

#include "core/RayTracer.h"
#include "core/Camera.h"
#include "core/Scene.h"


using namespace rt;
using namespace rapidjson;

float clamp(const float &lo, const float &hi, const float &v)
{ return std::max(lo, std::min(hi, v)); }

int main(int argc, char* argv[]){

	//parse commandline arguments
	char* inputFile=argv[1];    //first command line argument holds the path to the json input file
	char* outputFile=argv[2];   //second command line argument holds the path to the output image file

	std::printf("Input file: %s\n",inputFile);

	//parse json input file using rapidjson
	std::ifstream ifs(inputFile);
	IStreamWrapper is(ifs);
	Document d;     // d holds the complete json object
	d.ParseStream(is);

	//generate a camera according to the input file
	Camera* camera=Camera::createCamera(d["camera"]);

	//print camera data (based on the input file provided)
	camera->printCamera();

	//generate the scene according to the input file
	Scene* scene=new Scene();
	scene->createScene(d["scene"]);

	//
	// Main function, render scene
	//
	Vec3f* pixelbuffer=RayTracer::render(camera, scene, d["nbounces"].GetInt());
	// Render with BVH
//    Vec3f* pixelbuffer=RayTracer::render_BVH(camera, scene, d["nbounces"].GetInt());



	//free resources when rendering is finished
//	delete camera;
//	delete scene;



	//convert linear RGB pixel values [0-1] to range 0-255
//	RayTracer::tonemap(pixelbuffer);


    std::ofstream ofs;
    ofs.open("./out.ppm");
    ofs << "P6\n" << camera->getWidth() << " " << camera->getHeight() << "\n255\n";
    for (uint32_t i = 0; i < camera->getHeight() * camera->getWidth(); ++i) {
        char r = (char)(255 * clamp(0, 1, pixelbuffer[i].x));
        char g = (char)(255 * clamp(0, 1, pixelbuffer[i].y));
        char b = (char)(255 * clamp(0, 1, pixelbuffer[i].z));
        ofs << r << g << b;
    }

    ofs.close();

//    delete [] pixelbuffer;



	std::printf("Output file: %s\n",outputFile);

	//write rendered scene to file (pixels RGB values must be in range 0255)
//	PPMWriter::PPMWriter(camera->getWidth(), camera->getHeight(), pixelbuffer, outputFile);

	delete pixelbuffer;
    delete camera;
    delete scene;
}


