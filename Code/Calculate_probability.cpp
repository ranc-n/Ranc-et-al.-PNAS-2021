/*
 * Calculate_probability.cpp
 *
 *  Created on: 9 July 2019
 *      Author: Nathan Ranc
 */

#include "header.h"





// Function to calculate probabilities
void calculateProbability(structIterationResults & iteration_results, structConfig config_arg, int current_state_prev)
{

	int s;

	if(current_state_prev!=-9999)
	{
		double sum_attractions=iteration_results.attraction[0]+iteration_results.attraction[1]+iteration_results.attraction[2];
		iteration_results.probability[0]=iteration_results.attraction[0]/sum_attractions;
		iteration_results.probability[1]=iteration_results.attraction[1]/sum_attractions;
		iteration_results.probability[2]=iteration_results.attraction[2]/sum_attractions;

		// Prevent "0" probability
		for(s=0;s<3;s++)
		{
			if(iteration_results.probability[s]<=1e-100)
			{
				iteration_results.probability[s]=1e-100;
			}
		}
	}else{
		iteration_results.probability[0]=-9999;
		iteration_results.probability[1]=-9999;
		iteration_results.probability[2]=-9999;
	}
}





// Function to read_in probabilities
double extractProbability(structIterationResults iteration_results, int current_state)
{
	double return_values=-9999;	// default is NA

	int next_state=current_state;

	if(next_state!=-9999)
	{
		return_values=iteration_results.probability[next_state-1];
	}

	return return_values;
}
