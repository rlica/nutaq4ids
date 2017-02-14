
//RUN WITH: root -l -q root2spec.C"(Run_no)"; 


//define calibration coefficients calib[nr of det][calibration order]
// detector numbering starts from 1
// calibration order = 2 (linear function = p0+p1*x), 3 (quadratic), etc. 

float calib[2][2] = { 	1, 0.15, 
						1, 0.15, 
					}; 

const char *E1    = "E_Ge1", 
		   *E2    = "E_Ge2", 
		   *T1    = "T_Ge1", 
		   *T2    = "T_Ge2"; 
		   
const int TIMEGATE = 30;
const int SIZE = 8192;



int calibrate(int id, int energy) {
  
    int i;
    const int MAX_CAL = 2; 
	double prob;
	double d_energy = 0;
	int    i_energy = 0;
	gRandom = new TRandom3();

	for (i=0; i<MAX_CAL; i++)
		d_energy += calib[id-1][i] * pow(energy, i);
	 
	i_energy = d_energy;
	
   
	prob = (d_energy - i_energy);

  
	if (gRandom->Rndm() < prob) i_energy += 1;
	
	return i_energy;

}

void root2mat(const int Run_no){


int mat[SIZE][SIZE] = {}; //zero all elements
int overflow=0, entries=0;
srand(time(0));

FILE *fp;
fp=fopen(Form("%s-%s_%03d.mat", E1, E2, Run_no), "wb");

TChain t("t");
t.Add( Form("80Ga_list_%04d.bin.root", Run_no) );

TLeaf *leafE1 = t.GetLeaf(E1),
	  *leafE2 = t.GetLeaf(E2),
	  *leafT1 = t.GetLeaf(T1),
	  *leafT2 = t.GetLeaf(T2);



for (int i = 0; i < t.GetEntries(); i++) {
	
	
	leafE1->GetBranch()->GetEntry(i);
	leafE2->GetBranch()->GetEntry(i);
	leafT1->GetBranch()->GetEntry(i);
	leafT2->GetBranch()->GetEntry(i);

	int valueE1 = leafE1->GetValue(); 
	int valueE2 = leafE2->GetValue();
	int valueT1 = leafT1->GetValue();
	int valueT2 = leafT2->GetValue();
		
	//calibrate	
	if  (valueE1 > 0 && valueE2 > 0) {
		valueE1 = calibrate(1, valueE1);
		valueE2 = calibrate(2, valueE2);
	}
		
	if  (valueE1 > 0 && valueE2 > 0) {
		if (valueE1 < SIZE && valueE2 < SIZE) {
			if (abs(valueT1-valueT2) < TIMEGATE) {
				
				printf (" Processing entry %d / %d (%d \%) \r", i, t.GetEntries(), 1+100*i/t.GetEntries());
								
				mat[valueE1][valueE2]++;
				//mat[valueE2][valueE1]++; //uncomment for SYMM Matrix
				
				entries++;
			}
		}
		else overflow++;
	}


}

for (int i = 0; i<SIZE; i++) {
	fwrite (&mat[i], 1, SIZE*sizeof(int), fp);
}


cout << "\n Data written to " << Form("%s-%s_%03d.mat", E1, E2, Run_no) << endl;
cout << " Entries: " << entries << " Overflow: " << overflow << endl;   



}
