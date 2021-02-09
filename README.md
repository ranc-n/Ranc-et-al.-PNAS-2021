# Ranc-et-al.-PNAS-2021

Publicly available dataset and code for:

N. Ranc, P.R. Moorcroft, F. Ossi & F. Cagnacci. 2021. Memory drives foraging decisions in a large wild mammal: evidence from a field experiment. Proceedings of the National Academy of Sciences of the United States of America. https://doi.org/XXXXXXXXXXXXXX

The C++ program calculates the likelihood of a given parameter set given the empirical time-series.

## Inputs
1. Ranc_et_al_2021_PNAS_data_population_ts.csv: time-series
1. Ranc_et_al_2021_PNAS_data_population_tslv.csv: time since last visit and accessibility for initialization
1. configuration_file.txt: provides the parameters

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


## Outputs

## Running instructions


