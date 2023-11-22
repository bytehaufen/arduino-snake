#!/usr/bin/env python3

# Python3 script to convert a RGB png image to a C array
# for the Adafruit GFX library

import argparse
from PIL import Image


def convert_image_to_adafruit_array(input_file, output_file):
    namespaceName: str = output_file
    namespaceName = namespaceName[namespaceName.rfind("/") + 1 :].replace(".h", "")

    img = Image.open(input_file)
    img = img.convert("RGB")

    width, height = img.size
    data = img.load()

    output = []

    for y in range(height):
        for x in range(width):
            r, g, b = data[x, y]
            color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
            output.append(color)

    with open(output_file, "w") as f:
        f.write(f"#ifndef {namespaceName.upper()}_H\n")
        f.write(f"#define {namespaceName.upper()}_H\n\n")
        f.write("#include <stdint.h>\n")
        f.write("#include <avr/pgmspace.h>\n\n")
        f.write(f"namespace {namespaceName} {{\n")
        f.write(f"const int image_width = {width};\n")
        f.write(f"const int image_height = {height};\n\n")
        f.write("const uint16_t image_data[image_width * image_height] PROGMEM = {\n")
        for i, color in enumerate(output):
            f.write(f"  0x{color:04X}")
            if i != len(output) - 1:
                f.write(",")
            if (i + 1) % width == 0:
                f.write("\n")
        f.write("};\n")
        f.write(f"}} // namespace {namespaceName}\n\n")
        f.write(f"#endif // {namespaceName.upper()}_H\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Convert image to Adafruit-compatible uint16_t array"
    )
    parser.add_argument("input", help="Input image file name")
    parser.add_argument("output", help="Output array file name")

    args = parser.parse_args()

    convert_image_to_adafruit_array(args.input, args.output)
