"""
build_number
This script generate build_number file.
That file define build_number.h file, contains
build count number.
"""

import os
import argparse

VERBOSE = False

HEADER = "#ifndef BUILD_COUNTER_H \
\n#define BUILD_COUNTER_H \
\n\n#define BUILD_NUMBER"

FOOTER = "\n\n#endif //BUILD_COUNTER_H"
FILENAME = "build_number.h"
PURE_FILENAME = "build_number"
SCRIPT_PATH = os.path.dirname(os.path.realpath(__file__))


def create_parser():
    "create_parser"
    parser = argparse.ArgumentParser()

    parser.add_argument('-v', type=bool, default=False,
                        help='Enable verbose',
                        nargs='?')

    parser.add_argument('-p', type=bool, default=False,
                        help='Enable pure file',
                        nargs='?')

    parser.add_argument('-s', type=bool, default=False,
                        help='Enable header file',
                        nargs='?')

    return parser


def create_new_file(path, filename, file_string):
    "create_new_file"

    if VERBOSE:
        print("Create new " + filename + " file")

    try:
        open(path, 'a').close()
    except IOError:
        print("Error create new file")
        exit()

    try:
        file = open(path, 'w')
        file.write(file_string)
    except IOError:
        print("Error write file " + filename)

    file.close()


def write_file(path, file_string):
    "write_file"

    if VERBOSE:
        print("Write " + path + " file")

    try:
        file = open(path, 'w')
        file.write(file_string)
    except IOError:
        print("Error write file")
        exit()

    file.close()


def write_header_file(path, build_number):
    "write_header_file"

    new_build_number = int(build_number) + 1
    final_string = HEADER + " " + str(new_build_number) + FOOTER
    write_file(path, final_string)


def write_pure_file(path, build_number):
    "write_pure_file"

    new_build_number = int(build_number) + 1
    final_string = str(new_build_number)
    write_file(path, final_string)


def read_header_file():
    "read_header_file"

    full_path = SCRIPT_PATH + "/" + FILENAME
    final_string = HEADER + " " + str(0) + FOOTER

    if VERBOSE:
        print("Header file path: " + full_path)

    try:
        file = open(full_path, 'r')
    except IOError:
        if VERBOSE:
            print("Error open file " + FILENAME)
        create_new_file(full_path, FILENAME, final_string)

    file = open(full_path, 'r')

    line = file.readline()
    cnt = 1
    while line:
        line = file.readline()
        parse_number = parse_string(line)
        if parse_number != -1:
            break

        cnt += 1

    if VERBOSE:
        print("Build number = " + parse_number)

    if parse_number == -1:
        print("Error parse" + FILENAME)
        exit()

    write_header_file(full_path, parse_number)
    file.close()

    return "Build number = " + parse_number


def read_pure_file():
    "read_pure_file"

    full_path = SCRIPT_PATH + "/" + PURE_FILENAME
    try:
        file = open(full_path, 'r')
    except IOError:
        if VERBOSE:
            print("Error open file " + PURE_FILENAME)
        create_new_file(full_path, PURE_FILENAME, str(0))

    file = open(full_path, 'r')

    line = file.readline()

    if VERBOSE:
        print("Build number = " + line)

    write_pure_file(full_path, line)

    file.close()
    return "Build number = " + line


def process_file(pure_file=False, header_file=False):
    "process build_number.h file"

    if VERBOSE:
        print("Process file")

    if not pure_file and not header_file:
        print("No one filetype selected, please select filetype")
        exit()

    build_number = ""

    if pure_file:
        if VERBOSE:
            print("Process pure file")
        build_number = read_pure_file()
        print("Pure file " + build_number)

    if header_file:
        if VERBOSE:
            print("Process header file")
        build_number = read_header_file()
        print("Header file " + build_number)


def parse_string(build_string):
    "parse_string"

    if "BUILD_NUMBER" not in build_string:
        return -1

    if VERBOSE:
        print("Need string: " + build_string)

    split_string = build_string.replace("\n", "").split(" ")

    if VERBOSE:
        print("Split string: ")
        print(split_string)
    build_number = split_string[-1]

    return build_number


def main():
    "main"

    parser = create_parser()
    namespace = parser.parse_args()

    global VERBOSE
    if namespace.v is None:
        VERBOSE = True

    pure_file = False
    if namespace.p is None:
        pure_file = True

    header_file = False
    if namespace.s is None:
        header_file = True

    process_file(pure_file, header_file)
    exit()


if __name__ == "__main__":
    main()
