#include "Riostream.h"

void roottoascii_xtsp(TH1F * argv){

  TH1F hist2conv; 
  char filename[500];
  char outputfile[510];
  FILE * fout;

  strcpy(filename,argv->GetName());
  strcpy(outputfile,filename);
  strcat(outputfile,".xtsp");
  //  argv->Rebin(8);

  //  printf("filename is %s\n",filename);
  // strcpy(hist2conv,argv);
 fout = fopen(outputfile,"w");

  // printf("hist2conv is %s\n",hist2conv);
  // printf("The outputfile is %s\n",outputfile);
  //hist2conv->GetXaxis()->GetNbins();
int nbins=argv->GetXaxis()->GetNbins();
 printf("nbins = %d\n",nbins);
for (int bin=1;bin<=nbins;bin=bin+8){   
  fprintf(fout,"%4.1f %4.1f %4.1f %4.1f %4.1f %4.1f %4.1f %4.1f \n", argv->GetBinContent(bin),argv->GetBinContent(bin+1),  argv->GetBinContent(bin+2),  argv->GetBinContent(bin+3),  argv->GetBinContent(bin+4),  argv->GetBinContent(bin+5),  argv->GetBinContent(bin+6),argv->GetBinContent(bin+7) ); 

 };
 fclose(fout);


 //printf("%4.1f %4.1f %4.1f %4.1f %4.1f %4.1f %4.1f %4.1f \n", E_gam_0_0->GetBinContent(bin),E_gam_0_0->GetBinContent(bin+1),  E_gam_0_0->GetBinContent(bin+2),  E_gam_0_0->GetBinContent(bin+3),  E_gam_0_0->GetBinContent(bin+4),  E_gam_0_0->GetBinContent(bin+5),  E_gam_0_0->GetBinContent(bin+6),E_gam_0_0->GetBinContent(bin+7) )

}
