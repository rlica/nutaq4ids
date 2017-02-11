
//RUN WITH: root -l -q root2spec.C"(Run_no)"; 


void root2mat(const int Run_no){

const char *E1    = "E_Ge1", 
		   *E2    = "E_Ge2", 
		   *T1    = "T_Ge1", 
		   *T2    = "T_Ge2"; 
		   
const int TIMEGATE = 30;
const int SIZE = 8192;
int mat[SIZE][SIZE];
int overflow=0, underflow=0, entries=0;

FILE *fp;
fp=fopen(Form("%s-%s_%03d.mat", E1, E2, Run_no), "wb");

TChain t("t");
t.Add( Form("80Ga_list_%04d.bin.root", Run_no) );

TLeaf *leafE1 = t.GetLeaf(E1),
	  *leafE2 = t.GetLeaf(E2),
	  *leafT1 = t.GetLeaf(T1),
	  *leafT2 = t.GetLeaf(T2);

for (int i = 0; i<SIZE; i++) {
	for (int j = 0; j<SIZE; j++) {
		mat[i][j] = 0;
	}
}

for (int i = 0; i < t.GetEntries(); i++) {
	
	leafE1->GetBranch()->GetEntry(i);
	leafE2->GetBranch()->GetEntry(i);
	leafT1->GetBranch()->GetEntry(i);
	leafT2->GetBranch()->GetEntry(i);

	int valueE1 = leafE1->GetValue();
	int valueE2 = leafE2->GetValue();
	int valueT1 = leafT1->GetValue();
	int valueT2 = leafT2->GetValue();
	
	
	
	if  (valueE1 > 0 && valueE2 > 0) {
		if (valueE1 < SIZE && valueE2 < SIZE) {
			if (abs(valueT1-valueT2) < TIMEGATE) {
				mat[valueE1][valueE2]++;
				entries++;
			}
		}
		else overflow++;
	}
	else underflow++;

}

for (int i = 0; i<SIZE; i++) {
	fwrite (&mat[i], 1, SIZE*sizeof(int), fp);
}


cout << "Data written to " << Form("%s-%s_%03d.mat", E1, E2, Run_no) << endl;
cout << "Entries: " << entries << " Overflow: " << overflow << endl;   



}
