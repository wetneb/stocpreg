#!/bin/sh

column=$1
main_path=$2

rm -f $main_path/full_corpus
for section in `seq -w 0 24`; do
    for wsj_file in `ls $main_path/$section`; do
        cut -f $1 $main_path/$section/$wsj_file >> $main_path/full_corpus
    done;
done;

sort $main_path/full_corpus | uniq -c | sort -rnk 1,1 > $main_path/types.$column


