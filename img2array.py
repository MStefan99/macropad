from PIL import Image
import os
import sys
import re

INVERT_COLORS = False
THRESHOLD = 128  # 0-255 grayscale threshold for 1-bit conversion


def convert_image_to_c_array(in_file, out_file):
    try:
        img_name = re.sub(r"\.\w+$", "", os.path.basename(in_file))

        img = Image.open(in_file).convert('L')
        width, height = img.size

        pixels = list(img.getdata())

        hex_array = []
        current_word = 0
        bit_index = 0

        for pixel in pixels:
            is_white = pixel > THRESHOLD

            if not INVERT_COLORS:
                bit_value = 1 if is_white else 0
            else:
                bit_value = 0 if is_white else 1

            bit_position = 31 - ((3 - bit_index // 8) * 8 + bit_index % 8)
            current_word |= (bit_value << bit_position)
            bit_index += 1

            # When we hit 32 bits, save the word and reset
            if bit_index == 32:
                hex_array.append(f"0x{current_word:08x}")
                current_word = 0
                bit_index = 0

        # Chunk the array into rows of 8 for readability in the C header
        def chunk_array(lst, chunk_size):
            return [lst[i:i + chunk_size] for i in range(0, len(lst), chunk_size)]

        formatted_rows = [", ".join(chunk)
                          for chunk in chunk_array(hex_array, 8)]
        joined_array_content = ",\n    ".join(formatted_rows)

        c_array_string = f"""const uint32_t {img_name}[] = {{
    {joined_array_content}
}};
"""

        output_string = f"""// Generated from {in_file}
// Width: {width}px, Height: {height}px
#ifndef {img_name.upper()}_H
#define {img_name.upper()}_H
#include <stdint.h>

const uint32_t {img_name}_width = {width};
const uint32_t {img_name}_height = {height};

{c_array_string}

#endif
"""

        if out_file:
            with open(out_file, 'w') as f:
                f.write(output_string)
        else:
            print(c_array_string)

        print(
            f"Dimensions: {width}x{height} ({len(hex_array)} uint32_t elements)")
        print(f"Successfully converted {in_file}")
        if (out_file):
            print(f"Wrote data to {out_file}")

    except FileNotFoundError:
        print(f"Error: The file '{in_file}' was not found.")
    except Exception as e:
        print(f"Error processing image: {e}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise Exception("Input file is required")

    convert_image_to_c_array(
        sys.argv[1], sys.argv[2] if len(sys.argv) > 2 else None)
