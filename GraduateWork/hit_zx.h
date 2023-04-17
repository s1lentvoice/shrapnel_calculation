#pragma once

#ifndef HITZX_H
#define HITZX_H

#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <numbers>
#include "file_structs.h"
#include "functions.h"

double ZXDistance(auto T1, auto T2) {
	return std::sqrt(std::pow(T1.x - T2.x, 2) + std::pow(T1.z - T2.z, 2));
}

/*
res interpretation:
0	->	hit none
1	->	hit body
2	->	hit wings
3	->	hit empennage
4	->	hit cam
5	->	hit armament
6	->	hit navigation
7	->	hit flaps
8	->	hit elevator
9	->	hit engine
10	->	hit propeller
11	->	hit fuel tank
*/

unsigned HitTargetNaviCamZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = 5.5;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 5.5;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 3.0;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 3.0;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit) {
		coordinates cam_center;
		cam_center.x = 4.5;
		cam_center.z = 0.0;
		cam_center = MakeRotation(cam_center, T.path_obj, 0.0);
		cam_center.x += T.coord_n_obj.x;
		cam_center.z += T.coord_n_obj.z;
		if (ZXDistance(point, cam_center) < 0.2)
			res = 4; //hit cam
		else
			res = 6; //hit navigation
	}
	return res;
}

unsigned HitTargetFuelTankZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -1.0;
	temp.z = -0.2;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -1.0;
	temp.z = 0.2;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -2.5;
	temp.z = 0.2;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -2.5;
	temp.z = -0.2;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 11; //hit fuel tank

	return res;
}

unsigned HitTargetLowerEmpZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -3.0;
	temp.z = -0.05;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -3.0;
	temp.z = 0.05;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.2;
	temp.z = 0.05;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.2;
	temp.z = -0.05;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 3; //hit empennage

	return res;
}

unsigned HitTargetPropZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -4.98;
	temp.z = -1.402;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -5.02;
	temp.z = -1.402;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -5.02;
	temp.z = 1.402;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.98;
	temp.z = 1.402;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 10; //hit propeller

	return res;
}

unsigned HitTargetEngineEmpPropZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -3.0;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -3.0;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.2;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -5.4;
	temp.z = 0.2;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -5.5;
	temp.z = 0.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -5.4;
	temp.z = -0.2;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.2;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit) {
		res = HitTargetLowerEmpZX(T, point);

		if (!res)
			res = HitTargetPropZX(T, point);

		if (!res)
			res = 9; // hit propeller
	}
	return res;
}

unsigned HitTargetBodyZX(target_data T, coordinates point) {
	unsigned res = 0;
	bool is_hit;
	std::vector <coordinates> polygon_vertices;
	coordinates temp, a;

	a.x = 5.01;

	a = MakeRotation(a, T.path_obj, 0.0);
	a.x += T.coord_n_obj.x;
	a.z += T.coord_n_obj.z;

	temp.x = 5.5;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 5.5;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.2;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -5.4;
	temp.z = -0.2;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -5.5;
	temp.z = 0.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -5.4;
	temp.z = 0.2;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.2;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);
	
	if (is_hit) {
		res = HitTargetNaviCamZX(T, point);
		
		if (!res) 
			res = HitTargetFuelTankZX(T, point);

		if (!res)
			res = HitTargetEngineEmpPropZX(T, point);

		if (!res)
			res = 1; // hit body
	}

	return res;
}

unsigned HitTargetLFlapZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -0.413;
	temp.z = -9.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);
	

	temp.x = -0.113;
	temp.z = -9.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);
	
	temp.x = -0.404;
	temp.z = -3.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);


	temp.x = -0.704;
	temp.z = -3.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);


	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 7; //hit flap

	return res;
}

unsigned HitTargetRFlapZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -0.413;
	temp.z = 9.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -0.113;
	temp.z = 9.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -0.404;
	temp.z = 3.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -0.704;
	temp.z = 3.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 7; //hit flap

	return res;
}

unsigned HitTargetLargeRocketLeftZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = 1.0;
	temp.z = -1.7;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);
	

	temp.x = 1.3;
	temp.z = -1.5;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 1.0;
	temp.z = -1.3;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -1.0;
	temp.z = -1.3;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -1.0;
	temp.z = -1.7;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 5; //hit armament

	return res;
}

unsigned HitTargetLargeRocketRightZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = 1.0;
	temp.z = 1.7;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);
	
	temp.x = 1.3;
	temp.z = 1.5;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 1.0;
	temp.z = 1.3;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -1.0;
	temp.z = 1.3;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -1.0;
	temp.z = 1.7;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 5; //hit armament

	return res;
}

unsigned HitTargetSmallRocketLeftZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = 0.5;
	temp.z = -2.3;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);
	
	temp.x = 0.7;
	temp.z = -2.45;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 0.5;
	temp.z = -2.6;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -0.7;
	temp.z = -2.6;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -0.7;
	temp.z = -2.3;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 5; //hit armament

	return res;
}

unsigned HitTargetSmallRocketRightZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = 0.5;
	temp.z = 2.3;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);
	
	temp.x = 0.7;
	temp.z = 2.45;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 0.5;
	temp.z = 2.6;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -0.7;
	temp.z = 2.6;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -0.7;
	temp.z = 2.3;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 5; //hit armament

	return res;
}

unsigned HitTargetWingsZX(target_data T, coordinates point) {
	unsigned res = 0;
	bool is_hit;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = 0.825;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //1

	temp.x = 0.825;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //2

	temp.x = 0.365;
	temp.z = -10.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //3

	temp.x = -0.365;
	temp.z = -10.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //4

	temp.x = -0.825;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //5

	temp.x = -0.825;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //6

	temp.x = -0.365;
	temp.z = 10.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //7

	temp.x = 0.365;
	temp.z = 10.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //8

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit) {
		res = HitTargetLFlapZX(T, point);

		if (!res)
			res = HitTargetRFlapZX(T, point);

		if (!res)
			res = HitTargetLargeRocketLeftZX(T, point);

		if (!res)
			res = HitTargetLargeRocketRightZX(T, point);

		if (!res)
			res = HitTargetSmallRocketLeftZX(T, point);

		if (!res)
			res = HitTargetSmallRocketRightZX(T, point);

		if (!res)
			res = 2; //hit wings
	}

	return res;
}

unsigned HitTargetLElevZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -4.2;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);
	
	temp.x = -4.0;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.0;
	temp.z = -3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.2;
	temp.z = -3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 8; //hit elevator

	return res;
}

unsigned HitTargetRElevZX(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -4.2;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);
	
	temp.x = -4.0;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.0;
	temp.z = 3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = -4.2;
	temp.z = 3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit)
		res = 8; //hit elevator

	return res;
}

unsigned HitTargetEmpennageZX(target_data T, coordinates point) {
	unsigned res = 0;
	bool is_hit;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = -3.0;
	temp.z = 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //1
	
	temp.x = -3.0;
	temp.z = -0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //2

	temp.x = -3.6;
	temp.z = -3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //3

	temp.x = -4.2;
	temp.z = -3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //4

	temp.x = -4.2;
	temp.z = 3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //5

	temp.x = -3.6;
	temp.z = 3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //6

	is_hit = CrossingNumberAlgo(polygon_vertices, point);

	if (is_hit) {
		res = HitTargetLElevZX(T, point);

		if (!res)
			res = HitTargetRElevZX(T, point);

		if (!res)
			res = 3; //hit empennage
	}

	return res;
}

#endif