// #include <stdio.h>
// #include <string>
// #include <iostream>
// #define _USE_MATH_DEFINES
// #include <cmath>

// #define GLM_FORCE_RADIANS
// #include "glm/vec2.hpp"
// #include "glm/vec3.hpp"
// #include "glm/vec4.hpp"
// #include "glm/mat4x4.hpp"
// #include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
// #include "glm/gtc/matrix_inverse.hpp"

// glm::mat4 Multiply( glm::mat4 a, glm::mat4 b );
// glm::vec3 Multiply( glm::mat4 a, glm::vec3 b );
// glm::vec3 ScalePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::vec3 scale );
// glm::vec3 RotatePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third );
// void WhoAmI( std::string &yourName, std::string &yourEmailAddress );
// void PrintMatrix( glm::mat4 mat );


// void PrintMatrix(glm::mat4 mat)
// {
// 	for (int row = 0; row < 4; row++)
// 	{
// 		fprintf(stderr, "  %7.2f %7.2f %7.2f %7.2f\n", mat[row][0], mat[row][1], mat[row][2], mat[row][3]);
// 	}
// }

// void PrintVec3(glm::vec3 a) {
// 	printf("  %f, %f, %f\n", a.x, a.y, a.z);
// }


// int main()
// {
// 	printf("Grace's Tests\n\n");

// 	// Multiply 4x4 matrices
// 	{
// 		glm::mat4 first(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
// 		glm::mat4 second(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
// 		glm::mat4 expected(538, 612, 686, 760, 650, 740, 830, 920, 762, 868, 974, 1080, 874, 996, 1118, 1240);
// 		glm::mat4 result = Multiply(first, second);
// 		bool passed = expected == result;
// 		printf("Multiply matrices: %s\n", passed ? "passed" : "failed");
// 		if (!passed) {
// 			printf("Result:\n");
// 			PrintMatrix(result);
// 			printf("Expected:\n");
// 			PrintMatrix(expected);
// 		}
// 	}

// 	// Multiply vector by matrix
// 	{
// 		glm::mat4 first(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
// 		glm::vec3 second(17, 18, 19);
// 		glm::vec3 expected(291, 346, 401);
// 		glm::vec3 result = Multiply(first, second);
// 		bool passed = expected == result;
// 		printf("Multiply vector: %s\n", passed ? "passed" : "failed");
// 		if (!passed) {
// 			printf("Result:\n");
// 			PrintVec3(result);
// 			printf("Expected:\n");
// 			PrintVec3(expected);
// 		}
// 	}

// 	// Scale point around another point
// 	{
// 		glm::vec3 first(1, 2, 3);
// 		glm::vec3 second(4, 5, 6);
// 		glm::vec3 third(2, -1, 0);
// 		glm::vec3 expected(-2, 8, 6);
// 		glm::vec3 result = ScalePointAroundAnotherPoint(first, second, third);
// 		bool passed = expected == result;
// 		printf("Scale point: %s\n", passed ? "passed" : "failed");
// 		if (!passed) {
// 			printf("Result:\n");
// 			PrintVec3(result);
// 			printf("Expected:\n");
// 			PrintVec3(expected);
// 		}
// 	}

// 	// Rotate point around another point
// 	{
// 		const glm::mediump_float pi = 3.141592653f;
// 		glm::vec3 first(2, 2, 3);
// 		glm::vec3 second(4, 4, 6);
// 		glm::vec3 xaxis(1, 0, 0);
// 		glm::mat4 rotx(1);
// 		rotx = glm::rotate(rotx, pi, xaxis);
// 		glm::vec3 yaxis(0, 1, 0);
// 		glm::mat4 roty(1);
// 		roty = glm::rotate(roty, pi, yaxis);
// 		glm::vec3 zaxis(0, 0, 1);
// 		glm::mat4 rotz(1);
// 		rotz = glm::rotate(rotz, pi, zaxis);
// 		glm::vec3 expected(2, 2, 3);
// 		glm::vec3 result = RotatePointAroundAnotherPoint(first, second, rotx, roty, rotz);
// 		bool passed = round(expected) == round(result);
// 		printf("Rotate Point: %s\n", passed ? "passed" : "failed");
// 		if (!passed) {
// 			printf("Result:\n");
// 			PrintVec3(result);
// 			printf("Expected:\n");
// 			PrintVec3(expected);
// 		}
// 	}
// 	return 0;
// }

glm::mat4 Multiply( glm::mat4 a, glm::mat4 b ) {
	return a*b;
}

glm::vec3 Multiply( glm::mat4 a, glm::vec3 b ) {
	/*this will change b to a vec4 by adding a 0 to the last index and then multiplying and changing the result to a vec3*/
	glm::vec4 vec4b(b, 1.);
	glm::mat4 newMatrix(vec4b, vec4b, vec4b, vec4b);
	glm::mat4 matrixProduct(a*newMatrix);
	glm::vec3 vec3Product(0.0,0.0,0.0);

	for(int i = 0; i < 3; i++) {
		vec3Product[i] = matrixProduct[0][i];
	}

	return vec3Product;
}

glm::vec3 ScalePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::vec3 scale ) {
	glm::vec3 temp = inputPoint - centerPoint;
	return centerPoint + (scale*temp);
}

glm::vec3 RotatePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third ) {
	glm::vec3 temp = inputPoint - centerPoint;
	glm::mat4 calc = third*second*first;
	glm::vec3 test = centerPoint + Multiply(calc, temp);

	return centerPoint + (Multiply(calc, temp));
}

void WhoAmI( std::string &yourName, std::string &yourEmailAddress ) {
	yourName = "Grace Bullock";
	yourEmailAddress = "bullocgr@oregonstate.edu";
}