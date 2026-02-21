import subprocess
import serial
import serial.tools.list_ports
import time
import platform
import os

current_app = ""
port = None


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
    SERIAL_PORT = "COM4" if platform.system() == "Windows" else "/dev/ttyACM0"
    BAUD_RATE = 115200

    print(f"Monitoring active applications. Sending to {SERIAL_PORT}...")

    try:
        while True:
            available_ports = [
                p.device for p in serial.tools.list_ports.comports()]

            if not port:
                if SERIAL_PORT in available_ports:
                    try:
                        port = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
                        print(f"Connected to {SERIAL_PORT}")
                    except:
                        pass
            elif SERIAL_PORT not in available_ports:
                port.close()
                port = None
                current_app = ""
                print("Disconnected.")
            else:
                exe_name = get_active_executable()
                if exe_name and exe_name != current_app:
                    current_app = exe_name
                    send_over_serial(exe_name)

            time.sleep(1)

    except KeyboardInterrupt:
        if port:
            port.close()
