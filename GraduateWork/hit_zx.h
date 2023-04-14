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

bool HitTargetBodyZX(target_data T, coordinates point, coordinates base_x, coordinates base_z) {
	bool res;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = 0.0 + base_z.x * 5.5 + base_x.x * 5.5;
	temp.z = 0.0 + base_z.z * 0.49 + base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 + base_z.x * 5.5 + base_x.x * 5.5;
	temp.z = 0.0 - base_z.z * 0.49 - base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_z.x * 5.5 - base_x.x * 5.5;
	temp.z = 0.0 - base_z.z * 0.49 - base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	temp.x = 0.0 - base_z.x * 5.5 - base_x.x * 5.5;
	temp.z = 0.0 + base_z.z * 0.49 + base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp);

	res = CrossingNumberAlgo(polygon_vertices, point);

	return res;
}

bool HitTargetWingsZX(target_data T, coordinates point, coordinates base_x, coordinates base_z) {
	bool res;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = 0.0 + base_z.x * 0.825 + base_x.x * 0.825;
	temp.z = 0.0 + base_z.z * 0.49 + base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //1

	temp.x = 0.0 + base_z.x * 0.825 + base_x.x * 0.825;
	temp.z = 0.0 - base_z.z * 0.49 - base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //2

	temp.x = 0.0 + base_z.x * 0.365 + base_x.x * 0.365;
	temp.z = 0.0 - base_z.z * 10.0 - base_x.z * 10.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //3

	temp.x = 0.0 - base_z.x * 0.365 - base_x.x * 0.365;
	temp.z = 0.0 - base_z.z * 10.0 - base_x.z * 10.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //4

	temp.x = 0.0 - base_z.x * 0.825 - base_x.x * 0.825;
	temp.z = 0.0 - base_z.z * 0.49 - base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //5

	temp.x = 0.0 - base_z.x * 0.825 - base_x.x * 0.825;
	temp.z = 0.0 + base_z.z * 0.49 + base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //6

	temp.x = 0.0 - base_z.x * 0.365 - base_x.x * 0.365;
	temp.z = 0.0 + base_z.z * 10.0 + base_x.z * 10.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //7

	temp.x = 0.0 + base_z.x * 0.365 + base_x.x * 0.365;
	temp.z = 0.0 + base_z.z * 10.0 + base_x.z * 10.0;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //8

	res = CrossingNumberAlgo(polygon_vertices, point);

	return res;
}

bool HitTargetEmpennageZX(target_data T, coordinates point, coordinates base_x, coordinates base_z) {
	bool res;
	std::vector <coordinates> polygon_vertices;
	coordinates temp;

	temp.x = 0.0 - base_z.x * 3.0 - base_x.x * 3.0;
	temp.z = 0.0 + base_z.z * 0.49 + base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //1

	temp.x = 0.0 - base_z.x * 3.0 - base_x.x * 3.0;
	temp.z = 0.0 - base_z.z * 0.49 - base_x.z * 0.49;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //2

	temp.x = 0.0 - base_z.x * 3.6 - base_x.x * 3.6;
	temp.z = 0.0 - base_z.z * 3.4 - base_x.z * 3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //3

	temp.x = 0.0 - base_z.x * 4.2 - base_x.x * 4.2;
	temp.z = 0.0 - base_z.z * 3.4 - base_x.z * 3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //4

	temp.x = 0.0 - base_z.x * 4.2 - base_x.x * 4.2;
	temp.z = 0.0 + base_z.z * 3.4 + base_x.z * 3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //5

	temp.x = 0.0 - base_z.x * 3.6 - base_x.x * 3.6;
	temp.z = 0.0 + base_z.z * 3.4 + base_x.z * 3.4;
	temp = MakeRotation(temp, T.path_obj, 0.0);
	temp.x += T.coord_n_obj.x;
	temp.z += T.coord_n_obj.z;
	polygon_vertices.push_back(temp); //6

	res = CrossingNumberAlgo(polygon_vertices, point);
	return res;
}

#endif