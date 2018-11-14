#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <TSystem.h>
#include <TObjString.h>
#include <TKey.h>
#include <TDirectory.h>
#include <TClass.h>
#include <TMath.h>

#include "FileParser.h"
#include "SHist.h"

using namespace std;

FileParser::FileParser()
{
  m_file = NULL;
  m_hists = NULL;
  m_shapeSys = NULL;
  debug = true;
  m_do_cumulative = true;
}

FileParser::~FileParser()
{
  if (m_file){
    CloseFile();
  }
}

void FileParser::CloseFile()
{
  if (m_file){
    m_file->Close();
    delete m_file;
    m_file = NULL;
  }
}


void FileParser::Clear()
{
  // clear all arrays, but do not close file
  if (m_hists) m_hists->Clear();
  if (m_shapeSys) m_shapeSys->Clear();
}

bool FileParser::FileExists(TString filename)
{
  struct stat buf;
  if (stat(filename.Data(), &buf) != -1)
    {
      return true;
    }
  return false;
}


void FileParser::OpenFile(TString fname, TString cyclename)
{
  // open the root files with names given in the TObjArray

  if (m_file != NULL){
    cerr << "FileParser::OpenFile: Can not open new file, since file " 
	 << m_file->GetName() << " is still in memory. Abort." << endl;
    exit(EXIT_FAILURE);
  }

  if (cyclename.Sizeof()!=0){
    TString Prefix(cyclename);
    Prefix.Append(".");
    fname.Prepend(Prefix);
  }  


  // check if name consists of a wildcard, if so use hadd to combine histograms
  if (fname.Contains("*")){
    TString target(fname);
    target.ReplaceAll("*","");

    // check if target exists, delete if yes
    if (FileExists(target)){
      if (debug) cout << "Target exists, removing file " << target << endl;
      remove(target);
    }
      
    TString command = "hadd " + target + " " + fname;
    int res = gSystem->Exec(command);
    if(res != 0){
        cerr << "hadd command '" << command << "' failed with error code " << res << ", aborting." << endl;
        exit(EXIT_FAILURE);
    }
    fname = target;
  }

  // check if name consists of a wildcard, if so use hadd to combine histograms
  if (fname.Contains("?")){
    TString target(fname);
    target.ReplaceAll("?","");

    // check if target exists, delete if yes
    if (FileExists(target)){
      if (debug) cout << "Target exists, removing file " << target << endl;
      remove(target);
    }
      
    TString command = "hadd " + target + " " + fname;
    int res = gSystem->Exec(command);
    if(res != 0){
        cerr << "hadd command '" << command << "' failed with error code " << res << ", aborting." << endl;
        exit(EXIT_FAILURE);
    }
    fname = target;
  }

  if (debug) cout << "Opening file with name " << fname << "..." << endl;
  m_file = new TFile(fname, "READ");
  if (debug){
    cout << "... success! pointer = " << m_file << endl;
    cout << "name = " << m_file << endl;
    cout << " is open? " << m_file->IsOpen() << endl;
    m_file->ls();
  }
    
  if (!m_file->IsOpen()) {
    cout << endl << "FileParser: File " << fname << " does not exist!!!" << endl;
    exit(EXIT_FAILURE);
  } else { // success!
    cout << "FileParser: Successfully opened file " << fname << endl;
  }

  StoreProcessName(fname);

  // create a new TObjArray to store all histograms
  m_hists = new TObjArray();

  return;
}


void FileParser::OpenThetaFile(TString cyclename)
{
  // open the root files with names given in the TObjArray

  if (m_file != NULL){
    cerr << "FileParser::OpenFile: Can not open new file, since file " 
	 << m_file->GetName() << " is still in memory. Abort." << endl;
    exit(EXIT_FAILURE);
  }
  TString fname = "" ;
  if (cyclename.Sizeof()!=0){
    fname = cyclename;
      }  

  // fname = target;


  if (debug) cout << "Opening file with name " << fname << "..." << endl;
  m_file = new TFile(fname, "READ");
  if (debug){
    cout << "... success! pointer = " << m_file << endl;
    cout << "name = " << m_file << endl;
    cout << " is open? " << m_file->IsOpen() << endl;
    m_file->ls();
  }
    
  if (!m_file->IsOpen()) {
    cout << endl << "FileParser: File " << fname << " does not exist!!!" << endl;
    exit(EXIT_FAILURE);
  } else { // success!
    cout << "FileParser: Successfully opened file " << fname << endl;
 }

  StoreProcessName(fname);

  // create a new TObjArray to store all histograms
  m_hists = new TObjArray();
  m_shapeSys = new TObjArray();
  return;
}


void FileParser::StoreProcessName(TString name)
{
  
  TObjArray* pieces = name.Tokenize(".");
  for (int i=0; i<pieces->GetEntries(); ++i){
    TString piece = ((TObjString*)pieces->At(i))->GetString();
    if (piece.CompareTo("root")==0){
      m_process = ((TObjString*)pieces->At(i-1))->GetString();
      if (debug) cout << "Process in file = " << m_process << endl;
    }
  }
}


TObjArray* FileParser::FindSubdirs()
{
  // find all subdirectories (former histogram collections) in the open file
  // returns a TObjArray with the names of the subdirectories 

  m_file->cd();
  TObjArray* dirnames = new TObjArray();
  TString dirname(""); // empty directory, to stay in home dir first
  dirnames->Add(new TObjString(dirname));

  TKey *key;
  TIter nextkey( gDirectory->GetListOfKeys() );
  while ( (key = (TKey*)nextkey())) {
    TObject *obj = key->ReadObj();
    if ( obj->IsA()->InheritsFrom( "TDirectory" ) ) {    // found a subdirectory! 
      TString dirname(((TDirectory*) obj)->GetName());
      dirnames->Add(new TObjString(dirname));
      if (debug) cout << "Found directory " << dirname << endl;
    }
  }
  return dirnames;

}

void FileParser::BrowseFile()
{

  if (!m_file){
    cerr << "FileParser::BrowseFile: No file open. Abort." << endl;
    exit(EXIT_FAILURE);
  }
  TObjArray* dirs = FindSubdirs();

  // loop over all directories and get the histograms
  for (Int_t i=0; i<dirs->GetEntries(); ++i){

    TString dirname = ((TObjString*)dirs->At(i))->GetString();
    if (debug) cout << "Getting all histograms from directory " << dirname << endl;
    //  std::cout <<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$   "<<dirname<<"  $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<std::endl;
    m_file->cd();
    gDirectory->Cd(dirname);
    //  std::cout<<"Hier"<<std::endl;
    // loop over all histograms in the directory and store them
    TKey *key;
    TIter nextkey( gDirectory->GetListOfKeys() );
    while ( (key = (TKey*)nextkey())) {

      TObject *obj = key->ReadObj();

      if ( obj->IsA()->InheritsFrom( TH1::Class() ) ) {

	// histogram found
	TH1* thist = (TH1*) obj;
	if (m_do_cumulative) MakeCumulativeHist(thist);
	TString name(thist->GetName());

	//	std::cout<<"Hier1                            "<<name<<std::endl;
	//	if(name.Contains("partonWPt")) continue;
	// if(name.Contains("weights")) continue;
	// if(!name.Contains("Discriminator")) continue;
	//	if(!(dirname.Contains("twodcut")))continue;
	// if(name!="tau21") continue;
	//if(!dirname.Contains("pu"))continue;
	// //AN plots
	// if(!( (dirname.Contains("muon_twodcut") && (name=="pt" || name=="eta")) || (dirname.Contains("electron_twodcut") && (name=="pt" || name=="eta")) ||(dirname.Contains("jet_twodcut") && (name=="pt_jet" || name=="eta"))||(dirname.Contains("topjet_twodcut") && (name=="pt_1" || name=="eta_1"))  || (dirname.Contains("event_twodcut") && name=="MET") || (dirname.Contains("chi2min_reco") && name=="Discriminator") || ((dirname.Contains("chi2min_btag0")||dirname.Contains("chi2min_btag1")) && name=="M_ZPrime_rec"))) continue;
	//Paper plots
	//	if(!( (dirname.Contains("chi2min_reco") && name=="Discriminator") || ((dirname.Contains("chi2min_btag0")||dirname.Contains("chi2min_btag1")) && name=="M_ZPrime_rec"))) continue;
	//	if(!( (dirname.Contains("chi2min_chi2cut") && name=="M_ZPrime_rec")))continue;
	//if(!(dirname.Contains("topjet_btag1"))) continue;
		if(!(dirname.Contains("chi2min_btag1") && name.Contains("Pt"))) continue;


	TH1* rebinned = Rebin(thist, dirname);
	SHist* shist = NULL;
	if (rebinned){
	  shist = new SHist(rebinned);
	} else {
	  shist = new SHist(thist);
	}
   
	shist->SetProcessName(m_process);
	if (dirname==""){
	  shist->SetDir("Main");
	} else {
	  shist->SetDir(dirname);
	}
	if (debug) cout << "Adding hist " << shist->GetHist()->GetName() 
			<< " (process = " << m_process << ")" << endl;
	m_hists->Add(shist);	
      }
      
   
      delete obj;

    }

  }
  
  return;

}


void FileParser::BrowseThetaFile(TString sample)
{

  if (!m_file){
    cerr << "FileParser::BrowseFile: No file open. Abort." << endl;
    exit(EXIT_FAILURE);
  }
   
  m_file->cd();
  TKey *key;
  TIter nextkey( m_file->GetListOfKeys() );

  while ( (key = (TKey*)nextkey())) {
    
    TString histName = key->GetName();
    histName.ReplaceAll("__", "#");
    TObjArray* pieces = histName.Tokenize("#");

    if (((TObjString*)pieces->At(1))->GetString() == sample){

      TObject *obj = key->ReadObj();
      
      if ( obj->IsA()->InheritsFrom( TH1::Class() ) ) {

	// histogram found
	TH1* thist = (TH1*) obj;
	if (m_do_cumulative) MakeCumulativeHist(thist);
	TH1* rebinned = Rebin(thist, "");
	SHist* shist = NULL;
	if (rebinned){
	  shist = new SHist(rebinned);
	}
	else {
	  shist = new SHist(thist);
	}
	TString proc_name = ((TObjString*)pieces->At(1))->GetString();
	shist->SetProcessName(proc_name);
	SetProcessName(proc_name);
	TString hname = ((TObjString*)pieces->At(0))->GetString();
	shist->SetName(hname);

	shist->SetDir("Main");
	
	if (pieces->GetEntries()>2){
	  m_shapeSys->Add(shist);
	  proc_name = ((TObjString*)pieces->At(1))->GetString() + "__" + ((TObjString*)pieces->At(2))->GetString() + "__" + ((TObjString*)pieces->At(3))->GetString();
	  shist->SetProcessName(proc_name);	  
	  SetProcessName(proc_name);
	  if (debug) cout << "Adding hist to systematic sample: " << shist->GetHist()->GetName() 
	  		  << " (process = " << m_process << ")" << endl;
	} else {
	  m_hists->Add(shist);
	  if (debug) cout << "Adding hist " << shist->GetHist()->GetName() 
			  << " (process = " << m_process << ")" << endl;
	}
      }
      
      delete obj;
    }
  }

  
  return;

}

void FileParser::MakeCumulativeHist(TH1* hist)
{
  for (Int_t i=1; i<hist->GetNbinsX()+1; ++i){
    Double_t sum = 0;
    Double_t sumw2 = 0;
    for (int j=i; j<hist->GetNbinsX()+1; ++j){
      sum += hist->GetBinContent(j);
      sumw2 += hist->GetSumw2()->At(j);
    }
    hist->SetBinContent(i, sum);
    hist->SetBinError(i, TMath::Sqrt(sumw2));
  }

}


TH1* FileParser::Rebin(TH1* hist, TString dirname)
{		
  				
  TString name(hist->GetName());
  TString title(hist->GetTitle());
  
  //  cout << "name = " << name << " title = " << title <<" dirname= "<<dirname<< endl;
  if (name.CompareTo("toptags")==0){// && dirname.Contains("cutflow6") && title.Contains("electron")){
   
    Double_t binsx[] = {0, 960, 1020, 1080, 1140, 1200, 1260, 1320, 1380, 1440, 1500, 1560, 1620, 1680, 1740, 1800, 1860, 1920, 1980, 2040, 2100, 2400, 3000};
    name.Append("_rebin_lx");
    TH1* rebinned = hist->Rebin(22, name, binsx);
    rebinned->SetTitle("HT [GeV]");
    return rebinned;

  } else if (name.BeginsWith("mu_0top0btag_mttbar")) {
    
    TH1* rebinned = hist->Rebin(2);
    rebinned->GetXaxis()->SetRangeUser(0,3500);
    return rebinned; 
  } else if (name.BeginsWith("mu_0top1btag_mttbar")) {
    
    TH1* rebinned = hist->Rebin(2);
    rebinned->GetXaxis()->SetRangeUser(0,3500);
    return rebinned;

  } else if (name.BeginsWith("mu_1top_mttbar")) {
    
    TH1* rebinned = hist->Rebin(4);
    rebinned->GetXaxis()->SetRangeUser(0,3500);
    return rebinned;

  } else if (name.BeginsWith("el_0top0btag_mttbar")) {
    
    TH1* rebinned = hist->Rebin(2);
    rebinned->GetXaxis()->SetRangeUser(0,3500);
    return rebinned;

  } else if (name.BeginsWith("el_0top1btag_mttbar")) {
    
    TH1* rebinned = hist->Rebin(2);
    rebinned->GetXaxis()->SetRangeUser(0,3500);
    return rebinned;

  } else if (name.BeginsWith("el_1top_mttbar")) {
    
    TH1* rebinned = hist->Rebin(4);
    rebinned->GetXaxis()->SetRangeUser(0,3500);
    return rebinned; 
  } else if (name.Contains("Masse_ZPrime")) {
   
    hist->GetXaxis()->SetRangeUser(1000,5000);
    return hist; 
  } else if (name.Contains("Masse_TPrime")) {
   
    hist->GetXaxis()->SetRangeUser(500,3000);
    return hist;
  // }   else if (title.Contains("p_{T} muon")) {
  //   TH1* rebinned = hist->Rebin(5);
  //   return rebinned;
    
  // }else if (title.Contains("eta muon")||title.Contains("eta electron")||title.Contains("eta first jet")||title.Contains("p_{T} electron")||title.Contains("p_{T} muon")) {
  //   TH1* rebinned = hist->Rebin(5);
  //   return rebinned;  
  // } else if (title.Contains("p_{T} second jet")) {

  //   TH1* rebinned = hist->Rebin(1);
  //   if(dirname.Contains("twodcut"))  rebinned = hist->Rebin(2);
  //   if(dirname.Contains("twodcut"))  rebinned->GetXaxis()->SetRangeUser(0,600);
  //   if(dirname.Contains("chi2cut_btag")) rebinned->GetXaxis()->SetRangeUser(0,400);
  //   return rebinned; 
  // }else if (title.Contains("p_{T} first jet")) {

  //   TH1* rebinned = hist->Rebin(1);
  //   if(dirname.Contains("chi2cut_btag")) rebinned->GetXaxis()->SetRangeUser(0,700);
  //   return rebinned; 
  // // } else if (title.Contains("p_{T} topjet")) {

  // //   TH1* rebinned = hist->Rebin(1);
  // //   if(dirname.Contains("chi2cut_W")) rebinned->GetXaxis()->SetRangeUser(0,1100);
  // //   return rebinned;
  // // } else if (title.Contains("p_{T} first topjet")) {

  // //   TH1* rebinned = hist->Rebin(2);
  // //   return rebinned; 
  // // }else if (title.Contains("p_{T} jet")) {

  // //   // Double_t bin[23]={20, 79.2, 138.4, 197.6, 256.8, 316, 375.2, 434.4, 493.6, 552.8, 612, 671.2, 730.4, 789.6, 848.8, 908, 1026.4,  1144.8, 1204,  1263.2, 1322.4, 1381.6, 1440.8};
  // //   // name.Append("_rebin");
  // //   // TH1* rebinned = hist->Rebin(22, name, bin);
  // //   TH1* rebinned = hist->Rebin(2);
  // //   //  TH1* rebinned = hist->Rebin(22,"rebinned",bin);
  // //   // if(dirname.Contains("twodcut"))  rebinned = hist->Rebin(22,"rebinned",bin);
  // //   // if(dirname.Contains("triangcut"))  rebinned = hist->Rebin(2);
   
  // //   return rebinned; 

  // }  else if (!(title.CompareTo("M_{ZPrime}^{rec} [GeV/c^{2}]"))) {
 
  //   TH1* rebinned = hist->Rebin(2);
  //   return rebinned;
  }  else if (!(title.CompareTo("M_{TPrime}^{rec} [GeV/c^{2}]"))) {
 
    TH1* rebinned = hist->Rebin(2);
    return rebinned;
  } else if (title.Contains("number of jets")) {
    
    hist->GetXaxis()->SetRangeUser(0,10);
    if(dirname.Contains("twodcut")) hist->GetXaxis()->SetRangeUser(0,30);
    if(dirname.Contains("triangcut")) hist->GetXaxis()->SetRangeUser(0,30);
    return hist;
  } else if (title.Contains("number of topjets")) {
    
    hist->GetXaxis()->SetRangeUser(0,15);
    return hist;
  } else if (dirname.Contains("higgs_topjet_chi2cut")&&name.Contains("mass_subjet_sum")) {
    
    hist->GetXaxis()->SetRangeUser(90,170);
    return hist;
  } else if (dirname.Contains("zw_topjet_chi2cut")&&name.Contains("mass_subjet_sum")) {
    
    hist->GetXaxis()->SetRangeUser(50,130);
    return hist;
    // } else if (dirname.Contains("muon_chi2cut")&&name.Contains("eta")) {
    
    //   hist->GetXaxis()->SetRangeUser(-3,5);
    //   return hist;
  // } else if (!title.CompareTo("#Chi^{2}")) {
    
  //   TH1* rebinned = hist->Rebin(5);
  //   return rebinned;
    
  // } else if (title.Contains("missing E")) {
    
  //   TH1* rebinned = hist->Rebin(10);
  //   return rebinned;
  // //
    //  } else if ((dirname.Contains("topjet_twodcut") ||dirname.Contains("topjet_triangcut") )&&name.Contains("mass_subjet_sum")) {
    
  //   TH1* rebinned = hist->Rebin(4);
  //   return rebinned;
  } else if (dirname.Contains("topjet_chi2cut_other") &&name.Contains("mass_subjet_sum")) {
    
    TH1* rebinned = hist->Rebin(2);
    return rebinned;

  } else if (dirname.Contains("electron_twodcut") &&name.Contains("isolation")) {
    
    TH1* rebinned = hist->Rebin(4);
    return rebinned;

  } else if (dirname.Contains("topjet_twodcut") &&name.Contains("mass_subjet_sum")) {
    
    TH1* rebinned = hist->Rebin(4);
    return rebinned;

  } else if (dirname.Contains("topjet_topjet2") &&name.Contains("eta")) {
    
    TH1* rebinned = hist->Rebin(4);
    return rebinned;
    
  } else if (dirname.Contains("tagger_chi2cut")&&name.Contains("reco_mass_W")) {
    
    TH1* rebinned = hist->Rebin(2);
    return rebinned;
  } else if (dirname.Contains("tagger_zwtag")&&name.Contains("reco_mass_W")) {
    
    TH1* rebinned = hist->Rebin(2);
    rebinned->GetXaxis()->SetRangeUser(40,200);
    return rebinned;
  //   ////puppi
 //  } else if (title.Contains("H_{T}")) {
    
 //    TH1* rebinned = hist->Rebin(4);
 //    return rebinned; 

 //  } else if (dirname.Contains("alpha_p")&&name.Contains("eta")) {
    
 //    TH1* rebinned = hist->Rebin(2);
 //    return rebinned; 
   
 //  } else if (dirname.Contains("p_charged_pu")&&title.Contains("Number of particles")) {

 //    TH1* rebinned = hist->Rebin(15);
 //    rebinned->GetXaxis()->SetRangeUser(0,800);
 //    // TH1* rebinned = hist->Rebin(2);//pt1cut
 //    // rebinned->GetXaxis()->SetRangeUser(0,200); //pt1cut
 //    return rebinned; 

 //  } else if (dirname.Contains("p_charged_pv")&&title.Contains("Number of particles")) {
     
 //    TH1* rebinned = hist->Rebin(15);
 //    rebinned->GetXaxis()->SetRangeUser(0,400);
 //    return rebinned; 

 // } else if (dirname.Contains("alpha_p_not_charged")&&title.Contains("Number of particles")) {
    
 //    TH1* rebinned = hist->Rebin(30);
 //    rebinned->GetXaxis()->SetRangeUser(200,1800);
 //    // rebinned->GetXaxis()->SetRangeUser(0,800); //pt1cut
 //    return rebinned;  

 //  } else if (title.Contains("Number of particles")) {
    
 //    TH1* rebinned = hist->Rebin(30);
 //     rebinned->GetXaxis()->SetRangeUser(700,3000);
 //     // rebinned->GetXaxis()->SetRangeUser(0,600);
 //    return rebinned;
 //  } else if (dirname.Contains("charged_pu")&& title.Contains("pt")) {

 //    TH1* rebinned = hist->Rebin(1);
 //    rebinned->GetXaxis()->SetRangeUser(0,30);
 //    return rebinned;

 //   } else if (title.Contains("pt")) {
    
 //     //Double_t bin[23]={20, 79.2, 138.4, 197.6, 256.8, 316, 375.2, 434.4, 493.6, 552.8, 612, 671.2, 730.4, 789.6, 848.8, 908, 1026.4,  1144.8, 1204,  1263.2, 1322.4, 1381.6, 1440.8};
 //     // name.Append("_rebin");
 //     // TH1* rebinned = hist->Rebin(22, name, bin);

 //     TH1* rebinned = hist->Rebin(1);
 //     rebinned->GetXaxis()->SetRangeUser(0,30);
 //     return rebinned;

 // //    // } else if (dirname.Contains("higgs_topjet_chi2cut_tagged")) {
    
 // //    //   hist->SetMaximum()
 // //    //   return rebinned;

 } else if (title.Contains("#Chi^{2}")) {
    
    //TH1* rebinned = hist->Rebin(5);
    //return rebinned;
 // // } else if (title.Contains("M^{")) {
    
 // //    TH1* rebinned = hist->Rebin(4);
 // //    return rebinned;

  // } else if(name.Contains("MZPrime_side2_btag")){

  //   Double_t bin[31] = {600.0, 685.0, 770.0, 855.0, 940.0, 1025.0, 1110.0, 1195.0, 1280.0, 1365.0, 1450.0, 1535.0, 1620.0, 1705.0, 1790.0, 1875.0, 1960.0, 2045.0, 2130.0, 2215.0, 2300.0, 2385.0, 2470.0, 2555.0, 2640.0, 2725.0, 2810.0, 2895.0, 2980.0, 3065.0,4000.0};
  //   name.Append("_rebin");
  //   TH1* rebinned = hist->Rebin(30, name, bin);
  //   return rebinned;

  // }else if (name.Contains("higgsnotop_muon")){
  //   Double_t bin[24]={600.0, 685.0, 770.0, 855.0, 940.0, 1025.0, 1110.0, 1195.0, 1280.0, 1365.0, 1450.0, 1535.0, 1620.0, 1705.0, 1790.0, 1875.0, 1960.0, 2045.0, 2130.0,  2300.0,  2470.0,  2640.0, 2980.0,4000};
  //   name.Append("_rebin");
  //   TH1* rebinned = hist->Rebin(23, name, bin);
  //   return rebinned;

  // hack to fix display with negative weights
  } else if (name.Contains("MZPrime_higgsnotop_one_btag_elec")) {
    if (name=="MZPrime_higgsnotop_one_btag_elec__TTbar") hist->SetBinContent(29, 1.24756);
    if (name=="MZPrime_higgsnotop_one_btag_elec__DYJetsToLL") hist->SetBinContent(29, 0.0567404);    
    //cout << "name = " << name << endl;
    //cout << "bin content in bin 29 = " << hist->GetBinContent(29) << endl;
    return NULL;

  // hack to fix x-axis label
  } else if (name.Contains("MZPrime_topjet_twodcut_mass_subjet_sum")) {
    hist->SetTitle("M_{SD} [GeV]");
    return NULL;


  }  else {
    return NULL;
  }

}

void FileParser::SetInfo(TString legname, double weight, int colour, int marker, float unc)
{
  
  for (int i=0; i<m_hists->GetEntries(); ++i){
    SHist* sh = (SHist*)m_hists->At(i);
    sh->SetLegName(legname);
    sh->SetWeight(weight);
    sh->SetUnc(unc);
    if (weight>0) sh->GetHist()->Scale(weight);
    sh->GetHist()->SetMarkerColor(colour);
    sh->GetHist()->SetLineColor(colour);

    if (marker > 1 ){
      sh->SetDrawMarker(true);
      sh->GetHist()->SetMarkerStyle(marker);
    } else {
      sh->SetDrawMarker(false);
      sh->GetHist()->SetMarkerStyle(0);
      sh->GetHist()->SetMarkerSize(0);
      sh->GetHist()->SetLineWidth(2);   
    }

    // histogram is transparent if marker < 0  
    if (marker < 0 ){
      // change line style
      if (marker==-1) sh->GetHist()->SetLineStyle(kDashed);
      if (marker==-2) sh->GetHist()->SetLineStyle(kDotted);
      if (marker==-3) sh->GetHist()->SetLineStyle(kDashDotted);
      if (marker==-4) sh->GetHist()->SetLineStyle(kDashDotted);    
    }
  }
}
