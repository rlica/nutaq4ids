#!/bin/bash

#Author: R. Lica, razvan.lica@cern.ch

if [ -z $1 ] 
  then
    echo "ERROR: Run number required as argument (eg: 00X)."
    exit 1
fi

RUN_NUMBER=$1

echo "Run - " $RUN_NUMBER
ls run$RUN_NUMBER/ 

#######################   Reading the file list

declare -a FILELIST
for f in run$RUN_NUMBER/*; do 
    #FILELIST[length_of_FILELIST + 1]=filename
    FILELIST[${#FILELIST[@]}+1]=$(echo "$f");
done

SIZE=${#FILELIST[@]}

if (( $SIZE == 1 ))
then
echo "ERROR: Could not read any files from run$RUN_NUMBER/ . "
exit 1
else
echo $SIZE " files were successfully read. "
fi

#######################




########################    Writing the makechain file

echo "
#include <TFile.h>
#include <TChain.h>

using namespace std;

void makechain_run$RUN_NUMBER() 

{
TChain *chain = new TChain(\"copac\") ; 

" >makechain_run$RUN_NUMBER.C


for (( c=1; c<=$SIZE; c++ ))
do
   echo "chain->Add(\"${FILELIST[$c]}\");" >>makechain_run$RUN_NUMBER.C
done

echo "
};" >>makechain_run$RUN_NUMBER.C

#######################

cat makechain_run$RUN_NUMBER.C
