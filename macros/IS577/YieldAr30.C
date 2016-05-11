// Estimate the total yield of 31Ar

void YieldAr31(){

gStyle->SetOptStat(1000001);

// Get the number of events in U4 and U6 which a) look like protons
// and b) look like they come from 31Ar decay

TCut U4Energy = Form("UFOUR_F_E>400 && UFOUR_F_E<2500");
TCut U6Energy = Form("USIX_F_E>400 && USIX_F_E<2500");

TCut TIME = Form("TPROTONS>0 && TPROTONS<50e6");

UInt_t YieldU4 = h101->GetEntries(U4Energy && TIME);
UInt_t YieldU6 = h101->GetEntries(U6Energy && TIME);

// Statistical uncertanties on yields

Float_t ErrorU4 = YieldU4**0.5/YieldU4;
Float_t ErrorU6 = YieldU6**0.5/YieldU6;

// Estimated solid angles of detectors
Float_t SolidAngleU4 = 0.093;
Float_t SolidAngleU6 = 0.075;

// Get the number of T1 pulses (trigger type 2)
UInt_t Pulses = h101->GetEntries("TRIGGER==2");

// Set a rough number for the micro coulombs per pulse
Float_t Coulombs = 5.12;

// An estimate for the proton branching ratio
Float_t ProtonBR = 0.77;

// Calculate the yield per unit charge
Float_t RateU4 = YieldU4 / (SolidAngleU4 * ProtonBR * Pulses * Coulombs);
Float_t RateU6 = YieldU6 / (SolidAngleU6 * ProtonBR * Pulses * Coulombs);

// Uncertainties
Float_t StatErrU4 = RateU4 * ErrorU4;
Float_t StatErrU6 = RateU6 * ErrorU6;

// Give some output

cout << "*** Estimated yields per uC for 31Ar production ***" << endl;
cout << "*** Errors are statistical only ***" << endl;

cout << "U4 estimate: " << RateU4 << " ± " << StatErrU4 << endl;
cout << "U6 estimate: " << RateU6 << " ± " << StatErrU6 << endl;
	
// Draw some plots	

TCanvas *Can1;
Can1 = new TCanvas("Can1","Can1",800,800);
Can1->SetLogy();
Can1->Divide(2,2);

TPad *p1 = (TPad *)(Can1->cd(1)); 
p1->SetLogy();
h101->Draw("UFOUR_F_E>>E4(500,0,3000)");
TPad *p2 = (TPad *)(Can1->cd(2)); 
p2->SetLogy();
h101->Draw("USIX_F_E>>E6(500,0,3000)");
TPad *p3 = (TPad *)(Can1->cd(3)); 
p3->SetLogy();
h101->Draw("TPROTONS>>T4(100,0,50e6)","UFOUR_F_E>400 && UFOUR_F_E<2500");
TPad *p4 = (TPad *)(Can1->cd(4)); 
p4->SetLogy();
h101->Draw("TPROTONS>>T6(100,0,50e6)","USIX_F_E>400 && USIX_F_E<2500");

}
