#pragma once
#ifndef DATAMAKING_H
#define DATAMAKING_H

#include "file_structs.h"
#include "missile.h"
#include "target.h"
#include <fstream>

raw_data MakeRawData(std::string filename) {
	std::ifstream in(filename);
	raw_data temp;
	
	//1
	in >> temp.n >> temp.pr_c >> temp.epr >> temp.pr_r >> temp.kim >> temp.dov >> temp.rbv;
	//2
	in >> temp.time_to_mp >> temp.rel_v >> temp.beta_ast >> temp.time_start_homing;
	//3
	in >> temp.mis_coord_n.x >> temp.mis_coord_n.y >> temp.mis_coord_n.z >> temp.mis_v_proj_n.x >> temp.mis_v_proj_n.y >> temp.mis_v_proj_n.z;
	//4
	in >> temp.yaw_angle >> temp.pitch_angle >> temp.bank_angle >> temp.angle_of_attack >> temp.flow_angle;
	//5
	in >> temp.v_obj >> temp.path_obj >> temp.pitch_obj >> temp.coord_n_obj.x >> temp.coord_n_obj.y >> temp.coord_n_obj.z;
	//6
	in >> temp.proj_mp_miss.x >> temp.proj_mp_miss.y >> temp.proj_mp_miss.z >> temp.rel_v_n >> temp.tau_kin;
	//7
	in >> temp.nc_y >> temp.nc_z >> temp.t_dov >> temp.t_bv >> temp.t_sbv;
	//8
	in >> temp.proj_nsm_miss.x >> temp.proj_nsm_miss.y >> temp.proj_nsm_miss.z >> temp.delta_V01 >> temp.delta_V02 >> temp.beta_y;
	//9
	in >> temp.from_n_to_apa.c11 >> temp.from_n_to_apa.c12 >> temp.from_n_to_apa.c13 >> temp.proj_dov_miss.x >> temp.proj_dov_miss.y >> temp.proj_dov_miss.z;
	//10
	in >> temp.bank >> temp.pitch >> temp.ant_course >> temp.delta_gamma.inf >> temp.delta_gamma.exec >> temp.delta_gamma.sum;
	//11
	in >> temp.from_n_to_apa.c21 >> temp.from_n_to_apa.c22 >> temp.from_n_to_apa.c23 >> temp.from_n_to_apa.c31 >> temp.from_n_to_apa.c32 >> temp.from_n_to_apa.c33;
	
	return temp;
}

missile_data MakeDataMissile(raw_data T) {
	missile_data res;

	res.mis_coord_n.x = T.mis_coord_n.x;
	res.mis_coord_n.y = T.mis_coord_n.y;
	res.mis_coord_n.z = T.mis_coord_n.z;

	res.mis_v_proj_n.x = T.mis_v_proj_n.x;
	res.mis_v_proj_n.y = T.mis_v_proj_n.y;
	res.mis_v_proj_n.z = T.mis_v_proj_n.z;

	res.yaw_angle = T.yaw_angle;
	res.pitch_angle = T.pitch_angle;

	return res;
}

target_data MakeDataTarget(raw_data T) {
	target_data res;

	res.coord_n_obj.x = T.coord_n_obj.x;
	res.coord_n_obj.y = T.coord_n_obj.y;
	res.coord_n_obj.z = T.coord_n_obj.z;

	res.path_obj = T.path_obj;
	res.pitch_obj = T.pitch_obj;

	return res;
}

#endif