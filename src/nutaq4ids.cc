/*
 Nutaq LyrTech to GASPware and ROOT converter
 R. Lica, 2014 - 2015
 razvan.lica@cern.ch
 
 https://github.com/rlica/nutaq4ids
 
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <string.h>
#include <math.h>


#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH2.h"
#include "TRandom.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TROOT.h"


#include  "nutaq4ids.hh"
#include  "read_config.hh"
#include  "calibrate.hh"
#include  "read_cal.hh"
#include  "read_grain.hh"
#include  "merge_sort.hh"
#include  "define_root.hh"
#include  "event_builder.hh"
#include  "event_builder_list.hh"
#include  "event_builder_tree.hh"
#include  "correlations.hh"
#include  "write_correlations.hh"
#include  "write_gasp.hh"
#include  "write_stats.hh"
#include  "write_list.hh"
#include  "write_tree.hh"
#include  "write_time.hh"



int main( int argc, char **argv )
{
  
    
  
  srand(time(0));

  
  printf("\n\t\t----------------------------------");
  printf("\n\t\t         Nutaq Converter");
  printf("\n\t\t           v11.05.2015  ");
  printf("\n\t\thttps://github.com/rlica/nutaq4ids");
  printf("\n\t\t----------------------------------");
  printf("\n\n");


  read_config(argc, argv);

  read_cal(argc, argv);
   
  //Allocating memory
  DataArray   = (struct data*)   calloc(memoryuse+10000, sizeof(struct   data));
  TempArray   = (struct data*)   calloc(memoryuse+10000, sizeof(struct   data));	

  if (root == 1)
    TEventArray = (struct TEvent*) calloc(memoryuse+10000, sizeof(struct TEvent));

  if (gasp == 1 || list == 1) {
    EventArray  = (struct Event*)  calloc(memoryuse+10000, sizeof(struct  Event));
    GHeader     = (struct GaspRecHeader*)  calloc(1, sizeof(struct GaspRecHeader));
  }
    
  /////////////////////////////////////////////////////////////////// Reading run by run 
  for (runnumber = runstart; runnumber <= runstop; runnumber++) {
    
    totEvt=0;
    tref=0;
    
    // Open output file
    if ( (gasp == 1 || list == 1 || root == 1) && corr == 0) {
      
      //GASPware format
      if      (gasp == 1) {
        sprintf(outname, "Run%03d", runnumber);
        fp_out = fopen(outname, "wt");
        if (!fp_out) {
          fprintf(stderr, "ERROR: Unable to create %s - %m\n", outname);
          exit(0);
        } 
      }
      
      //Event List format
      else if (list == 1) {
        sprintf(outname, "Run%03d.list", runnumber);
        fp_out = fopen(outname, "wt");
        if (!fp_out) {
          fprintf(stderr, "ERROR: Unable to create %s - %m\n", outname);
          exit(0);
        } 
      }
      
      //ROOT format
      else if (root == 1) {
        sprintf(outname, "Run%03d.root", runnumber); 
        rootfile = TFile::Open(outname, "recreate");
        if (!rootfile) {
          fprintf(stderr, "ERROR: Unable to create %s - %m\n", outname);
          exit(0);
        }
        define_root();
      }
      
            
    }

    if (rate == 1) {   //Rate mode takes the input file as the second argument
      if (argc < 3) {
        printf("Config file and input file required as arguments: ...$n4i [config_file_name] [input file] \n");
        exit(0);
      }
      sprintf(filename, "%s", argv[2]);
      fp_in = fopen(argv[2], "rb");
      if (!fp_in) {
        fprintf(stderr, "Unable to open %s - %m\n", filename);
        exit(0);
      }
      
      start_clock = (double)clock();
      while (end_of_file == 0) {
                    
        iData=0, iEvt=0;
        read_grain();
        
        if (root == 1) {
          
          event_builder_tree();
          write_tree();
          totEvt+=iEvt;	
          printf (" (%3d ev/blk) %9d events written to %s ",  
          iEvt/(current_block - prev_block + 1), totEvt, outname);
	        write_time();
	      
        }
        
      }
        
    }    

    
    else for (runpart = 0; runpart < 1000; runpart++) {    
   
    end_of_file = 0;
    check_block_size=0;
         
    start_clock = (double)clock();
  
          
      sprintf(filename, "%s%d_%d", runname, runnumber, runpart);
      fp_in = fopen(filename, "rb");
      if (!fp_in) {
        fprintf(stderr, "Unable to open %s - %m\n", filename);
        break;
      }   
             
           
    
    while (end_of_file == 0) {
      
            
      iData=0, iEvt=0;
      
      // Reading large portions of data one by one until the end of file
      read_grain();       
      
      // Writing statistics
      if (stat == 1) {
	      write_time();
        continue;
      }
      
    
      // Sorting the data chronologically
      MergeSort(DataArray, TempArray, 0, iData);
      
            
      //Looking for correlations
      if (corr > 0) {
	      correlations();
	      continue;
      }
      
      
      // Writing to GASPWare
      else if (gasp == 1) {        
        event_builder();
        write_gasp();
        totEvt+=iEvt;
	    
        printf (" (%3d ev/blk) %9d events written to %s ",  
        iEvt/(current_block - prev_block + 1), totEvt, outname); //Fixed a very old bug -> add 1 to avoid division by zero (AAAAAAARGH)
	    
	    write_time();
      }
      
      
      // Writing event lists
      else if (list == 1) {
        event_builder_list();
        write_list();
        totEvt+=iEvt;
        printf (" (%3d ev/blk) %9d events written to %s ",  
		    iEvt/(current_block - prev_block + 1), totEvt, outname);
	      write_time();
      }
      
 
      // Writing a ROOT Tree
      else if (root == 1) {
        event_builder_tree();
        write_tree();
        totEvt+=iEvt;
	
        printf (" (%3d ev/blk) %9d events written to %s ",  
        iEvt/(current_block - prev_block + 1), totEvt, outname);
	      write_time();
	
      }
      

    }
    
    printf("\n");
    current_block=0;
    
    }
    
   
    //Printing statistics for each run if not in correlation mode
    if (corr == 0)
       write_stats();
    
    
    
    if (root == 1 && corr == 0) {
      // Write everything
      rootfile->Write();
      // Close output root file
      rootfile->Save(); 
      rootfile->Close();  
      
    }
    
    
    
  
  } ////////////////////////////////////////////////////////////// end of Run
  
  
  //Writing correlation statistics for all runs to file
    if (corr > 0) 
      write_correlations();
    
        
  exit(0);

  
}//end of main 

