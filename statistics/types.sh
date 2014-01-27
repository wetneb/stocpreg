#!/bin/sh

column=$1

rm -f full_corpus
for section in `seq -w 0 24`; do
    for wsj_file in `ls $section`; do
        cut -f $1 $section/$wsj_file >> full_corpus
    done;
done;

sort full_corpus | uniq -c | sort -rnk 1,1 > types.$column


