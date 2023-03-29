#pragma once
#ifndef MISSILE_H
#define MISSILE_H

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
};

#endif