#!/usr/bin/env python3

# ***************************************************************************
# 8 channel pin signal(HIGH) delay(er) - debian linux python3 part
# - by Philipp Rauch - VigilanteSystems - opensource - 23.03.2023
# ***************************************************************************
# It delays signals from 8 channel parallel port signals to relays
# to avoid toggling relays at system reboot/bootup etc ... bootup toggle...
# ***************************************************************************

import sys
import os.path
import parallel

# Define constants for pin numbers
PIN_DATA_START = 2
PIN_DATA_END = 9

# Define constants for pin values
PIN_LOW = 0
PIN_HIGH = 1

# Define constants for the last state file
LAST_STATE_FILE = os.path.join(os.path.dirname(__file__), "last_state.txt")

# Open LPT1 or /dev/parport0
p = parallel.Parallel()

# Define a mapping of pin numbers to corresponding bit masks
PIN_MASKS = {pin: 2 ** (pin - PIN_DATA_START) for pin in range(PIN_DATA_START, PIN_DATA_END + 1)}

# Initialize last data to all zeroes
last_data = 0

# Load the last state from file
if os.path.isfile(LAST_STATE_FILE):
    with open(LAST_STATE_FILE, "r") as f:
        last_data = int(f.read().strip())

def setPin(pin, value):
    global last_data

    if pin not in PIN_MASKS:
        raise ValueError("invalid pin number")

    bit_mask = PIN_MASKS[pin]
    last_data = (last_data & (255 - bit_mask)) | (bit_mask if value == PIN_HIGH else 0)
    p.setData(last_data)

    print(f"Pin {pin} set to {value}")
    print(f"Current data: {bin(last_data)[2:].zfill(8)}")

    # Save the new state to file
    with open(LAST_STATE_FILE, "w") as f:
        f.write(str(last_data))

if len(sys.argv) < 3:
    print("Please provide pin and value as arguments.")
    sys.exit(1)

pin = int(sys.argv[1])
value = sys.argv[2].upper()

if value == "HIGH":
    setPin(pin, PIN_HIGH)
elif value == "LOW":
    setPin(pin, PIN_LOW)
else:
    print("Invalid value. Please enter 'HIGH' or 'LOW'.")
