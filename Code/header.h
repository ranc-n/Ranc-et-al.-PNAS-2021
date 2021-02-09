/*
 * header.h
 *
 *  Created on: 9 July 2019
 *      Author: Nathan Ranc
 */

#ifndef HEADER_H_
#define HEADER_H_

/*
 *
 * LIBRARIES
 *
 */

#include		<stdlib.h>
#include 	<cmath>
#include		<math.h>
#include 	<iostream>
#include 	<fstream>
#include 	<string>
#include 	<random>
#include 	<sys/types.h>
#include 	<dirent.h>
#include 	<errno.h>
#include 	<vector>
#include 	<ctime>
#include 	<sstream>
#include 	<algorithm>


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


/*
 *
 * STRUCTURES
 *
 */


// Structure storing configuration parameters
struct structConfig
{
	std::string outputDirectoryPath;				// output directory path
	std::string timeSeriesPath;					// time series of states (regularized, with interpolated NAs); main FS (M)=1, alternative FS (A)=2, vegetation (V)=3, NA=-9999
	std::string initializationDataPath;			// time since last visit for 1 and 2 expressed in hours prior to the initiation of the time series and corresponding accessibility
	int modelType;								// 0 = omniscient; 1 = perception; 2 = spatial memory; 3 = spatial + attribute memory
	double fsLightIBeta;							// selection coefficient for light variable (intensity) in FS state (movement towards M or A from other state)
	double fsLightRBeta;							// selection coefficient for light variable (rate of change) in FS state (movement towards M or A from other state)
	double fsLightAbsRBeta;						// selection coefficient for light variable (absolute rate of change) in FS state (movement towards M or A from other state)
	double fsMinDailyTemp;						// selection coefficient for minimum daily temperature in FS state
	double fsResPresBeta;						// selection coefficient for resource presence variable in FS state (movement towards M or A from other state)
	double fsResPresWithinBeta;					// selection coefficient for resource presence variable in FS state (movement within M or within A)
	double fsResAccessBeta;						// selection coefficient for resource accessibility variable in FS state (movement towards M or A from other state)
	double fsResAccessWithinBeta;				// selection coefficient for resource accessibility variable in FS state (movement within M or within A)
	double manipulatedFsPref;					// preference coefficient for M
	double refMemDecay;							// reference (spatial) memory decay rate [0,1]
	double attMemDecay;							// attribute memory decay rate [0,1]
};


// Structure storing the time series (states and associated covariates)
struct structTs
{
	std::vector<int>expId;						// experimental ID (i.e., animal-year)
	std::vector<int>currentState;				// state (int: M=1, A=2, V=3)
	std::vector<int>resAccessM;					// covariate: accessibility of food at M (1/0)
	std::vector<double>lightI;					// covariate: light intensity (continuous)
	std::vector<double>lightR;					// covariate: light rate of change (continuous)
	std::vector<double>lightAbsR;				// covariate: light absolute rate of change (continuous)
	std::vector<double>minDayTemp;				// covariate: minimum daily temperature (continuous)
};


// Structure storing summary statistics of the time series
struct structSummaryTs
{
    int totalLength;
	std::vector<int>expId;
	std::vector<int>expIdCount;
	std::vector<double>tslvM;					// time since last visit at state M
	std::vector<double>tslvA;					// time since last visit at state A
	std::vector<double>alvM;						// accessibility during last visit at state M
	std::vector<double>alvA;						// accessibility during last visit at state A
	std::vector<double>refMem;					// individual reference (spatial) memory decay rate
	std::vector<double>attMem;					// individual attribute memory decay rate
};


// Structure storing iteration results for omniscience model
struct structIterationResults
{
	double attraction [3];						// M, A, V
	double probability [3];						// M, A, V
};


// Structure storing simple reference (spatial) memory
struct structRefMem
{
	double refMemM;
	double refMemA;
};


// Structure storing previous resource accessibility values
struct structExpAccess
{
	double expectedAccessM;						// stores the previous accessibility at M - last visit (m2) or a function of previous visits (m3)
	double expectedAccessA;						// stores the previous accessibility at A - last visit (m2) or a function of previous visits (m3)
};


// Structure storing the iterations at which each states have been visited
struct structVisitHistory
{
	std::vector<int>visitIterationM;				// iteration(s) at which M was visited
	std::vector<int>visitIterationA;				// iteration(s) at which A was visited
	std::vector<int>visitAccessM;				// accessibility value(s) corresponding to previous visit(s) of M
	std::vector<int>visitAccessA;				// accessibility value(s) corresponding to previous visit(s) of A
};


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


/*
 *
 * FUNCTIONS
 *
 */


// Calculate_attraction.cpp: calculates the attraction of the three states for different models 0, 1 and 2/3
void calculateAttractionM0(structIterationResults & iteration_results, structConfig config_arg,double base_calc, int previous_state, int res_access_M_prev);
void calculateAttractionM1(structIterationResults & iteration_results, structConfig config_arg,double base_calc, int previous_state, int res_access_M_prev);
void calculateAttractionM2(structIterationResults & iteration_results, structConfig config_arg, structRefMem ref_mem, structExpAccess exp_access, double base_calc, int previous_state, int res_access_M_prev);

// Calculate_probability.cpp
void calculateProbability(structIterationResults & iteration_results, structConfig config_arg, int current_state_prev);
double extractProbability(structIterationResults iteration_results, int current_state);

// Likelihood.cpp
double calculateObjFunction(double objective_function, double extracted_prob);
void writeObjFunction(double obj_fxn, std::string output_directory);

// Load_config_parameters.cpp
structConfig launchConfig(std::string path_to_config);

// Load_other_inputs.cpp
void loadIndSummary(std::string path_to_tslv, structSummaryTs & summary_ts);

// Load_time_series.cpp
structTs launchTs(std::string path_to_ts);
structSummaryTs getTsMetrics(structTs ts);

// Memory_dynamics.cpp
void refMemInitialization(structRefMem & ref_mem, structConfig config_arg, structSummaryTs ts_metrics, int ind); // for M2 and M3
void expAccessInitialization(structExpAccess & exp_access, structSummaryTs ts_metrics, int ind); // for M2 and M3
structVisitHistory visitHistoryInitialization(int n_observations, int tslv_m, int tslv_a, int aslv_m, int aslv_a); // for M3
void memUpdateM2(structRefMem & ref_mem, structExpAccess & exp_access, int current_state_prev, int res_access_M_prev, double ref_mem_decay);
void memUpdateM3(structRefMem & ref_mem, structExpAccess & exp_access, structVisitHistory & visit_log, int current_state_prev, int current_state, int res_access_M_prev, int iteration, double ref_mem_decay, double att_mem_decay);


#endif /* HEADER_H_ */
