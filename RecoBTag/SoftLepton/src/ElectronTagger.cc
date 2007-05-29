#include <typeinfo>

#include "DataFormats/BTauReco/interface/SoftLeptonTagInfo.h"
#include "RecoBTag/SoftLepton/interface/ElectronTagger.h"

/// b-tag a jet based on track-to-jet parameters in the extened info collection
float ElectronTagger::discriminator(const reco::BaseTagInfo & tagInfo) const {
  // default value, used if there are no leptons associated to this jet
  float bestTag = -1.;
  try {
    const reco::SoftLeptonTagInfo & info = dynamic_cast<const reco::SoftLeptonTagInfo &>(tagInfo);
    // if there are multiple leptons, look for the highest tag result
    for (unsigned int i = 0; i < info.leptons(); i++) {
      const reco::SoftLeptonProperties & properties = info.properties(i);
      float tag = theNet.value(0, properties.ptRel, properties.sip3d, properties.deltaR, properties.ratioRel);
      if (tag > bestTag) 
        bestTag = tag;
    }
  } catch(std::bad_cast e) {
    // ERROR - trying to use the wrong XxxTagInfo
    throw edm::Exception(edm::errors::LogicError) << "Wrong reco::BaseTagInfo-derived collection passed, expected reco::SoftLeptonTagInfo";
  }
  return bestTag;
}
