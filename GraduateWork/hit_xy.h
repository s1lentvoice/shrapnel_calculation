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

bool HitTargetBodyXY(target_data T, coordinates point, coordinates base_x, coordinates base_y) {
	bool res;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = 0.0 + base_x.x * 5.5 + base_y.x * 5.5;
	temp.y = 0.0 + base_x.y * 0.625 + base_y.y * 0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 + base_x.x * 5.5 + base_y.x * 5.5;
	temp.y = 0.0 - base_x.y * 0.625 - base_y.y * 0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_x.x * 5.5 - base_y.x * 5.5;
	temp.y = 0.0 - base_x.y * 0.625 - base_y.y * 0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_x.x * 5.5 - base_y.x * 5.5;
	temp.y = 0.0 + base_x.y * 0.625 + base_y.y * 0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	res = CrossingNumberAlgoXY(polygon_vertices, point);

	return res;
}

bool HitTargetEmpennageXYupper(target_data T, coordinates point, coordinates base_x, coordinates base_y) {
	bool res;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = 0.0 - base_y.x * 3.0 - base_x.x * 3.0;
	temp.y = 0.0 + base_x.y * 0.0 + base_y.y * 0.0;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_x.x * 3.6 - base_y.x * 3.6;
	temp.y = 0.0 + base_x.y * 2.01 + base_y.y * 2.01;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_x.x * 4.1 - base_y.x * 4.1;
	temp.y = 0.0 + base_x.y * 2.01 + base_y.y * 2.01;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_x.x * 4.1 - base_y.x * 4.1;
	temp.y = 0.0 + base_x.y * 0.0 + base_y.y * 0.0;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	res = CrossingNumberAlgoXY(polygon_vertices, point);

	return res;
}

bool HitTargetEmpennageXYlower(target_data T, coordinates point, coordinates base_x, coordinates base_y) {
	bool res;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = 0.0 - base_y.x * 3.0 - base_x.x * 3.0;
	temp.y = 0.0 - base_x.y * 0.625 - base_y.y * 0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_x.x * 3.6 - base_y.x * 3.6;
	temp.y = 0.0 - base_x.y * 1.6 - base_y.y * 1.6;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_x.x * 4.1 - base_y.x * 4.1;
	temp.y = 0.0 - base_x.y * 1.6 - base_y.y * 1.6;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_x.x * 4.1 - base_y.x * 4.1;
	temp.y = 0.0 - base_x.y * 0.625 - base_y.y * 0.625;
	temp = MakeRotation(temp, 0.0, T.pitch_obj);
	temp.x += T.coord_n_obj.x;
	temp.y += T.coord_n_obj.y;
	polygon_vertices.push_back(temp);

	res = CrossingNumberAlgoXY(polygon_vertices, point);

	return res;
}

#endif