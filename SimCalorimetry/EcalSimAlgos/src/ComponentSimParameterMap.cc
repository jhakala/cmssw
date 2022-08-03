#include "SimCalorimetry/EcalSimAlgos/interface/ComponentSimParameterMap.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "DataFormats/EcalDetId/interface/EcalSubdetector.h"
#include <iostream>

/** Relevant constants are:
  4.5 photoelectrons per MeV (J. Nash's slides)
  APD gain 50, but analog signal stays in GeV
  Account for excess noise factor
 */

//ComponentSimParameterMap::ComponentSimParameterMap()
//    : theComponentParameters(2250., 1. / 2250., 1., 0, 10, 6, true, true),
//      m_addToBarrel(false),
//      m_separateDigi(false) {}

ComponentSimParameterMap::ComponentSimParameterMap( bool addToBarrel,
                                         bool separateDigi,
                                         double simHitToPhotoelectronsBarrel,
                                         double simHitToPhotoelectronsEndcap,
                                         double photoelectronsToAnalogBarrel,
                                         double photoelectronsToAnalogEndcap,
                                         double samplingFactor,
                                         double timePhase,
                                         int readoutFrameSize,
                                         int binOfMaximum,
                                         bool doPhotostatistics,
                                         bool syncPhase)
    :  m_addToBarrel(addToBarrel),
       m_separateDigi(separateDigi),
       theComponentParameters(simHitToPhotoelectronsBarrel,
                          photoelectronsToAnalogBarrel,
                          samplingFactor,
                          timePhase,
                          readoutFrameSize,
                          binOfMaximum,
                          doPhotostatistics,
                          syncPhase)   {}

/*
  CaloSimParameters(double simHitToPhotoelectrons, double photoelectronsToAnalog, 
                 double samplingFactor, double timePhase,
                 int readoutFrameSize, int binOfMaximum,
                 bool doPhotostatistics, bool syncPhase)
  */

const CaloSimParameters& ComponentSimParameterMap::simParameters(const DetId& detId) const {
    return theComponentParameters;
}
