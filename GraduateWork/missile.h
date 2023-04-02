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

	fragment(double mass = 0.0)
		: mass(mass)
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
	std::uniform_real_distribution<double> distibY(-0.35, 0.35);
	std::uniform_real_distribution<double> distibPhi(0.0, 1.0);

	additional = M.v_proj_n;
	
	target.x = T.v_obj;
	target.y = 0.0;
	target.z = 0.0;

	target = MakeRotationVelo(target, T.path_obj, T.pitch_obj);

	additional += target;


	for (int i = 0; i < N; ++i) {
		frag.mass = 0.1;

		coord.y = distibY(generator);
		phi = 2 * std::numbers::pi_v<double> *distibPhi(generator);
		coord.x = M.r * std::sin(phi);
		coord.z = M.r * std::cos(phi);

		coord = MakeRotation(coord, M.yaw_angle, M.pitch_angle);
		velo = MakeFragmentVelocity(coord, InitialSpeed);
		velo += additional;

		frag.coord = coord;
		frag.velo = velo;

		if (AngleBetweenVectors(frag.velo, T.basis_y) < 0.0)
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

#endif