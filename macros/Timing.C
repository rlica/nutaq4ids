
//ids->Draw("E_TacBetaLa1:E_La1>>(1000,0,2000,16000,0,16000)", "E_La1>0 && E_Beta>0 && E_TacBetaLa1>0", "colz")
//ids->Draw("E_TacBetaLa1>>(1500,3000,4500)", "E_La1>475 && E_Beta>0 && E_La1 < 543 && E_TacBetaLa1>0")

void Timing(){

  gROOT->Reset();
  gStyle->SetOptStat(1000000);
  gStyle->SetOptFit(11);

  
  //Define Detectors
  const char *E    = "E_La1",
             *Trig = "E_Beta",
             *Tac  = "E_TacBetaLa1";
  
  
  //Define Gates
  int   E_gate_low  = 300,
        E_gate_high = 330,
  
        E_bg_low    = 330,
        E_bg_high   = 365,
  
      Trig_gate_low  = 740,
      Trig_gate_high = 1840;
      
  int    Tac_range_low  = 1900,
         Tac_range_high = 2150;
  

  double mean, err_mean, sigma, fwhm;
  
  //fwhm = 2.35482 * sigma 
  
  
  TChain ids("ids");
  ids.Add("Run045.root");
  //ids.Add("Run046.root");
  //ids.Add("Run047.root");



  //Scaling factor for background subtraction
  float NORM = -(float)(E_gate_high - E_gate_low) / (float)(E_bg_high - E_bg_low);
  
  
  
  
  
  const char *gate    = Form("%s>%d && %s<%d && %s>%d && %s<%d", 
                          E, E_gate_low, E, E_gate_high, Trig, Trig_gate_low, Trig, Trig_gate_high);
  const char *bg_gate = Form("%s>%d && %s<%d && %s>%d && %s<%d", 
                          E, E_bg_low,   E, E_bg_high,   Trig, Trig_gate_low, Trig, Trig_gate_high);

  
  TH1I *hTemp      = new TH1I("hTemp","",8000,1,8000);
  TH1I *hGate     =  new TH1I("hGated", Form("%s (%d,%d) - Peak",E, E_gate_low, E_gate_high)   ,8000,1,8000);
  TH1I *hBGGate   =  new TH1I("hBG"   , Form("%s (%d,%d) - Background",E, E_bg_low, E_bg_high) ,8000,1,8000);
  TH1I *hFinal    =  new TH1I("hFinal", Form("Background subtracted. Scaling factor %f", NORM) ,8000,1,8000);
  
  TCanvas *Can1;
  Can1 = new TCanvas("FastTiming","Fast Timing",800,800); 
  Can1->Divide(1,3);

 
  
  
  
  //Peak
  TPad *p1 = (TPad *)(Can1->cd(1));
  printf("Reading %s with gate %s\n", Tac, gate);
  ids.Draw(Form("%s>>hTemp", Tac),gate);
  hGate->Add(hTemp);
  hGate->GetXaxis()->SetRangeUser(Tac_range_low, Tac_range_high);
  hGate->Draw();
  hGate->Fit("gaus");
  
  
  //Background
  TPad *p2 = (TPad *)(Can1->cd(2)); 
  printf("Reading %s with gate %s\n", Tac, bg_gate);
  ids.Draw(Form("%s>>hTemp", Tac),bg_gate);
  hBGGate->Add(hTemp);
  hBGGate->GetXaxis()->SetRangeUser(Tac_range_low, Tac_range_high);
  hBGGate->Draw();
  hBGGate->Fit("gaus");

  //Final (Peak - Background)
  TPad *p3 = (TPad *)(Can1->cd(3)); 
  
  hFinal->Add(hGate);
  hFinal->Add(hBGGate,NORM);
  hFinal->GetXaxis()->SetRangeUser(Tac_range_low, Tac_range_high);
  hFinal->Draw();
  hFinal->Fit("gaus");

  
}
