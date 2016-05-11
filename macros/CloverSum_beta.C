// Estimate the total yield of 31Ar

void CloverSum_beta(){


  gROOT->Reset();
  gStyle->SetOptStat(1000000);
  
  
  TChain ids("ids");
  ids.Add("Run078.root");
  //ids.Add("Run046.root");
  //ids.Add("Run047.root");
  
  

  TH1I *hTemp = new TH1I("hTemp","",8000,1,8000);
  TH1I *hSum_gated =  new TH1I("hSum_gated" ,"Beta gated Clover Sum",8000,1,8000);
  TH1I *hSum       =  new TH1I("hSum" ,"Clover Sum",8000,1,8000);
  
  TCanvas *Can1;
  Can1 = new TCanvas("Can1","Can1",800,800); 
  Can1->Divide(1,2);

  /////GATED SUM
 
  
  TPad *p1 = (TPad *)(Can1->cd(1)); 
  const char *gate = "E_Beta>0";
  
 
  cout << "Reading beta gated Clover 1\n";
  ids.Draw("E_Clov1>>hTemp",gate);
  hSum_gated->Add(hTemp);
  
  printf("Reading beta gated Clover 2\n");
  ids.Draw("E_Clov2>>hTemp",gate);
  hSum_gated->Add(hTemp);
  
  printf("Reading beta gated Clover 3\n");
  ids.Draw("E_Clov3>>hTemp",gate);
  hSum_gated->Add(hTemp);
   
  printf("Reading beta gated Clover 4\n");
  ids.Draw("E_Clov4>>hTemp",gate);
  hSum_gated->Add(hTemp);
   
  
  hSum_gated->Draw();
  printf("Finished drawing beta gated Clover Sum\n\n");
  
  
  
  
  ///////SUM 
  TPad *p2 = (TPad *)(Can1->cd(2)); 
  const char *gate = "";
  
  printf("Reading Clover 1\n");
  ids.Draw("E_Clov1>>hTemp",gate);
  hSum->Add(hTemp);
  
  printf("Reading Clover 2\n");
  ids.Draw("E_Clov2>>hTemp",gate);
  hSum->Add(hTemp);
  
  printf("Reading Clover 3\n");
  ids.Draw("E_Clov3>>hTemp",gate);
  hSum->Add(hTemp);
   
  printf("Reading Clover 4\n");
  ids.Draw("E_Clov4>>hTemp",gate);
  hSum->Add(hTemp);
   
  hSum->SetLineColor(2);
  hSum->Draw();
  printf("Finished drawing Clover Sum\n\n");
  
  


}
