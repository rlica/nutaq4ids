#!/bin/bash

#Author: R. Lica, razvan.lica@cern.ch
# This script will perform 1D cuts of 3D matrices using 'cmat - M2D'

########################## EDIT HERE ############################


# 142 keV - 148Ba
# LEFT=(279 290)   #Left limit of each region  
#RIGHT=(286 297)   #Right limit of each region


# 158 keV - 148Ce
 LEFT=(312 322)   #Left limit of each region  
RIGHT=(321 331)   #Right limit of each region

# 295 keV - 148Ce
# LEFT=(587 602)   #Left limit of each region  
#RIGHT=(593 608)   #Right limit of each region

 FILE="EET-Ge-La2-Beta-148Cs"
 EXTENSION="cmat"
 INDEX_TO_PROJECT="2 3"
 FACTORS="1 -1"

#################################################################



################# USE this for filename as argument #############
#if [ -z $1 ] 
#  then
#    echo "ERROR: File name required as argument."
#   exit 1
#fi

#if [ ! -f $1 ]
#  then 
#	 echo "ERROR: File $1 does not exist"
#	 exit 1
#fi

# FILE=$1
#################################################################


####### Cleaning up existing files

TEMP="${FILE}_${LEFT[0]}-${RIGHT[0]}_sub.${EXTENSION}";

   if [ -f $TEMP ]; then
     echo Removing existing file: $TEMP
     rm -f $TEMP
   fi



####### CMAT

    
cmat -l << echo
o $FILE
m2d
$INDEX_TO_PROJECT
n
${LEFT[0]} ${RIGHT[0]}


temp1
m2d
$INDEX_TO_PROJECT
n
${LEFT[1]} ${RIGHT[1]}


temp2
c
add
2
temp1
temp2
${FILE}_${LEFT[0]}-${RIGHT[0]}_sub.${EXTENSION}
$FACTORS

q
echo

rm temp1.cmat temp2.cmat

    
