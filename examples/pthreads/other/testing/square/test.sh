#!/bin/bash

./square < tests/input001.txt | diff - tests/output001.txt
./square < tests/input002.txt | diff - tests/output002.txt
