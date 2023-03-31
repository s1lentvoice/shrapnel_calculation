#pragma once


#ifndef MISSILE_H
#define MISSILE_H

#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <numbers>
#include "file_structs.h"



struct missile_data {
	coordinates coord_n;
	velocity v_proj_n;

	double r;

	double yaw_angle;
	double pitch_angle;
};

struct fragment {
	coordinates coord;
	velocity velo;

	double mass;
};

coordinates MakeRotation(coordinates T, double phi, double theta) {
	coordinates res;

	phi = phi * std::numbers::pi_v<double> / 180.0;
	theta = theta * std::numbers::pi_v<double> / 180.0;

	res.z = std::cos(phi) * T.z - std::sin(phi) * T.x;
	res.x = std::sin(phi) * T.z + std::cos(phi) * T.x;

	res.x = std::cos(theta) * T.x - std::sin(theta) * T.y;
	res.y = std::sin(theta) * T.x + std::cos(theta) * T.y;

	return res;
}

std::vector <fragment> MakeFragments(missile_data T, int N) {
	coordinates coord;
	velocity velo;
	double phi;
	std::vector <fragment> res;
	fragment frag;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_real_distribution<double> distibY(-0.35, 0.35);
	std::uniform_real_distribution<double> distibPhi(0.0, 1.0);

	for (int i = 0; i < N; ++i) {
		frag.mass = 0.1;

		coord.y = distibY(generator);
		phi = 2 * std::numbers::pi_v<double> *distibPhi(generator);
		coord.x = T.r * std::sin(phi);
		coord.z = T.r * std::cos(phi);

		coord = MakeRotation(coord, T.yaw_angle, T.pitch_angle);

	}
	//to_do_next_first
	return res;
}


#endif