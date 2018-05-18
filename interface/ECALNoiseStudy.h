#ifndef ECALNoiseStudy_h
#define ECALNoiseStudy_h

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "RecoEcal/EgammaCoreTools/interface/PositionCalc.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "RecoVertex/PrimaryVertexProducer/interface/PrimaryVertexSorter.h"
#include "RecoVertex/PrimaryVertexProducer/interface/VertexHigherPtSquared.h"

// ROOT include
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include <vector>


// Less than operator for sorting EcalRecHits according to energy.
class ecalRecHitLess : public std::binary_function<EcalRecHit, EcalRecHit, bool>
{
public:
  bool operator()(EcalRecHit x, EcalRecHit y)
  {
    return (x.energy() > y.energy());
  }
};


class ECALNoiseStudy : public edm::EDAnalyzer {

      public:
         explicit ECALNoiseStudy(const edm::ParameterSet&);
	 ~ECALNoiseStudy();

      private:
	 virtual void beginJob() ;
	 virtual void analyze(const edm::Event&, const edm::EventSetup&);
	 virtual void endJob() ;

	 // ----------member data ---------------------------
	 edm::EDGetTokenT<reco::VertexCollection> vertexToken_;
   edm::EDGetTokenT<reco::EcalRecHitCollection>                    recHitCollection_EB_;
	 edm::EDGetTokenT<reco::EcalRecHitCollection>                    recHitCollection_EE_;
   edm::EDGetTokenT<reco::PFRecHitCollection>                PFrecHitCollection_;
   edm::EDGetTokenT<reco::PFClusterCollection>                         PFclusterCollection_;
	 edm::EDGetTokenT<reco::BasicClusterCollection>            basicClusterCollection_EB_;//reco::BasicClusterCollection
	 edm::EDGetTokenT<reco::BasicClusterCollection>            basicClusterCollection_EE_;
	 edm::EDGetTokenT<reco::SuperClusterCollection>            superClusterCollection_EB_;//reco::SuperClusterCollection
	 edm::EDGetTokenT<reco::SuperClusterCollection>            superClusterCollection_EE_;
	 edm::EDGetTokenT<reco::BeamSpot>                      	  beamSpot_ ;//reco::BeamSpot

   bool SaveSrFlag_;

	 double ethrEB_;
	 double ethrEE_;
	 double scEtThrEB_;
	 double scEtThrEE_;

   // tree
   //TTree *outTree;

	 // ------------- HISTOGRAMS ------------------------------------
	 int naiveId_;
	 TH1D *h_nPVs;
	 TH1D *h_numberOfEvents;

   // Rechits and PfRechit vs eta
   std::vector<TString> regions={"EB", "EEM", "EEP"};
   std::map<TString, std::map<TString, TH1F*>> h_recHits_energy_etaBinned;
   std::map<TString, std::map<TString, TH1F*>> h_recHits_et_etaBinned;
   std::map<TString, std::map<TString, TH1F*>> h_PFrecHits_energy_etaBinned;

   std::map<TString, std::vector<TString>> eta_keys;
   std::map<TString, std::map<TString, std::pair<Float_t,Float_t>>> eta_edges;

	 // RecHits ----------------------------------------------
	 TH1D *h_recHits_EB_size;
	 TH1D *h_recHits_EB_eta;
	 TH1D *h_recHits_EB_maxEneEta;
	 TH1D *h_recHits_EB_energy;
   TH1D *h_recHits_EB_energyMax;
	 TH1D *h_recHits_EB_time;
	 TH1D *h_recHits_EB_Chi2;
	 TH1D *h_recHits_EB_OutOfTimeChi2;
	 TH1D *h_recHits_EB_E1oE4;
   TH1D *h_recHits_EB_iPhiOccupancy;
   TH1D *h_recHits_EB_iEtaOccupancy;
	 TH2D *h_recHits_EB_occupancy;
	 TH2D *h_recHits_EB_occupancy_gt10;
	 TH2D *h_recHits_EB_occupancy_lt10;
	 TH1D *h_recHits_EB_energy_spike;
   TH2D *h_recHits_EB_eneVSieta;

   TH1D *h_PFrecHits_EB_eta;
   TH1D *h_PFrecHits_EB_energy;
   TH1D *h_PFrecHits_EB_time;
   TH2D *h_PFrecHits_EB_occupancy;
   TH2D *h_PFrecHits_EB_eneVSieta;

	 //... barrel ( with spike cleaning )
	 TH1D *h_recHits_EB_size_cleaned;
	 TH1D *h_recHits_EB_energy_cleaned;
	 TH1D *h_recHits_EB_time_cleaned;
	 TH1D *h_recHits_EB_Chi2_cleaned;

	 // ... endcap
	 TH1D *h_recHits_EE_size;
	 TH1D *h_recHits_EEP_size;
	 TH1D *h_recHits_EEP_eta;
	 TH1D *h_recHits_EEP_maxEneEta;
	 TH1D *h_recHits_EEP_energy;
	 TH1D *h_recHits_EEP_energy_gt25;
	 TH1D *h_recHits_EEP_energyMax;
	 TH1D *h_recHits_EEP_time;
	 TH1D *h_recHits_EEP_Chi2;
	 TH1D *h_recHits_EEP_OutOfTimeChi2;
	 TH1D *h_recHits_EEP_E1oE4;
   TH1D *h_recHits_EEP_iXoccupancy;
   TH1D *h_recHits_EEP_iYoccupancy;
	 TH2D *h_recHits_EEP_occupancy;
   TH2D *h_recHits_EEP_occupancy_etaphi;
	 TH2D *h_recHits_EEP_occupancy_gt10;
	 TH2D *h_recHits_EEP_occupancy_lt10;

   TH1D *h_PFrecHits_EEP_eta;
   TH1D *h_PFrecHits_EEP_energy;
   TH1D *h_PFrecHits_EEP_time;
   TH2D *h_PFrecHits_EEP_occupancy;
   TH2D *h_PFrecHits_EEP_eneVSieta;


	 TH1D *h_recHits_EEM_size;
	 TH1D *h_recHits_EEM_eta;
	 TH1D *h_recHits_EEM_maxEneEta;
	 TH1D *h_recHits_EEM_energy;
	 TH1D *h_recHits_EEM_energy_gt25;
	 TH1D *h_recHits_EEM_energyMax;
	 TH1D *h_recHits_EEM_time;
	 TH1D *h_recHits_EEM_Chi2;
	 TH1D *h_recHits_EEM_OutOfTimeChi2;
	 TH1D *h_recHits_EEM_E1oE4;
   TH1D *h_recHits_EEM_iXoccupancy;
   TH1D *h_recHits_EEM_iYoccupancy;
	 TH2D *h_recHits_EEM_occupancy;
	 TH2D *h_recHits_EEM_occupancy_gt10;
	 TH2D *h_recHits_EEM_occupancy_lt10;

   TH1D *h_PFrecHits_EEM_eta;
   TH1D *h_PFrecHits_EEM_energy;
   TH1D *h_PFrecHits_EEM_time;
   TH2D *h_PFrecHits_EEM_occupancy;
   TH2D *h_PFrecHits_EEM_eneVSieta;

   TH1D *h_recHits_eta;  // all

   TH2D *h_recHits_EEP_neighbourEt_eta20;
   TH2D *h_recHits_EEP_neighbourEt_eta24;
   TH1D *h_recHits_EEP_sumneighbourEt_eta20;
   TH1D *h_recHits_EEP_sumneighbourEt_eta24;


	 // Basic Clusters ----------------------------------------------

	 // ... barrel
	 TH1D *h_basicClusters_EB_size;
	 TH1D *h_basicClusters_EB_nXtals;
	 TH1D *h_basicClusters_EB_energy;

	 // ... endcap
	 TH1D *h_basicClusters_EEP_size;
	 TH1D *h_basicClusters_EEP_nXtals;
	 TH1D *h_basicClusters_EEP_energy;

	 TH1D *h_basicClusters_EEM_size;
	 TH1D *h_basicClusters_EEM_nXtals;
	 TH1D *h_basicClusters_EEM_energy;

	 TH1D *h_basicClusters_eta;
	 TH1D *h_basicClusters_EB_eta;
	 TH1D *h_basicClusters_EE_eta;

	 // Super Clusters ----------------------------------------------
	 // ... barrel
	 TH1D *h_superClusters_EB_size;
	 TH1D *h_superClusters_EB_nXtals;
	 TH1D *h_superClusters_EB_nBC;
	 TH1D *h_superClusters_EB_energy;
	 TH1D *h_superClusters_EB_rawEnergy;
	 TH1D *h_superClusters_EB_et;

	 // ... endcap
	 TH1D *h_superClusters_EEP_size;
	 TH1D *h_superClusters_EEP_nXtals;
	 TH1D *h_superClusters_EEP_nBC;
	 TH1D *h_superClusters_EEP_energy;
	 TH1D *h_superClusters_EEP_rawEnergy;
	 TH1D *h_superClusters_EEP_et;

	 TH1D *h_superClusters_EEM_size;
	 TH1D *h_superClusters_EEM_nXtals;
	 TH1D *h_superClusters_EEM_nBC;
	 TH1D *h_superClusters_EEM_energy;
	 TH1D *h_superClusters_EEM_rawEnergy;
	 TH1D *h_superClusters_EEM_et;

	 TH1D *h_superClusters_eta;
	 TH1D *h_superClusters_EB_eta;
	 TH1D *h_superClusters_EE_eta;

	 TH2D *h_superClusters_nBCvsEta;
	 TH1D *h_superClusters_nBC_0to1;
	 TH1D *h_superClusters_nBC_1to1d5;
	 TH1D *h_superClusters_nBC_1d5to1d8;
	 TH1D *h_superClusters_nBC_1d8to2d1;
	 TH1D *h_superClusters_nBC_2d1to2d5;
	 TH1D *h_superClusters_nBC_2d5to3;

};


#endif
