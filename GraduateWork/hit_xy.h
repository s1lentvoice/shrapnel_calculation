#pragma once

#ifndef HITXY_H
#define HITXY_H

#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <numbers>
#include "file_structs.h"
#include "functions.h"


double XYDistance(auto T1, auto T2) {
	return std::sqrt(std::pow(T1.x - T2.x, 2) + std::pow(T1.y - T2.y, 2));
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

unsigned HitTargetElevUpperXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -4.1;
	temp.y = 2.01;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);
	
	temp.x = -4.1;
	temp.y = 0.0;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -3.9;
	temp.y = 0.0;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -3.9;
	temp.y = 2.01;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit)
		res = 8; //hit elevator

	return res;
}

unsigned HitTargetEmpennageXYupper(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -3.0;
	temp.y = 0.0;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);
	
	temp.x = -3.6;
	temp.y = 2.01;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -4.1;
	temp.y = 2.01;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -4.1;
	temp.y = 0.0;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit) {
		res = HitTargetElevUpperXY(T, point);

		if (!res)
			res = 3; //hit empennage
	}

	return res;
}

unsigned HitTargetElevLowerXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -4.1;
	temp.y = -0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -4.1;
	temp.y = -1.6;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -3.9;
	temp.y = -1.6;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -3.9;
	temp.y = -0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit)
		res = 8; //hit elevator

	return res;
}

unsigned HitTargetEmpennageXYlower(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -3.0;
	temp.y = -0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);
	
	temp.x = -3.6;
	temp.y = -1.6;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -4.1;
	temp.y = -1.6;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -4.1;
	temp.y = -0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);
	
	if (is_hit) {
		res = HitTargetElevLowerXY(T, point);

		if (!res)
			res = 3; //hit empennage
	}

	return res;
}

unsigned HitTargetPropXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -4.98;
	temp.y = -1.247;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);
	
	temp.x = -5.02;
	temp.y = -1.247;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -5.02;
	temp.y = 1.557;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -4.98;
	temp.y = 1.557;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit)
		res = 10; //hit propeller

	return res;
}

unsigned HitTargetEngineEmpPropXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -2.9;
	temp.y = -0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //1
	
	temp.x = -4.35;
	temp.y = -0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //2

	temp.x = -5.4;
	temp.y = 0.01;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //3

	temp.x = -5.5;
	temp.y = 0.155;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //4

	temp.x = -5.4;
	temp.y = 0.3;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //5

	temp.x = -4.35;
	temp.y = 0.8;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //6

	temp.x = -4.2;
	temp.y = 0.8;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //7

	temp.x = -4.1;
	temp.y = 0.9;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //8

	temp.x = -3.269;
	temp.y = 0.9;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //9

	temp.x = -2.4;
	temp.y = 0.8;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //10

	temp.x = -2.4;
	temp.y = 0.6;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //11

	temp.x = -2.5;
	temp.y = 0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //12

	temp.x = -2.9;
	temp.y = 0.0;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //13

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit) {
		res = HitTargetEmpennageXYupper(T, point);

		if (!res)
			res = HitTargetPropXY(T, point);

		if (!res)
			res = 9; //hit engine
	}

	return res;
}

unsigned HitTargetFuelTankXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -1.0;
	temp.y = -0.2;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);
	
	temp.x = -2.5;
	temp.y = -0.2;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -2.5;
	temp.y = 0.2;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -1.0;
	temp.y = 0.2;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit)
		res = 11; //hit fuel tank

	return res;
}

unsigned HitTargetNaviXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = 1.49;
	temp.y = 0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //1
	
	temp.x = 3.0;
	temp.y = 0.9;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //2

	temp.x = 4.0;
	temp.y = 0.9;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //3

	temp.x = 5.295;
	temp.y = -0.3;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //4

	temp.x = 2.0;
	temp.y = -0.3;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //5

	temp.x = 1.4;
	temp.y = 0.35;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //6

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit)
		res = 6; //hit navigation

	return res;
}

unsigned HitTargetRocketXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = -1.0;
	temp.y = -0.075;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);
	
	temp.x = 1.0;
	temp.y = -0.075;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 1.275;
	temp.y = -0.275;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 1.0;
	temp.y = -0.475;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -1.0;
	temp.y = -0.475;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit)
		res = 5; //hit armament

	return res;
}

unsigned HitTargetWingsXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = 0.825;
	temp.y = 0.075;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);
	
	temp.x = 0.825;
	temp.y = -0.075;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -0.825;
	temp.y = -0.075;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -0.825;
	temp.y = 0.075;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit)
		res = 2; //hit wings

	return res;
}

unsigned HitTargetBodyXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = 1.49;
	temp.y = 0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //1
	
	temp.x = 3.0;
	temp.y = 0.9;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //2

	temp.x = 4.0;
	temp.y = 0.9;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //3

	temp.x = 5.5;
	temp.y = -0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //4

	temp.x = 4.95;
	temp.y = -0.75;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //5

	temp.x = 4.09;
	temp.y = -0.75;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //6

	temp.x = 1.49;
	temp.y = -0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //7

	temp.x = -4.35;
	temp.y = -0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //8

	temp.x = -5.4;
	temp.y = 0.01;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //9

	temp.x = -5.5;
	temp.y = 0.155;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //10

	temp.x = -5.4;
	temp.y = 0.3;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //11

	temp.x = -4.35;
	temp.y = 0.8;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //12

	temp.x = -4.2;
	temp.y = 0.8;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //13

	temp.x = -4.1;
	temp.y = 0.9;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //14

	temp.x = -3.269;
	temp.y = 0.9;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //15

	temp.x = -2.4;
	temp.y = 0.8;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //16

	temp.x = -2.4;
	temp.y = 0.6;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //17

	temp.x = -2.5;
	temp.y = 0.49;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp); //18

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit) {
		res = HitTargetEngineEmpPropXY(T, point);

		if (!res)
			res = HitTargetFuelTankXY(T, point);

		if (!res)
			res = HitTargetNaviXY(T, point);

		if (!res)
			res = HitTargetRocketXY(T, point);

		if (!res)
			res = HitTargetWingsXY(T, point);

		if (!res)
			res = 1; //hit body
	}

	return res;
}

unsigned HitTargetCamXY(target_data T, coordinates point) {
	unsigned res = 0;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;
	bool is_hit;

	temp.x = 4.3;
	temp.y = -0.75;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 4.7;
	temp.y = -0.75;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 4.7;
	temp.y = -0.95;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 4.3;
	temp.y = -0.95;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	is_hit = CrossingNumberAlgoXY(polygon_vertices, point);

	if (is_hit) {
		coordinates cam_center;
		cam_center.x = 4.5;
		cam_center.y = -0.75;
		cam_center = MakeRotation(cam_center, 0.0, T.pitch_obj);
		cam_center.x += T.coord_n_obj.x;
		cam_center.y += T.coord_n_obj.y;
		
		if (XYDistance(point, cam_center) < 0.2)
			res = 4; //hit cam
		
	}
		

	return res;
}

#endif