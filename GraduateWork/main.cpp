﻿#include <iostream>
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
	missile_data missile;
	target_data target;
	raw_data temp, a, b;
	double FragmentsInitialSpeed = 7000.0;
	int FragmentsQuantity = 1000;
	coordinates base_x;

	base_x.x = 1.0;
	base_x.y = 0.0;
	base_x.z = 0.0;

	std::string filename = "1.txt";
	std::ofstream out("output.txt");
	
	raw_dataset = MakeRawData(filename);

	for (int k = 0; k < 8; k++) {
		std::cout << "[" << k << "] set:" << std::endl << std::endl;

		out << "[" << k << "] set:";

		temp = raw_dataset[k];

		missile = MakeDataMissile(temp);
		base_x = MakeRotation(base_x, missile.yaw_angle, missile.pitch_angle);
		target = ModifyCoords(MakeDataTarget(temp), missile);
		surface TargetSurfaceZX, TargetSurfaceXY, TargetSurfaceYZ;

		TargetSurfaceZX = MakeTargetSurface(target.basis_y, target.coord_n_obj);
		TargetSurfaceYZ = MakeTargetSurface(target.basis_x, target.coord_n_obj);
		TargetSurfaceXY = MakeTargetSurface(target.basis_z, target.coord_n_obj);

		std::cout << TargetSurfaceZX.A << "x + " << TargetSurfaceZX.B << "y + " << TargetSurfaceZX.C << "z + " << TargetSurfaceZX.D << " = 0" << std::endl;

		std::cout << TargetSurfaceXY.A << "x + " << TargetSurfaceXY.B << "y + " << TargetSurfaceXY.C << "z + " << TargetSurfaceXY.D << " = 0" << std::endl;
		fragments = MakeFragments(missile, target, FragmentsInitialSpeed, FragmentsQuantity);
		int total_near = 0;
		double avg_near = 0.0;
		int counter = 1;
		int counter_near = 0;
		int counter_miss = 0;
		int counter_fragments_to_surface = 0;


		progressbar bar(100);
		bar.set_todo_char(" ");
		bar.set_done_char("#");

		for (int j = 0; j < 1000; j++) {
			fragments = MakeFragments(missile, target, FragmentsInitialSpeed, FragmentsQuantity);
			counter_near = 0;
			double distance = 0.0;
			coordinates point;

			for (unsigned int i = 0; i < fragments.size(); ++i) {
				if (fragments[i].hitZX && !fragments[i].calculated) {
					point = PointOfImpact(fragments[i], TargetSurfaceZX);
					//distance = PointsDistance(point, target.coord_n_obj);

					//out << "(" << point.z << ", " << point.x << ")" << std::endl;
					if (HitTargetZX(target, point)) {
						counter_near++;
						fragments[i].calculated = true;
					}
				}
				if (fragments[i].hitXY && !fragments[i].calculated) {
					point = PointOfImpact(fragments[i], TargetSurfaceXY);
					//distance = PointsDistance(point, target.coord_n_obj);

					//out << "(" << point.z << ", " << point.x << ")" << std::endl;
					if (HitTargetXY(target, point)) {
						counter_near++;
						fragments[i].calculated = true;
					}
				}
			}

			//std::cout << "[" << j + 1 << "] fragments to target surface: " << counter << std::endl
				//<< "[" << j + 1 << "] fragments hit the target: " << counter_near << std::endl << std::endl;
			total_near += counter_near;

			if (counter_near == 0)
				counter_miss++;
			if (counter == 10) {
				counter = 0;
				bar.update();
			}
			counter++;
		}
		avg_near = total_near / 1000;
		std::cout << std::endl << std::endl << "avg fragments hit the target: " << avg_near << std::endl << std::endl;
		std::cout << "missed: " << counter_miss << std::endl << std::endl;
		std::cout << "avg to surface: " << counter_fragments_to_surface / 10000 << std::endl << std::endl;
		
		out << std::endl << "avg fragments hit the target: " << avg_near << std::endl;
		out << "missed: " << counter_miss << std::endl << std::endl;
	}
	
	//to_do_next
}