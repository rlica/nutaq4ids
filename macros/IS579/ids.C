{
//////////////////////////////////////////////////////////
//   This file has been automatically generated 
//     (Mon Dec  1 19:39:13 2014 by ROOT version5.34/20)
//   from TTree chain/Isolde Decay Station Tree
//   found on file: Run075.root
//////////////////////////////////////////////////////////


//Reset ROOT and connect tree file
//   gROOT->Reset();
//   TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Run075.root");
//   if (!f) {
 //     f = new TFile("Run075.root");
 //  }
//    f->GetObject("ids",tree);

	TH1F *btime = new TH1F("TIME","Time with repspect to proton",5000,0,5000);
	TH1F *eclov1 = new TH1F("E_Clov1","Eclov1",2048,0,2048);
	TH1F *eclov2 = new TH1F("E_Clov2","Eclov2",2048,0,2048);
	TH1F *eclov3 = new TH1F("E_Clov3","Eclov3",2048,0,2048);
	TH1F *eclov4 = new TH1F("E_Clov4","Eclov4",2048,0,2048);
	TH1F *eclov = new TH1F("E_Clov","Eclov",2048,0,2048);
	TH1F *eclovbg = new TH1F("E_Clovbg","Eclovbg",2048,0,2048);

//Declaration of leaves types
   Int_t           MULT;
   Int_t           TIME;
   Int_t           E_Clov1;
   Int_t           E_Clov2;
   Int_t           E_Clov3;
   Int_t           E_Clov4;
   Int_t           E_TAC_La1_La2;
   Int_t           E_TAC_BM_La1;
   Int_t           E_TAC_BM_La2;
   Int_t           E_TAC_BR_La1;
   Int_t           E_TAC_BL_La2;
   Int_t           E_La1;
   Int_t           E_La2;
   Int_t           E_Beta_M;
   Int_t           E_Beta_L;
   Int_t           E_Beta_R;
   Int_t           E_Proton_T1;
   Int_t           E_Tape_Start;
   Int_t           T_Clov1;
   Int_t           T_Clov2;
   Int_t           T_Clov3;
   Int_t           T_Clov4;
   Int_t           T_TAC_La1_La2;
   Int_t           T_TAC_BM_La1;
   Int_t           T_TAC_BM_La2;
   Int_t           T_TAC_BR_La1;
   Int_t           T_TAC_BL_La2;
   Int_t           T_La1;
   Int_t           T_La2;
   Int_t           T_Beta_M;
   Int_t           T_Beta_L;
   Int_t           T_Beta_R;
   Int_t           T_Proton_T1;
   Int_t           T_Tape_Start;

   // Set branch addresses.
   chain->SetBranchAddress("Multiplicity",&MULT);
   chain->SetBranchAddress("Time vs. ref",&TIME);
   chain->SetBranchAddress("Energy_Clov1",&E_Clov1);
   chain->SetBranchAddress("Energy_Clov2",&E_Clov2);
   chain->SetBranchAddress("Energy_Clov3",&E_Clov3);
   chain->SetBranchAddress("Energy_Clov4",&E_Clov4);
   chain->SetBranchAddress("Energy_TAC_La1_La2",&E_TAC_La1_La2);
   chain->SetBranchAddress("Energy_TAC_BM_La1",&E_TAC_BM_La1);
   chain->SetBranchAddress("Energy_TAC_BM_La2",&E_TAC_BM_La2);
   chain->SetBranchAddress("Energy_TAC_BR_La1",&E_TAC_BR_La1);
   chain->SetBranchAddress("Energy_TAC_BL_La2",&E_TAC_BL_La2);
   chain->SetBranchAddress("Energy_La1",&E_La1);
   chain->SetBranchAddress("Energy_La2",&E_La2);
   chain->SetBranchAddress("Energy_Beta_M",&E_Beta_M);
   chain->SetBranchAddress("Energy_Beta_L",&E_Beta_L);
   chain->SetBranchAddress("Energy_Beta_R",&E_Beta_R);
   chain->SetBranchAddress("Energy_Proton_T1",&E_Proton_T1);
   chain->SetBranchAddress("Energy_Tape_Start",&E_Tape_Start);
   chain->SetBranchAddress("Time_Clov1",&T_Clov1);
   chain->SetBranchAddress("Time_Clov2",&T_Clov2);
   chain->SetBranchAddress("Time_Clov3",&T_Clov3);
   chain->SetBranchAddress("Time_Clov4",&T_Clov4);
   chain->SetBranchAddress("Time_TAC_La1_La2",&T_TAC_La1_La2);
   chain->SetBranchAddress("Time_TAC_BM_La1",&T_TAC_BM_La1);
   chain->SetBranchAddress("Time_TAC_BM_La2",&T_TAC_BM_La2);
   chain->SetBranchAddress("Time_TAC_BR_La1",&T_TAC_BR_La1);
   chain->SetBranchAddress("Time_TAC_BL_La2",&T_TAC_BL_La2);
   chain->SetBranchAddress("Time_La1",&T_La1);
   chain->SetBranchAddress("Time_La2",&T_La2);
   chain->SetBranchAddress("Time_Beta_M",&T_Beta_M);
   chain->SetBranchAddress("Time_Beta_L",&T_Beta_L);
   chain->SetBranchAddress("Time_Beta_R",&T_Beta_R);
   chain->SetBranchAddress("Time_Proton_T1",&T_Proton_T1);
   chain->SetBranchAddress("Time_Tape_Start",&T_Tape_Start);

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// chain->SetBranchStatus("*",0);  // disable all branches
// TTreePlayer->SetBranchStatus("branchname",1);  // activate branchname

   Long64_t nentries = chain->GetEntries();

   Long64_t nbytes = 0;
   for (Long64_t i=0; i<nentries;i++) {
	E_Clov1=0;



      nbytes += chain->GetEntry(i);
	btime->Fill(TIME);
//	eclov1->Fill(E_Clov1);
//	eclov2->Fill(E_Clov2);
//	eclov3->Fill(E_Clov3);
//	eclov4->Fill(E_Clov4);
//	if (TIME>10&&TIME<60&&MULT>2){
	if (TIME>10&&TIME<60){
//	btime->Fill(TIME);
	if (T_Clov1>800){
		eclov->Fill(E_Clov1);
	}
	if (T_Clov2>800){
		eclov->Fill(E_Clov2);
	}
	if (T_Clov3>800){
		eclov->Fill(E_Clov3);
	}
	if (T_Clov4>800){
		eclov->Fill(E_Clov4);
	}
		eclov1->Fill(E_Clov1);
		eclov2->Fill(E_Clov2);
		eclov3->Fill(E_Clov3);
		eclov4->Fill(E_Clov4);
	}
		if (TIME>70&&TIME<120){
			if (T_Clov1>800){
				eclovbg->Fill(E_Clov1);
			}
			if (T_Clov2>800){
				eclovbg->Fill(E_Clov2);
			}
			if (T_Clov3>800){
				eclovbg->Fill(E_Clov3);
			}
			if (T_Clov4>800){
				eclovbg->Fill(E_Clov4);
			}
		}
			

   }
}