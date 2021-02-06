void PET_Analysis(char* filename, char* outname)
{
   
   gROOT->Reset();

   TFile f(filename);

   TTree *Coincidences = (TTree*)gDirectory->Get("Coincidences");
   TTree *Hits = (TTree*)gDirectory->Get("Hits");
   TTree *Singles = (TTree*)gDirectory->Get("Singles");
   TTree *delay = (TTree*)gDirectory->Get("delay");

//
//Declaration of leaves types - TTree Coincidences
//  
   Int_t           RayleighCrystal1;
   Int_t           RayleighCrystal2;
   Int_t           RayleighPhantom1;
   Int_t           RayleighPhantom2;
   Char_t          RayleighVolName1[40];
   Char_t          RayleighVolName2[40];
   Float_t         axialPos;
   Char_t          comptVolName1[40];
   Char_t          comptVolName2[40];
   Int_t           compton1;
   Int_t           compton2;
   Int_t           crystalID1;
   Int_t           crystalID2;
   Int_t           comptonPhantom1;
   Int_t           comptonPhantom2;
   Float_t         energy1;
   Float_t         energy2;   
   Int_t           eventID1;
   Int_t           eventID2;
   Float_t         globalPosX1;
   Float_t         globalPosX2;
   Float_t         globalPosY1;
   Float_t         globalPosY2;      
   Float_t         globalPosZ1;
   Float_t         globalPosZ2;
   Int_t           layerID1;
   Int_t           layerID2;
   Int_t           moduleID1;
   Int_t           moduleID2;
   Float_t         rotationAngle;
   Int_t           rsectorID1;
   Int_t           rsectorID2;
   Int_t           runID;
   Float_t         sinogramS;
   Float_t         sinogramTheta;
   Int_t           sourceID1;
   Int_t           sourceID2;
   Float_t         sourcePosX1;
   Float_t         sourcePosX2;
   Float_t         sourcePosY1;
   Float_t         sourcePosY2;
   Float_t         sourcePosZ1;
   Float_t         sourcePosZ2;
   Int_t           submoduleID1;
   Int_t           submoduleID2;
   Double_t         time1;
   Double_t         time2;
   
   Float_t         zmin,zmax,z;
//   
//Set branch addresses - TTree Coincicences
//  
   Coincidences->SetBranchAddress("RayleighCrystal1",&RayleighCrystal1);
   Coincidences->SetBranchAddress("RayleighCrystal2",&RayleighCrystal2);
   Coincidences->SetBranchAddress("RayleighPhantom1",&RayleighPhantom1);
   Coincidences->SetBranchAddress("RayleighPhantom2",&RayleighPhantom2);
   Coincidences->SetBranchAddress("RayleighVolName1",&RayleighVolName1);
   Coincidences->SetBranchAddress("RayleighVolName2",&RayleighVolName2);
   Coincidences->SetBranchAddress("axialPos",&axialPos);
   Coincidences->SetBranchAddress("comptVolName1",&comptVolName1);
   Coincidences->SetBranchAddress("comptVolName2",&comptVolName2);
   Coincidences->SetBranchAddress("comptonCrystal1",&compton1);
   Coincidences->SetBranchAddress("comptonCrystal2",&compton2);
   Coincidences->SetBranchAddress("crystalID1",&crystalID1);
   Coincidences->SetBranchAddress("crystalID2",&crystalID2);
   Coincidences->SetBranchAddress("comptonPhantom1",&comptonPhantom1);
   Coincidences->SetBranchAddress("comptonPhantom2",&comptonPhantom2);
   Coincidences->SetBranchAddress("energy1",&energy1);
   Coincidences->SetBranchAddress("energy2",&energy2);   
   Coincidences->SetBranchAddress("eventID1",&eventID1);
   Coincidences->SetBranchAddress("eventID2",&eventID2);
   Coincidences->SetBranchAddress("globalPosX1",&globalPosX1);
   Coincidences->SetBranchAddress("globalPosX2",&globalPosX2);
   Coincidences->SetBranchAddress("globalPosY1",&globalPosY1);
   Coincidences->SetBranchAddress("globalPosY2",&globalPosY2);      
   Coincidences->SetBranchAddress("globalPosZ1",&globalPosZ1);
   Coincidences->SetBranchAddress("globalPosZ2",&globalPosZ2);
   Coincidences->SetBranchAddress("layerID1",&layerID1);
   Coincidences->SetBranchAddress("layerID2",&layerID2);
   Coincidences->SetBranchAddress("moduleID1",&moduleID1);
   Coincidences->SetBranchAddress("moduleID2",&moduleID2);
   Coincidences->SetBranchAddress("rotationAngle",&rotationAngle);
   Coincidences->SetBranchAddress("rsectorID1",&rsectorID1);
   Coincidences->SetBranchAddress("rsectorID2",&rsectorID2);
   Coincidences->SetBranchAddress("runID",&runID);
   Coincidences->SetBranchAddress("sinogramS",&sinogramS);
   Coincidences->SetBranchAddress("sinogramTheta",&sinogramTheta);
   Coincidences->SetBranchAddress("sourceID1",&sourceID1);
   Coincidences->SetBranchAddress("sourceID2",&sourceID2);
   Coincidences->SetBranchAddress("sourcePosX1",&sourcePosX1);
   Coincidences->SetBranchAddress("sourcePosX2",&sourcePosX2);
   Coincidences->SetBranchAddress("sourcePosY1",&sourcePosY1);
   Coincidences->SetBranchAddress("sourcePosY2",&sourcePosY2);
   Coincidences->SetBranchAddress("sourcePosZ1",&sourcePosZ1);
   Coincidences->SetBranchAddress("sourcePosZ2",&sourcePosZ2);
   Coincidences->SetBranchAddress("submoduleID1",&submoduleID1);
   Coincidences->SetBranchAddress("submoduleID2",&submoduleID2);
   Coincidences->SetBranchAddress("time1",&time1);
   Coincidences->SetBranchAddress("time2",&time2);
   
  
   Int_t nentries = Coincidences->GetEntries();
   Int_t nbytes = 0, nbytesdelay = 0, nrandom = 0, nscatter = 0, ntrue = 0, count = 0;
   Float_t scatter_frac;
   Float_t NEC;
   Float_t x_avg;
   Float_t y_avg;
   Float_t z_avg;
   Float_t runtime, end, start;

   
//
// Loop for each event in the TTree Coincidences
//
  Coincidences->GetEntry(0);
  start = time1;
  for (Int_t i=0; i<nentries;i++) {
    
     nbytes += Coincidences->GetEntry(i);
     
	  if (abs (globalPosY1) < 255) { // Y max
	     if (abs (globalPosY2) < 255) { // Y max
     		if (abs (globalPosZ1) < 180) { // Z max
		   if (abs (globalPosZ2) < 180) { // Z max


     			if (eventID1 != eventID2) { // Random coincidence
       				++nrandom;
       				++count;
    			 } 
			else {  // True coincidence
       			if (comptonPhantom1 == 0 && comptonPhantom2 == 0 &&
          		 RayleighPhantom1 == 0 && RayleighPhantom2 == 0) {  // true unscattered coincidence
	    			++ntrue;
       			 	++count;
                                x_avg += (sourcePosX1 +sourcePosX2)/2 ;
				y_avg += (sourcePosY1 +sourcePosY2)/2 ;
				z_avg += (sourcePosZ1 +sourcePosZ2)/2 ;

      			 } else { // true scattered coincidence
         			++nscatter;
       	  			++count;
       
			}  

     			}
	  
  			}
	            }
		}
            }
	}

   x_avg = x_avg/ntrue;
   y_avg = y_avg/ntrue;
   z_avg = z_avg/ntrue;

   end = time2;
   scatter_frac = (float)nscatter/(float)(count);
 
   NEC = (float)ntrue*ntrue/(float)(count);
 
   runtime = end - start;  



   cout << x_avg << " X-Position (mm)" << endl;
   cout << y_avg << " Y-Position (mm)" << endl;
   cout << z_avg << " Z-Position (mm)" << endl;

   cout << runtime << " Simulated Time (s)" << endl;

   cout << nentries << " Total Coincidences" << endl;
   cout << count << " Active Area Coincidences" << endl;
   cout << ntrue << " True Coincidences" << endl;
   cout << nrandom << " Random Coincidences" << endl;
   cout << nscatter << " Scattered Coincidences" << endl;
   cout << NEC << " Noise Equivalent Counts" << endl;

   cout << nentries/runtime/1000 << " Total Coincidences Rate (kHz)" << endl;
   cout << count/runtime/1000 << " Active Area Coincidence Rate (kHz)" << endl;
   cout << ntrue/runtime/1000 << " True Coincidence Rate (kHz)" << endl;
   cout << nrandom/runtime/1000 << " Random Coincidence Rate (kHz)" << endl;
   cout << nscatter/runtime/1000 << " Scattered Coincidence Rate (kHz)" << endl;
   cout << NEC/runtime/1000 << " Noise Equivalent Count Rate (kHz)" << endl;
   
   cout << (float)ntrue/(float)count << " True Fraction" << endl;
   cout << (float)nrandom/(float)count << " Random Fraction" << endl;
   cout << (float)nscatter/(float)count << " Scatter Fraction" << endl;
   cout << endl;


   ofstream myfile;
   myfile.open (outname);

   myfile << x_avg << " X-Position (mm)" << endl;
   myfile << y_avg << " Y-Position (mm)" << endl;
   myfile << z_avg << " Z-Position (mm)" << endl;
   
   myfile << runtime << " Simulated Time (s)" << endl;
   
   myfile << nentries << " Total Coincidences" << endl;
   myfile << count << " Active Area Coincidences" << endl;
   myfile << ntrue << " True Coincidences" << endl;
   myfile << nrandom << " Random Coincidences" << endl;
   myfile << nscatter << " Scattered Coincidences" << endl;
   myfile << NEC << " Noise Equivalent Counts" << endl;

   myfile << nentries/runtime/1000 << " Total Coincidence Rate (kHz)" << endl;
   myfile << count/runtime/1000 << " Active Area Coincidence Rate (kHz)" << endl;
   myfile << ntrue/runtime/1000 << " True Coincidence Rate (kHz)" << endl;
   myfile << nrandom/runtime/1000 << " Random Coincidence Rate (kHz)" << endl;
   myfile << nscatter/runtime/1000 << " Scattered Coincidence Rate (kHz)" << endl;
   myfile << NEC/runtime/1000 << " Noise Equivalent Count Rate (kHz)" << endl;
   
   myfile << (float)ntrue/(float)count << " True Fraction" << endl;
   myfile << (float)nrandom/(float)count << " Random Fraction" << endl;
   myfile << (float)nscatter/(float)count << " Scatter Fraction" << endl;
   myfile << endl;

   exit(0);
}	



