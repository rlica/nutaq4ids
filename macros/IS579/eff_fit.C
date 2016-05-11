#include <fstream>
#include <iostream>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TFile.h>
#include <cstring>
#include <TROOT.h>
#include <TH1.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <cstdlib>
#include <cmath>
#include "TMath.h"
#include "math.h"

Double_t fitf(Double_t *x, Double_t *par)
{

  Double_t fitval = 0;
  Double_t arg = 0;
  Double_t arg2 = 0;
  arg = log(x[0]/100);
  //cout<<"arg "<<arg<<endl;
  arg2 = log(x[0]/1000);
  fitval = TMath::Exp(pow(pow(par[0]+par[1]*arg+par[2]*arg*arg,-par[6]) + pow(par[3]+par[4]*arg2+par[5]*arg2*arg2,-par[6]),-1/par[6]) );
  
  return fitval;
  
}

void ajuste(){

  Int_t n1=11; // Number of experimental points Cd
 Int_t n2=10; // Number of experimental points Sn
 Int_t n3=18; // Number of experimental points Eu
 Int_t n = 14; // Number of points old efficiency curve
 Int_t xmin = 20; //// Non toccare
 Int_t xmax = 2000; //// Non toccare
 Double_t a,b,c,d,e,f,g,h,av;
 Double_t X[n];
 Double_t Y[n];
 Double_t X1[n1];
 Double_t Y1[n1];
 Double_t EX1[n1];
 Double_t EY1[n1];
 Double_t X2[n2];
 Double_t Y2[n2];
 Double_t EX2[n2];
 Double_t EY2[n2];
 Double_t X3[n3];
 Double_t Y3[n3];
 Double_t EX3[n3];
 Double_t EY3[n3];
 Char_t buffer[256],buffer2[256],buffer3[256],buffer4[256],buffer5[256];
 Double_t X1_norm[n1];
 Double_t Y1_norm[n1];
 Double_t EX1_norm[n1];
 Double_t EY1_norm[n1];
 Double_t X2_norm[n2];
 Double_t Y2_norm[n2];
 Double_t EX2_norm[n2];
 Double_t EY2_norm[n2];
 Int_t dummy;


 strcpy(buffer,"Clover_Sum_AddBack_AbsEff.txt");
 strcpy(buffer2,"cd129_efficiency_noqbeta_addback_e1e2_100.txt");
 strcpy(buffer3,"sn132_efficiency_noqbeta_addback_e1e2_100.txt");
 strcpy(buffer4,"152Eu_EffAb_fit_function_060514.txt");
  
  std::cout<<buffer<<std::endl;
  
  ifstream *in = new ifstream(buffer);
  ifstream *in2 = new ifstream(buffer2);
  ifstream *in3 = new ifstream(buffer3);
  ifstream *in4 = new ifstream(buffer4);

  for(Int_t i=0;i<n;i++){
    *in>>X[i]>>Y[i];
  }
  cout<<"X["<<n-1<<"] "<<X[n-1]<<" Y["<<n-1<<"] "<<Y[n-1]<<endl;

 for(Int_t i=0;i<n;i++){
   X1[i] = X[i];
   Y1[i] = Y[i]*100;
  }
  cout<<"X1["<<n-1<<"] "<<X1[n-1]<<" Y1["<<n-1<<"] "<<Y1[n-1]<<endl;

 
//Draw function and experimental points for Cd and Sn 
 TCanvas *c1 = new  TCanvas("c1","c1",0,0,900,500);
 c1->Draw();


 TGraph *gr4=new TGraph(n,X1,Y1);
 gr4->SetMarkerColor(1);
 gr4->SetMarkerSize(1);
 gr4->SetMarkerStyle(8);
 gr4->Draw("AP");

 TF1 *Fitf = new TF1("Fitf",fitf,xmin,xmax,7);
 Fitf->SetLineWidth(2);
 Fitf->SetLineColor(1);
 Fitf->SetLineStyle(1);
 Fitf -> SetParameters(7.7224588E+00,3.9924026E+00,0.0000000E+00,5.1526990E+00,-6.2648928E-01,-8.1755184E-02,1.5000000E+01);
 gr4->Fit("Fitf","WW","",xmin,xmax);
 Fitf->Draw("same");
 
 a=Fitf->GetParameter(0);
 b=Fitf->GetParameter(1);
 c=Fitf->GetParameter(2);
 d=Fitf->GetParameter(3);
 e=Fitf->GetParameter(4);
 f=Fitf->GetParameter(5);
 g=Fitf->GetParameter(6);

 std::cout<<a<<std::endl;
 std::cout<<b<<std::endl;
 std::cout<<c<<std::endl;
 std::cout<<d<<std::endl;
 std::cout<<e<<std::endl;
 std::cout<<f<<std::endl;
 std::cout<<g<<std::endl;

  sprintf(buffer5,"AbsEff_curve_CloverSum_addback_011214.txt");

  
 ofstream *salida = new ofstream(buffer5,ios::app);
  
 Double_t Ynew[xmax-xmin];
 for(Int_t i=xmin;i<xmax;i++){
   av = Fitf->Eval(i);
   Ynew[i-xmin] = av/100;
   
   *salida << i <<"\t" << Ynew[i-xmin] <<"\t" <<endl;
   
 }

 *salida << "Fit Parameters" << endl;
 *salida << a << "\t" <<  b << "\t" << c << "\t" << d << "\t" << e << "\t" << f << "\t" << g << "\t" << endl;
 *salida << "Energy" <<"\t"<< "Abs Eff"<<endl;

 // Search for relative errors
 Double_t diff[n];

 for(Int_t i=0;i<n;i++){
   dummy = (int)X[i];
   diff[i] = abs(Ynew[dummy-xmin]-Y[i])/Ynew[dummy-xmin];
   cout<<"Ynew["<<dummy-xmin<<"] "<<Ynew[dummy-xmin]<<" Y["<<i<<"] "<<Y[i]<<" diff["<<i<<"] "<<diff[i]<<endl;
 }

 Double_t Eeff = 100*diff[0];
 for(Int_t i=1;i<n;i++){
   if(100*diff[i]>Eeff) Eeff = 100*diff[i];
 }

 Double_t mean_Eeff = 0;
 for(Int_t i=0;i<n;i++){
   mean_Eeff = mean_Eeff + 100*diff[i];
 }


 mean_Eeff = mean_Eeff/(n);

 // for(Int_t i=0;i<n1+n2+n3;i++) cout<<" diff["<<i<<"] "<<diff[i]<<endl;

 cout<<"Eeff "<<Eeff<<" mean_Eeff "<<mean_Eeff<<endl;
 *salida << "max_eff_error(%)" <<"\t" << Eeff <<"\t"<< "mean_eff_error(%)" <<"\t" << mean_Eeff <<endl;

} // Close function ajuste