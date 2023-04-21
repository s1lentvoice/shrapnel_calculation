#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <map>
#include <iomanip>
#include "file_structs.h"
#include "data_making.h"
#include "missile.h"
#include "target.h"
#include "progressbar.h"


int main() {
	std::vector <raw_data> data;
	std::vector <fragment> fragments;
	std::vector <raw_data> raw_dataset;
	std::vector <int> raw_results = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	std::vector <int> raw_results_missed;
	std::vector <double> results;
	missile_data missile;
	target_data target;
	raw_data temp, a, b;
	double FragmentsInitialSpeed = 7000.0;
	int FragmentsQuantity = 1000;
	coordinates base_x;
	velocity t_velo;

	base_x.x = 0.0;
	base_x.y = 0.0;
	base_x.z = 0.0;

	std::string filename = "1.txt";
	std::string filename_out;
	std::ofstream out("output.txt");

	raw_dataset = MakeRawData(filename);
	temp = raw_dataset[0];
	int counter = 1;
	double delay;
	/*
	// start
	missile = MakeDataMissile(temp);
	//missile.yaw_angle = 75.0;
	//missile.pitch_angle = 45.0;
	target = ModifyCoords(MakeDataTarget(temp), missile);

	surface TargetSurfaceZX, TargetSurfaceXY, TargetSurfaceYZ;
	coordinates zero;

	//std::cout << "distance: " << PointsDistance(target.coord_n_obj, zero) << std::endl;

	TargetSurfaceZX = MakeTargetSurface(target.basis_y, target.coord_n_obj);
	TargetSurfaceXY = MakeTargetSurface(target.basis_z, target.coord_n_obj);
	//std::cout << TargetSurfaceZX.A << "x + " << TargetSurfaceZX.B << "y + " << TargetSurfaceZX.C << "z + " << TargetSurfaceZX.D << " = 0" << std::endl;
	coordinates point;
	fragments = MakeFragments(missile, target, FragmentsInitialSpeed, FragmentsQuantity);
	for (unsigned i = 0; i < fragments.size(); ++i) {
		if (fragments[i].hitXY) {
			point = PointOfImpact(fragments[i], TargetSurfaceXY);
			//distance = PointsDistance(point, target.coord_n_obj);

			out << "(" << point.x << ", " << point.y << ")" << std::endl;
		}
	}
	std::cout << counter;
	//end
	*/


	for (int m = 0; m < 20; ++m) {
		filename_out = std::to_string(m) + "delay.txt";
		std::ofstream current_out(filename_out);
		
		for (int k = 0; k < 100; ++k) {
			delay = (double)m / 1000.0;
			

			//out << "[" << k << "] set:";
			//out << "[" << k + 1 << "] set:" << std::endl;
			std::cout << "[" << k + 1 << "] set:" << std::endl;
			temp = raw_dataset[k];

			missile = MakeDataMissile(temp);
			//std::cout << missile.pitch_angle << " -> " << missile.pitch_angle + 12.0 << std::endl;
			target = ModifyCoords(MakeDataTarget(temp), missile);
			
			t_velo.x = target.v_obj;
			t_velo.y = 0.0;
			t_velo.z = 0.0;

			t_velo = MakeRotationVelo(t_velo, target.path_obj, target.pitch_obj);

			t_velo -= missile.v_proj_n;

			target.coord_n_obj = MoveTarget(target, t_velo, delay);
			//missile.yaw_angle += (double)k;
			//std::cout << "current angle: " << missile.yaw_angle << std::endl;
			surface TargetSurfaceZX, TargetSurfaceXY, TargetSurfaceYZ;
			coordinates zero;
			raw_results = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
			raw_results_missed.push_back(0);
			//std::cout << "distance: " << PointsDistance(target.coord_n_obj, zero) << std::endl;

			TargetSurfaceZX = MakeTargetSurface(target.basis_y, target.coord_n_obj);
			//TargetSurfaceYZ = MakeTargetSurface(target.basis_x, target.coord_n_obj);
			TargetSurfaceXY = MakeTargetSurface(target.basis_z, target.coord_n_obj);

			//std::cout << TargetSurfaceZX.A << "x + " << TargetSurfaceZX.B << "y + " << TargetSurfaceZX.C << "z + " << TargetSurfaceZX.D << " = 0" << std::endl;

			//std::cout << TargetSurfaceXY.A << "x + " << TargetSurfaceXY.B << "y + " << TargetSurfaceXY.C << "z + " << TargetSurfaceXY.D << " = 0" << std::endl;
			int total_near = 0;
			double avg_near = 0.0;

			int counter_near = 0;
			int counter_miss = 0;
			int counter_fragments_to_surface = 0;
			unsigned hit_res = 0;


			progressbar bar(100);
			bar.set_todo_char(" ");
			bar.set_done_char("#");

			for (int j = 0; j < 1000; j++) {
				fragments = MakeFragments(missile, target, FragmentsInitialSpeed, FragmentsQuantity);
				counter_near = 0;
				double distance = 0.0;
				coordinates point;

				for (unsigned i = 0; i < fragments.size(); ++i) {
					if (fragments[i].hitZX && !fragments[i].calculated) {
						point = PointOfImpact(fragments[i], TargetSurfaceZX);
						//distance = PointsDistance(point, target.coord_n_obj);
						hit_res = HitTargetZX(target, point);
						//out << "(" << point.z << ", " << point.x << ")" << std::endl;
						if (hit_res) {
							raw_results[hit_res] += 1;
							counter_near++;
							fragments[i].calculated = true;
						}
					}
					if (fragments[i].hitXY && !fragments[i].calculated) {
						point = PointOfImpact(fragments[i], TargetSurfaceXY);
						//distance = PointsDistance(point, target.coord_n_obj);
						hit_res = HitTargetXY(target, point);
						//out << "(" << point.z << ", " << point.x << ")" << std::endl;
						if (hit_res) {
							raw_results[hit_res] += 1;
							counter_near++;
							fragments[i].calculated = true;
						}
					}
				}
				hit_res = 0;
				//std::cout << "[" << j + 1 << "] fragments to target surface: " << counter << std::endl
					//<< "[" << j + 1 << "] fragments hit the target: " << counter_near << std::endl << std::endl;
				total_near += counter_near;

				if (counter_near == 0)
					raw_results_missed[k] += 1;
				if (counter == 10) {
					counter = 0;
					bar.update();
				}
				counter++;
			}
			avg_near = total_near / 1000.0;

			for (int i = 0; i < 12; ++i) {
				results.push_back(raw_results[i] / 1000.0);
			}
			raw_results.clear();
			//std::cout << std::endl << "avg fragments hit the target: " << avg_near << std::endl << std::endl;
			//std::cout << "missed: " << counter_miss << std::endl << std::endl;
			//std::cout << "avg to surface: " << counter_fragments_to_surface / 10000 << std::endl << std::endl;

			std::cout << std::endl << "avg body: " << round(results[1]) << std::endl;
			std::cout << "avg wings: " << round(results[2]) << std::endl;
			std::cout << "avg empennage: " << round(results[3]) << std::endl;
			std::cout << "avg cam: " << round(results[4]) << std::endl;
			std::cout << "avg armament: " << round(results[5]) << std::endl;
			std::cout << "avg navigation: " << round(results[6]) << std::endl;
			std::cout << "avg flaps: " << round(results[7]) << std::endl;
			std::cout << "avg elevator: " << round(results[8]) << std::endl;
			std::cout << "avg engine: " << round(results[9]) << std::endl;
			std::cout << "avg propeller: " << round(results[10]) << std::endl;
			std::cout << "avg fuel tank: " << round(results[11]) << std::endl;
			std::cout << "missed: " << raw_results_missed[k] << std::endl;
			std::cout << "distance: " << PointsDistance(target.coord_n_obj, base_x) << std::endl;
			std::cout << "total: " << round(avg_near) << std::endl << std::endl;

			current_out << round(results[1]) << "\t";
			current_out << round(results[2]) << "\t";
			current_out << round(results[3]) << "\t";
			current_out << round(results[4]) << "\t";
			current_out << round(results[5]) << "\t";
			current_out << round(results[6]) << "\t";
			current_out << round(results[7]) << "\t";
			current_out << round(results[8]) << "\t";
			current_out << round(results[9]) << "\t";
			current_out << round(results[10]) << "\t";
			current_out << round(results[11]) << std::endl;
			//out << "missed: " << raw_results_missed[k] << std::endl << std::endl;

			results.clear();
			//out << "missed: " << counter_miss << std::endl << std::endl;
			//if (avg_near < EPS)
				//break;
		}

		
	}

	

	//to_do_next
}