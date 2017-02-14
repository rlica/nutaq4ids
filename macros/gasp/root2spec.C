
//RUN WITH: root -l -q root2spec.C"(Run_no)"; 

//define calibration coefficients calib[calibration order]
// calibration order = 2 (linear function = p0+p1*x), 3 (quadratic), etc. 

float calib[2]    = { 0, 1 }; //p0, p1

const char *E    = "E_Ge1"; 
const int SIZE = 16384;


int calibrate(int energy) {
  
    int i;
    const int MAX_CAL = 2; 
	double prob;
	double d_energy = 0;
	int    i_energy = 0;
	gRandom = new TRandom3();

	for (i=0; i<MAX_CAL; i++)
		d_energy += calib[i] * pow(energy, i);
	 
	i_energy = d_energy;
	
   
	prob = (d_energy - i_energy);

  
	if (gRandom->Rndm() < prob) i_energy += 1;
	
	return i_energy;

}



void root2spec(const int Run_no){


int spec[SIZE] = {}; //zero all elements
int overflow=0, entries=0;

FILE *fp;
fp=fopen(Form("spec%03d.a%d", Run_no, SIZE/1000), "wt");

TChain t("t");
//t.Add( Form("Run%03d.root", Run_no) );
t.Add( Form("80Ga_list_%04d.bin.root", Run_no) );

TLeaf *leaf = t.GetLeaf(E);
				


for (int i = 0; i < t.GetEntries(); i++) {
	leaf->GetBranch()->GetEntry(i);
	int value = leaf->GetValue();
	
	if (value > 0) value = calibrate(value);
	
	if (value > 0) {
		if  (value < SIZE) {

			printf (" Processing entry %d / %d (%d \%) \r", i, t.GetEntries(), 1+100*i/t.GetEntries());

			spec[value]++;
			entries++;
		}
		else overflow++;
	}
}


for (int i = 0; i < SIZE; i++) {
	fprintf(fp, "%d\n", spec[i]);
}

cout << "\n Data written to " << Form("spec%03d.a%d", Run_no, SIZE/1000) << endl;
cout << " Valid entries: " << entries << " Overflow: " << overflow << endl;   



}
