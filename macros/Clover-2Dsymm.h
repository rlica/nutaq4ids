//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Nov 13 16:26:12 2014 by ROOT version 5.32/04
// from TTree ids/Isolde Decay Station Tree
// found on file: Run045.root
//////////////////////////////////////////////////////////

#ifndef Clover-2Dsymm_h
#define Clover-2Dsymm_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Clover-2Dsymm : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   // Declaration of leaf types
   Int_t           Multiplicity;
   Int_t           Time vs_ ref;
   Int_t           Energy_Clov1;
   Int_t           Energy_Clov2;
   Int_t           Energy_Clov3;
   Int_t           Energy_Clov4;
   Int_t           Energy_Beta;
   Int_t           Energy_La2;
   Int_t           Energy_TacBetaLa2;
   Int_t           Energy_La1;
   Int_t           Energy_TacBetaLa1;
   Int_t           Energy_TacLa1La2;
   Int_t           Energy_PROTON;
   Int_t           Time_Clov1;
   Int_t           Time_Clov2;
   Int_t           Time_Clov3;
   Int_t           Time_Clov4;
   Int_t           Time_Beta;
   Int_t           Time_La2;
   Int_t           Time_TacBetaLa2;
   Int_t           Time_La1;
   Int_t           Time_TacBetaLa1;
   Int_t           Time_TacLa1La2;
   Int_t           Time_PROTON;

   // List of branches
   TBranch        *b_MULT;   //!
   TBranch        *b_TIME;   //!
   TBranch        *b_E_Clov1;   //!
   TBranch        *b_E_Clov2;   //!
   TBranch        *b_E_Clov3;   //!
   TBranch        *b_E_Clov4;   //!
   TBranch        *b_E_Beta;   //!
   TBranch        *b_E_La2;   //!
   TBranch        *b_E_TacBetaLa2;   //!
   TBranch        *b_E_La1;   //!
   TBranch        *b_E_TacBetaLa1;   //!
   TBranch        *b_E_TacLa1La2;   //!
   TBranch        *b_E_PROTON;   //!
   TBranch        *b_T_Clov1;   //!
   TBranch        *b_T_Clov2;   //!
   TBranch        *b_T_Clov3;   //!
   TBranch        *b_T_Clov4;   //!
   TBranch        *b_T_Beta;   //!
   TBranch        *b_T_La2;   //!
   TBranch        *b_T_TacBetaLa2;   //!
   TBranch        *b_T_La1;   //!
   TBranch        *b_T_TacBetaLa1;   //!
   TBranch        *b_T_TacLa1La2;   //!
   TBranch        *b_T_PROTON;   //!

   Clover-2Dsymm(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Clover-2Dsymm() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(Clover-2Dsymm,0);
};

#endif

#ifdef Clover-2Dsymm_cxx
void Clover-2Dsymm::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Multiplicity", &Multiplicity, &b_MULT);
   fChain->SetBranchAddress("Time vs. ref", &Time vs_ ref, &b_TIME);
   fChain->SetBranchAddress("Energy_Clov1", &Energy_Clov1, &b_E_Clov1);
   fChain->SetBranchAddress("Energy_Clov2", &Energy_Clov2, &b_E_Clov2);
   fChain->SetBranchAddress("Energy_Clov3", &Energy_Clov3, &b_E_Clov3);
   fChain->SetBranchAddress("Energy_Clov4", &Energy_Clov4, &b_E_Clov4);
   fChain->SetBranchAddress("Energy_Beta", &Energy_Beta, &b_E_Beta);
   fChain->SetBranchAddress("Energy_La2", &Energy_La2, &b_E_La2);
   fChain->SetBranchAddress("Energy_TacBetaLa2", &Energy_TacBetaLa2, &b_E_TacBetaLa2);
   fChain->SetBranchAddress("Energy_La1", &Energy_La1, &b_E_La1);
   fChain->SetBranchAddress("Energy_TacBetaLa1", &Energy_TacBetaLa1, &b_E_TacBetaLa1);
   fChain->SetBranchAddress("Energy_TacLa1La2", &Energy_TacLa1La2, &b_E_TacLa1La2);
   fChain->SetBranchAddress("Energy_PROTON", &Energy_PROTON, &b_E_PROTON);
   fChain->SetBranchAddress("Time_Clov1", &Time_Clov1, &b_T_Clov1);
   fChain->SetBranchAddress("Time_Clov2", &Time_Clov2, &b_T_Clov2);
   fChain->SetBranchAddress("Time_Clov3", &Time_Clov3, &b_T_Clov3);
   fChain->SetBranchAddress("Time_Clov4", &Time_Clov4, &b_T_Clov4);
   fChain->SetBranchAddress("Time_Beta", &Time_Beta, &b_T_Beta);
   fChain->SetBranchAddress("Time_La2", &Time_La2, &b_T_La2);
   fChain->SetBranchAddress("Time_TacBetaLa2", &Time_TacBetaLa2, &b_T_TacBetaLa2);
   fChain->SetBranchAddress("Time_La1", &Time_La1, &b_T_La1);
   fChain->SetBranchAddress("Time_TacBetaLa1", &Time_TacBetaLa1, &b_T_TacBetaLa1);
   fChain->SetBranchAddress("Time_TacLa1La2", &Time_TacLa1La2, &b_T_TacLa1La2);
   fChain->SetBranchAddress("Time_PROTON", &Time_PROTON, &b_T_PROTON);
}

Bool_t Clover-2Dsymm::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Clover-2Dsymm_cxx
