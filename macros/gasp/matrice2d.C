#include <iomanip>
#include <cstring>
#include "CSpec2D.hh"
#include "CSpec2D.cc"
void matrice2d(){

int ch1,ch2;
//TH1D *peaks = new TH1D("peaks","peaks",4000,0,4000);







//TH1D *sum = new TH1D("sum","sum",4000,0,4000);

TFile *f= new TFile ("GGAB_10B.root");
//Histograms->cd();
//user-> cd();
CSpec2D *theMat= new CSpec2D(2000,2000,1);
//user_gamma_gamma_energy_214_Zmean->ProjectionX("asseX");
//user_gamma_gamma_energy_214_Zmean->ProjectionY("asseY");
for(int i=0; i<2000; i++)
{
  
  if (!(i%50)) cout << i << endl;
   for (int j=0; j<2000; j++){
       theMat -> set(c1(i,j),i,j,0);
  }
}


theMat -> write("GGAB_10B.mat");
//user_gamma_gamma_energy_214_Zmean;






}
