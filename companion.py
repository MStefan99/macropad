import subprocess
import serial
import serial.tools.list_ports
import time
import platform
import os
import json
import sys

current_app = ""
port = None


def map_app_to_alias(app_name, alias_file="aliases.json"):
    try:
        with open(alias_file, 'r') as f:
            aliases = json.load(f)
        if app_name in aliases:
            return aliases[app_name]
        else:
            return app_name
    except FileNotFoundError:
        return app_name
    except json.JSONDecodeError:
        return app_name
    except Exception as e:
        return app_name


def get_active_executable():
    system = platform.system()

    try:
        if system == "Windows":
            import ctypes
            from ctypes import wintypes

            # Load necessary Windows DLLs
            user32 = ctypes.windll.user32
            kernel32 = ctypes.windll.kernel32
            psapi = ctypes.windll.psapi

            # 1. Get the handle of the foreground window
            hwnd = user32.GetForegroundWindow()
            if not hwnd:
                return None

            # 2. Get the Process ID (PID) from the window handle
            pid = wintypes.DWORD()
            user32.GetWindowThreadProcessId(hwnd, ctypes.byref(pid))

            # 3. Open the process to query its information
            # PROCESS_QUERY_INFORMATION (0x0400) | PROCESS_VM_READ (0x0010)
            process_handle = kernel32.OpenProcess(0x0400 | 0x0010, False, pid)

            if not process_handle:
                return None

            # 4. Get the executable path
            buffer = ctypes.create_unicode_buffer(MAX_PATH := 260)
            psapi.GetModuleFileNameExW(process_handle, None, buffer, MAX_PATH)
            kernel32.CloseHandle(process_handle)

            # Return just the filename without ".exe" (e.g., 'explorer')
            return os.path.basename(buffer.value).lower().replace('.exe', '')

        else:
            # Linux Logic (assuming kdotool)
            # 1. Get the PID of the active window
            pid = subprocess.check_output(['kdotool', 'getactivewindow', 'getwindowpid'],
                                          universal_newlines=True).strip()

            # 2. Read the symlink in /proc to find the executable path
            exe_path = os.readlink(f"/proc/{pid}/exe")
            return os.path.basename(exe_path).lower()

    except Exception as e:
        print(f"Error: {e}")
        return None


def send_over_serial(exe_name):
    try:
        command = f"a>{exe_name}"
        port.write(command.encode('utf-8'))
        port.write(b'\n')
        print(f"Switching profile to: {exe_name}")

        time.sleep(0.1)
        if port.in_waiting > 0:
            response = port.read(port.in_waiting).decode(
                'utf-8', errors='ignore').strip()
            print(f"Macropad says: {response}")

    except Exception as e:
        print(f"Serial error: {e}")


if __name__ == "__main__":
    BAUD_RATE = 115200

    if (len(sys.argv) <= 1):
        raise Exception("Serial port name must be provided as an argument")

    serial_port = sys.argv[1]

    print(f"Monitoring active applications. Sending to {serial_port}...")

    try:
        while True:
            available_ports = [
                p.device for p in serial.tools.list_ports.comports()]

            if not port:
                if serial_port in available_ports:
                    try:
                        port = serial.Serial(serial_port, BAUD_RATE, timeout=1)
                        print(f"Connected to {serial_port}")
                    except:
                        pass
            elif serial_port not in available_ports:
                port.close()
                port = None
                current_app = ""
                print("Disconnected.")
            else:
                exe_name = map_app_to_alias(get_active_executable())
                if exe_name and exe_name != current_app:
                    current_app = exe_name
                    send_over_serial(exe_name)

            time.sleep(1)

    except KeyboardInterrupt:
        if port:
            port.close()
