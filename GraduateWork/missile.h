#pragma once


#ifndef MISSILE_H
#define MISSILE_H

#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <numbers>
#include "file_structs.h"
#include "functions.h"


struct missile_data {
	coordinates coord_n;
	velocity v_proj_n;

	double r;

	double yaw_angle;
	double pitch_angle;

	missile_data(double r = 0.0, double yaw_angle = 0.0, double pitch_angle = 0.0)
		: r(r), yaw_angle(yaw_angle), pitch_angle(pitch_angle)
	{}
};

struct fragment {
	coordinates coord;
	velocity velo;

	double mass;

	bool hitZX;
	bool hitXY;
	bool calculated;

	fragment(double mass = 0.0, bool hitZX = false, bool hitXY = false, bool calculated = false)
		: mass(mass), hitZX(hitZX), hitXY(hitXY), calculated(calculated)
	{}
};

velocity MakeFragmentVelocity(coordinates T, double VeloValue) {
	velocity res;
	double length;
	double multiplier;

	length = std::sqrt(std::pow(T.x, 2) + std::pow(T.y, 2) + std::pow(T.z, 2));
	multiplier = VeloValue / length;

	res = T * multiplier;

	return res;
}

std::vector <fragment> MakeFragments(missile_data M, target_data T, double InitialSpeed, int N) {
	coordinates coord;
	velocity velo, additional, target;
	double phi;
	std::vector <fragment> res;
	fragment frag;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_real_distribution<double> distibX(-0.35, 0.35);
	std::uniform_real_distribution<double> distibPhi(0.0, 1.0);

	additional = M.v_proj_n;
	
	target.x = T.v_obj;
	target.y = 0.0;
	target.z = 0.0;

	target = MakeRotationVelo(target, T.path_obj, T.pitch_obj);

	additional += target;


	for (int i = 0; i < N; ++i) {
		frag.mass = 0.1;

		coord.x = distibX(generator);
		phi = 2 * std::numbers::pi_v<double> *distibPhi(generator);
		coord.y = M.r * std::sin(phi);
		coord.z = M.r * std::cos(phi);

		coord = MakeRotation(coord, M.yaw_angle, M.pitch_angle);
		velo = MakeFragmentVelocity(coord, InitialSpeed);
		velo += additional;

		frag.coord = coord;
		frag.velo = velo;

		if (AngleBetweenVectors(frag.velo, T.basis_z) < 0.0)
			frag.hitXY = true;

		if (AngleBetweenVectors(frag.velo, T.basis_y) < 0.0)
			frag.hitZX = true;

		if (frag.hitXY || frag.hitZX)
			res.push_back(frag);
	}

	return res;
}

coordinates PointOfImpact(fragment F, surface T) {
	double t;
	coordinates intersection;

	t = -(T.D + T.A * F.coord.x + T.B * F.coord.y + T.C * F.coord.z) / 
		(T.A * F.velo.x + T.B * F.velo.y + T.C * F.velo.z);

	intersection.x = F.coord.x + t * F.velo.x;
	intersection.y = F.coord.y + t * F.velo.y;
	intersection.z = F.coord.z + t * F.velo.z;

	return intersection;
}

bool IsInRectangle(std::vector <coordinates> polygon_vertices, coordinates point) {
	bool res;
	double d1, d2, d3, d4;
	
	d1 = (polygon_vertices[1].x - polygon_vertices[0].x) * (point.z - polygon_vertices[0].z) - (polygon_vertices[1].z - polygon_vertices[0].z) * (point.x - polygon_vertices[0].x);
	d2 = (polygon_vertices[2].x - polygon_vertices[1].x) * (point.z - polygon_vertices[1].z) - (polygon_vertices[2].z - polygon_vertices[1].z) * (point.x - polygon_vertices[1].x);
	d3 = (polygon_vertices[3].x - polygon_vertices[2].x) * (point.z - polygon_vertices[2].z) - (polygon_vertices[3].z - polygon_vertices[2].z) * (point.x - polygon_vertices[2].x);
	d4 = (polygon_vertices[0].x - polygon_vertices[3].x) * (point.z - polygon_vertices[3].z) - (polygon_vertices[0].z - polygon_vertices[3].z) * (point.x - polygon_vertices[3].x);

	if ((d1 < 0 && d2 < 0 && d3 < 0 && d4 < 0) ||
		(d1 > 0 && d2 > 0 && d3 > 0 && d4 > 0))
		res = true;
	else
		res = false;

	return res;
}

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

bool HitTargetZX(target_data T, coordinates point) {
	bool res;
	std::vector <coordinates> points;
	coordinates base_x, base_z, temp;

	base_x.x = 1.0;
	base_x.y = 0.0;
	base_x.z = 0.0;

	base_z.x = 0.0;
	base_z.y = 0.0;
	base_z.z = 1.0;



	res = HitTargetBodyZX(T, point, base_x, base_z);

	if (!res) 
		res = HitTargetWingsZX(T, point, base_x, base_z);

	if (!res)
		res = HitTargetEmpennageZX(T, point, base_x, base_z);

	return res;
}

bool HitTargetXY(target_data T, coordinates point) {
	bool res;
	std::vector <coordinates> points;
	coordinates base_x, base_y, temp;

	base_x.x = 1.0;
	base_x.y = 0.0;
	base_x.z = 0.0;

	base_y.x = 0.0;
	base_y.y = 1.0;
	base_y.z = 0.0;

	res = HitTargetBodyXY(T, point, base_x, base_y);
	return res;
}

#endif