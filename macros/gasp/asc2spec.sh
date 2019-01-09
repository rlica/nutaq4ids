#!/bin/bash
#Author: R. Lica, razvan.lica@cern.ch

if [ -z $1 ] 
  then
    echo "ERROR: Filename required as argument."
    exit 1
fi

awk '{ print $2 }' $1 >$1.a16
echo "File created: $1.a16|a:16"
xtrackn