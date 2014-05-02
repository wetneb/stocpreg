#!/bin/sh

ccgbank_loc=$1
noannot=$2
output=`pwd`/statistics$2/

mkdir -p $output

for section in `seq -w 0 24`; do
    mkdir -p $output/$section
    for wsj_file in `ls $ccgbank_loc/$section`; do
        cat $ccgbank_loc/$section/$wsj_file | ./ccgbank $2 > $output/$section/$wsj_file
    done;
done


