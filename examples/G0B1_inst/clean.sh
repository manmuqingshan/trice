#!/bin/bash

# Calling "make clean" does not remove the Trice IDs from the source code but "clean.sh" will do as well.
trice clean -cache -liPath full -src ./Core -src ../exampleData -src ../../_test/testdata 
make clean -f main.mak
