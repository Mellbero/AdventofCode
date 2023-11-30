#!/bin/bash
for day in Day{11..25}; do
    for task in Task{1..2}; do
        touch "$day/$task/day_${day: -2}_${task: -1}.c"
    done
done

