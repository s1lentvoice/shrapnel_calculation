#pragma once
#ifndef FSTRUCTS_H
#define FSTRUCTS_H

#include <cmath>


struct coordinates {
	double x;
	double y;
	double z;

	coordinates(double x = 0.0, double y = 0.0, double z = 0.0)
		: x(x), y(y), z(z)
	{}

	coordinates& operator= (const auto& V) {
		x = V.x;
		y = V.y;
		z = V.z;

		return *this;
	}

	coordinates& operator+= (const auto& V) {
		x += V.x;
		y += V.y;
		z += V.z;

		return *this;
	}

	coordinates& operator-= (const auto& V) {
		x -= V.x;
		y -= V.y;
		z -= V.z;

		return *this;
	}
};

coordinates operator+ (coordinates T1, coordinates T2) {
	T1.x += T2.x;
	T1.y += T2.y;
	T1.z += T2.z;
	
	return T1;
}

coordinates operator* (coordinates T, double n) {
	T.x *= n;
	T.y *= n;
	T.z *= n;

	return T;
}


struct velocity {
	double x;
	double y;
	double z;

	velocity(double x = 0.0, double y = 0.0, double z = 0.0)
		: x(x), y(y), z(z)
	{}

	velocity& operator= (const auto& V) {
		x = V.x;
		y = V.y;
		z = V.z;

		return *this;
	}

	velocity& operator+= (const auto& V) {
		x += V.x;
		y += V.y;
		z += V.z;

		return *this;
	}

	velocity& operator-= (const auto& V) {
		x -= V.x;
		y -= V.y;
		z -= V.z;

		return *this;
	}
};

velocity operator+ (velocity T1, velocity T2) {
	T1.x += T2.x;
	T1.y += T2.y;
	T1.z += T2.z;

	return T1;
}

velocity operator * (velocity T, double n) {
	T.x *= n;
	T.y *= n;
	T.z *= n;

	return T;
}

struct surface {
	double A;
	double B;
	double C;
	double D;

	surface(double A = 0.0, double B = 0.0, double C = 0.0, double D = 0.0)
		: A(A), B(B), C(C), D(D)
	{}
};

struct line {
	double A;
	double B;
	double C;

	line(double A = 0.0, double B = 0.0, double C = 0.0)
		: A(A), B(B), C(C)
	{}
};

struct missile_n_sys_coordinates {
	double x;
	double y;
	double z;
};

struct missile_v_proj_n_sys {
	double x;
	double y;
	double z;
};

struct obj_n_sys_coordinates {
	double x;
	double y;
	double z;
};

struct missing_mp_time_proj_n_sys {
	double x;
	double y;
	double z;
};

struct missing_nsm_time_proj_n_sys {
	double x;
	double y;
	double z;
};

struct missing_dov_time_proj_n_sys {
	double x;
	double y;
	double z;
};

struct bank_angle_mistakes {
	double inf;
	double exec;
	double sum;
};

struct trans_matrix {
	double c11;
	double c12;
	double c13;

	double c21;
	double c22;
	double c23;

	double c31;
	double c32;
	double c33;
};

struct raw_data {
	//1
	int n;
	bool pr_c;
	double epr;
	int pr_r;
	bool kim;
	bool dov;
	bool rbv;

	//2
	double time_to_mp;
	double rel_v;
	double beta_ast;
	double time_start_homing;

	//3
	missile_n_sys_coordinates mis_coord_n;
	missile_v_proj_n_sys mis_v_proj_n;

	//4
	double yaw_angle;
	double pitch_angle;
	double bank_angle;
	double angle_of_attack;
	double flow_angle;

	//5
	double v_obj;
	double path_obj;
	double pitch_obj;
	obj_n_sys_coordinates coord_n_obj;

	//6
	missing_mp_time_proj_n_sys proj_mp_miss;
	double rel_v_n;
	double tau_kin;

	//7
	double nc_y;
	double nc_z;
	double t_dov;
	double t_bv;
	double t_sbv;

	//8
	missing_nsm_time_proj_n_sys proj_nsm_miss;
	double delta_V01;
	double delta_V02;
	double beta_y;

	//9
	missing_dov_time_proj_n_sys proj_dov_miss;

	//10
	double bank;
	double pitch;
	double ant_course;
	bank_angle_mistakes delta_gamma;

	//11
	trans_matrix from_n_to_apa;

	//additional
	double h;
	int i;
};

double GetVelocityValue(velocity T) {
	return std::sqrt(std::pow(T.x, 2) + std::pow(T.y, 2) + std::pow(T.z, 2));
}
//to_do_next
#endif