import FWCore.ParameterSet.Config as cms

# Module for 2D rechit building 
# The algo uses the Linear Drift Velocity from DB (which is a 1D rec hit algo)
# The block of the reconstruction
from RecoLocalMuon.DTSegment.DTCombinatorialPatternReco2DAlgo_LinearDriftFromDB_CosmicData_cfi import *
dt2DSegments = cms.EDProducer("DTRecSegment2DProducer",
    # The reconstruction algo and its parameter set
    DTCombinatorialPatternReco2DAlgo_LinearDriftFromDB_CosmicData,
    # debuggin opt
    debug = cms.untracked.bool(False),
    # name of the rechit 1D collection in the event
    recHits1DLabel = cms.InputTag("dt1DRecHits")
)

# enable the t0 seg correction (event by event)
dt2DSegments.Reco2DAlgoConfig.performT0SegCorrection = False
dt2DSegments.Reco2DAlgoConfig.performT0_vdriftSegCorrection = False
