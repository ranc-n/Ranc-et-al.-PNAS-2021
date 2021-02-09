/*
 * Calculate_attraction.cpp
 *
 *  Created on: 9 July 2019
 *      Author: Nathan Ranc
 */

#include "header.h"





// Calculates attraction for model 0 (omniscience)
void calculateAttractionM0(structIterationResults & iteration_results, structConfig config_arg, double base_calc, int previous_state, int res_access_M_prev)
{
	// Attraction if current state is known
	if(previous_state!=-9999)
	{
		iteration_results.attraction[2]=1;		// Vegetation attraction is always 1 (reference level)

		// Attraction for feeding site states (M/A)
		if(previous_state==1) // if in M
		{
			iteration_results.attraction[0]=base_calc*exp(
					config_arg.manipulatedFsPref+
					config_arg.fsResPresWithinBeta+
					config_arg.fsResAccessWithinBeta*res_access_M_prev);

			iteration_results.attraction[1]=base_calc*exp(
					config_arg.fsResPresBeta+
					config_arg.fsResAccessBeta);
		}

		if(previous_state==2)		// if in A
		{
			iteration_results.attraction[0]=base_calc*exp(
					config_arg.manipulatedFsPref+
					config_arg.fsResPresBeta+
					config_arg.fsResAccessBeta*res_access_M_prev);

			iteration_results.attraction[1]=base_calc*exp(
					config_arg.fsResPresWithinBeta+
					config_arg.fsResAccessWithinBeta);
		}

		if(previous_state==3)		// if in V
		{
			iteration_results.attraction[0]=base_calc*exp(
					config_arg.manipulatedFsPref+
					config_arg.fsResPresBeta+
					config_arg.fsResAccessBeta*res_access_M_prev);

			iteration_results.attraction[1]=base_calc*exp(
					config_arg.fsResPresBeta+
					config_arg.fsResAccessBeta);
		}
	}else	// Attraction if current state is not known
	{
		iteration_results.attraction[0]=-9999;
		iteration_results.attraction[1]=-9999;
		iteration_results.attraction[2]=-9999;
	}
}





// Calculates attraction for model 1 (perception)
void calculateAttractionM1(structIterationResults & iteration_results, structConfig config_arg, double base_calc, int previous_state, int res_access_M_prev)
{
	// Attraction if current state is known
	if(previous_state!=-9999)
	{
		iteration_results.attraction[2]=1;		// Vegetation attraction is always 1 (reference level)

		// Attraction for feeding site states (M/A)
		if(previous_state==1) 		// if in M
		{
			iteration_results.attraction[0]=base_calc*exp(
					config_arg.manipulatedFsPref+
					config_arg.fsResPresWithinBeta+
					config_arg.fsResAccessWithinBeta*res_access_M_prev);

			iteration_results.attraction[1]=base_calc*exp(
					config_arg.fsResPresBeta);
		}

		if(previous_state==2)		// if in A
		{
			iteration_results.attraction[0]=base_calc*exp(
					config_arg.manipulatedFsPref+
					config_arg.fsResPresBeta);

			iteration_results.attraction[1]=base_calc*exp(
					config_arg.fsResPresWithinBeta+
					config_arg.fsResAccessWithinBeta);
		}

		if(previous_state==3)		// if in V
		{
			iteration_results.attraction[0]=base_calc*exp(
					config_arg.manipulatedFsPref+
					config_arg.fsResPresBeta);

			iteration_results.attraction[1]=base_calc*exp(
					config_arg.fsResPresBeta);
		}
	}else	// Attraction if current state is not known
	{
		iteration_results.attraction[0]=-9999;
		iteration_results.attraction[1]=-9999;
		iteration_results.attraction[2]=-9999;
	}
}





// Calculates attraction for model 2/3 (memory)
void calculateAttractionM2(structIterationResults & iteration_results, structConfig config_arg, structRefMem ref_mem, structExpAccess exp_access, double base_calc, int previous_state, int res_access_M_prev)
{
	// Attraction if current state is known
	if(previous_state!=-9999)
	{
		iteration_results.attraction[2]=1; // Vegetation attraction is always 1 (reference level)

		// Attraction for feeding site states (M/A)
		if(previous_state==1)		// if in M
		{
			iteration_results.attraction[0]=base_calc*exp(
					config_arg.manipulatedFsPref+
					config_arg.fsResPresWithinBeta+
					config_arg.fsResAccessWithinBeta*res_access_M_prev);
			iteration_results.attraction[1]=ref_mem.refMemA*base_calc*exp(
					config_arg.fsResPresBeta+
					config_arg.fsResAccessBeta*exp_access.expectedAccessA);
		}

		if(previous_state==2)		// if in A
		{
			iteration_results.attraction[0]=ref_mem.refMemM*base_calc*exp(
					config_arg.manipulatedFsPref+
					config_arg.fsResPresBeta+
					config_arg.fsResAccessBeta*exp_access.expectedAccessM);

			iteration_results.attraction[1]=base_calc*exp(
					config_arg.fsResPresWithinBeta+
					config_arg.fsResAccessWithinBeta);
		}

		if(previous_state==3)		// if in V
		{
			iteration_results.attraction[0]=ref_mem.refMemM*base_calc*exp(
					config_arg.manipulatedFsPref+
					config_arg.fsResPresBeta+
					config_arg.fsResAccessBeta*exp_access.expectedAccessM);

			iteration_results.attraction[1]=ref_mem.refMemA*base_calc*exp(
					config_arg.fsResPresBeta+
					config_arg.fsResAccessBeta*exp_access.expectedAccessA);

		}
	}else	// Attraction if current state is not known
	{
		iteration_results.attraction[0]=-9999;
		iteration_results.attraction[1]=-9999;
		iteration_results.attraction[2]=-9999;
	}
}
