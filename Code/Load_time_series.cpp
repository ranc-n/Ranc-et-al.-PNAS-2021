/*
 * Load_time_series.cpp
 *
 *  Created on: 9 July 2019
 *      Author: Nathan Ranc
 */

#include "header.h"





// Import time series
structTs launchTs(std::string path_to_ts)
{

	structTs returnValues;

	int counter=0;
	int total_observations=0;
	int reserve_number=0;

	std::string line, extracted;
	std::string filePath_sLength = path_to_ts;
	std::ifstream sLength (filePath_sLength.c_str());

	while(getline(sLength, line))
	{
		total_observations=total_observations+1;
	}
	total_observations=total_observations-1;
	reserve_number=total_observations+5;

	returnValues.expId.reserve(reserve_number);
	returnValues.currentState.reserve(reserve_number);
	returnValues.resAccessM.reserve(reserve_number);
	returnValues.lightI.reserve(reserve_number);
	returnValues.lightR.reserve(reserve_number);
	returnValues.lightAbsR.reserve(reserve_number);
	returnValues.minDayTemp.reserve(reserve_number);

	std::string line2, extracted2;
	std::string::size_type sz2;
	std::ifstream sLength2 (filePath_sLength.c_str());

	while(getline(sLength2, line2))
	{
		counter=counter+1;

		if(counter>1)
		{
			extracted2 = line2.substr(0, line2.find(","));
			returnValues.expId.push_back(std::stoi (extracted2,&sz2));
			line2=line2.erase(0, line2.find(",")+1);

			extracted2 = line2.substr(0, line2.find(","));
			returnValues.currentState.push_back(std::stoi (extracted2,&sz2));
			line2=line2.erase(0, line2.find(",")+1);

			extracted2 = line2.substr(0, line2.find(","));
			returnValues.resAccessM.push_back(std::stoi (extracted2,&sz2));
			line2=line2.erase(0, line2.find(",")+1);

			extracted2 = line2.substr(0, line2.find(","));
			returnValues.lightI.push_back(std::stod (extracted2,&sz2));
			line2=line2.erase(0, line2.find(",")+1);

			extracted2 = line2.substr(0, line2.find(","));
			returnValues.lightR.push_back(std::stod (extracted2,&sz2));
			line2=line2.erase(0, line2.find(",")+1);

			extracted2 = line2.substr(0, line2.find(","));
			returnValues.lightAbsR.push_back(std::stod (extracted2,&sz2));
			line2=line2.erase(0, line2.find(",")+1);

			extracted2 = line2.substr(0, line2.find(","));
			returnValues.minDayTemp.push_back(std::stod (extracted2,&sz2));
			line2=line2.erase(0, line2.find(",")+1);
		}
	}

	return returnValues;
}





// Extract summary stats
structSummaryTs getTsMetrics(structTs ts)
{
	int l;
	int ind=-9999;
	int indCount=0;
	int count;
	structSummaryTs returnValues;

	returnValues.totalLength=ts.expId.size();
	returnValues.expId.reserve(100);
	returnValues.expIdCount.reserve(100);
	returnValues.tslvM.reserve(100);
	returnValues.tslvA.reserve(100);
	returnValues.alvM.reserve(100);
	returnValues.alvA.reserve(100);
	returnValues.refMem.reserve(100);
	returnValues.attMem.reserve(100);

	for(l=0;l<returnValues.totalLength;l++)
	{
		if(ts.expId[l]!=ind)
		{
			indCount=indCount+1;
			ind=ts.expId[l];

			returnValues.expId.push_back(ts.expId[l]);
			returnValues.tslvM.push_back(666);
			returnValues.tslvA.push_back(666);
			returnValues.alvM.push_back(666);
			returnValues.alvA.push_back(666);
			returnValues.refMem.push_back(666);
			returnValues.attMem.push_back(666);

			if(indCount!=1)
			{
				returnValues.expIdCount.push_back(count);
			}

			count=1;
		}

		else
		{
			count=count+1;
		}
	}

	returnValues.expIdCount.push_back(count);
	return returnValues;
}
