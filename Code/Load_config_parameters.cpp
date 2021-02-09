/*
 * Load_config_parameters.cpp
 *
 *  Created on: 9 July 2019
 *      Author: Nathan Ranc
 */

#include "header.h"





// Loads configuration file
structConfig launchConfig(std::string path_to_config)
{
	structConfig returnValues;
    std::string filePath_sLength = path_to_config;
	std::string line2;
	std::ifstream sLength2 (filePath_sLength.c_str());

	getline(sLength2, line2); // header line

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
	returnValues.outputDirectoryPath=line2.substr(0, line2.size());

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
	returnValues.timeSeriesPath=line2.substr(0, line2.size());

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
	returnValues.initializationDataPath=line2.substr(0, line2.size());

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
	if(line2=="0")
	{
		returnValues.modelType=0;	// omniscience
	}
	if(line2=="1")
	{
		returnValues.modelType=1;	// perception
	}
	if(line2=="2")
	{
		returnValues.modelType=2;	// spatial memory
	}
	if(line2=="3")
	{
		returnValues.modelType=3;	// spatial + attribute memory
	}

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.fsLightIBeta=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.fsLightRBeta=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.fsLightAbsRBeta=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.fsMinDailyTemp=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.fsResPresBeta=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.fsResPresWithinBeta=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.fsResAccessBeta=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.fsResAccessWithinBeta=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.manipulatedFsPref=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.refMemDecay=std::stod(line2);

	getline(sLength2, line2);
	line2=line2.erase(0, line2.find(";")+1);
    returnValues.attMemDecay=std::stod(line2);

	return returnValues;
}
