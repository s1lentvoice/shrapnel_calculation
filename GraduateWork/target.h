#pragma once
#ifndef TARGET_H
#define TARGET_H

#include "file_structs.h"


struct target_data {
	coordinates coord_n_obj;

	double v_obj = 64.44;
	double path_obj;
	double pitch_obj;
};

#endif