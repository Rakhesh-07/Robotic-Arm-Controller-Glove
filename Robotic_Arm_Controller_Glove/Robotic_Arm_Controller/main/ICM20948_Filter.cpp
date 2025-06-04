#include "ICM20948_Filter.h"

#define FILTER_UPDATE_RATE_HZ 100  // Adjust as needed for responsiveness
#define ALPHA 0.25  // Complementary filter constant for pitch and roll 0-1. Lower value = faster return speed

ICM20948Filter::ICM20948Filter() : pitch(0), roll(0), yaw(0) {}

// Initialization
bool ICM20948Filter::begin() {
    if (!icm.begin_I2C()) {
        return false;
    }

    icm.setAccelRange(ICM20948_ACCEL_RANGE_4_G);
    icm.setGyroRange(ICM20948_GYRO_RANGE_500_DPS);
    icm.setAccelRateDivisor(0);  // Max performance mode
    icm.setGyroRateDivisor(0);   // Max performance mode

    return true;
}

// Update the sensor readings for accel, gyro, mag
void ICM20948Filter::update() {
    sensors_event_t accel, gyro, mag, temp;
    icm.getEvent(&accel, &gyro, &temp, &mag);
    calculateOrientation(accel, gyro);
}

// Calculations for pitch, yaw, and roll using accelerometer and gyroscope
void ICM20948Filter::calculateOrientation(sensors_event_t& accel, sensors_event_t& gyro) {
    //declare accelerometer readings
    float ax = accel.acceleration.x;
    float ay = accel.acceleration.y;
    float az = accel.acceleration.z;

    // Calculate acceleration for pitch and roll
    float accelPitch = atan2(ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
    float accelRoll = atan2(ay, sqrt(ax * ax + az * az)) * 180.0 / PI;

    // Calculate gyroscope reading for pitch and roll, convert to degrees
    float gyroPitchRate = gyro.gyro.x * 180.0 / PI;
    float gyroRollRate = gyro.gyro.y * 180.0 / PI;

    // Tilt-compensated gyro yaw rate
    float sinPitch = sin(pitch * PI / 180);
    float cosPitch = cos(pitch * PI / 180);
    float sinRoll = sin(roll * PI / 180);
    float cosRoll = cos(roll * PI / 180);

    // Calculate yaw using pitch and roll and gyroscope
    float gyroYawRate = ((gyro.gyro.z * cosPitch) - (gyro.gyro.y * sinRoll * sinPitch) + (gyro.gyro.x * cosRoll * sinPitch)) * 180.0 / PI;

    // Apply complementary filter for pitch and roll
    pitch = ALPHA * (pitch + gyroPitchRate / FILTER_UPDATE_RATE_HZ) + (1 - ALPHA) * accelPitch;
    roll = ALPHA * (roll + gyroRollRate / FILTER_UPDATE_RATE_HZ) + (1 - ALPHA) * accelRoll;

    // Complementary filter for yaw to prevent jitteriness and drift
    if (abs(gyroYawRate) > 10) {  // If movement is big
        yaw += (gyroYawRate / 10);  // Slowly reduce drift
    }

} 

// Change the return values depending on the orientation of the ICM-20948
float ICM20948Filter::getPitch() const { return roll; }
float ICM20948Filter::getRoll() const { return pitch; }
float ICM20948Filter::getYaw() const { return yaw; }