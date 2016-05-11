/*********************************************
func/*********************************************
function to fit beta decay curve. assume
the nuclei taken into account are:
X0 ------> X1 ------> X2 ------> X3 ------> X4 (stable)
           --
           -- n emit
           --
           ---------> X5 ------> X6 ------> X7 (stable)
           -
           -  2n emit
           -
           ---------> X8 ------> X9 ------> X10 (stable)

There are 10 parameters to fit the total curve:
p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]
 X0 ,, pn ,, p2n ,,t1 ,, t2 ,, t3 ,, t5 ,, t6 ,, t8 ,, C
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
#include "TFile.h"
#include "TStyle.h"



Double_t Xacc(Double_t *t, Double_t *p){
   Double_t l1=log(2)/p[3];
   Double_t X0=p[0];
   Double_t acc;
   Int_t cycle = 350;
   if(t[0]>0 && t[0]<=cycle){
     acc = X0*log(2)*p[3]*(1-TMath::Exp(-1*l1*t[0]));
     //if(t[0]==cycle) cout<<p[0]<<"\t"<<t[0]<<"\t"<<acc<<endl;
     return acc;
   }else /*if(t[0]>=cycle)*/{
     //if(t[0]==12) acc = X0*log(2)*p[1]*(1-TMath::Exp(-1*l1*t[0]));
     return acc*TMath::Exp(-1*l1*(t[0]-cycle));
   }else{
     return -1;
   }
}

Double_t X1(Double_t *t, Double_t *p){
   Double_t l1=log(2)/p[3];
   Double_t X0=p[0];
   if(t[0]>0){
      return X0*TMath::Exp(-1*l1*t[0]);
   }
   else{
      return -1;
   }
}
Double_t lX1(Double_t *t, Double_t *p){
   return X1(t,p);
}

Double_t X2(Double_t *t, Double_t *p){
   Double_t p1[4], p2[4];
   Double_t l1=log(2)/p[3];
   Double_t l2=log(2)/p[4];
   Double_t pb=1-p[1]-p[2];
   Double_t X0=p[0];
   Double_t expon1 = X0*TMath::Exp(-1*l1*t[0]) ;
   Double_t expon2 = X0*TMath::Exp(-1*l2*t[0]) ;
   p1[0]=p[0];
   p1[3]=p[3];
   p2[0]=p[0];
   p2[3]=p[4];
   if(t[0]>0){
      return pb*(expon1/(l2-l1)+expon2/(l1-l2));
   }else{
      return -1;
   }
}
Double_t lX2(Double_t *t, Double_t *p){
   Double_t l2=log(2)/p[4];
   return l2*X2(t,p);
}


Double_t X3(Double_t *t, Double_t *p){
   Double_t p1[2], p2[2], p3[2];
   Double_t l1=log(2.0)/p[3];
   Double_t l2=log(2.0)/p[4];
   Double_t l3=log(2.0)/p[5];
   Double_t pb=1-p[1]-p[2];
   Double_t A = (l2-l1)*(l3-l1);
   Double_t B = (l1-l2)*(l3-l2);
   Double_t C = (l1-l3)*(l2-l3);
   Double_t X0=p[0];
   Double_t expon1 = X0*TMath::Exp(-1*l1*t[0]) ;
   Double_t expon2 = X0*TMath::Exp(-1*l2*t[0]) ;
   Double_t expon3 = X0*TMath::Exp(-1*l3*t[0]) ;
   p1[0]=p[0];
   p1[1]=p[3];
   p2[0]=p[0];
   p2[1]=p[4];
   p3[0]=p[0];
   p3[1]=p[5];
   if(t[0]>0){
     return pb*l2*(expon1/A+expon2/B+expon3/C); 
   }else{
      return -1;
   }
}
Double_t lX3(Double_t *t, Double_t *p){
   Double_t l3=log(2)/p[5];
   return l3*X3(t,p);
}

Double_t X5(Double_t *t, Double_t *p){
   Double_t p1[4], p5[4];
   Double_t l1=log(2)/p[3];
   Double_t l5=log(2)/p[6];
   Double_t pn=p[1];
   Double_t X0=p[0];
   Double_t expon1 = X0*TMath::Exp(-1*l1*t[0]) ;
   Double_t expon5 = X0*TMath::Exp(-1*l5*t[0]) ;
   p1[0]=p[0];
   p1[3]=p[3];
   p5[0]=p[0];
   p5[3]=p[6];
   if(t[0]>0){
      return pn*(expon1/(l5-l1)+expon5/(l1-l5));
   }else{
      return -1;
   }
}
Double_t lX5(Double_t *t, Double_t *p){
   Double_t l5=log(2)/p[6];
   return l5*X5(t,p);
}

Double_t X8(Double_t *t, Double_t *p){
   Double_t p1[4], p8[4];
   Double_t l1=log(2.0)/p[3];
   Double_t l8=log(2.0)/p[8];
   Double_t p2n=p[2];
   Double_t X0=p[0];
   Double_t expon1 = X0*TMath::Exp(-1*l1*t[0]) ;
   Double_t expon8 = X0*TMath::Exp(-1*l8*t[0]) ;
   Double_t A = (l8-l1);
   Double_t B = (l1-l8);
   p1[0]=p[0];
   p1[3]=p[3];
   p8[0]=p[0];
   p8[3]=p[8];
   if(t[0]>0){
     return p2n*(expon1/A+expon8/B);
   }else{
      return -1;
   }
}
Double_t lX8(Double_t *t, Double_t *p){
   Double_t l8=log(2)/p[8];
   return l8*X8(t,p);
}

Double_t lX9(Double_t *t, Double_t *p){
   Double_t l9=log(2)/p[9];
   return l9*X9(t,p);
}

Double_t dNdt(Double_t *t, Double_t *p){
   //Double_t l1=p[3];
   //Double_t l2=p[4];
   //Double_t l3=p[5];
   //Double_t l5=p[6];
   //Double_t l6=p[7];
   //Double_t l8=p[8];
   if(t[0]>=0){
      //return l1*X1(t,p)+l2*X2(t,p)+l3*X3(t,p)+l5*X5(t,p)+l6*X6(t,p)+p[7];
     //return lX1(t,p)+lX2(t,p)+lX3(t,p)+lX5(t,p)+lX8(t,p)+p[9];
     return lX1(t,p)+p[9];
     //return Xacc(t,p)+p[9];

   }
   else{
      return -1;
   }
}


void fit_decay(int time_bin, Double_t Dtime_L, Double_t Dtime_U, char * CUT){
   long time_L = Dtime_L*1e5;
   long time_U = Dtime_U*1e5;
   Int_t beam_gate = 350;//////
   TFile *f = new TFile(CUT);
   TCanvas *c1 = new TCanvas("c1","c1",0,0,900,700);
   c1->Draw();
   //c1->cd()->SetLogy(1);
   f->Get("decay_curve");
 
   TH1F *h = decay_curve;
 
   //h->SetStats(kFALSE); // Eliminate statistics box
   gStyle->SetOptTitle(0); // Eliminate title
   //c1->TPad::SetTicks(0,1); // Set ticks on left y axis
   //h->GetXaxis()->SetLimits(0,Dtime_U);
   //h->SetMinimum(1);
   //h->SetMaximum(1000000);
   h->GetXaxis()->SetTitle("Time [ms]");
   Int_t width = (Dtime_U-Dtime_L)/time_bin;
   cout<<"width "<<width<<endl;
   h->GetYaxis()->SetTitle(Form("Counts / %d ms",width));
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
   //h->SetMarkerStyle(2);
   //h->SetMarkerSize(1);
 
   h->Rebin(2);
   //h1->SetStats(0);


   //Linear bg
 
   TF1 *myfit = new TF1("myfit",dNdt,Dtime_L,Dtime_U,10);
   TF1 *decay_parent = new TF1("decay_parent",lX1,Dtime_L,Dtime_U,10);
   TF1 *decay_dbeta = new TF1("decay_dbeta",lX2,Dtime_L,Dtime_U,10);
   TF1 *decay_gdbeta = new TF1("decay_gdbeta",lX3,Dtime_L,Dtime_U,10);
   TF1 *decay_dbetan = new TF1("decay_dbetan",lX5,Dtime_L,Dtime_U,10);
   TF1 *decay_dbeta2n = new TF1("decay_dbeta2n",lX8,time_L,time_U,10);
   TF1 *decay_bg = new TF1("decay_bg","[0]",Dtime_L,Dtime_U);

   myfit->SetLineWidth(2);
   myfit->SetLineColor(1);
   myfit->SetLineStyle(1);
   decay_parent->SetLineWidth(2);
   decay_parent->SetLineColor(2);
   decay_parent->SetLineStyle(1);
   decay_dbeta->SetLineWidth(2);
   decay_dbeta->SetLineColor(4);
   decay_dbeta->SetLineStyle(1);
   decay_gdbeta->SetLineWidth(2);
   decay_gdbeta->SetLineColor(3);
   decay_gdbeta->SetLineStyle(1);
   decay_bg->SetLineWidth(2);
   decay_bg->SetLineColor(1);
   decay_bg->SetLineStyle(2);

   // Linear bg
   myfit->SetParNames("X0","Pn","P2n","t1","t2","t3","t5","t6","t8","C","cycle");
   myfit->SetParameters(250,0.2,0.04,33,90,1630,840,10000,1000,0,350);

   myfit->SetParLimits(0,0,1e6);
   //myfit->SetParLimits(1,0,1);
   //myfit->SetParLimits(2,0,1);
   myfit->SetParLimits(3,0,10000000);
   //myfit->SetParLimits(4,0,1000000);
   //myfit->SetParLimits(5,0,1000000);
   //myfit->SetParLimits(6,0,10000);
   //myfit->SetParLimits(7,0,10000);
   //myfit->SetParLimits(8,0,10000);
   myfit->SetParLimits(9,0,100000000);
   myfit->SetParLimits(10,0,500);

   //myfit->FixParameter(0,1e5);
   myfit->FixParameter(1,0.2);
   myfit->FixParameter(2,0.04);
   //myfit->FixParameter(3,0.071);
   myfit->FixParameter(4,680);
   myfit->FixParameter(5,1630);
   myfit->FixParameter(6,840);
   myfit->FixParameter(7,100000000000);
   myfit->FixParameter(8,100000000000);
   //myfit->FixParameter(9,0.188);
   //myfit->FixParameter(10,250);

 

   cout<<"function to fit beta decay curve. assume"<<endl;
   cout<<"the nuclei taken into account are:"<<endl;
   cout<<"X0 ------> X1 ------> X2 ------> X3 ------> X4 (stable)"<<endl;
   cout<<"           --"<<endl;
   cout<<"           -- n emit"<<endl;
   cout<<"           --"<<endl;
   cout<<"           ---------> X5 ------> X6 ------> X7 (stable)"<<endl;
   cout<<"           -"<<endl;
   cout<<"           -  2n emit"<<endl;
   cout<<"           -"<<endl;
   cout<<"           ---------> X8 ------> X9 ------> X10 (stable)"<<endl<<endl;
   cout<<"There are 10 parameters to fit the total curve:"<<endl;
   cout<<"p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]"<<endl;
   cout<<" X0 ,, pn ,, p2n,, t1 ,, t2 ,, t3 ,, t5 ,, t6 ,, t8 ,, C"<<endl<<endl;
   h->Fit("myfit","L","",Dtime_L,Dtime_U);
   c1->Update();
   Double_t *para = myfit->GetParameters();
   Double_t *sig = myfit->GetParErrors();
   decay_parent->SetParameters(para);
   decay_dbeta->SetParameters(para);
   decay_gdbeta->SetParameters(para);
   decay_dbetan->SetParameters(para);
   decay_dbeta2n->SetParameters(para);
   decay_bg->SetParameters(&para[9]);
   myfit->Draw("same");
   //decay_parent->Draw("same");
   //decay_dbeta->Draw("same");
   //decay_gdbeta->Draw("same");
   //decay_dbetan->Draw("same");
   //decay_dbeta2n->Draw("same");
   decay_bg->Draw("same");

   Double_t time1 = para[3];
   Double_t sigma1 = sig[3];
   Double_t t_half1 = time1;
   Double_t t_error1 = sigma1;
   Double_t time2 = para[4];
   Double_t sigma2 = sig[4];
   Double_t t_half2 = time2;
   Double_t t_error2 = sigma2;
   Double_t time3 = para[5];
   Double_t sigma3 = sig[5];
   Double_t t_half3 = time3;
   Double_t t_error3 = sigma3;
   Double_t time4 = para[6];
   Double_t sigma4 = sig[6];
   Double_t t_half4 = time4;
   Double_t t_error4 = sigma4;

   //Double_t lambda4 = para[8];
   //Double_t sigma4 = sig[8];
   //Double_t t_half4 = log(2)*10*1e-9/lambda4;
   //Double_t t_error4=log(2)/lambda4*sigma4/lambda4*10*1e-9;
   //Double_t counts = decay_parent->Integral(0,Dtime_U)/width;

  Char_t legend1[200],legend2[200],legend3[200],legend4[200],legend5[200];
  Double_t integral = myfit->Integral(beam_gate,Dtime_U)/width;
  sprintf(legend1,"#font[132]{#scale[1]{t_{1/2}^{^{149}Cs} = %0.1f(%0.1f) ms}}",t_half1,t_error1);
  sprintf(legend2,"#font[132]{#scale[1]{t_{1/2}^{^{72}Ni} = %0.1f(%0.1f) ms}}",t_half2,t_error2);
  sprintf(legend3,"#font[132]{#scale[1]{t_{1/2}^{^{72}Cu} = %0.1f(%0.1f) ms}}",t_half3,t_error3);
  sprintf(legend4,"#font[132]{#scale[1]{t_{1/2}^{^{71}Ni} = %0.1f(%0.1f) ms}}",t_half4,t_error4);
  sprintf(legend5,"#font[132]{#scale[1]{counts = %d}}",integral);
  TLatex *t1=new TLatex( 2000, 50,legend1);
  TLatex *t2=new TLatex( 50, 50000, legend2);
  TLatex *t3=new TLatex( 50, 30000, legend3);
  TLatex *t4=new TLatex( 50, 20000, legend4);
  TLatex *t5=new TLatex( 3000,10, legend5);

 
  t1->Draw();
  // t2->Draw();
  //t3->Draw();
  //t4->Draw();
  t5->Draw();


   cout<<"T1/2(parent) = "<<setiosflags(ios::fixed)<<setprecision(4)<<t_half1<<" ± "<<setiosflags(ios::fixed)<<setprecision(4)<<t_error1<<" ms"<<endl;
   //cout<<"T1/2(beta_daughter) = "<<setiosflags(ios::fixed)<<setprecision(4)<<t_half2<<" ± "<<setiosflags(ios::fixed)<<setprecision(4)<<t_error2<<" ms"<<endl;
   //cout<<"T1/2(beta_gdaughter) = "<<setiosflags(ios::fixed)<<setprecision(4)<<t_half3<<" ± "<<setiosflags(ios::fixed)<<setprecision(4)<<t_error3<<" ms"<<endl;
   //cout<<"T1/2(n_beta_daughter) = "<<setiosflags(ios::fixed)<<setprecision(4)<<t_half4<<" ± "<<setiosflags(ios::fixed)<<setprecision(4)<<t_error4<<" ms"<<endl;
   cout<<"Counts for parent decay = "<<integral<<endl;
   //cout<<"Counts for parent decay = "<<decay_parent->Integral(0,Dtime_U)/width<<endl;
   //cout<<"T1/2(15C) = "<<setiosflags(ios::fixed)<<setprecision(2)<<t_half4*1000<<" ± "<<setiosflags(ios::fixed)<<setprecision(2)<<t_error4*1000<<" ms"<<endl;
}