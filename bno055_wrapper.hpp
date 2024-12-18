#ifndef BNO055_WRAPPER_HPP
#define BNO055_WRAPPER_HPP

#include <string>

extern "C" {
    #include "getbno055.h"
}

class BNO055 {
public:
    BNO055(const std::string& i2c_bus = "/dev/i2c-1", const std::string& address = "0x28");
    ~BNO055();

    // Device management
    void reset();
    void set_mode(::opmode_t mode);
    void set_mode_from_string(const std::string& mode);
    std::string get_mode() const;
    void set_power_mode(const std::string& mode);
    std::string get_power_mode() const;

    // Data reading
    struct EulerAngles {
        double heading;
        double roll;
        double pitch;
    };

    struct Quaternion {
        double w;
        double x;
        double y;
        double z;
    };

    struct Vector3 {
        double x;
        double y;
        double z;
    };

    // Sensor data methods
    EulerAngles get_euler();
    Quaternion get_quaternion();
    Vector3 get_accelerometer();
    Vector3 get_magnetometer();
    Vector3 get_gyroscope();
    Vector3 get_gravity();
    Vector3 get_linear_acceleration();

    // Calibration
    bool is_fully_calibrated() const;
    void save_calibration(const std::string& filename);
    void load_calibration(const std::string& filename);

private:
    std::string i2c_bus_;
    std::string address_;
    bool initialized_;
};

#endif // BNO055_WRAPPER_HPP