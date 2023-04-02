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


int main() {
	std::vector <raw_data> data;
	std::vector <fragment> fragments;
	missile_data missile;
	target_data target;
	raw_data temp;
	double FragmentsInitialSpeed = 7000.0;
	int FragmentsQuantity = 100;
	

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
	int counter = 0;
	int counter_near = 0;
	int counter_miss = 0;

	for (int j = 0; j < 100000; j++) {
		fragments = MakeFragments(missile, target, FragmentsInitialSpeed, FragmentsQuantity);
		counter = 0;
		counter_near = 0;
		double distance = 0.0;
		coordinates point;


		for (int i = 0; i < fragments.size(); ++i) {
			counter++;
			point = PointOfImpact(fragments[i], TargetSurface);
			distance = PointsDistance(point, target.coord_n_obj);
			if (HitTarget(target, point))
				counter_near++;
		}

		std::cout << "[" << j + 1 << "] fragments to target surface: " << counter << std::endl
			<< "[" << j + 1 << "] fragments hit the target: " << counter_near << std::endl << std::endl;
		total_near += counter_near;
		if (counter_near == 0)
			counter_miss++;
	}
	avg_near = total_near / 100000;
	std::cout << "avg fragments hit the target: " << avg_near << std::endl << std::endl;
	std::cout << "missed: " << counter_miss << std::endl << std::endl;

	//to_do_next
}