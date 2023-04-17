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

bool HitTargetBodyXY(target_data T, coordinates point) {
	bool res;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = 5.5;
	temp.y = 0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 5.5;
	temp.y = -0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -5.5;
	temp.y = -0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = -5.5;
	temp.y = 0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	res = CrossingNumberAlgoXY(polygon_vertices, point);

	return res;
}

bool HitTargetEmpennageXYupper(target_data T, coordinates point) {
	bool res;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

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

	res = CrossingNumberAlgoXY(polygon_vertices, point);

	return res;
}

bool HitTargetEmpennageXYlower(target_data T, coordinates point) {
	bool res;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = -3.0;
	temp.y = -0.625;
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
	temp.y = -0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	res = CrossingNumberAlgoXY(polygon_vertices, point);

	return res;
}

#endif