#pragma once
#ifndef TARGET_H
#define TARGET_H

#include "file_structs.h"
#include "data_making.h"
#include "functions.h"
#include "missile.h"


struct target_data {
	coordinates coord_n_obj;
	coordinates basis_x, basis_y, basis_z;

	double v_obj;
	double path_obj;
	double pitch_obj;

	target_data(double v_obj = 0.0, double path_obj = 0.0, double pitch_obj = 0.0)
		: v_obj(v_obj), path_obj(path_obj), pitch_obj(pitch_obj)
	{}
};

#endif