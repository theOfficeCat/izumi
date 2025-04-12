#!/usr/bin/env python3

'''
Generate a list of undocumented items with gtk-doc
'''

import os
import sys

from pathlib import Path
from tempfile import TemporaryDirectory
from subprocess import DEVNULL, check_call

def main():
    if len(sys.argv) > 2 or (len(sys.argv) == 2 and sys.argv[1] != '--test'):
        print(f"Usage: {sys.argv[0]} [--test]")
        sys.exit(1)

    source_root = os.getenv("MESON_SOURCE_ROOT")
    if not source_root:
        print("The environment variable MESON_SOURCE_ROOT must be set!")
        sys.exit(1)
    
    subdir = os.getenv("MESON_SUBDIR")
    if not subdir:
        print("The environment variable MESON_SUBDIR must be set!")
        sys.exit(1)
    
    source_dir = Path(source_root) / subdir
    
    with TemporaryDirectory() as tmpd:
        tmpd = Path(tmpd)
        
        check_call(
            [
                'gtkdoc-scan',
                '--module', 'izumi',
                '--source-dir', source_dir.parent,
                '--output-dir', tmpd
            ],
            stdout=DEVNULL,
            stderr=DEVNULL,
        )
        
        check_call(
            [
                'gtkdoc-mkdb',
                '--module', 'izumi',
                '--source-dir', source_dir.parent,
            ],
            cwd=tmpd,
            stdout=DEVNULL,
            stderr=DEVNULL,
        )
        
        undocumented = 0
        
        with open(tmpd / 'izumi-undocumented.txt') as f:
            undocumented = []
            for line in f.readlines()[4:]:
                line = line.strip()
                if line:
                    undocumented.append(line)
        
        if undocumented:
            print(f'Found {len(undocumented)} undocumented items:')
            for line in undocumented:
                print(f'- {line}')
            if len(sys.argv) == 2 and sys.argv[1] == '--test':
                exit(1)

if __name__ == "__main__":
    main()