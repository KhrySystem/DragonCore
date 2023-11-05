import sys

args = sys.argv

def run_on_file(f, o):
    input_file = open(f , 'r')
    output = open(o, 'a')
    possible_extensions = []
    current_extension = None
    enum_name = None
    total_enums = 0
    tab_level = 0

    count = 0
    while True:
        count += 1
        line = input_file.readline()

        if not line:
            break

        line = line.strip()

        if enum_name != None:
            data = line.split(" ")
            if line.find("}") >= 0:
                output.write(f"\t\tdefault: return \"Unhandled {enum_name}\";\n\t{'}'}\n{'}'}\n\n")
                enum_name = None
                tab_level = 0
            elif line.find("#") >= 0:
                output.write(f"\t{line}\n")
                if line.find("endif") >= 0:
                    tab_level -= 1
                else:
                    tab_level += 1
            elif len(data) >= 3:
                for i in range(tab_level):
                    output.write("\t")
                if not data[2].startswith("VK") and data[0].find("BITS_MAX_ENUM") < 0:
                    output.write(f"case {data[0]}: return \"{data[0]}\";\n")

        elif line.find("NAME") >= 0 and (line.find("VK_KHR") >= 0 or line.find("VK_EXT")) >= 0:
            data = line.split(" ")
            if data[0] == '#define':
                name = data[1]
                if current_extension is not None:
                    output.write("#endif\n\n")
                possible_extensions.append(data[len(data) - 1])
                current_extension = name
                output.write(f"#ifdef {current_extension}\n")

        elif line.find("enum") >= 0 and line.find("#") < 0:
            data = line.split(" ")
            output.write(f"static inline const char* string_{data[2]}({data[2]} inputValue) {'{'}\n\tswitch(inputValue) {'{'}\n")
            enum_name = data[2]
            total_enums += 1
            tab_level = 2

    if current_extension != None:
        output.write("#endif\n\n")

    input_file.close()
    output.close()
    possible_extensions.sort()
    print(f"{len(possible_extensions)} extensions found: ")
    for ext in possible_extensions:
        print(f"\t{ext}")
    print(f"In {f}, {total_enums} enums were found.")

def main(vulkan_core_file_path, output_file_path):
    output = open(output_file_path, 'w')
    output.write("#pragma once\n\n#include <vulkan/vulkan.h>\n#include<vulkan/vk_layer.h>\n\n")
    output.close()

    run_on_file(vulkan_core_file_path + "/vulkan_core.h", output_file_path)
    run_on_file(vulkan_core_file_path + "/vk_layer.h", output_file_path)

    

if __name__ == "__main__":
    main(args[1], args[2])