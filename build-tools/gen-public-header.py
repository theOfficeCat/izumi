#!/usr/bin/env python3

'''
Generate a public header file from a private one.

All #include "ABC.h" instances are replaced with #include <izumi/ABC.h>.
'''

import sys

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <input_file> <output_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]
    
    with open(output_file, 'w') as f:
        process_file(f, input_file)

def process_file(output_stream, input_file):
    with open(input_file, 'r') as f:
        for line in f.readlines():
            
            # Replace private includes with public ones
            if line.startswith("#include") and "\"" in line:
                line = line.replace("\"", "<izumi/", 1)
                line = line.replace("\"", ">", 1)
            
            output_stream.write(line)

if __name__ == "__main__":
    main()