import subprocess
import serial
import serial.tools.list_ports
import time
import platform
import os
import json
import sys
import re

current_app = ""
port = None

MACROPAD_VID = 0x239A  # Adafruit VID
MACROPAD_PID = 0x8106  # Macropad RP2040 PID
BAUD_RATE = 115200


def find_macropad_port(vid, pid):
    for p in serial.tools.list_ports.comports():
        if p.vid == vid and p.pid == pid:
            return p.device
    return None


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
        print(f"Switching profile to \"{exe_name}\"")

        time.sleep(0.1)
        if port.in_waiting > 0:
            response = port.read(port.in_waiting).decode(
                'utf-8', errors='ignore').strip()
            res = re.search(r"^a(\S)(\w+)", response)

            if response == "a-":
                print("Macropad cannot switch profiles right now")
            elif res.group(1) == "=":
                print(f"Macropad found and switched to \"{res.group(2)}\"")
            elif res.group(1) == ":":
                print(
                    f"Macropad found and is already using \"{res.group(2)}\"")
            elif res.group(1) == "!":
                print(
                    f"Macropad couldn't find \"{exe_name}\" and switched to \"{res.group(2)}\"")
            elif res.group(1) == "~":
                print(
                    f"Macropad couldn't find \"{exe_name}\" and is already using \"{res.group(2)}\"")
            else:
                print("Macropad sent unknown status")

    except Exception as e:
        print(f"Serial error: {e}")


if __name__ == "__main__":
    print(f"Monitoring active applications...")

    try:
        while True:
            target_port_path = find_macropad_port(MACROPAD_VID, MACROPAD_PID)

            if not port:
                if target_port_path:
                    try:
                        port = serial.Serial(
                            target_port_path, BAUD_RATE, timeout=1)
                        print(f"Connected to Macropad at {target_port_path}")
                    except Exception as e:
                        print(f"Port found but could not connect: {e}")

            elif port and not target_port_path:
                port.close()
                port = None
                current_app = ""
                print("Macropad disconnected. Waiting for reconnection...")

            else:
                exe_name = map_app_to_alias(get_active_executable())
                if exe_name and exe_name != current_app:
                    current_app = exe_name
                    send_over_serial(exe_name)

            time.sleep(1)

    except KeyboardInterrupt:
        if port:
            port.close()
