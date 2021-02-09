/*
 * Load_other_inputs.cpp
 *
 *  Created on: 9 July 2019
 *      Author: Nathan Ranc
 */

#include "header.h"





// Load initialization data (time since last visit and associated accessibility)
void loadIndSummary(std::string path_to_tslv, structSummaryTs & summary_ts)
{
	int counter=0;
	int nAnimals=summary_ts.expId.size();
	int ind;
	int loaded_ind=666;

	std::string filePath_sLength = path_to_tslv;

	std::string line2, extracted2;
	std::string::size_type sz2;
	std::ifstream sLength2 (filePath_sLength.c_str());

	while(getline(sLength2, line2))
	{
		counter=counter+1;

		if(counter>1)
		{
			extracted2 = line2.substr(0, line2.find(","));
			loaded_ind=(std::stoi(extracted2,&sz2));
			line2=line2.erase(0, line2.find(",")+1);

			for(ind=0;ind<nAnimals;ind++) 									// INDIVIDUAL LOOP
			{
				if(summary_ts.expId[ind]==loaded_ind)
				{
					extracted2 = line2.substr(0, line2.find(","));
					summary_ts.tslvM[ind]=(std::stod(extracted2,&sz2));
					line2=line2.erase(0, line2.find(",")+1);

					extracted2 = line2.substr(0, line2.find(","));
					summary_ts.tslvA[ind]=(std::stod(extracted2,&sz2));
					line2=line2.erase(0, line2.find(",")+1);

					extracted2 = line2.substr(0, line2.find(","));
					summary_ts.alvM[ind]=(std::stod(extracted2,&sz2));
					line2=line2.erase(0, line2.find(",")+1);

					extracted2 = line2.substr(0, line2.find(","));
					summary_ts.alvA[ind]=(std::stod(extracted2,&sz2));
					line2=line2.erase(0, line2.find(",")+1);
				}
			}
		}
	}
}
