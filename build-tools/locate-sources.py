#!/usr/bin/env python3

'''
Find all files in the current source directory that match a given pattenrn.
'''

import glob
import os
import sys

from pathlib import Path

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <pattern>")
        sys.exit(1)
    
    pattern = sys.argv[1]

    source_root = os.getenv("MESON_SOURCE_ROOT")
    if not source_root:
        print("The environment variable MESON_SOURCE_ROOT must be set!")
        sys.exit(1)
    
    subdir = os.getenv("MESON_SUBDIR")
    if not subdir:
        print("The environment variable MESON_SUBDIR must be set!")
        sys.exit(1)
    
    source_dir = Path(source_root) / subdir
    
    for file in glob.iglob(pattern, root_dir=source_dir):
        print(file)

if __name__ == "__main__":
    main()