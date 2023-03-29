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
	coordinates mis_coord_n;
	velocity mis_v_proj_n;

	double r = 0.5;

	double yaw_angle;
	double pitch_angle;
};

struct fragment {
	coordinates frag_coord;
	velocity frag_velo;

	double mass = 0.1;
};


std::vector <fragment> MakeFragments(missile_data T, int N) {
	double x;
	double y;
	double z;
	double phi;
	std::vector <fragment> res;

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 generator(seed);
	std::uniform_real_distribution<double> distibY(-0.35, 0.35);
	std::uniform_real_distribution<double> distibPhi(0.0, 1.0);

	for (int i = 0; i < N; ++i) {
		y = distibY(generator);
		phi = 2 * std::numbers::pi_v<double> *distibPhi(generator);
		x = T.r * std::sin(phi);
		z = T.r * std::cos(phi);
	}
	//to_do_next_first
	return res;
}


#endif