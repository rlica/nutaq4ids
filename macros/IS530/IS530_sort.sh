#!/bin/bash

#Author: R. Lica, razvan.lica@cern.ch

if [ -z $1 ] 
  then
    echo "ERROR: Run number required as argument (eg: 00X)."
    exit 1
fi


printf -v RUN_NUMBER "%03d" $1
echo $RUN_NUMBER


FILE1="TE-TpClov-R$RUN_NUMBER.cmat";
    
       if [ -f $FILE1 ]; then
         echo Removing existing file: $FILE1
	 rm -f $FILE1
       fi

FILE2="TE-TpBeta-R$RUN_NUMBER.cmat";
    
       if [ -f $FILE2 ]; then
         echo Removing existing file: $FILE2
	 rm -f $FILE2
       fi

FILE3="TE-TpClov-beta-R$RUN_NUMBER.cmat";
    
       if [ -f $FILE3 ]; then
         echo Removing existing file: $FILE3
	 rm -f $FILE3
       fi

FILE1b="TE-TsClov-R$RUN_NUMBER.cmat";
    
       if [ -f $FILE1b ]; then
         echo Removing existing file: $FILE1b
	 rm -f $FILE1b
       fi

FILE2b="TE-TsBeta-R$RUN_NUMBER.cmat";
    
       if [ -f $FILE2b ]; then
         echo Removing existing file: $FILE2b
	 rm -f $FILE2b
       fi

FILE3b="TE-TsClov-beta-R$RUN_NUMBER.cmat";
    
       if [ -f $FILE3b ]; then
         echo Removing existing file: $FILE3b
	 rm -f $FILE3b
       fi


FILE4="ESymm-Clov-beta-R$RUN_NUMBER.cmat";
    
       if [ -f $FILE4 ]; then
         echo Removing existing file: $FILE4
	 rm -f $FILE4
       fi


#Writing the sorting script used by GASPware

echo "format GASP




*** R. Lica
******************************************************
**** EXPERIMENT IS530 - Sep 2015 ********
******************************************************


*-------------------------------------------------------------------------------------------
*                              Detector definitions
* F = Run Timestamp 
* C = Clover (1,2,3,4)
* B = Beta (1,2)     
* Coincidence time = HRT - 10 ns/chan 
* Time vs. Proton  = LRT - 10 ms/chan
* Timestamp        = 60 s/chan


*-------------------------------------------------------------------------------------------
*                              Energy(0) HRT(1)    LRT(2)   TAC(3)  TAC_Start(3) TAC_Stop(4)  
*-------------------------------------------------------------------------------------------
header      F   1  8192 PLUS 1 8192
cdetector   C   4  SEG 4   3   8192      2048      8192
cdetector   B   1  SEG 4   3   8192      2048      8192
*-------------------------------------------------------------------------------------------



*---------------------------------------------------------
* Calibration
*---------------------------------------------------------

***ENERGY (0.5 keV/chan)
recal        C0   Cal/ClovE_IS530_2Clov_207Bi.cal 0.0	2.00  10   8192  0 16
**********************************************************



**** Timestamp vs Clover Energy Sum with addback
addback C0
sort2d C2 C0 $FILE1 Res 8192 8192 Step 128 128
sort2d F0 C0 $FILE1b Res 8192 8192 Step 128 128

**** Timestamp vs Beta Energy Sum with addback
fold B 2 2
addback B0
sort2d C2 B0 $FILE2 Res 8192 1024 Step 128 16 
sort2d F0 B0 $FILE2b Res 8192 1024 Step 128 16

**** Timestamp vs Beta-gated(prompt) Clover energy Sum with addback
*sort2d B0 C0 EE-BetaAB-CloverAB Res 1024 8192 Step 16 128
gate B0 54 8191 IN 1 2
gate B1 10 2000 IN 1 2
mean B1 F1
add  C1 F1 C1 Fact 1.00 -1.00 Off 1000
gate C1 995 1015 IN 1 16
*sort2d C1 C0 $FILE3 Res 8192 8192 Step 128 128
sort2d C2 C0 $FILE3 Res 8192 8192 Step 128 128
sort2d F0 C0 $FILE3b Res 8192 8192 Step 128 128


**** Beta-gated (Prompt) Clover symm
fold C 2 16
sort2d_symm C0 $FILE4 Res 8192 " >script_R$RUN_NUMBER.setup



#Unpacking the raw data using Nutaq4IDS

n4i config_gasp <<echo
$RUN_NUMBER
$RUN_NUMBER
echo


gsort << echo
script_R$RUN_NUMBER.setup
128
128
128
128
D
Run$RUN_NUMBER
16
N
N
echo

n4i config_stat <<echo
$RUN_NUMBER
$RUN_NUMBER
echo

ls -lrth *$RUN_NUMBER.cmat

xtrackn 









