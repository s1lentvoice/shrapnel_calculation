#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "file_structs.h"
#include "data_making.h"
#include "missile.h"
#include "target.h"

const double EPS = 1e-9;

coordinates MakeRotation(auto T, double phi, double theta) {
	coordinates res, res_temp;

	phi = phi * std::numbers::pi_v<double> / 180.0;
	theta = theta * std::numbers::pi_v<double> / 180.0;

	res_temp.x = std::cos(theta) * T.x - std::sin(theta) * T.y;
	res_temp.y = std::sin(theta) * T.x + std::cos(theta) * T.y;
	res_temp.z = T.z;

	res.z = std::cos(phi) * res_temp.z + std::sin(phi) * res_temp.x;
	res.x = -(std::sin(phi)) * res_temp.z + std::cos(phi) * res_temp.x;
	res.y = res_temp.y;

	return res;
}

velocity MakeRotationVelo(auto T, double phi, double theta) {
	velocity res, res_temp;

	phi = phi * std::numbers::pi_v<double> / 180.0;
	theta = theta * std::numbers::pi_v<double> / 180.0;

	res_temp.x = std::cos(theta) * T.x - std::sin(theta) * T.y;
	res_temp.y = std::sin(theta) * T.x + std::cos(theta) * T.y;
	res_temp.z = T.z;

	res.z = std::cos(phi) * res_temp.z + std::sin(phi) * res_temp.x;
	res.x = -(std::sin(phi)) * res_temp.z + std::cos(phi) * res_temp.x;
	res.y = res_temp.y;


	return res;
}

//returns vector length
double VectorMod(auto T) {
	return std::sqrt(std::pow(T.x, 2) + std::pow(T.y, 2) + std::pow(T.z, 2));
}

double VectorModZX(auto T) {
	return std::sqrt(std::pow(T.x, 2) + std::pow(T.z, 2));
}

double VectorModXY(auto T) {
	return std::sqrt(std::pow(T.x, 2) + std::pow(T.y, 2));
}

//returns cos() of angle
double AngleBetweenVectors(auto T1, auto T2) {
	double num = T1.x * T2.x + T1.y * T2.y + T1.z * T2.z;
	double denom = VectorMod(T1) * VectorMod(T2);
	return num / denom;
}

double AngleBetweenVectorsZX(auto T1, auto T2) {
	double num = T1.x * T2.x + T1.z * T2.z;
	double denom = VectorModZX(T1) * VectorModZX(T2);
	return num / denom;
}

double AngleBetweenVectorsXY(auto T1, auto T2) {
	double num = T1.x * T2.x + T1.y * T2.y;
	double denom = VectorModXY(T1) * VectorModXY(T2);
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

line MakeLine(coordinates point1, coordinates point2) {
	line res;
	
	res.A = point1.x - point2.x;
	res.B = point2.z - point1.z;
	res.C = point1.z * point2.x - point2.z * point1.x;

	return res;
}

line MakeLineXY(coordinates point1, coordinates point2) {
	line res;

	res.A = point1.y - point2.y;
	res.B = point2.x - point1.x;
	res.C = point1.x * point2.y - point2.x * point1.y;

	return res;
}

template <typename T>
inline void swap(T& arg1, T& arg2)
{
	T temp = arg1;
	arg1 = arg2;
	arg2 = temp;
};

double det(double a, double b, double c, double d) {
	return a * d - b * c;
}

bool PointIsGood(coordinates border1, coordinates border2, coordinates point) {
	coordinates b1 = border1;
	coordinates b2 = border2;
	bool res;

	if (b1.z > b2.z)
		swap(b1, b2);

	if (std::abs(b1.z - b2.z) < EPS) {
		if (b1.x > b2.x)
			swap(b1, b2);
		if (b1.x < point.x && point.x < b2.x)
			res = true;
		else
			res = false;
	}
	else {
		if (std::abs(b1.x - b2.x) < EPS) {
			if (b1.z < point.z && point.z < b2.z)
				res = true;
			else
				res = false;
		}
		else {
			if (b1.z < point.z && point.z < b2.z && std::min(b1.x, b2.x) < point.x
				&& point.x < std::max(b1.x, b2.x))
				res = true;
			else
				res = false;
		}
	}
	return res;
}

bool DirectionIsGood(coordinates start, coordinates direction_vector, coordinates point) {
	coordinates vector1, vector2;
	double cos_alpha;

	vector1.x = direction_vector.x - start.x;
	vector1.z = direction_vector.z - start.z;

	vector2.x = point.x - start.x;
	vector2.z = point.z - start.z;

	cos_alpha = AngleBetweenVectorsZX(vector1, vector2);
	
	if (cos_alpha > 0.0)
		return true;
	else
		return false;
}

bool PointIsGoodXY(coordinates border1, coordinates border2, coordinates point) {
	coordinates b1 = border1;
	coordinates b2 = border2;
	bool res;

	if (b1.x > b2.x)
		swap(b1, b2);

	if (std::abs(b1.x - b2.x) < EPS) {
		if (b1.y > b2.y)
			swap(b1, b2);
		if (b1.y < point.y && point.y < b2.y)
			res = true;
		else
			res = false;
	}
	else {
		if (std::abs(b1.y - b2.y) < EPS) {
			if (b1.x < point.x && point.x < b2.x)
				res = true;
			else
				res = false;
		}
		else {
			if (b1.x < point.x && point.x < b2.x && std::min(b1.y, b2.y) < point.y
				&& point.y < std::max(b1.y, b2.y))
				res = true;
			else
				res = false;
		}
	}
	return res;
}

bool DirectionIsGoodXY(coordinates start, coordinates direction_vector, coordinates point) {
	coordinates vector1, vector2;
	double cos_alpha;

	vector1.y = direction_vector.y - start.y;
	vector1.x = direction_vector.x - start.x;

	vector2.y = point.y - start.y;
	vector2.x = point.x - start.x;

	cos_alpha = AngleBetweenVectorsXY(vector1, vector2);

	if (cos_alpha > 0.0)
		return true;
	else
		return false;
}

bool CrossingNumberAlgo(std::vector <coordinates> polygon_vertices, coordinates point) {
	bool res;
	int crossings = 0;
	double zn = 0.0;
	line L1, L2;
	coordinates direction, intersection_point;

	direction = point;
	direction.x += 1.0;

	L1 = MakeLine(point, direction);

	for (unsigned int i = 0; i < polygon_vertices.size(); ++i) {
		L2 = MakeLine(polygon_vertices[i], polygon_vertices[(i + 1) % polygon_vertices.size()]);

		zn = det(L1.A, L1.B, L2.A, L2.B);
		if (std::abs(zn) > EPS) {
			intersection_point.z = -det(L1.C, L1.B, L2.C, L2.B) / zn;
			intersection_point.x = -det(L1.A, L1.C, L2.A, L2.C) / zn;
			if (PointIsGood(polygon_vertices[i], polygon_vertices[(i + 1) % polygon_vertices.size()], intersection_point)
				&& DirectionIsGood(point, direction, intersection_point))
				crossings++;
		}
	}

	if (crossings % 2 == 1)
		return true;
	else
		return false;
}

bool CrossingNumberAlgoXY(std::vector <coordinates> polygon_vertices, coordinates point) {
	bool res;
	int crossings = 0;
	double zn = 0.0;
	line L1, L2;
	coordinates direction, intersection_point;

	direction = point;
	direction.x += 1.0;

	L1 = MakeLineXY(point, direction);

	for (unsigned int i = 0; i < polygon_vertices.size(); ++i) {
		L2 = MakeLineXY(polygon_vertices[i], polygon_vertices[(i + 1) % polygon_vertices.size()]);

		zn = det(L1.A, L1.B, L2.A, L2.B);
		if (std::abs(zn) > EPS) {
			intersection_point.x = -det(L1.C, L1.B, L2.C, L2.B) / zn;
			intersection_point.y = -det(L1.A, L1.C, L2.A, L2.C) / zn;
			if (PointIsGoodXY(polygon_vertices[i], polygon_vertices[(i + 1) % polygon_vertices.size()], intersection_point)
				&& DirectionIsGoodXY(point, direction, intersection_point))
				crossings++;
		}
	}

	if (crossings % 2 == 1)
		return true;
	else
		return false;
}

coordinates MoveTarget(target_data T, velocity velo, double time) {
	coordinates res;

	res.x = T.coord_n_obj.x + time * velo.x;
	res.y = T.coord_n_obj.y + time * velo.y;
	res.z = T.coord_n_obj.z + time * velo.z;

	return res;
}

#endif