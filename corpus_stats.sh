#!/bin/sh

ccgbank_loc=$1
output=`pwd`/statistics/

mkdir -p $output

for section in `seq -w 0 24`; do
    mkdir -p $output/$section
    for wsj_file in `ls $ccgbank_loc/$section`; do
        cat $ccgbank_loc/$section/$wsj_file | ./ccgbank > $output/$section/$wsj_file
    done;
done


