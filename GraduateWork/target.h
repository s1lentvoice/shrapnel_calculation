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
};


//to_do_next
#endif