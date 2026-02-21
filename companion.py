import subprocess
import serial
import time
import os

current_app = ""
port = None


def get_active_window_title():
  try:
    result = subprocess.check_output(['kdotool', 'getactivewindow', 'getwindowclassname'], universal_newlines=True)
    title = result.strip().split('.')[-1]
    return title
  except subprocess.CalledProcessError as e:
    print(f"Error getting window title: {e}")
    return None
  except FileNotFoundError:
    print("kdotool not found.  Please make sure it is installed.")
    return None


def send_over_serial(title):
  try:
    command = f"a>{title}"
    port.write(command.encode('utf-8'))
    port.write(b'\n')
    print(f"Opening {title}")

    time.sleep(0.1)
    if port.in_waiting > 0:
      response = port.read(port.in_waiting).decode('utf-8', errors='ignore').strip();
      print(f"Received from macropad: {response}")

  except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
  except Exception as e:
    print(f"An unexpected error occurred: {e}")


if __name__ == "__main__":
  SERIAL_PORT = "/dev/ttyACM0"
  BAUD_RATE = 115200
  SLEEP_INTERVAL = 1

  try:
    while True:
      if not port:
        try:
          if os.path.exists(SERIAL_PORT):
            port = serial.Serial(SERIAL_PORT, BAUD_RATE)
            print(f"Connected to {SERIAL_PORT}")
        except Exception as e:
          printf(f"Could not connect to {SERIAL_PORT}: {e}")
          pass

      elif not os.path.exists(SERIAL_PORT):
        port.close()
        port = None
        current_app = ""
        print(f"Disconnected from {SERIAL_PORT}")

      else:
        window_title = get_active_window_title()

        if window_title:
          if (window_title != current_app):
            current_app = window_title
            send_over_serial(window_title)

      time.sleep(SLEEP_INTERVAL)

  except Exception as e:
    print(f"An unexpected error occurred: {e}")
    port.close()
