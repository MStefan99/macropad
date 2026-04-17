import socketserver
import subprocess
import http.server
import serial
import serial.tools.list_ports
from threading import Thread
import time
import platform
import os
import json
import re

current_app = ""
current_profile = "sys"
port = None

WEB_PORT = 6227
MACROPAD_VID = 0x239A  # Adafruit VID
MACROPAD_PID = 0x8106  # Macropad RP2040 PID
BAUD_RATE = 115200


class Server(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        self.send_response(404)
        self.end_headers()
        self.wfile.write(b"Only POST requests are supported\n")

    def do_POST(self):
        content_length = int(self.headers['Content-Length'])
        profile = self.headers['Profile']
        data = self.rfile.read(content_length)[0:64].decode('utf-8')
        print(f"Requested to send \"{data}\" from profile \"{profile}\"")

        if profile != current_profile:
            self.send_response(400)
            self.end_headers()
            self.wfile.write(b"App not active\n")
            print(
                f"Profile \"{profile}\" is not active. Active profile is \"{current_profile}\"")

        elif port:
            try:
                port.write(f"d>{data}\n".encode(
                    'ascii', errors='backslashreplace'))
                print(f"Profile \"{profile}\" sent \"{data}\" to Macropad")
                time.sleep(0.25)
                self.send_response(200)
                self.end_headers()
                response = port.read(port.in_waiting).decode(
                    'ascii', errors='ignore').strip()
                res = re.search(r"^d>(.+)", response)
                if res:
                    print(
                        f"Profile \"{profile}\" received \"{res.group(1)}\" from Macropad")
                    self.wfile.write(f"{res.group(1)}\n".encode('utf-8'))
                else:
                    print("Macropad did not respond")
                    self.wfile.write(b"")

            except Exception as e:
                self.send_response(500)
                self.end_headers()
                self.wfile.write(f"{str(e)}\n".encode('utf-8'))
                print(f"Error sending data to Macropad: {e}")

        else:
            self.send_response(500)
            self.end_headers()
            self.wfile.write(b"Macropad not connected\n")
            print("Macropad not connected")

    def log_message(self, format, *args):
        pass  # Logging above


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
        port.write(f"p>{exe_name}\n".encode(
            'ascii', errors='backslashreplace'))
        print(f"Switching profile to \"{exe_name}\"")

        time.sleep(0.1)
        if port.in_waiting > 0:
            response = port.read(port.in_waiting).decode(
                'ascii', errors='ignore').strip()
            res = re.search(r"^p(\S)(\w+)", response)

            try:
                if response == "p-":
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
                current_profile = res.group(2)
            except Exception as e:
                print(f"Macropad sent an unknown message: {response}")

    except Exception as e:
        print(f"Serial error: {e}")


if __name__ == "__main__":
    print(f"Monitoring active applications...")

    with socketserver.TCPServer(("127.0.0.1", WEB_PORT), Server) as httpd:
        print(f"Web server started on port {WEB_PORT}")
        try:
            thread = Thread(target=httpd.serve_forever, daemon=True)
            thread.start()

            while True:
                target_port_path = find_macropad_port(
                    MACROPAD_VID, MACROPAD_PID)

                if not port:
                    if target_port_path:
                        try:
                            port = serial.Serial(
                                target_port_path, BAUD_RATE, timeout=1)
                            print(
                                f"Connected to Macropad at {target_port_path}")
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
                        send_over_serial(exe_name[0:64])

                time.sleep(1)

        except KeyboardInterrupt:
            httpd.server_close()
            if port:
                port.close()
