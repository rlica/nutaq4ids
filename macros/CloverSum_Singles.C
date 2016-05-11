// Estimate the total yield of 31Ar

void CloverSum_Singles(){


  gROOT->Reset();
  gStyle->SetOptStat(0000001);

  
  TH1I *hTemp = new TH1I("hTemp","",16384,1,16384);
  TH1I *hSum_gated =  new TH1I("hSum_gated" ,"Clover Sum (Addback)",16384,1,16384);
  TH1I *hSum       =  new TH1I("hSum" ,"Clover Sum (no Addback)",16384,1,16384);
  
  TCanvas *Can1;
  Can1 = new TCanvas("Can1","Can1",800,800); 
  Can1->Divide(1,2);

  /////Addback SUM
  
  TPad *p1 = (TPad *)(Can1->cd(1)); 
  
  const char *gate = "";
  
  ids->Draw("E_Clov1>>hTemp",gate);
  hSum_gated->Add(hTemp);
  
  ids->Draw("E_Clov2>>hTemp",gate);
  hSum_gated->Add(hTemp);
   
  ids->Draw("E_Clov3>>hTemp",gate);
  hSum_gated->Add(hTemp);
   
  ids->Draw("E_Clov4>>hTemp",gate);
  hSum_gated->Add(hTemp);
   
  
  hSum_gated->Draw();
  
  
  ///////No addback SUM 
  TPad *p2 = (TPad *)(Can1->cd(2)); 
  
  hSum->Add(h0_Clov1);
  hSum->Add(h1_Clov1);
  hSum->Add(h2_Clov1);
  hSum->Add(h3_Clov1);
  hSum->Add(h4_Clov2);
  hSum->Add(h5_Clov2);
  hSum->Add(h6_Clov2);
  hSum->Add(h7_Clov2);
  hSum->Add(h8_Clov3);
  hSum->Add(h9_Clov3);
  hSum->Add(h10_Clov3);
  hSum->Add(h11_Clov3);
  hSum->Add(h12_Clov4);
  hSum->Add(h13_Clov4);
  hSum->Add(h14_Clov4);
  hSum->Add(h15_Clov4);
  
    
  hSum->SetLineColor(kRed);
  hSum->Draw();
  
  


}
