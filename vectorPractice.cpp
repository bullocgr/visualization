// #include <stdio.h>
// #include <string>
// #include <iostream>
// #define _USE_MATH_DEFINES
// #include <cmath>

// #define GLM_FORCE_RADIANS
// #include "glm/vec2.hpp"
// #include "glm/vec3.hpp"
// #include "glm/mat4x4.hpp"
// #include "glm/gtc/matrix_transform.hpp"
// #include "glm/gtc/matrix_inverse.hpp"



// void WhoAmI(std::string &yourName, std::string &yourEmailAddress);
// glm::vec3 WhatPartOfALivesInBDir(glm::vec3 a, glm::vec3 b);
// glm::vec3 WhatPartOfALivesPerpToB(glm::vec3 a, glm::vec3 b);
// glm::vec3 UnitSurfaceNormal(glm::vec3 q, glm::vec3 r, glm::vec3 s);
// float Area(glm::vec3 q, glm::vec3 r, glm::vec3 s);
// bool IsPointInTriangle(glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p);
// float DistanceFromPointToPlane(glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p);


// int main() {
// 	glm::vec3 vectorA = glm::vec3(3.0,9.0,3.0);
// 	glm::vec3 vectorB = glm::vec3(0.0,0.0,4.0);
// 	glm::vec3 vectorS = glm::vec3(12.0,0.0,5.0);
// 	glm::vec3 vectorP = glm::vec3(5.0,3.0,3.0);


// /*finished*/
// 	// WhatPartOfALivesInBDir(vectorA, vectorB);
// 	// WhatPartOfALivesPerpToB(vectorA, vectorB);
// 	// UnitSurfaceNormal(vectorA, vectorB, vectorS);
// 	// Area(vectorA, vectorB, vectorS);
// 	// DistanceFromPointToPlane(vectorA, vectorB, vectorS, vectorP);
// 	// IsPointInTriangle(vectorA, vectorB, vectorS, vectorP);

// 	return 0;
// }



/*Functions starting*/

glm::vec3 WhatPartOfALivesInBDir(glm::vec3 a, glm::vec3 b) {
	float bMag = 0.0;
	float dotResult = 0.0;
	glm::vec3 bUnitVec = glm::vec3(0.0, 0.0, 0.0);

	bUnitVec = glm::normalize(b);

	return cross(bUnitVec,(glm::cross(a, bUnitVec)));
}

glm::vec3 WhatPartOfALivesPerpToB(glm::vec3 a, glm::vec3 b) {
	glm::vec3 finalVec = glm::vec3(0.0,0.0,0.0);

	for(int i = 0; i < 3; i++) {
		finalVec[i] = a[i] - (WhatPartOfALivesInBDir(a,b)[i]);
	}

	return finalVec;
}

glm::vec3 UnitSurfaceNormal(glm::vec3 q, glm::vec3 r, glm::vec3 s) {
	//n = (q-r) x (s-q)
	glm::vec3 qAndr = glm::vec3(0.0,0.0,0.0);
	glm::vec3 sandq = glm::vec3(0.0,0.0,0.0); 

	/*subtract the vectors to set them up to cross them*/
	qAndr = q - r;
	sandq = s - q;

	return glm::cross(qAndr, sandq);
}

float Area(glm::vec3 q, glm::vec3 r, glm::vec3 s) {
	/*First take the cross product of q to s and q to r
	then calculate the magnitude of this vector and divide by 2*/
	glm::vec3 xproduct = glm::vec3(0.0,0.0,0.0);
	glm::vec3 QToS = glm::vec3(0.0,0.0,0.0);
	glm::vec3 QToR = glm::vec3(0.0,0.0,0.0);
	float mag = 0.0;

	QToS = s - q;
	QToR = r - q;

	xproduct = cross(QToS, QToR);

	//calculate the magnitude of the cross product
	for(int i = 0; i < 3/*length(b)*/; i++) {
		float current = pow(xproduct[i], 2.0);
		mag += current;
	}

	return sqrt(mag)/2.0;
}

bool IsPointInTriangle(glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p) {
	/*First calculate all the vectors from the point
	then find the vector from r (or the other points) to s (or the points that the vector is going to)
	then calculate the perpendicular value and take the dot product of that and the first value
	then check to see if all are >0 and if true return true because the point is in the triangle
	REMINDER 0 is false and 1 is true*/

	float RToS = ((p.x - s.x) * (r.y - s.y)) - ((r.x - s.x) * (p.y - s.y));
	float SToQ = ((p.x - q.x) * (s.y - q.y)) - ((s.x - q.x) * (p.y - q.y));
	float QToR = ((p.x - r.x) * (q.y - r.y)) - ((q.x - r.x) * (p.y - r.y)); 
	bool hasNeg, hasPos;

	hasNeg = (RToS < 0 || SToQ < 0 || QToR < 0);
	hasPos = (RToS > 0 || SToQ > 0 || QToR > 0);

	std::cout<<"is point in triangle: "<<!(hasNeg && hasPos)<<std::endl;
	return !(hasNeg && hasPos);
}

float DistanceFromPointToPlane(glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p) {
	/*find n which is already a function written
	then find the unit vector of n */

	glm::vec3 n = UnitSurfaceNormal(q, r, s);
	glm::vec3 nUnitVec = glm::vec3(0.0,0.0,0.0);
	float nMag = 0.0;

	for(int i = 0; i < 3/*length(b)*/; i++) {
		float current = pow(n[i], 2.0);
		nMag += current;
	}

	/*This calculates the unit vector of B and stores it into a new vector*/
	for(int i = 0; i < 3; i++) {
		nUnitVec[i] = n[i]/(sqrt(nMag));
	}

	// fprintf( stderr, "n = (%6.2f,%6.2f,%6.2f)\n", n.x, n.y, n.z );
	glm::vec3 test = glm::vec3(0.0,0.0,0.0);
	test = p-q;

	return dot((p-q),nUnitVec);	
}

void WhoAmI(std::string &yourName, std::string &yourEmailAddress) {
	yourName = "Grace Bullock";
	yourEmailAddress = "bullocgr@oregonstate.edu";
}


