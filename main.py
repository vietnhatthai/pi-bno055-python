#!/usr/bin/env python3

import sys
import time

try:
    from bno055 import BNO055
except ImportError as e:
    print("Error: Could not import bno055 module")
    print("Make sure the module is installed or the build directory is in PYTHONPATH")
    print(f"Original error: {e}")
    sys.exit(1)

def main():
    try:
        # Create sensor object
        sensor = BNO055(address='0x29')
        
        # Set the sensor mode to NDOF (9-DOF fusion)
        print("Setting sensor mode to NDOF...")
        sensor.set_mode("ndof")
        
        print("Starting sensor readings...")
        while True:
            try:
                # Read Euler angles
                euler = sensor.get_euler()
                print(f"\rEuler angles - Heading: {euler.heading:6.2f}°, Roll: {euler.roll:6.2f}°, Pitch: {euler.pitch:6.2f}°", end='')
                
                time.sleep(0.1)
                
            except KeyboardInterrupt:
                print("\nExiting...")
                break
            except Exception as e:
                print(f"\nError reading sensor: {e}")
                time.sleep(1)
                
    except Exception as e:
        print(f"Error initializing sensor: {e}")
        return 1
    
    return 0

if __name__ == "__main__":
    sys.exit(main())
