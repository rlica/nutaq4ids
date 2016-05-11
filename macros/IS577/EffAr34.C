
void EffAr34(){
	gStyle->SetOptStat(1111111);

	char*	si	= "PONE";
	char* ge 	= "GEONE1";
	FILE *myfile = fopen(Form("EffGamma_34Ar_%s_%s.dat",si,ge),"a+");
	//ifstream myfile;
	//myfile.open(Form("EffGamma_34Ar_%s_%s.dat",si,ge),"update");

	for(Int_t nn = 0; nn<300; nn++){
		_file0->cd();	
		Int_t nrj	= nn*2;	
		Float_t BR_666 	= 0.025;
		Float_t tt	= 1e9;
	
		TCut TIME	= Form("TPROTONS>0 && TPROTONS<%f",tt);
		TCut P4Energy	= Form("%s_E>%i && TPROTONS>0 && TPROTONS<%f",si,nrj,tt); 
		TCut P4EFull	= Form("%s_E>0 && TPROTONS>0 && TPROTONS<%f",si,tt); 
		//TCut P1Energy	= Form("PONE_E>%i && TPROTONS>0 && TPROTONS<%f",nrj,tt);
		TCut GE1_666cut	= Form("%sE>422 && %sE<430 && TPROTONS>0 && TPROTONS<%f",ge,ge,tt);
	
		UInt_t P4E_Single	= h101->GetEntries(P4EFull);
		UInt_t P4E_Gated	= h101->GetEntries(P4Energy);
		UInt_t GE1_666		= h101->GetEntries(GE1_666cut);
		UInt_t GE1_666_Gated 	= h101->GetEntries(P4Energy && GE1_666cut);
	
		Float_t EffGamma 	= GE1_666_Gated/(P4E_Gated*BR_666);
	
	
	//	TCanvas *cv[4];
	//	for(Int_t ff=0; ff<4 ; ff++){
	//		cv[ff] = new TCanvas(Form("plot %d",ff),Form("plot %d",ff),1400,600);
	//	}
	//	//cv0->Divide(2,2);
	//	cv[0]->cd();
	//	h101->Draw("PFOUR_E>>p4esingle(4096,0,4096)",P4EFull,"");
	//	cv[1]->cd();
	//	h101->Draw("PFOUR_E>>p4egated(4096,0,4096)",P4Energy,"");
	//	cv[2]->cd();
	//	h101->Draw("GEONE1E>>ge1_666(4096,0,4096)",GE1_666cut,"");
	//	cv[3]->cd();
	//	h101->Draw("GEONE1E>>ge1_666_gated(4096,0,4096)",GE1_666cut && P4Energy,"");
//		cout	<< endl <<  endl <<  endl <<"***************************************" << endl;
//		cout	<< "Si Energy Threshold PFOUR_E > "<< nrj << endl ;
//		cout	<< "P4E_Single = "    << P4E_Single    <<endl
//			<< "P4E_Gated = "     << P4E_Gated     <<endl
//			<< "GE1_666 = "       << GE1_666       <<endl
//			<< "GE1_666_Gated = " << GE1_666_Gated <<endl;
		cout	<< Form("Eff.%s = ",ge)  << EffGamma <<endl;	
	
//		cout	<< "***************************************" << endl;
		//myfile->cd();
//		myfile << nrj <<"\t" << EffGamma << endl;
		fprintf(myfile,"%d \t %f \n",nrj,EffGamma);		
	}
	fclose(myfile);
	cout <<"Finished :D !!!!"<<endl;

}
