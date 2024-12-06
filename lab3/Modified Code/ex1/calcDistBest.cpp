#include <math.h>
#include "calcDist.h"


void calcDistancesHW(float* data_hw, float* dists_hw)
{
	float data_hw_tmp[MOVIES_NUM][USERS_NUM];
	float movie_tmp[USERS_NUM];
	float dists_hw_tmp[MOVIES_NUM];

#pragma HLS ARRAY_PARTITION variable=data_hw_tmp block factor=2 dim=1
#pragma HLS ARRAY_PARTITION variable=movie_tmp block factor=2 dim=1
#pragma HLS ARRAY_PARTITION variable=dists_hw_tmp block factor=2 dim=1


LOAD_DATA_HW_TMP:
	for (int i = 0; i < MOVIES_NUM; i++) {
#pragma HLS PIPELINE II=1
		for (int j = 0; j < USERS_NUM; j++) {
#pragma HLS PIPELINE II=1
			data_hw_tmp[i][j] = data_hw[i * USERS_NUM + j];
		}
	}

LOAD_MOVIE_TMP:
	for (int i = 0; i < USERS_NUM; i++){
#pragma HLS PIPELINE II=1
		movie_tmp[i] = data_hw_tmp[MOVIE_ID][i];
	}

COMPUTE_DISTS:
	for (int i = 0; i < MOVIES_NUM; i++) {
#pragma HLS PIPELINE II=1
		float sum = 0.0, diff = 0.0;
		for (int j = 0; j < USERS_NUM; j++){
#pragma HLS PIPELINE II=1
			diff = data_hw_tmp[i][j] - movie_tmp[j];
			sum += diff * diff;
		}
		dists_hw_tmp[i] = sqrt(sum);
	}

WRITE_DISTS:
	for (int i = 0; i < MOVIES_NUM; i++) {
#pragma HLS PIPELINE II=1
		dists_hw[i] = dists_hw_tmp[i];
	}
}
