/*********************************************
function to fit beta-gamma decay curves.

There are 4 parameters to fit the experimental distribution:
p[0], p[1], p[2], p[3],
C, sigma, centroid, lifetime
**********************************************/
#include "TMath.h"
#include "math.h"
#include "Riostream.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TROOT.h"
#include "TF1.h"
#include "TH1.h"
#include "TLatex.h"


Double_t T(Double_t *t, Double_t *p){
  Double_t pi = 3.14159;
  Double_t l1 = sqrt(pi/2);
  Double_t l2 = (p[1]*p[1]+2*p[2]*p[3]-2*t[0]*p[3])/(2*p[3]*p[3]);
  Double_t l3 = (p[1]*p[1] + (p[2]-t[0])*p[3])/(sqrt(2)*p[1]*p[3]);
  // Double_t prueba = TMath::Erfc(l3));
//if(t[0]>-1 && t[0]<-0.8) cout<<"l1 "<<l1<<" prueba "<<prueba<<endl;
  return p[0]*l1*p[1]*TMath::Exp(l2)*TMath::Erfc(l3);

}

void get_histo_mean(char *outputfile){

  Double_t n = 4; ///// Number of files
  Double_t in = 1/n;
  TFile *f1 = new TFile("/data/riken/analysis/anabel/external_macros/root_files_beta_delayed_gammas_afterBEffP/72Co_diffBg_210714/72Co_ab_T_gammas_allBNeighPixNeighSi_bg2_270ms_160714.root");
  TFile *f2 = new TFile("/data/riken/analysis/anabel/external_macros/root_files_beta_delayed_gammas_afterBEffP/72Co_diffBg_210714/72Co_ab_T_gammas_allBNeighPixNeighSi_bg3_270ms_160714.root");
  TFile *f3 = new TFile("/data/riken/analysis/anabel/external_macros/root_files_beta_delayed_gammas_afterBEffP/72Co_diffBg_210714/72Co_ab_T_gammas_allBNeighPixNeighSi_bg4_270ms_160714.root");
  TFile *f4 = new TFile("/data/riken/analysis/anabel/external_macros/root_files_beta_delayed_gammas_afterBEffP/72Co_diffBg_210714/72Co_ab_T_gammas_allBNeighPixNeighSi_bg5_270ms_160714.root");
  //TFile *f5 = new TFile("/data/riken/analysis/anabel/external_macros/root_files_beta_delayed_gammas_afterBEffP/72Co_diffBg_210714/72Co_ab_T_gammas_allBNeighPix_SiWT_bg2_255ms_210714.root");
  //TFile *f6 = new TFile("/data/riken/analysis/anabel/external_macros/root_files_beta_delayed_gammas_afterBEffP/72Co_diffBg_210714/72Co_ab_T_gammas_allBNeighPix_SiWT_bg3_255ms_210714.root");
  //TFile *f7 = new TFile("/data/riken/analysis/anabel/external_macros/root_files_beta_delayed_gammas_afterBEffP/72Co_diffBg_210714/72Co_ab_T_gammas_allBNeighPix_SiWT_bg4_255ms_210714.root");
  //TFile *f8 = new TFile("/data/riken/analysis/anabel/external_macros/root_files_beta_delayed_gammas_afterBEffP/72Co_diffBg_210714/72Co_ab_T_gammas_allBNeighPix_SiWT_bg5_255ms_210714.root");

  TH1D *h1 = (TH1D*)f1->Get("h1_bgE");
  TH1D *h2 = (TH1D*)f2->Get("h1_bgE");
  TH1D *h3 = (TH1D*)f3->Get("h1_bgE");
  TH1D *h4 = (TH1D*)f4->Get("h1_bgE");
  /*
  TH1D *h5 = (TH1D*)f5->Get("h1_bgE");
  TH1D *h6 = (TH1D*)f6->Get("h1_bgE");
  TH1D *h7 = (TH1D*)f7->Get("h1_bgE");
  TH1D *h8 = (TH1D*)f8->Get("h1_bgE");
  */
  TH1D *h1_bgE = (TH1D*)h1->Clone("h1_bgE");
  *h1_bgE = *h1_bgE + *h2 + *h3 + *h4 /*+ *h5 + *h6 + *h7 + *h8*/;
  *h1_bgE = *h1_bgE*in;

  TFile *file = new TFile(outputfile,"recreate");
  h1_bgE->Write();
  file->Close();
} // Close function get_histo_mean



void fit_T(int time_bin, Double_t Dtime_L, Double_t Dtime_U, char * file){

   TFile *f = new TFile(file);
   TCanvas *c1 = new TCanvas("c1","c1",0,0,600,700);
   c1->Draw();
   c1->cd()->SetLogy(1);
   TH1D *h = (TH1D*)f->Get("h1_bgE");
   //f->Get("hSum");
   //TH1F *h = hSum;
   //h1->GetXaxis()->SetLimits(0,Dtime_U);
   //h->SetStats(kFALSE); // Eliminate statistics box
   gStyle->SetOptTitle(0); // Eliminate title
   h->TPad::SetTicks(0,1); // Set ticks on left y axis
   h->GetXaxis()->SetTitle("Time (ns)");
   Int_t width = (Dtime_U-Dtime_L)*1000/time_bin;
   cout<<"width "<<width<<endl;
   h->GetYaxis()->SetTitle(Form("Counts / %d ps",width));
   h->GetXaxis()->SetTitleFont(132);
   h->GetYaxis()->SetTitleFont(132);
   h->GetXaxis()->SetLabelFont(132);
   h->GetYaxis()->SetLabelFont(132);
   h->GetXaxis()->CenterTitle();
   h->GetYaxis()->CenterTitle();
   h->GetXaxis()->SetTitleSize(0.06);
   h->GetYaxis()->SetTitleSize(0.06);
   h->GetXaxis()->SetLabelSize(0.05);
   h->GetYaxis()->SetLabelSize(0.05);
   h->GetXaxis()->SetTitleOffset(0.8);
   h->GetYaxis()->SetTitleOffset(1);
   h->GetXaxis()->SetNdivisions(5,5,kTRUE);
   h->SetMarkerStyle(4);
   h->SetMarkerSize(1);
   
   h->Rebin(2);
   //h->Smooth(5,"R");
   h->Draw("E2");
   //c1->Update;

   TF1 *myfit = new TF1("myfit",T,Dtime_L,Dtime_U,4);
   TF1 *mygaus = new TF1("mygaus","gaus",Dtime_L,Dtime_U);
   TF1 *myexp = new TF1("myexp","expo",Dtime_L,Dtime_U);
   myfit->SetLineWidth(1);
   myfit->SetLineColor(1);
   myfit->SetLineStyle(1);
   myfit->SetParNames("C","sigma","centroid","tau");
   myfit->SetParameters(100,0.3088,0.02391,0.7);

   myfit->SetParLimits(0,0,100000);
   //myfit->SetParLimits(1,0,1);
   //myfit->SetParLimits(2,-10,10);
   myfit->SetParLimits(3,0,100);

   //myfit->FixParameter(0,100);
   myfit->FixParameter(1,0.247192);
   myfit->FixParameter(2,-0.0179896);
   //myfit->FixParameter(3,1.0);

   cout<<"function to fit half lives of excited states through beta-gamma FasT measurements"<<endl;

   cout<<"There are 4 parameters to fit the experimental curve:"<<endl;
   cout<<"p[0], p[1], p[2], p[3]"<<endl;
   cout<<"C,sigma, centroid,tau"<<endl<<endl;
   h->Fit("myfit","L","",Dtime_L,Dtime_U);
   //myfit->Draw("same");
   //c1->Update();
   Double_t *para = myfit->GetParameters();
   Double_t *sig = myfit->GetParErrors();
   //mygaus->SetParameters(&para[0],&para[1],&para[2]);
   //mygaus->SetParameters(para);
   //myexp->SetParameters(&para[0],&para[3]);
   myexp->SetParameter(0,log(para[0]));
   myexp->SetParameter(1,-1/para[3]);
   //mygaus->Draw("same");
   //c1->Update();
   //myexp->Draw("same");

   Double_t C = para[0];
   Double_t EC = sig[0];
   Double_t sigma = para[1]*1000;
   Double_t Esigma = sig[1]*1000;
   Double_t centroid = para[2]*1000;
   Double_t Ecentroid = sig[2]*1000;
   Double_t t_half = log(2)*para[3]*1000;
   Double_t Et_half = log(2)*sig[3]*1000;

  Char_t legend1[200],legend2[200],legend3[200],legend4[200];

  sprintf(legend1,"#font[132]{#scale[1.2]{t_{1/2}^{6^{+}} = %d(%d) ps}}",t_half,Et_half);
  sprintf(legend2,"#font[132]{#scale[1.2]{#sigma = %d(%d) ps}}",sigma,Esigma);
  sprintf(legend3,"#font[132]{#scale[1.2]{C = %d(%d) ps}}",centroid,Ecentroid);
  sprintf(legend4,"#font[132]{#scale[1.2]{^{72}Ni}}");

  TLatex *t1=new TLatex( 5, 20,legend1);
  TLatex *t2=new TLatex( 5, 15, legend2);
  TLatex *t3=new TLatex( 5, 10, legend3);
  TLatex *t4=new TLatex( 5, 25, legend4);
 
  t1->Draw();
  t2->Draw();
  t3->Draw();
  t4->Draw();


   cout<<"T1/2(state) = "<<setiosflags(ios::fixed)<<setprecision(4)<<t_half<<" ± "<<setiosflags(ios::fixed)<<setprecision(4)<<Et_half<<" ns"<<endl;

} // Close fit function
