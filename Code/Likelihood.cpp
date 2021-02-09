/*
 * Likelihood.cpp
 *
 *  Created on: 9 July 2019
 *      Author: Nathan Ranc
 */

#include "header.h"





// Calculates the objective function
double calculateObjFunction(double objective_function, double extracted_prob)
{
	double return_values=-9999;

	if(objective_function==-9999)
	{
		if(extracted_prob==-9999)
		{
			return_values=-9999;
		}
		else
		{
			return_values=log(extracted_prob);
		}
	}
	else
	{
		if(extracted_prob==-9999)
		{
			return_values=objective_function;
		}
		else
		{
			return_values=objective_function+log(extracted_prob);
		}
	}

	return return_values;
}





// Returns the objective function value
void writeObjFunction(double obj_fxn, std::string output_directory)
{
    std::string filePath_output2 =  output_directory + "objective_function.csv";
    std::ofstream objFunctionFile;
    objFunctionFile.setf(std::ios::fixed, std::ios::floatfield);
    objFunctionFile.precision(7);
    objFunctionFile.open(filePath_output2.c_str());
    objFunctionFile << obj_fxn<< std::endl;
    objFunctionFile.close();
}
