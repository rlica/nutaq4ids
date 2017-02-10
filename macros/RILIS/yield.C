// Estimate the total yield of 31Ar
//RUN WITH: root -l -q yield.C"(Run_no)"; 


void yield(const int Run_no){
	
		
const char *E    = "E_NIM"; 
int left = 0,
	right = 3000;
float unit_time = 0.1; //  in seconds
	
		
FILE *fp;
fp=fopen(Form("out%d.txt", Run_no), "wt");

TChain ids("ids");
ids.Add( Form("Run%03d.root", Run_no) );
		
gStyle->SetOptStat(1000001);

//Reading the recording time
float rec_time;

TLeaf *leaf_T = ids.GetLeaf("TIMESTAMP");
   leaf_T->GetBranch()->GetEntry(1);
   rec_time = leaf_T->GetValue();
   leaf_T->GetBranch()->GetEntry(ids.GetEntries()-1);
   rec_time = (leaf_T->GetValue() - rec_time) * unit_time;
   cout << "Rec time = " << rec_time << " s" << endl;



//Reading the AREA
TCut E_LIMITS = Form("%s>%d && %s<%d", E, left, E, right);
int AREA = ids.GetEntries(E_LIMITS);
float RATE = AREA / rec_time;

int Error_AREA = AREA**0.5;
cout << "Area = " << AREA << " (" << Error_AREA << ")" << endl;
cout << "Rate = " << RATE << endl;


// Write to output file

fprintf(fp, "%.1f\n", RATE);







}
