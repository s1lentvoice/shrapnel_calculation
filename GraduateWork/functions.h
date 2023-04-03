#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "file_structs.h"
#include "data_making.h"
#include "missile.h"
#include "target.h"


coordinates MakeRotation(auto T, double phi, double theta) {
	coordinates res, res_temp;

	phi = phi * std::numbers::pi_v<double> / 180.0;
	theta = theta * std::numbers::pi_v<double> / 180.0;

	res_temp.z = std::cos(phi) * T.z - std::sin(phi) * T.x;
	res_temp.x = std::sin(phi) * T.z + std::cos(phi) * T.x;
	res_temp.y = T.y;

	res.x = std::cos(theta) * res_temp.x - std::sin(theta) * res_temp.y;
	res.y = std::sin(theta) * res_temp.x + std::cos(theta) * res_temp.y;
	res.z = res_temp.z;

	return res;
}

velocity MakeRotationVelo(auto T, double phi, double theta) {
	velocity res, res_temp;

	phi = phi * std::numbers::pi_v<double> / 180.0;
	theta = theta * std::numbers::pi_v<double> / 180.0;

	res_temp.z = std::cos(phi) * T.z - std::sin(phi) * T.x;
	res_temp.x = std::sin(phi) * T.z + std::cos(phi) * T.x;
	res_temp.y = T.y;

	res.x = std::cos(theta) * res_temp.x - std::sin(theta) * res_temp.y;
	res.y = std::sin(theta) * res_temp.x + std::cos(theta) * res_temp.y;
	res.z = res_temp.z;

	return res;
}

//returns vector length
double VectorMod(auto T) {
	return std::sqrt(std::pow(T.x, 2) + std::pow(T.y, 2) + std::pow(T.z, 2));
}

//returns cos() of angle
double AngleBetweenVectors(auto T1, auto T2) {
	double num = T1.x * T2.x + T1.y * T2.y + T1.z * T2.z;
	double denom = VectorMod(T1) * VectorMod(T2);
	return num / denom;
}

double PointsDistance(coordinates T1, coordinates T2) {
	double res;

	res = std::sqrt(std::pow(T1.x - T2.x, 2) + std::pow(T1.y - T2.y, 2) + std::pow(T1.z - T2.z, 2));

	return res;
}

//returns coefficients of surface equation
surface MakeTargetSurface(coordinates norm, coordinates point) {
	double A, B, C, D;
	surface res;

	A = norm.x;
	B = norm.y;
	C = norm.z;
	D = -(norm.x * point.x) - (norm.y * point.y) - (norm.z * point.z);

	res.A = A;
	res.B = B;
	res.C = C;
	res.D = D;

	return res;
}

bool CrossingNumberAlgo(std::vector <coordinates> polygon_vertices, coordinates point) {
	bool res;

	res = true;

	return res;
}

#endif