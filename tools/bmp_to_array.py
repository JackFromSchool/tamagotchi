import sys
import os

if len(sys.argv) > 2 or len(sys.argv) == 1:
    print("Please supply an image to convert!")
    exit(0)

file_path = sys.argv[1]
base_name = os.path.basename(file_path)
file_name = os.path.splitext(base_name)[0]

image = open(file_path, "rb")

image.read(2)  # ID
size = int.from_bytes(image.read(4), 'little')
image.read(4)
offset = int.from_bytes(image.read(4), 'little')
image.read(4)
width = int.from_bytes(image.read(4), 'little')
height = int.from_bytes(image.read(4), 'little')
padding_size = (width*3) % 4

rows = []

image.seek(offset, os.SEEK_SET)
for row in range(height):
    rows.append([])
    for col in range(width):
        # print(str(row) + " " + str(col))
        color = int.from_bytes(image.read(3), 'little')
        if color == 0:
            rows[row].append(1)
        else:
            rows[row].append(0)

    image.read(padding_size)

image.close()

rows.reverse()

array_bytes = []

for row in range(height):
    if row % 8 == 0:
        array_bytes.append([0 for i in range(width)])
    for col in range(width):
        # print(str(row) + " " + str(col))
        array_bytes[row // 8][col] |= rows[row][col] << (row % 8)

with open(file_name + ".txt", "w") as file:
    file.write("#define " + file_name.swapcase() +
               "_HEIGHT " + str(height) + "\n")
    file.write("#define " + file_name.swapcase() +
               "_WIDTH " + str(width) + "\n")
    file.write("\n")
    file.write("const uint8_t " + file_name + "_data[] = { ")
    first = True
    for row in array_bytes:
        for col in row:
            if first:
                file.write(hex(col))
                first = False
            else:
                file.write(", "+hex(col))

    file.write(" };\n")
    file.write("\n")
    file.write("struct Sprite " + file_name + " = {\n")
    file.write("    .data = " + file_name + "_data,\n")
    file.write("    .width = " + file_name.swapcase() + "_WIDTH,\n")
    file.write("    .height = " + file_name.swapcase() + "_HEIGHT,\n")
    file.write("    .x_pos = 0,\n")
    file.write("    .y_pos = 0,\n")
    file.write("};\n")
