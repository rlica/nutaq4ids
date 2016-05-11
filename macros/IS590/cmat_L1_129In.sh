#!/bin/bash

#Author: R. Lica, razvan.lica@cern.ch
# This script will perform 1D cuts of 2D matrices using 'cmat'

########################## EDIT HERE ############################

 LEFT=(108 158 223 343 418 538 677 856 299 704 750 618 )   #Left limit of each region  
RIGHT=(146 207 268 381 452 583 698 946 327 733 780 661 )   #Right limit of each region

 FILE="Tac1E-LaBr-EBeta-bWalkCorr-R45-47.cmat"

 INDEX_TO_PROJECT="1"

#################################################################

#Finding the array size (number of regions)
REG=${#LEFT[@]}     


################# USE this for filename as argument #############
#if [ -z $1 ] 
#  then
#    echo "ERROR: File name required as argument."
#    exit 1
#fi

#if [ ! -f $1 ]
#  then 
#	 echo "ERROR: File $1 does not exist"
#	 exit 1
#fi

# FILE=$1
#################################################################


####### Cleaning up existing files
for (( i=0; i < $REG; i++ ));
    do 
    
    TEMP="${FILE}_${LEFT[i]}-${RIGHT[i]}.l8";
    
       if [ -f $TEMP ]; then
         echo Removing existing file: $TEMP
	 rm -f $TEMP
       fi
    
    done



####### CMAT
for (( i=0; i < $REG; i++ ));
    do 
    
cmat -l << echo
o $FILE
gate
$INDEX_TO_PROJECT
n
${LEFT[i]} ${RIGHT[i]}

Y
${FILE}_${LEFT[i]}-${RIGHT[i]}.l8|l:8
q

echo

spec2root_time.sh ${FILE}_${LEFT[i]}-${RIGHT[i]}.l8

    done
    
