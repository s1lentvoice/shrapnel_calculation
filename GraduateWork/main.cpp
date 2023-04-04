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
	missile_data missile;
	target_data target;
	raw_data temp;
	double FragmentsInitialSpeed = 7000.0;
	int FragmentsQuantity = 360;
	

	std::string filename = "1.txt";
	std::ofstream out("output.txt");
	
	temp = MakeRawData(filename);

	missile = MakeDataMissile(temp);
	target = ModifyCoords(MakeDataTarget(temp), missile);
	surface TargetSurface;
	TargetSurface = MakeTargetSurface(target.basis_y, target.coord_n_obj);

	fragments = MakeFragments(missile, target, FragmentsInitialSpeed, FragmentsQuantity);
	int total_near = 0;
	double avg_near = 0.0;
	int counter = 1;
	int counter_near = 0;
	int counter_miss = 0;


	progressbar bar(100);
	bar.set_todo_char(" ");
	bar.set_done_char("#");
	
	for (int j = 0; j < 10000; j++) {
		fragments = MakeFragments(missile, target, FragmentsInitialSpeed, FragmentsQuantity);
		
		counter_near = 0;
		double distance = 0.0;
		coordinates point;


		for (unsigned int i = 0; i < fragments.size(); ++i) {
			
			point = PointOfImpact(fragments[i], TargetSurface);
			distance = PointsDistance(point, target.coord_n_obj);
			if (HitTarget(target, point))
				counter_near++;
		}

		//std::cout << "[" << j + 1 << "] fragments to target surface: " << counter << std::endl
			//<< "[" << j + 1 << "] fragments hit the target: " << counter_near << std::endl << std::endl;
		total_near += counter_near;
		
		if (counter_near == 0)
			counter_miss++;
		if (counter == 100) {
			counter = 0;
			bar.update();
		}
		counter++;
	}
	avg_near = total_near / 10000;
	std::cout << std::endl << std::endl << "avg fragments hit the target: " << avg_near << std::endl << std::endl;
	std::cout << "missed: " << counter_miss << std::endl << std::endl;

	//to_do_next
}