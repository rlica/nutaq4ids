
//RUN WITH: root -l -q root2spec.C"(Run_no)"; 


void root2spec(const int Run_no){

const char *E    = "E_Ge1"; 
const int SIZE = 8192;
int spec[SIZE] = {}; //zero all elements
int overflow=0, underflow=0, entries=0;

FILE *fp;
fp=fopen(Form("spec%03d.a%d", Run_no, SIZE/1000), "wt");

TChain t("t");
//t.Add( Form("Run%03d.root", Run_no) );
t.Add( Form("80Ga_list_%04d.bin.root", Run_no) );

TLeaf *leaf = t.GetLeaf(E);
				


for (int i = 0; i < t.GetEntries(); i++) {
	leaf->GetBranch()->GetEntry(i);
	int value = leaf->GetValue();
	if (value > 0) {
		if  (value < SIZE) {
			spec[value]++;
			entries++;
		}
		else overflow++;
	}
	else underflow++;
}


for (int i = 0; i < SIZE; i++) {
	fprintf(fp, "%d\n", spec[i]);
}

cout << "Data written to " << Form("spec%03d.a%d", Run_no, SIZE/1000) << endl;
cout << "Valid entries: " << entries << " Overflow: " << overflow << " Underflow: " << underflow << endl;   



}
