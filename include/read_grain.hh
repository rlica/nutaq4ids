
// Taken from N.Warr.
// Read data in Great format 3.1.3, assuming Nutaq (= Lyrtec) VHS ADCs
// We give each channel an ID, which is the module number * 32 + channel
// number on that module. We use the grain format calibration file which
// has the ID number = and then four numbers, three for the calibration
// and one for the time shift. The calibration file is called online.gains
// e.g. 1548 = -0.461876 0.17868361 -3.403245E-8 0
// which means module 48 channel 12 (48 * 32 + 12 = 1548) has that cubic
// calibration.
// See http://npg.dl.ac.uk/documents/edoc504/edoc504.html for the format.


/*
Updates (R.Lica)

20.08.2014: Added ext_ts to extract full timestamp from 'SYNC100' and 'Extended item timestamp'
04.09.2014: Old read_grain could not identify baseline data. Now it can 


*/



int32_t expect_samples = 0, pile_up = 0;
uint64_t first_ts = 0, last_ts = 0, pause_ts = 0, ext_ts = 0;


// 24 byte data block header - See
// http://ns.ph.liv.ac.uk/MTsort-manual/TSformat.html for details
// Note however, they assume that "long" is only 32 bits, which is incorrect
// on 64-bit systems!
typedef struct s_data_header {
    char       id[8];      // contains the string  EBYEDATA
    uint32_t   sequence;   // within the file
    uint16_t   stream;     // data acquisition stream number (in the range 1=>4)
    uint16_t   tape;       // =1
    uint16_t   MyEndian;   // written as a native 1 by the tape server
    uint16_t   DataEndian; // written as a native 1 in the hardware structure of the data following
    uint32_t   dataLen;    // total length of useful data following the header in bytes
} DATA_HEADER;


//-----------------------------------------------------------------------------
// Treat a trace sample word
void treat_trace_sample(uint64_t  datum) {
#if 0
   printf("SAMPLE: ts = 0x%016llX", datum);
   printf("\n");
#endif
}

//-----------------------------------------------------------------------------
// Treat a trace header word
void treat_trace_header(uint64_t  datum) {
   uint64_t len     = (datum >> 32) & 0xFFFF; // Number of samples
   expect_samples = len;

   uint64_t chan_id = (datum >> 48) & 0xF;    // ID of ADC
   uint64_t module  = (datum >> 53) & 0x3F;   // Module number for Nutaq
   uint64_t tr      = (datum >> 52) & 1;      // Trace/raw flag
   uint64_t ts      = datum & 0xFFFFFFF;      // Timestamp
   
   //printf("TRACE: ts = 0x%012llX module=%lld ADC=%lld sample_length=%-5lld %s",
   //       ts, module, chan_id, len, (tr) ? "raw" : "trace");
   //printf("\n");

}

//-----------------------------------------------------------------------------
// Treat an information word
void treat_information(uint64_t datum) {
   pile_up = 0;
   uint64_t modnum, code, field, ts;
   field   = (datum >> 32) & 0xFFFFF;
   code    = (datum >> 52) & 0xF;
   modnum  = (datum >> 56) & 0x3F;
   ts      = datum & 0xFFFFFFF;       // Timestamp
   switch(code) {
    case 1: // ADC channel pile-up
      stats[0][modnum][field+1]++;  //to know the ratio pileup/fail
      return;
      printf("INFO(pile-up): ts = 0x%012llX module=%-2lld code=%lld channel=%lld\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
    case 2: // Pause timestamp
      ts |= (field << 28);
      last_ts = ts;
      printf("INFO(pause ts): \tts = 0x%012llX\n", (long long)ts);
      pause_ts = ts;
      break;
    case 3: // Resume timestamp
      ts |= (field << 28);
      last_ts = ts;
      printf("INFO(resume ts):\tts = 0x%012llX after %g s\n", (long long)ts, ((double)ts - (double)pause_ts) * 10e-9);
      break;
    case 4: // SYNC100 timestamp
      ts |= (field << 28);
                
      last_ts = ts;
      ext_ts = field;
      if (first_ts == 0 && (current_block > 1 || rate == 1) ) { //changed on 11 May IS605, to get rid of the old buffer at the beginning of new file problem 
	first_ts = ts; 
	//printf("First timestamp = %.2f s\n\n", first_ts/(float)S);
	
      } 
      
//      printf("INFO(sync): \tts = 0x%012llX\n", ts);
      break;
    case 7: // Extended item timestamp
      ts |= (field << 28);
      last_ts = ts;
      ext_ts = field;
      printf("INFO(ext ts):\t ts = 0x%012llX module=%-2lld code=%lld ext_ts=0x%03llX\n",
           (long long)ext_ts, (long long)modnum, (long long)code, (long long)field);
      break;
    case 8: // Scanning table information
      printf("INFO(scanning table): ts = 0x%012llX module=%-2lld code=%lld field=0x%03llX\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
//    case 8: // Aida fee64 discr data - why are there two code=8 in the doc?
//      printf("INFO(Aida fee64 discr): ts = 0x%012llX module=%-2lld code=%lld field=0x%03llX\n",
//             ts, modnum, code, field);
//      break;
    case 9: // ADC channel/energy over-range
      return;
      printf("INFO(ADC channel/energy over-range): ts = 0x%012llX module=%-2lld code=%lld channel=%lld\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
    case 10: // ADC channel/energy under-range
      printf("INFO(under-range): ts = 0x%012llX module=%-2lld code=%lld channel=%lld\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
    case 11: // ADC channel overflow
      return;
      printf("INFO(overflow): ts = 0x%012llX module=%-2lld code=%lld channel=%lld\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
    case 12: // ADC channel underflow
      return;
      printf("INFO(underflow): ts = 0x%012llX module=%-2lld code=%lld channel=%lld\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
    case 13: // Trigger sequence number (event number)
      printf("INFO(trigger sequence): ts = 0x%012llX module=%-2lld code=%lld module seq no.=0x%03llX\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
    case 14: // Data link statistics
      printf("INFO(data link stats): ts = 0x%012llX module=%-2lld code=%lld link no.=0x%03llX\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
    case 15: // SHARC link number
      printf("INFO(SHARC link): ts = 0x%012llX module=%-2lld code=%lld link no.=0x%03llX\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
    default:
      printf("INFO(unknown): ts = 0x%012llX module=%-2lld code=%lld field=0x%03llX\n",
             (long long)ts, (long long)modnum, (long long)code, (long long)field);
      break;
   }
}

//-----------------------------------------------------------------------------
// Treat an ADC data word 
void treat_adc_data(uint64_t datum) {

   int mod, chan, baseline, i;
   uint64_t veto    = (datum >> 60) & 1;      // Veto bit (contains ADC range setting 0 = low, 1 = high)
   uint64_t id      = (datum >> 48) & 0xFFF;    // ID of ADC
   uint64_t adc     = (datum >> 32) & 0xFFFF; // ADC conversion value

   uint64_t fail    = (datum >> 61) & 1;      // Failure bit
   uint64_t ts      = datum & 0xFFFFFFF;      // Timestamp
   //if (llabs(ts - last_ts) > 50) printf("\n");

   ts |= (ext_ts << 28);
   
      
   mod      = id / 32;     // module numbering starts from 1
   chan     = id % 16 + 1; //channel numbering starts from 1
   baseline = (id % 32)/16; 
   //printf("ADC data: \t ts = 0x%012llX ID=%-4lld MOD=%d CHAN=%-3d BL=%-3d ADC=%-5lld veto=%lld fail=%lld\n", ts, id, mod, chan, baseline, adc, veto, fail);
  
  //I don't look yet at baseline data
  if (baseline==1) { printf("Baseline\n"); return; } 
  
   
  ///applying delay corrections
  ts += delay[mod][chan];  
  
  
  //in correlation mode, we delay the stop (stop = secondCh,secondMod)
  if (corr > 0)
    for (i=0; i<corr; i++) if (chan == secondCh[i] && mod == secondMod[i])
	      ts += CORR_DELAY*(int)corr_unit; //corr_unit is hardcoded as 1 in nutaq4ids.hh
	   // ts += CORR_DELAY;
  
  
  //total number of signals from a specific channel
  stats[2][mod][chan]++; 
  // Don't store fail ADC, only count it 
  //          pile_up => fail
  // adc out of range => fail
  if (fail) { 
    stats[1][mod][chan]++;
    return;
  }
  
  
  

  
  //storing only good data from ADC defined in config
  
  if (tmc[mod][chan] == 0) {
    return;
  }
  
  DataArray[iData].energy  =  calibrate(id, adc);
  //DataArray[iData].energy  =  adc;
  DataArray[iData].time    =   ts;
  DataArray[iData].chnum   = chan; //channel numbering from 1
  DataArray[iData].modnum  =  mod;   //module numbering from 1
  
  
  //Filling ROOT Histogram
  if (root == 1 && corr == 0) {
  int line = lmc[mod][chan];
  hStats->AddBinContent(line, 1);
  h[line]->Fill(DataArray[iData].energy);
  }
  
  iData++; 
}

  
//-----------------------------------------------------------------------------
// Treat any word
void treat_word(uint64_t datum) {

  
//  For the great standalone format (since 27 Aug 2014 @IDS), comment this two lines  
//  datum = ((datum & 0xFFFFFFFF00000000LL) >> 32) |
//          ((datum & 0x00000000FFFFFFFFLL) << 32);

  
  /*
  printf("%016llX\n", datum);
  return;
*/
   // Theoretically, a sample might have one of the two most significant bits
   // set, so we shouldn't use the key for this case.
   if (expect_samples) {
      treat_trace_sample(datum);
      expect_samples--;
      return;
   }

   // The two most significant bits are a key, which tell us what the word is
   // This means there are four possibilities: trace sample, trace header,
   // information and ADC data. However, the manual explicitly warns that
   // for the trace sample, the hardware might set the most significant bits,
   // so we shouldn't rely on them, if we expect sample (i.e. because we had
   // a header, which tells us how many samples to expect).
   uint32_t key = (datum >> 62) & 3;
   switch(key) {
    case 0: // Trace sample
      treat_trace_sample(datum);
      break;
    case 1: // Trace header
      treat_trace_header(datum);
      break;
    case 2: // Information
      treat_information(datum);
      break;
    case 3: // ADC data
      treat_adc_data(datum);
      break;
   }
}

//-----------------------------------------------------------------------------
// Swap a 32-bit integer
uint32_t Swap32(uint32_t datum) {
   return(((datum & 0xFF000000) >> 24) |
          ((datum & 0x00FF0000) >> 8) |
          ((datum & 0x0000FF00) << 8) |
          ((datum & 0x000000FF) << 24));
}

//-----------------------------------------------------------------------------
// Read a single file


void read_grain() 

{
  
   //first_ts = 0;  
   int32_t status;
   uint32_t jj;
   unsigned char block[131072];
   DATA_HEADER *header = (DATA_HEADER *)block;
   uint64_t *data = (uint64_t *)(block + sizeof(DATA_HEADER));
   
   
   prev_block = current_block;

 
///////////////////////////////////////////// Try to figure out the block size - only once
   
   if (check_block_size == 0) {
     
   for (blocklen = 8192; blocklen <= sizeof(block); blocklen *= 2) {
      fseek(fp_in, blocklen, SEEK_SET);
      status = fread(block, sizeof(unsigned char), blocklen, fp_in);
      if (status != (int32_t)blocklen) {
         fclose(fp_in);
	      printf("ERROR: read_grain.h - (status) %d != (blocklen) %d \n", status, blocklen);
         exit(0);
      }
      
      if (!strncmp(header->id, "EBYEDATA", 8)) break;
   }
   
   //Try to figure out fast the full size of the file:
    
   full_size = 0;
   int increment = 10000;
   status = (int32_t)blocklen;
   
   while (increment > 0) {
     while (status == (int32_t)blocklen) {
       printf("\rFile size is %6d blocks.", full_size);
       fflush(stdout);
       fseek(fp_in, (full_size)*blocklen, SEEK_SET);
       status = fread(block, sizeof(unsigned char), blocklen, fp_in);
       full_size+=increment; 
     }
     full_size-=2*increment;
     increment = increment / 10;
     fseek(fp_in, (full_size)*blocklen, SEEK_SET);
     status = fread(block, sizeof(unsigned char), blocklen, fp_in);
     full_size+=increment;
     
   }
   printf("\n");

  
   // Moving to the beginning of the file
   fseek(fp_in, 0, SEEK_SET);
   //printf("\nBlock size seems to be %d bytes\n", blocklen);
   check_block_size = 1;

   }
   
   //ratemeter mode 
   if (rate == 1 && current_block == 0) { /* move rate_eof_block blocks from the end of the file */
   fseek(fp_in, (full_size-rate_eof_blocks)*blocklen, SEEK_SET);
   }

////////////////////////////////////////////////////////////////////////////////////////////



   
   if (header->DataEndian != 1)
     printf("Need to swap data\n");
   
   // Loop over blocks
   for (; ; current_block++) {
     
     

      // Read block
      status = fread(block, sizeof(unsigned char), blocklen, fp_in);
      if (status != (int32_t)blocklen) { //Check if we arrived at the end of the file
	end_of_file = 1;
	//printf("WARNING: Block %d - (status) %d != (blocklen) %d \n", i, status, blocklen);
	break;
      }
      
      // Check header
      if (strncmp(header->id, "EBYEDATA", 8)) {
         fprintf(stderr, "ERROR: Invalid data format for file %s\n", filename);
         exit(0);
      }

      // Swap if needed
      if (header->MyEndian != 1) header->dataLen = Swap32(header->dataLen);

      // Loop over data
      for (jj = 0; jj < header->dataLen / sizeof(uint64_t); jj++) {
	treat_word(data[jj]);
      }

      // Write a message
      
      printf("\r %s: Blocks %5d ", filename, current_block);
      fflush(stdout);

      //After finishing reading the full block, we check if we have reached the size limit and then start analysing
      //When the analysis is finished, we continue with the next block - NO DATA LEFT BEHIND!!!
      
      if ( iData > memoryuse - 20000 ) {
         if (iData > memoryuse) { //If we have more than 20000 signals in a block (unlikely) it will exit
            printf("ERROR: iData > memoryuse - See read_grain.hh at line 405\n\n");
            exit(0);
         }
         else {
            current_block++;
            return;
         }
      }
   }

   // Close input file
   fclose(fp_in);

      
}

