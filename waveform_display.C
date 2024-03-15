#include "AraEventCalibrator.h"

void draw(int run, int evt, double depth){

	TFile *file = new TFile("/data/exp/SPICEcore/spiceCoreData2018-2019/L1/ARA05/1227/run_004002/event004002.root");
	TTree *eventTree = (TTree*) file->Get("eventTree");

	RawAtriStationEvent *rawEvent = 0;
	eventTree->SetBranchAddress("event", &rawEvent);

	eventTree->GetEntry(evt);

	UsefulAtriStationEvent *usefulEvent = 
	new UsefulAtriStationEvent(rawEvent, AraCalType::kLatestCalib14to20_Bug);

	vector<TGraph*> graphs;

	for(int i = 0; i < 16; ++i){
		graphs.push_back(usefulEvent->getGraphFromRFChan(i));
	}

	TCanvas *c = new TCanvas("c","c",1100,850);
	TPad *pad = new TPad(); // FLAG!

	c->Divide(4,4);

	for(int j = 0; j < 16; ++j){
		c->cd(j+1);
		graphs[j]->SetTitle(Form("%d",j));
		graphs[j]->Draw("AL");

		if(graphs[j]->GetN() == 0) break;

	}


}
