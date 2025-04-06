#!/usr/bin/env python3

'''
List all curses headers that are included in a list of files.
'''

import sys

from concurrent.futures import ThreadPoolExecutor

def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <input_file> [<input_file0> [<input_file1> ...]]")
        sys.exit(1)

    input_files = sys.argv[1:]
    
    curses_headers = set()
    
    with ThreadPoolExecutor() as executor:
        for partial in executor.map(list_curses_includes, input_files):
            curses_headers.update(partial)
    
    print("\n".join(curses_headers))
            
def list_curses_includes(input_file):
    curses_headers = set()
    
    with open(input_file, 'r') as f:
        for line in f.readlines():
            # Find an include...
            if not line.startswith("#include"):
                continue
            
            # ...of a curses library...
            if "curses" not in line:
                continue
            
            # ...and parse it.
            curses_header = line.split('<')[1].split('>')[0]
            
            curses_headers.add(curses_header)
    
    return curses_headers

if __name__ == "__main__":
    main()