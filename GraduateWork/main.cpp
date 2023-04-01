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
	

	std::string filename = "1.txt";
	std::ofstream out("output.txt");
	
	temp = MakeRawData(filename);

	missile = MakeDataMissile(temp);
	target = MakeDataTarget(temp);
	fragments = MakeFragments(missile, target, 7000.0, 100);

	for (int j = 0; j < 50; j++) {
		fragments = MakeFragments(missile, target, 7000.0, 100);
		int counter = 0;

		for (int i = 0; i < 100; ++i) {
			if (AngleBetweenVectors(fragments[i].velo, target.basis_y) < 0.0)
				counter++;
		}

		std::cout << "[" << j + 1 << "] fragments to target surface: " << counter << std::endl;
	}
	
	//to_do_next
}