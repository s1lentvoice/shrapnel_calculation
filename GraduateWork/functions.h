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

bool HitTarget(target_data T, coordinates point) {
	bool res;
	std::vector <coordinates> points;
	coordinates base_x, base_z, temp;

	base_x.x = 1.0;
	base_x.y = 0.0;
	base_x.z = 0.0;

	base_z.x = 0.0;
	base_z.y = 0.0;
	base_z.z = 1.0;

	base_x = MakeRotation(base_x, T.path_obj, 0.0);
	base_z = MakeRotation(base_z, T.path_obj, 0.0);

	temp.x = T.coord_n_obj.x + base_z.x * 5.4 + base_x.x * 5.4;
	temp.z = T.coord_n_obj.z + base_z.z * 0.49 + base_x.z * 0.49;

	points.push_back(temp);

	temp.x = T.coord_n_obj.x + base_z.x * 5.5 + base_x.x * 5.5;
	temp.z = T.coord_n_obj.z - base_z.z * 0.49 - base_x.z * 0.49;

	points.push_back(temp);

	temp.x = T.coord_n_obj.x - base_z.x * 5.5 - base_x.x * 5.5;
	temp.z = T.coord_n_obj.z - base_z.z * 0.49 - base_x.z * 0.49;

	points.push_back(temp);

	temp.x = T.coord_n_obj.x - base_z.x * 5.5 - base_x.x * 5.5;
	temp.z = T.coord_n_obj.z + base_z.z * 0.49 + base_x.z * 0.49;

	points.push_back(temp);

	double d1, d2, d3, d4;
	d1 = (points[1].x - points[0].x) * (point.z - points[0].z) - (points[1].z - points[0].z) * (point.x - points[0].x);
	d2 = (points[2].x - points[1].x) * (point.z - points[1].z) - (points[2].z - points[1].z) * (point.x - points[1].x);
	d3 = (points[3].x - points[2].x) * (point.z - points[2].z) - (points[3].z - points[2].z) * (point.x - points[2].x);
	d4 = (points[0].x - points[3].x) * (point.z - points[3].z) - (points[0].z - points[3].z) * (point.x - points[3].x);

	if ((d1 < 0 && d2 < 0 && d3 < 0 && d4 < 0) ||
		(d1 > 0 && d2 > 0 && d3 > 0 && d4 > 0))
		res = true;
	else
		res = false;

	if (!res) {
		points.clear();
		temp.x = T.coord_n_obj.x + base_z.x * 0.825 + base_x.x * 0.825;
		temp.z = T.coord_n_obj.z + base_z.z * 10.0 + base_x.z * 10.0;

		points.push_back(temp);

		temp.x = T.coord_n_obj.x + base_z.x * 0.825 + base_x.x * 0.825;
		temp.z = T.coord_n_obj.z - base_z.z * 10.0 - base_x.z * 10.0;

		points.push_back(temp);

		temp.x = T.coord_n_obj.x - base_z.x * 0.825 - base_x.x * 0.825;
		temp.z = T.coord_n_obj.z - base_z.z * 10.0 - base_x.z * 10.0;

		points.push_back(temp);

		temp.x = T.coord_n_obj.x - base_z.x * 0.825 - base_x.x * 0.825;
		temp.z = T.coord_n_obj.z + base_z.z * 10.0 + base_x.z * 10.0;

		points.push_back(temp);

		double d1, d2, d3, d4;
		d1 = (points[1].x - points[0].x) * (point.z - points[0].z) - (points[1].z - points[0].z) * (point.x - points[0].x);
		d2 = (points[2].x - points[1].x) * (point.z - points[1].z) - (points[2].z - points[1].z) * (point.x - points[1].x);
		d3 = (points[3].x - points[2].x) * (point.z - points[2].z) - (points[3].z - points[2].z) * (point.x - points[2].x);
		d4 = (points[0].x - points[3].x) * (point.z - points[3].z) - (points[0].z - points[3].z) * (point.x - points[3].x);

		if ((d1 < 0 && d2 < 0 && d3 < 0 && d4 < 0) ||
			(d1 > 0 && d2 > 0 && d3 > 0 && d4 > 0))
			res = true;
		else
			res = false;
	}
	
	return res;
}

#endif