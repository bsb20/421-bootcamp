#! /usr/bin/env python3

import unittest
import subprocess
import sys
import os

p = os.path.dirname(os.path.abspath(__file__))

db_file = os.path.join(p,"imdb-cmudb2022.db")
submission_sql = os.path.join(p,"{}.sql")
ref_sol = os.path.join(p,".do/not/peek/ref/{}.ref")


def run_unit(name, should_sort=False):
    actual = subprocess.check_output(["sqlite3", db_file], stdin=open(submission_sql.format(name)), encoding='utf-8').strip()
    expected = open(ref_sol.format(name), encoding='utf-8').read().strip()
    if should_sort:
        actual = '\n'.join(sorted(actual.split()))
        expected = '\n'.join(sorted(expected.split()))
    if actual == expected:
        print('''\033[92m
    ==============
    ==== OK! =====
    ==============\
    \033[0m
    ''')
    else:
        print('''\033[91m
    ==============
    === Fail :(===
    ==============\
    \033[0m
    ''')
        print("Query result does not match our solution.")
        sol_lines = actual.split("\n")
        ref_lines = expected.split("\n")
        for idx in range(len(sol_lines)):
            if idx >= len(ref_lines):
                print(sol_lines[idx] + " << >> \"\"") 
                break
            elif sol_lines[idx] != ref_lines[idx]:
                print((sol_lines[idx] or "\"\"") + " << >> " + (ref_lines[idx] or "\"\""))
                break
            elif idx == len(sol_lines) - 1:
                print(" \"\" << >> " + ref_lines[idx+1])
                break

if __name__ == "__main__":
    test_name = sys.argv[1] if not sys.argv[1].endswith(".sql") else os.path.basename(sys.argv[1]).split(".")[0]
    run_unit(test_name)
