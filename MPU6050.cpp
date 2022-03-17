#include <MPU6050.h>
#include <Wire.h>

int addr;
int AcX,AcY,AcZ;
int rx, ry, rz;
int min = 265, max = 402;
double x, y, z;

void MPU6050::begin(int add, int val){
	addr = add;
	Wire.begin();
	Wire.beginTransmission(addr);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Wire.beginTransmission(addr);
    Wire.write(0x1A);
    Wire.write(val);
    Wire.endTransmission(true);
}

void MPU6050::read(){
	Wire.beginTransmission(addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(addr,8,true);
  
    rx=Wire.read()<<8|Wire.read();
    ry=Wire.read()<<8|Wire.read();
    rz=Wire.read()<<8|Wire.read();
  
    AcX = map(rx,min,max,-90,90); //設定分量在90~-90
    AcY = map(ry,min,max,-90,90); //固定比例
    AcZ = map(rz,min,max,-90,90);
   
    x= RAD_TO_DEG * (atan2(-AcY, -AcZ)+PI); //取tan^-1 -> 角度
    y= RAD_TO_DEG * (atan2(-AcX, -AcZ)+PI);
    z= RAD_TO_DEG * (atan2(-AcY, -AcX)+PI);

    if(x>180)x -= 360;
    if(y>180)y -= 360;
    if(z>180)z -= 360;
}

int MPU6050::Xaxis(){
	return int(x);
}

int MPU6050::Yaxis(){
	return int(y);
}

int MPU6050::Zaxis(){
	return int(z);
}

int MPU6050::Xraw(){
    return int(rx);
}

int MPU6050::Yraw(){
    return int(ry);
}

int MPU6050::Zraw(){
    return int(rz);
}