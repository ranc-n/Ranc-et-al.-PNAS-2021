/*
 * Memory_dynamics.cpp
 *
 *  Created on: 9 July 2019
 *      Author: Nathan Ranc
 */

#include "header.h"






/////////////////////
// INITIALIZATIONS
/////////////////////

// Function to initialize the reference (spatial) memory
void refMemInitialization(structRefMem & ref_mem, structConfig config_arg, structSummaryTs ts_metrics, int ind)
{
	double tslvM=ts_metrics.tslvM[ind]-1;	//initialize to tslv-1 because the 1st action in each iteration is to increment the memory decay (if initialized to tslv, the memory decay should be skipped in iteration 0)
	double tslvA=ts_metrics.tslvA[ind]-1;

	ref_mem.refMemM=1*pow((1-config_arg.refMemDecay),tslvM);
	ref_mem.refMemA=1*pow((1-config_arg.refMemDecay),tslvA);
}



// Function to initialize the expected resource accessibility
void expAccessInitialization(structExpAccess & exp_access, structSummaryTs ts_metrics, int ind)
{
	exp_access.expectedAccessM=ts_metrics.alvM[ind];
	exp_access.expectedAccessA=ts_metrics.alvA[ind];
}



// Function to initialize the visit history
structVisitHistory visitHistoryInitialization(int n_observations, int tslv_m, int tslv_a, int aslv_m, int aslv_a)
{
	structVisitHistory returnValue;

	int reserve_number=n_observations+5;

	returnValue.visitIterationM.reserve(reserve_number);
	returnValue.visitIterationA.reserve(reserve_number);
	returnValue.visitAccessM.reserve(reserve_number);
	returnValue.visitAccessA.reserve(reserve_number);
	returnValue.visitIterationM.push_back(-1*(tslv_m));
	returnValue.visitIterationA.push_back(-1*(tslv_a));
	returnValue.visitAccessM.push_back(aslv_m);
	returnValue.visitAccessA.push_back(aslv_a);

	return returnValue;
}





/////////////////////
// UPDATES
/////////////////////

// Function to update reference (spatial) memory and expected access for model m2 i.e., reference (spatial) memory only
void memUpdateM2(structRefMem & ref_mem, structExpAccess & exp_access, int current_state_prev, int res_access_M_prev, double ref_mem_decay)
{
	if(current_state_prev==1) // if previous state was M
	{
		ref_mem.refMemM=1;														// update reference memory of M to 1
		exp_access.expectedAccessM=res_access_M_prev; 							// update expected access of M
		ref_mem.refMemA=ref_mem.refMemA-ref_mem_decay*ref_mem.refMemA; 			// decay reference memory of A
	}

	if(current_state_prev==2) // if previous state was A
	{
		ref_mem.refMemA=1;														// update reference memory of A to 1
		exp_access.expectedAccessA=1;											// A is always accessible
		ref_mem.refMemM=ref_mem.refMemM-ref_mem.refMemM*ref_mem_decay; 			// decay reference memory of M
	}

	if(current_state_prev==3 || current_state_prev==-9999) //!!! ASSUMPTION: if current state is unknown assumed to be vegetation
	{
		ref_mem.refMemM=ref_mem.refMemM-ref_mem.refMemM*ref_mem_decay;
		ref_mem.refMemA=ref_mem.refMemA-ref_mem.refMemA*ref_mem_decay;
	}
}



// Function to update reference memory and expected access for model m3 i.e., reference (spatial) memory + attribute memory
void memUpdateM3(structRefMem & ref_mem, structExpAccess & exp_access, structVisitHistory & visit_log, int current_state_prev, int current_state, int res_access_M_prev, int iteration, double ref_mem_decay, double att_mem_decay)
{
	int v=0;
	int lengthVisits=0;			// number of previous visits
	double sum_numerator=0;		// for calculation of expected access
	double sum_denominator=0;	// for calculation of expected access

	if(current_state_prev==1) // IF PREVIOUS STATE WAS M
	{
		ref_mem.refMemM=1;														// update reference memory of M to 1
		ref_mem.refMemA=ref_mem.refMemA-ref_mem.refMemA*ref_mem_decay; 			// decay reference memory of A

		if(current_state!=1) // if current state is different from M (i.e., end of visit of M)
		{
			visit_log.visitIterationM.push_back(iteration);						// update the visit history of M with previous iteration
			visit_log.visitAccessM.push_back(res_access_M_prev);					// update the visit history of M with previous accessibility

			lengthVisits=visit_log.visitIterationM.size();
			for(v=0;v<lengthVisits;v++)
			{
				sum_numerator=sum_numerator+1*pow((1-att_mem_decay),((iteration)-visit_log.visitIterationM[v]))*visit_log.visitAccessM[v];
				sum_denominator=sum_denominator+1*pow((1-att_mem_decay),((iteration)-visit_log.visitIterationM[v]));
			}
			exp_access.expectedAccessM=sum_numerator/sum_denominator; 			// update expected access of M
		}
	}

	if(current_state_prev==2) // IF PREVIOUS STATE WAS A
	{
		ref_mem.refMemM=ref_mem.refMemM-ref_mem.refMemM*ref_mem_decay; 			// decay reference memory of M
		ref_mem.refMemA=1;														// update reference memory of A to 1

		if(current_state!=2) // if current state is different from A (i.e., end of visit of A)
		{
			visit_log.visitIterationA.push_back(iteration);						// update the visit history of A with previous iteration
			visit_log.visitAccessA.push_back(1);									// update the visit history of A with previous accessibility (i.e., 1)

			lengthVisits=visit_log.visitIterationA.size();
			for(v=0;v<lengthVisits;v++)
			{
				sum_numerator=sum_numerator+1*pow((1-att_mem_decay),((iteration)-visit_log.visitIterationA[v]))*visit_log.visitAccessA[v];
				sum_denominator=sum_denominator+1*pow((1-att_mem_decay),((iteration)-visit_log.visitIterationA[v]));
			}
			exp_access.expectedAccessA=sum_numerator/sum_denominator; 			// update expected access of A
		}
	}

	if(current_state_prev==3 || current_state_prev==-9999) 						//!!! ASSUMPTION: if current state is unknown assumed to be vegetation
	{
		ref_mem.refMemM=ref_mem.refMemM-ref_mem.refMemM*ref_mem_decay;
		ref_mem.refMemA=ref_mem.refMemA-ref_mem.refMemA*ref_mem_decay;
	}
}


