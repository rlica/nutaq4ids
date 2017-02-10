#!/bin/bash

RAW_PATH='/home/TapeData/RILIS0/'
EXP_PATH='/home/idsuser/Experiments/2017/RILIS0'
REC_TIME=20




#nutaq start
#sleep $REC_TIME
#nutaq stop 


#Reading the most recent file number - format Run_X_0
cd $RAW_PATH
RUN_NO="$(ls -1t | head -1 | sed 's/Run_//' | sed 's/_0//')"
echo Sorting Run $RUN_NO

#Sorting RAW data into ROOT Format
cd $EXP_PATH

n4i config_root << echo
$RUN_NO     
$RUN_NO
echo

#Extracting info from the ROOT tree

root -b -l -q yield.C"($RUN_NO)"

cat out$RUN_NO.txt >/home/idsuser/RILIS/out.txt

