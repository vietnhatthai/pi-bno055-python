#include "bno055_wrapper.hpp"
#include <stdexcept>

extern "C" {
    #include "getbno055.h"
}

BNO055::BNO055(const std::string& i2c_bus, const std::string& address) 
    : i2c_bus_(i2c_bus), address_(address), initialized_(false) {
    get_i2cbus(const_cast<char*>(i2c_bus_.c_str()), const_cast<char*>(address_.c_str()));
    initialized_ = true;
}

BNO055::~BNO055() {}

void BNO055::reset() {
    if (bno_reset() != 0) {
        throw std::runtime_error("Failed to reset BNO055");
    }
}

void BNO055::set_mode(opmode_t mode) {
    if (::set_mode(mode) != 0) {
        throw std::runtime_error("Failed to set mode");
    }
}

void BNO055::set_mode_from_string(const std::string& mode) {
    opmode_t newmode;
    if (mode == "config") newmode = config;
    else if (mode == "acconly") newmode = acconly;
    else if (mode == "magonly") newmode = magonly;
    else if (mode == "gyronly") newmode = gyronly;
    else if (mode == "accmag") newmode = accmag;
    else if (mode == "accgyro") newmode = accgyro;
    else if (mode == "maggyro") newmode = maggyro;
    else if (mode == "amg") newmode = amg;
    else if (mode == "imu") newmode = imu;
    else if (mode == "compass") newmode = compass;
    else if (mode == "m4g") newmode = m4g;
    else if (mode == "ndof") newmode = ndof;
    else if (mode == "ndof_fmc") newmode = ndof_fmc;
    else throw std::invalid_argument("Invalid mode");

    set_mode(newmode);
}

std::string BNO055::get_mode() const {
    int mode = ::get_mode();
    switch(mode) {
        case config: return "config";
        case acconly: return "acconly";
        case magonly: return "magonly";
        case gyronly: return "gyronly";
        case accmag: return "accmag";
        case accgyro: return "accgyro";
        case maggyro: return "maggyro";
        case amg: return "amg";
        case imu: return "imu";
        case compass: return "compass";
        case m4g: return "m4g";
        case ndof: return "ndof";
        case ndof_fmc: return "ndof_fmc";
        default: return "unknown";
    }
}

void BNO055::set_power_mode(const std::string& mode) {
    power_t newmode;
    if (mode == "normal") newmode = normal;
    else if (mode == "low") newmode = low;
    else if (mode == "suspend") newmode = suspend;
    else throw std::invalid_argument("Invalid power mode");

    if (::set_power(newmode) != 0) {
        throw std::runtime_error("Failed to set power mode");
    }
}

std::string BNO055::get_power_mode() const {
    int mode = ::get_power();
    switch(mode) {
        case normal: return "normal";
        case low: return "low";
        case suspend: return "suspend";
        default: return "unknown";
    }
}

BNO055::EulerAngles BNO055::get_euler() {
    struct bnoeul data;
    if (get_eul(&data) != 0) {
        throw std::runtime_error("Failed to get euler angles");
    }
    return {data.eul_head, data.eul_roll, data.eul_pitc};
}

BNO055::Quaternion BNO055::get_quaternion() {
    struct bnoqua data;
    if (get_qua(&data) != 0) {
        throw std::runtime_error("Failed to get quaternion");
    }
    return {data.quater_w, data.quater_x, data.quater_y, data.quater_z};
}

BNO055::Vector3 BNO055::get_accelerometer() {
    struct bnoacc data;
    if (get_acc(&data) != 0) {
        throw std::runtime_error("Failed to get accelerometer data");
    }
    return {data.adata_x, data.adata_y, data.adata_z};
}

BNO055::Vector3 BNO055::get_magnetometer() {
    struct bnomag data;
    if (get_mag(&data) != 0) {
        throw std::runtime_error("Failed to get magnetometer data");
    }
    return {data.mdata_x, data.mdata_y, data.mdata_z};
}

BNO055::Vector3 BNO055::get_gyroscope() {
    struct bnogyr data;
    if (get_gyr(&data) != 0) {
        throw std::runtime_error("Failed to get gyroscope data");
    }
    return {data.gdata_x, data.gdata_y, data.gdata_z};
}

BNO055::Vector3 BNO055::get_gravity() {
    struct bnogra data;
    if (get_gra(&data) != 0) {
        throw std::runtime_error("Failed to get gravity data");
    }
    return {data.gravityx, data.gravityy, data.gravityz};
}

BNO055::Vector3 BNO055::get_linear_acceleration() {
    struct bnolin data;
    if (get_lin(&data) != 0) {
        throw std::runtime_error("Failed to get linear acceleration data");
    }
    return {data.linacc_x, data.linacc_y, data.linacc_z};
}

bool BNO055::is_fully_calibrated() const {
    struct bnocal cal;
    if (get_calstatus(&cal) != 0) {
        throw std::runtime_error("Failed to get calibration status");
    }
    return cal.scal_st == 3;
}

void BNO055::save_calibration(const std::string& filename) {
    if (save_cal(const_cast<char*>(filename.c_str())) != 0) {
        throw std::runtime_error("Failed to save calibration");
    }
}

void BNO055::load_calibration(const std::string& filename) {
    if (load_cal(const_cast<char*>(filename.c_str())) != 0) {
        throw std::runtime_error("Failed to load calibration");
    }
}
