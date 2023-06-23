#include "Geometry/HcalCommonData/interface/HcalHitRelabeller.h"
#include "DataFormats/HcalDetId/interface/HcalTestNumbering.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

//#define EDM_ML_DEBUG

HcalHitRelabeller::HcalHitRelabeller(bool nd) : theRecNumber(nullptr), neutralDensity_(nd) {
#ifdef EDM_ML_DEBUG
  edm::LogVerbatim("HcalSim") << "HcalHitRelabeller initialized with"
                              << " neutralDensity " << neutralDensity_;
#endif
}

void HcalHitRelabeller::process(std::vector<PCaloHit>& hcalHits) {
  if (theRecNumber) {
#ifdef EDM_ML_DEBUG
    int ii(0);
#endif
    for (auto& hcalHit : hcalHits) {
#ifdef EDM_ML_DEBUG
      edm::LogVerbatim("HcalSim") << "Hit[" << ii << "] " << std::hex << hcalHit.id() << std::dec << " Neutral density "
                                  << neutralDensity_;
#endif
      double energy = (hcalHit.energy());
      if (neutralDensity_) {
        energy *= (energyWt(hcalHit.id()));
        hcalHit.setEnergy(energy);
      }
      DetId newid = relabel(hcalHit.id());
#ifdef EDM_ML_DEBUG
      edm::LogVerbatim("HcalSim") << "Hit " << ii << " out of " << hcalHits.size() << " " << std::hex << newid.rawId()
                                  << std::dec << " E " << energy;
#endif
      hcalHit.setID(newid.rawId());
#ifdef EDM_ML_DEBUG
      edm::LogVerbatim("HcalSim") << "Modified Hit " << HcalDetId(hcalHit.id());
      ++ii;
#endif
    }
  } else {
    edm::LogWarning("HcalSim") << "HcalHitRelabeller: no valid HcalDDDRecConstants";
  }
}

void HcalHitRelabeller::setGeometry(const HcalDDDRecConstants*& recNum) { theRecNumber = recNum; }

DetId HcalHitRelabeller::relabel(const uint32_t testId) const {
  return HcalHitRelabeller::relabel(testId, theRecNumber);
}

DetId HcalHitRelabeller::relabel(const uint32_t testId, const HcalDDDRecConstants* theRecNumber) {
#ifdef EDM_ML_DEBUG
  edm::LogVerbatim("HcalSim") << "Enter HcalHitRelabeller::relabel";
#endif
  HcalDetId hid;
  int det, z, depth, eta, phi, layer, sign;
  HcalTestNumbering::unpackHcalIndex(testId, det, z, depth, eta, phi, layer);
#ifdef EDM_ML_DEBUG
  edm::LogVerbatim("HcalSim") << "det: " << det << " "
                              << "z: " << z << " "
                              << "depth: " << depth << " "
                              << "ieta: " << eta << " "
                              << "iphi: " << phi << " "
                              << "layer: " << layer;
#endif
  sign = (z == 0) ? (-1) : (1);
  HcalDDDRecConstants::HcalID id = theRecNumber->getHCID(det, sign * eta, phi, layer, depth);

  if (id.subdet == int(HcalBarrel)) {
    hid = HcalDetId(HcalBarrel, sign * id.eta, id.phi, id.depth);
  } else if (id.subdet == int(HcalEndcap)) {
    hid = HcalDetId(HcalEndcap, sign * id.eta, id.phi, id.depth);
  } else if (id.subdet == int(HcalOuter)) {
    hid = HcalDetId(HcalOuter, sign * id.eta, id.phi, id.depth);
  } else if (id.subdet == int(HcalForward)) {
    hid = HcalDetId(HcalForward, sign * id.eta, id.phi, id.depth);
  }
#ifdef EDM_ML_DEBUG
  edm::LogVerbatim("HcalSim") << " new HcalDetId -> hex.RawID = " << std::hex << hid.rawId() << std::dec
                              << " det, z, depth, eta, phi = " << det << " " << z << " " << id.depth << " " << id.eta
                              << " " << id.phi << " ---> " << hid;
#endif
  return hid;
}

double HcalHitRelabeller::energyWt(const uint32_t testId) const {
  HcalDetId hid;
  hid = relabel(testId);
  double wt = (((hid.subdet() == HcalSubdetector::HcalBarrel) || (hid.subdet() == HcalEndcap)) && (hid.depth() == 1)) ? 
              theRecNumber->getLayer0Wt(hid.subdet(), hid.iphi(), hid.zside()) : 1.0;
#ifdef EDM_ML_DEBUG
  edm::LogVerbatim("HcalSim") << "EnergyWT::det: " << hid.subdet() << " zside: " << hid.zside() << " depth: " << hid.depth()
                              << " ieta: " << hid.ieta() << " iphi: " << hid.iphi() << " wt " << wt;
#endif
  return wt;
}
