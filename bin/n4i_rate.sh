#!/bin/bash



#R.Lica
##############################

CONFIG_FILE=$1;   
NUMBER_OF_BLOCKS=10           
WRITE_ROOT='n'

##############################

OLD_FILE_SIZE=0              

if [ -z $2 ] 
  then
    echo "ERROR: Run path required as argument."
    exit 1
fi

if [ ! -f $1 ] 
  then
    echo "ERROR: Cannot find <config_rate>."
    exit 1
fi



while [ 1 = 1 ] ; do

 INPUT_FILE="$(ls -t $2* | head -1)"
 NEW_FILE_SIZE=$(stat -c%s "$INPUT_FILE")


 if [ $NEW_FILE_SIZE -ne $OLD_FILE_SIZE ];
  then
n4i $CONFIG_FILE $INPUT_FILE << echo
$NUMBER_OF_BLOCKS     
$WRITE_ROOT
echo

    printf "$(date)    $(du -h $INPUT_FILE) \n"
    sleep 3
    OLD_FILE_SIZE=$NEW_FILE_SIZE
    	
   else
    printf "$(date)    $(du -h $INPUT_FILE)    Waiting for file update ... \r"
    sleep 1
 fi

done
