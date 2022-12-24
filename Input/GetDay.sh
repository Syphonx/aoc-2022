#!/bin/bash

export AOC_SESSION=53616c7465645f5fc06c2cea7eff3f2752a40b0128430f31f5b640bc273ba9b66e2bc1975b69d009404e62bffd05a4e7223e987edfbb999ca2338ef92d853f1b

read -p "Enter year: " year
read -p "Enter day: " day
echo

echo Downloading Day $day...
aocd $year > Day$day.txt


