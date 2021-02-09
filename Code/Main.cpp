/*
 * Main.cpp
 *
 *  Created on: 9 July 2019
 *      Author: Nathan Ranc
 */


#include "header.h"
using namespace std;

int main(int argc, char* argv[])
{
	time_t iniTime = time(0);

	bool short_output_writing=true;		// to remove short output writing, turn this to false AND comment sections of the code marked with AAA

	bool execute_command_line=true;		// if execute_command_line=TRUE  => config file via command line
										// if execute_command_line=FALSE => default config (e.g., for debugging)


	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////


	/*
	 *
	 * LOAD CONFIG FILE
	 *
	 */


	string configFile;

	if(execute_command_line==false)		// Obtains default config file
	{
		// POPULATION-LEVEL -- FULL MODELS
		//configFile="/Path/to/config_omniscience_full.txt";
		//configFile="/Path/to/config_perception_full.txt";
		//configFile="/Path/to/config_memory_full.txt";

		// POPULATION-LEVEL -- BEST MODELS
		//configFile="/Path/to/config_omniscience_best.txt";
		//configFile="/Path/to/config_perception_best.txt";
		//configFile="/Path/to/config_memory_best.txt";

		// INDIVIDUAL-LEVEL -- BEST MODELS; MEDIAN PARAMETER VALUES
		//configFile="/Path/to/config_omniscience_best_medianInd.txt";
		//configFile="/Path/to/config_perception_best_medianInd.txt";
		//configFile="/Path/to/config_memory_best_medianInd.txt";

	}
	else									// Obtains config file path via command line arguments
	{
	    if (argc != 3)
	    {
	        std::cout << "PROGRAM ENDED: expecting a single parameter (too few or too many)"<<endl;
	        exit(0);
	    }
	    else
	    {
	        for (int a = 1; a < argc; a++)
	        {
	            std::string arg = argv[a];
	            if (a + 1 != argc)
	            {
	            	if (arg == "-config")
	                {
	            		configFile=argv[a+1];
	                }
	             }
	        }
	    }
	}

    structConfig configArg=launchConfig(configFile);


	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////


    /*
     *
     * VARIABLE DECLARATION
     *
     */


    int ind, ite;
    int rowCount=0;
    double objectiveFunction=-9999;
    double extractedProb=0.0;
    double base_attraction=0.0;
    structIterationResults iterationResults;
    structVisitHistory visitLog = visitHistoryInitialization(1,1,1,1,1); // initializes the structure with temporary values (is updated thereafter)


    ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////


	/*
	 *
	 * LOADING TIME SERIES
	 *
	 */


	structTs tsInput=launchTs(configArg.timeSeriesPath); 			// Imports the time series in the program (expID, states and covariates)
    structSummaryTs TsMetrics=getTsMetrics(tsInput);					// Gets summary statistics (total number of observations and per expID)

	loadIndSummary(configArg.initializationDataPath,TsMetrics);			// Gets the time since last visit values for each expID

	int nAnimals=TsMetrics.expId.size();								// Extracts the number of expID

	double short_output_prob[tsInput.expId.size()][3];				// Creates array to stock probabilities


	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////


	/*
	 *
	 * MODELS
	 *
	 */


	///////////////////////////////////////////////////////////
	// MODEL 0 (OMNISCIENCE)
	///////////////////////////////////////////////////////////

	if(configArg.modelType==0)
	{
		for(ind=0;ind<nAnimals;ind++) 									// INDIVIDUAL LOOP
		{
			for(ite=0;ite<TsMetrics.expIdCount[ind];ite++) 				// ITERATION LOOP
			{
				rowCount=rowCount+1;

				// Calculate attractions
				base_attraction=exp(configArg.fsLightIBeta*tsInput.lightI[rowCount-1]+
						configArg.fsLightRBeta*tsInput.lightR[rowCount-1]+
						configArg.fsLightAbsRBeta*tsInput.lightAbsR[rowCount-1]+
						configArg.fsMinDailyTemp*tsInput.minDayTemp[rowCount-1]);
				calculateAttractionM0(iterationResults, configArg, base_attraction, tsInput.currentState[rowCount-1], tsInput.resAccessM[rowCount-1]);

				// Calculate probabilities
				calculateProbability(iterationResults, configArg, tsInput.currentState[rowCount-1]);

				// Writing short output (POINT AAA)
				short_output_prob[rowCount-1][0]=iterationResults.probability[0]; // for M
				short_output_prob[rowCount-1][1]=iterationResults.probability[1]; // for O
				short_output_prob[rowCount-1][2]=iterationResults.probability[2]; // for V

			    if(ite!=(TsMetrics.expIdCount[ind]-1))	// If last observation writing is different
			    	{
		    			extractedProb=extractProbability(iterationResults, tsInput.currentState[rowCount]);
		    			objectiveFunction=calculateObjFunction(objectiveFunction,extractedProb);
			    	}
			}
		}
	}


	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////
	// MODEL 1 (PERCEPTION)
	///////////////////////////////////////////////////////////

	if(configArg.modelType==1)
	{
		for(ind=0;ind<nAnimals;ind++) 									// INDIVIDUAL LOOP
		{
			for(ite=0;ite<TsMetrics.expIdCount[ind];ite++) 				// ITERATION LOOP
			{
				rowCount=rowCount+1;

				// Calculate attractions
				base_attraction=exp(configArg.fsLightIBeta*tsInput.lightI[rowCount-1]+
						configArg.fsLightRBeta*tsInput.lightR[rowCount-1]+
						configArg.fsLightAbsRBeta*tsInput.lightAbsR[rowCount-1]+
						configArg.fsMinDailyTemp*tsInput.minDayTemp[rowCount-1]);
				calculateAttractionM1(iterationResults, configArg, base_attraction, tsInput.currentState[rowCount-1], tsInput.resAccessM[rowCount-1]);

				// Calculate probabilities
				calculateProbability(iterationResults, configArg, tsInput.currentState[rowCount-1]);

				// Writing short output (POINT AAA)
				short_output_prob[rowCount-1][0]=iterationResults.probability[0]; // for M
				short_output_prob[rowCount-1][1]=iterationResults.probability[1]; // for O
				short_output_prob[rowCount-1][2]=iterationResults.probability[2]; // for V


			    if(ite!=(TsMetrics.expIdCount[ind]-1))	// If last observation writing is different
			    	{
		    		extractedProb=extractProbability(iterationResults, tsInput.currentState[rowCount]);

					objectiveFunction=calculateObjFunction(objectiveFunction,extractedProb);
			    	}
			}
		}
	}


	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////
	// MODEL 2 (SPATIAL MEMORY)
	///////////////////////////////////////////////////////////

	if(configArg.modelType==2)
	{
	    structRefMem refMem;
	    structExpAccess expAccess;

		for(ind=0;ind<nAnimals;ind++) 									// INDIVIDUAL LOOP
		{
			// MEMORY INITIALIZATION (in all model cases because outputs are printed)
			refMemInitialization(refMem,configArg,TsMetrics,ind); 		
			expAccessInitialization(expAccess,TsMetrics,ind);

			for(ite=0;ite<TsMetrics.expIdCount[ind];ite++) 				// ITERATION LOOP
			{
				rowCount=rowCount+1;

				// Calculate memory dynamics
				memUpdateM2(refMem,expAccess, tsInput.currentState[rowCount-1], tsInput.resAccessM[rowCount-1], configArg.refMemDecay);

				// Calculate attractions
				base_attraction=exp(configArg.fsLightIBeta*tsInput.lightI[rowCount-1]+
						configArg.fsLightRBeta*tsInput.lightR[rowCount-1]+
						configArg.fsLightAbsRBeta*tsInput.lightAbsR[rowCount-1]+
						configArg.fsMinDailyTemp*tsInput.minDayTemp[rowCount-1]);
				calculateAttractionM2(iterationResults, configArg, refMem, expAccess, base_attraction, tsInput.currentState[rowCount-1], tsInput.resAccessM[rowCount-1]);

				// Calculate probabilities
				calculateProbability(iterationResults, configArg, tsInput.currentState[rowCount-1]);

				// Writing short output (POINT AAA)
				short_output_prob[rowCount-1][0]=iterationResults.probability[0]; // for M
				short_output_prob[rowCount-1][1]=iterationResults.probability[1]; // for O
				short_output_prob[rowCount-1][2]=iterationResults.probability[2]; // for V


			    if(ite!=(TsMetrics.expIdCount[ind]-1))	// If last observation writing is different
			    	{
			    		extractedProb=extractProbability(iterationResults, tsInput.currentState[rowCount]);

					objectiveFunction=calculateObjFunction(objectiveFunction,extractedProb);
			    	}
			}
		}
	}


	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////
	// MODEL 3 (SPATIAL + ATTRIBUTE MEMORY)
	///////////////////////////////////////////////////////////

	if(configArg.modelType==3)
	{
	    structRefMem refMem;
	    structExpAccess expAccess;

		for(ind=0;ind<nAnimals;ind++) 									// INDIVIDUAL LOOP
		{

			// MEMORY INITIALIZATION (in all model cases because outputs are printed)
			refMemInitialization(refMem,configArg,TsMetrics,ind);
			expAccessInitialization(expAccess,TsMetrics,ind);

			// VISIT HISTORY INITIALIZATION
			visitLog = visitHistoryInitialization(TsMetrics.expIdCount[ind], TsMetrics.tslvM[ind], TsMetrics.tslvA[ind], TsMetrics.alvM[ind], TsMetrics.alvA[ind]);


			for(ite=0;ite<TsMetrics.expIdCount[ind];ite++) 				// ITERATION LOOP
			{

				rowCount=rowCount+1;

				// Calculate memory dynamics
				memUpdateM3(refMem, expAccess, visitLog, tsInput.currentState[rowCount-1], tsInput.currentState[rowCount], tsInput.resAccessM[rowCount-1], ite, configArg.refMemDecay, configArg.attMemDecay);

				// Calculate attractions
				base_attraction=exp(configArg.fsLightIBeta*tsInput.lightI[rowCount-1]+
						configArg.fsLightRBeta*tsInput.lightR[rowCount-1]+
						configArg.fsLightAbsRBeta*tsInput.lightAbsR[rowCount-1]+
						configArg.fsMinDailyTemp*tsInput.minDayTemp[rowCount-1]);
				calculateAttractionM2(iterationResults, configArg, refMem, expAccess, base_attraction, tsInput.currentState[rowCount-1], tsInput.resAccessM[rowCount-1]);

				// Calculate probabilities
				calculateProbability(iterationResults, configArg, tsInput.currentState[rowCount-1]);

//				// Writing short output  (POINT AAA)
				short_output_prob[rowCount-1][0]=iterationResults.probability[0]; // for M
				short_output_prob[rowCount-1][1]=iterationResults.probability[1]; // for O
				short_output_prob[rowCount-1][2]=iterationResults.probability[2]; // for V

			    if(ite!=(TsMetrics.expIdCount[ind]-1))	// If last observation writing is different
			    	{
			    		extractedProb=extractProbability(iterationResults, tsInput.currentState[rowCount]);
					objectiveFunction=calculateObjFunction(objectiveFunction,extractedProb);
			    	}
			}
		}
	}


	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////


	// WRITING OUTPUTS
	if(short_output_writing==true)
    {
        std::string filePath_outputProb = configArg.outputDirectoryPath + "state_probabilities.csv";
        std::ofstream stateProbFile;
        stateProbFile.setf(std::ios::fixed, std::ios::floatfield);
        stateProbFile.precision(10);
        stateProbFile.setf(std::ios::scientific, std::ios::floatfield);
        stateProbFile.precision(5);
        stateProbFile.open(filePath_outputProb.c_str());
        stateProbFile << "exp_id;current_state;prob_M;prob_A;prob_V"<< endl;

		for(ite=0;ite<tsInput.currentState.size();ite++)
		{
	        stateProbFile << tsInput.expId[ite] << ";"<<
	        		tsInput.currentState[ite] << ";"<<
					short_output_prob[ite][0]<< ";"<<
					short_output_prob[ite][1]<< ";"<<
					short_output_prob[ite][2]<< endl;
		}
		stateProbFile.close();
    }

	writeObjFunction(objectiveFunction,configArg.outputDirectoryPath);


	///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////


	// WRAPPING UP
	time_t endTime = time(0);
	cout << "MODEL FITTING ENDS, run time: "<< endTime-iniTime << " seconds" << endl;
}
