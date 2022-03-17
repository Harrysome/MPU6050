#ifndef MPU6050_H
#define MPU6050_H

#include <Arduino.h>

struct MPU6050{
	void begin(int add, int val);  //change the sensitivity
	void read();
	int Xaxis();  //return DEG num from 180 ~ -180
	int Yaxis();
	int Zaxis();
	int Xraw();  //return the raw accel num
	int Yraw();
	int Zraw();
};

#endif