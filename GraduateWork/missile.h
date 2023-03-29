#pragma once
#ifndef MISSILE_H
#define MISSILE_H

#include "file_structs.h"


struct missile_data {
	missile_n_sys_coordinates mis_coord_n;
	missile_v_proj_n_sys mis_v_proj_n;

	double r = 0.5;

	double yaw_angle;
	double pitch_angle;
};

#endif