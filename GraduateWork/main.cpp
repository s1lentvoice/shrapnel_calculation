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
	missile_data missile;
	target_data target;
	
	std::string filename = "1.txt";
	
	std::ofstream out("output.txt");

	raw_data temp;
	
	temp = MakeRawData(filename);

	missile = MakeDataMissile(temp);
	target = MakeDataTarget(temp);
	
	//to_do_next
	
}