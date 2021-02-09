# Ranc-et-al.-PNAS-2021

Publicly available dataset and program code for:

N. Ranc, P.R. Moorcroft, F. Ossi & F. Cagnacci. 2021. Memory drives foraging decisions in a large wild mammal: evidence from a field experiment. Proceedings of the National Academy of Sciences of the United States of America. https://doi.org/XXXXXXXXXXXXXX
<br> 
<br>
The C++ program calculates the likelihood of a given parameter set given the empirical time-series.\
<br>
<br>

## Inputs
1. **Ranc_et_al_2021_PNAS_data_population_ts.csv**: time-series
1. **Ranc_et_al_2021_PNAS_data_population_tslv.csv**: time since last visit and accessibility for initialization
1. **configuration_files**: input parameter values
<br>

### Ranc_et_al_2021_PNAS_data_population_ts.csv
This file stores the hourly state **time-series** for each animal-year as well as corresponding covariates. The file includes the following columns:
* **exp_id**: animal-year identifier (short code for experimental id)
* **current_state_code**: resource state currently utilized; 1 = manipulated feeding site (M); 2 = alternative feeding site (A); 3 = vegetation (V)
* **res_access_m**: accessibility of resources at the manipulated feeding site (M); 1 during pre-closure and post-closure; 0 during closure
* **light_i**: light intensity (standardized)
* **light_r**: light rate of change (standardized)
* **light_abs_r**: light absolute rate of change (standardized)
* **min_temp**: minimum daily temperature (standardized)

### Ranc_et_al_2021_PNAS_data_population_tslv.csv
This file stores the **time since last visit** and corresponding accessibility for each animal-year to be used for initialization purposes. The file includes the following columns:
* **exp_id**: animal-year identifier (short code for experimental id)
* **tslv_m**: time since last visit of M at the onset of the time-series (in hours)
* **tslv_a**: time since last visit of a at the onset of the time-series (in hours)
* **access_m**: resource accessibility at M in the last visit (1 = accessible; 0 = inaccessible)
* **access_a**: resource accessibility at A in the last visit (1 = accessible; 0 = inaccessible)

### Configuration files
The *Configuration_files* folder stores the configuration files required to reproduce the results of the six fitted models (the parameter values in the config files have been estimated through maximum likelihood):
* **config_omniscience_full.txt**: full population-level omniscience model
* **config_perception_full.txt**: full population-level perception model
* **config_memory_full.txt**: full population-level memory model

* **config_omniscience_best.txt**: best population-level omniscience model (does not include light_abs_r)
* **config_perception_best.txt**: best population-level perception model (does not include light_abs_r)
* **config_memory_best.txt**: best population-level memory model (does not include light_abs_r)

* **config_omniscience_best_medianInd.txt**: best median of individual-level omniscience models (does not include light_abs_r)
* **config_perception_best_medianInd.txt**: best median of individual-level perception models (does not include light_abs_r)
* **config_memory_best_medianInd.txt**: best median of individual-level memory models (does not include light_abs_r)

The configuration files list 15 parameters:
* **output_directory_path**: /Path/to/outputs/
* **time_series_path**: /Path/to/Ranc_et_al_2021_PNAS_data_population_ts.txt
* **initialization_data_path**: /Path/to/Ranc_et_al_2021_PNAS_data_population_tslv.txt
* **model_type**: 0 (omniscience), 1 (perception) or 3 (memory)
* **fs_light_i_beta**: selection coefficient for light intensity
* **fs_light_r_beta**: selection coefficient for light rate of change
* **fs_light_abs_r_beta**: selection coefficient light absolute rate of change
* **fs_min_daily_temp_beta**: selection coefficient for minimum daily temperature
* **fs_res_pres_beta**: between-state feeding site attraction intercept
* **fs_res_pres_within_beta**: within-state feeding site attraction intercept
* **fs_res_access_beta**: between-state selection for accessible feeding sites
* **fs_res_access_within_beta**: within-state selection for accessible feeding sites
* **manipulated_fs_pref**: preference for the manipulated (M) feeding site over alternates (A)
* **ref_decay_rate**: spatial (reference) memory decay rate [0,1]
* **att_decay_rate**: attribute memory decay rate [0,1]
<br>


## Outputs
The program produces two outputs:
* **objective_function**: log-likelihood of the model parameter set given the data
* **state_probabilities**: for each hourly record stores the current state, as well as the probabilities that the animal will be at any of the three states *in the next hour*
<br>


## Running instructions
To run the code, the program must first be compiled. For example, using the gcc compiler with an unix shell command line:

*cd /Path/to/code*
*g++ -std=c++11 Main.cpp Calculate_attraction.cpp Calculate_probability.cpp Likelihood.cpp Load_config_parameters.cpp Load_other_inputs.cpp Load_time_series.cpp Memory_dynamics.cpp -o roe_deer_program*

The program can then be called with a given configuration file; for example:
*./roe_deer_program -config /Path/to/config_memory_best.txt*

The program can then be called with any optimization algorithm to estimate the model parameters (MCMC, Particle Swarm Optimization, etc.).
