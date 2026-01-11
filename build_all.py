import os
import subprocess
import sys

# Configuration
SOURCE_DIR = "."
OUTPUT_DIR = "bin"
COMPILER = "g++"

def compile_cpp_files():
    # Create output directory if it doesn't exist
    if not os.path.exists(OUTPUT_DIR):
        try:
            os.makedirs(OUTPUT_DIR)
            print(f"Created directory: {OUTPUT_DIR}")
        except OSError as e:
            print(f"Error creating directory {OUTPUT_DIR}: {e}")
            return

    # List all files in the source directory
    files = [f for f in os.listdir(SOURCE_DIR) if os.path.isfile(os.path.join(SOURCE_DIR, f))]

    cpp_files = [f for f in files if f.endswith(".cpp")]

    if not cpp_files:
        print("No .cpp files found to compile.")
        return

    print(f"Found {len(cpp_files)} C++ files. Starting compilation...\n")

    success_count = 0
    fail_count = 0

    for cpp_file in cpp_files:
        # Construct output executable path
        # Using .exe extension for Windows consistency
        exe_name = os.path.splitext(cpp_file)[0] + ".exe"
        output_path = os.path.join(OUTPUT_DIR, exe_name)

        # Build command: g++ filename.cpp -o bin/filename.exe
        command = [COMPILER, cpp_file, "-o", output_path]

        print(f"Compiling {cpp_file} -> {output_path}...")

        try:
            # Run the compilation command
            result = subprocess.run(command, text=True, capture_output=True)

            if result.returncode == 0:
                print(f"  [SUCCESS]")
                success_count += 1
            else:
                print(f"  [FAILED]")
                print(f"  Error output:\n{result.stderr}")
                fail_count += 1

        except FileNotFoundError:
            print(f"  [ERROR] '{COMPILER}' compiler not found. Is MinGW/G++ installed and in your PATH?")
            return
        except Exception as e:
            print(f"  [ERROR] An unexpected error occurred: {e}")
            fail_count += 1

    print("\nCompilation Summary:")
    print(f"  Successful: {success_count}")
    print(f"  Failed:     {fail_count}")

if __name__ == "__main__":
    compile_cpp_files()
