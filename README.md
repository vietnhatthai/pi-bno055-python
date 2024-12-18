# BNO055 Python Interface for Raspberry Pi

This is a Python interface for the Bosch BNO055 9-DOF IMU sensor, built on top of the pi-bno055 C library. Optimized for use with Raspberry Pi.

## Requirements

### Hardware

- Raspberry Pi (any model with I2C support)
- BNO055 IMU sensor
- I2C connection:
  - BNO055 SDA -> Raspberry Pi GPIO2 (Pin 3)
  - BNO055 SCL -> Raspberry Pi GPIO3 (Pin 5)
  - BNO055 VIN -> 3.3V
  - BNO055 GND -> GND

### Software

- Raspberry Pi OS (or other compatible Linux distribution)
- Python 3.x with development headers
- CMake 3.4 or higher
- pybind11
- Required packages:

```bash
sudo apt-get update
sudo apt-get install -y python3-dev cmake build-essential libi2c-dev i2c-tools
```

## Raspberry Pi Setup

1. Enable I2C interface:

```bash
sudo raspi-config
# Navigate to: Interface Options -> I2C -> Enable
```

1. Add your user to the i2c group:

```bash
sudo usermod -a -G i2c $USER
```

1. Verify I2C device detection:

```bash
sudo i2cdetect -y 1
# You should see the BNO055 device (usually at address 0x28 or 0x29)
```

## Installation

1. Clone the repository:

```bash
git clone https://github.com/vietnhatthai/pi-bno055-python.git
cd pi-bno055-python
```

2. Build and install:

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

## Usage

```python
from bno055 import BNO055

# Create sensor object (default: /dev/i2c-1, address 0x28)
sensor = BNO055()

# Optional: specify different I2C bus or address
# sensor = BNO055(i2c_bus="/dev/i2c-1", address="0x29")

# Set operation mode (options: ndof, imu, compass, m4g, etc.)
sensor.set_mode("ndof")

# Read sensor data
euler = sensor.get_euler()
print(f"Heading: {euler.heading}°")
print(f"Roll: {euler.roll}°")
print(f"Pitch: {euler.pitch}°")

# Other available methods:
# sensor.get_quaternion()
# sensor.get_accelerometer()
# sensor.get_magnetometer()
# sensor.get_gyroscope()
# sensor.get_gravity()
# sensor.get_linear_acceleration()
```

## Troubleshooting

1. I2C Not Detected:
   - Verify wiring connections
   - Check if I2C is enabled: `ls -l /dev/i2c*`
   - Verify device address: `sudo i2cdetect -y 1`

2. Permission Denied:
   - Ensure user is in i2c group: `groups`
   - Logout and login again after adding to group
   - Check device permissions: `ls -l /dev/i2c-1`

3. Build Errors:
   - Ensure all dependencies are installed
   - Check CMake version: `cmake --version`
   - Verify Python development headers are installed

## Contributing

Feel free to submit issues and pull requests.

## Credits

This project is based on [pi-bno055](https://github.com/fm4dd/pi-bno055) by Frank4DD. The original C implementation has been wrapped with pybind11 to create a Python-friendly interface.

## License

This project inherits the license from the original pi-bno055 project by Frank4DD.

## See Also

- [Original pi-bno055 Repository](https://github.com/fm4dd/pi-bno055)
- [BNO055 Product Page](https://www.bosch-sensortec.com/products/smart-sensors/bno055/)
- [BNO055 Datasheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bno055-ds000.pdf)
