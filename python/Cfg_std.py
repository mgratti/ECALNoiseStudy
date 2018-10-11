# cmsRun Python Configuration file
# for more info on the syntax, see https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideAboutPythonConfigFile

import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')
# default arguments
options.outputFile = 'test0.root'
options.inputFiles = 'file:/scratch/mratti/ECALDPG_test_samples/CMSSW_10_0_0_RelValZEE_13_GEN-SIM-DIGI-RAW-RECO_PU25ns_100X_upgrade2018_realistic_v7_HS-v1__A_FILE.root'
# if not using file: it will look in the local storage element
options.maxEvents = -1 # -1 means all events, maxEvents considers the total over files considered
options.parseArguments()


# Define the process and set some options for it
process = cms.Process("Validation")


# initialize MessageLogger and output report
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(100)

# output
process.TFileService = cms.Service("TFileService",
     fileName = cms.string(options.outputFile)
)

# input
process.source = cms.Source("PoolSource",
    fileNames      = cms.untracked.vstring (options.inputFiles),
)

# number of events
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(options.maxEvents))


# Load CMSSW libraries that are needed - geometry
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff" )
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '100X_upgrade2018_realistic_forECAL_A_alpha_v1')
process.GlobalTag = GlobalTag(process.GlobalTag, '100X_upgrade2018_realistic_v7')
######### IS THE GT IMPORTANT HERE ??????????? maybe for the geometry it is !!!!!!! TODO: xcheck this

# Load the algorithm and send configurable arguments to it
process.ecalnoisestudy = cms.EDAnalyzer("ECALNoiseStudy",

    PVTag                     = cms.InputTag("offlinePrimaryVertices"),
    vertex                    = cms.InputTag("offlinePrimaryVertices"),

    genParticleCollection     = cms.InputTag("genParticles"),

    recHitCollection_EE       = cms.InputTag("ecalRecHit","EcalRecHitsEE"),
    recHitCollection_EB       = cms.InputTag("ecalRecHit","EcalRecHitsEB"),
    beamSpot                  = cms.InputTag("offlineBeamSpot"),

    #despite the name "Cleaned", this collection contains dirty PFRechits, those which do not pass the cleaning
    PFrecHitCollection = cms.InputTag("particleFlowRecHitECAL:Cleaned"),
#    PFrecHitCollection = cms.InputTag("particleFlowRecHitECAL"),

    PFclusterCollection = cms.InputTag("particleFlowClusterECAL"),

    superClusterCollection_EB = cms.InputTag("particleFlowSuperClusterECAL","particleFlowSuperClusterECALBarrel"),
    superClusterCollection_EE = cms.InputTag("particleFlowSuperClusterECAL","particleFlowSuperClusterECALEndcapWithPreshower"),

    ethrEB = cms.double(0.0),
    ethrEE = cms.double(0.0),
    scEtThrEB = cms.double(0.0),
    scEtThrEE = cms.double(0.0),

    anaName = cms.string('DoubleElectron'), # DoublePhoton, DoubleElectron, DoubleNu
)

process.p = cms.Path(
    process.ecalnoisestudy
    )
