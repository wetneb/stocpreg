#!/bin/sh

cat $1 |\
    sed -e 's/(<T[^>]*> \([^\( )\)]*\) )//' |\
    sed -e 's/

