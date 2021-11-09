#include <Wire.h>
#include <math.h>
int mpu = 0x68; // I2C address of the MPU-6050
long AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
float gX, gY, gZ, rX, rY, rZ;
void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
 Wire.begin();
 Wire.beginTransmission(mpu);
 Wire.write(0x6B);
 Wire.write(0);
 Wire.endTransmission(true);
 pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
 // put your main code here, to run repeatedly:
 getAcceleration();
 getGyro();
 printMat();
 delay(33);
}
void getAcceleration()
{
 Wire.beginTransmission(mpu);
 Wire.write(0x3B);
 Wire.endTransmission(false);
 Wire.requestFrom(mpu, 14, true);
 AcX = Wire.read()<<8|Wire.read();
 AcY = Wire.read()<<8|Wire.read();
 AcZ = Wire.read()<<8|Wire.read();
 gX = AcX / 16384.0;
 gY = AcY / 16384.0;
 gZ = AcZ / 16384.0;
}
void getGyro()
{
 Tmp = Wire.read()<<8|Wire.read();
 GyX = Wire.read()<<8|Wire.read();
 GyY = Wire.read()<<8|Wire.read();
 GyZ = Wire.read()<<8|Wire.read();
 rX = GyX / 131.0;
 rY = GyY / 131.0;
 rZ = GyZ / 131.0;
}
void printMat()
{
 Serial.print("X (g) = ");
 Serial.print(gX);
 Serial.print("Y (g) = ");
 Serial.print(gY);
 Serial.print("Z (g) = ");
 Serial.print(gZ);
 Serial.print("X (deg) =");
 Serial.print(rX);
 Serial.print("Y (deg) =");
 Serial.print(rY);
 Serial.print("Z (deg) =");
 Serial.print(rZ);
 Serial.println(" ");
}
