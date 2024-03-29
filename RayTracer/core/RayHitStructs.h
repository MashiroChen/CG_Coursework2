/*
 * RayHitStructs.h
 */

#ifndef CORE_RAYHITSTRUCTS_H_
#define CORE_RAYHITSTRUCTS_H_

#include "math/geometry.h"

namespace rt{

/*
 * Ray structure definition
 */
enum RayType {PRIMARY, SECONDARY, SHADOW};

struct Ray{

	RayType raytype;
	Vec3f dir;
	Vec3f origin;



	//----------Ray variables to be filled------
};


struct Hit{

	Vec3f point; //point where ray hits a shape
	//----------Hit variables to be filled------
	Vec3f reflectedColor;
	bool intersection=false;

};

}


#endif /* CORE_RAYHITSTRUCTS_H_ */
