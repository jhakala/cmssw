#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "SimCalorimetry/EcalSimAlgos/interface/ComponentShapeCollection.h"


//These methods are here to parallel what is in EcalShapeBase -- TODO: move this to a ComponentShapeCollection base class
ComponentShapeCollection::ComponentShapeCollection(bool useDBShape)
     : m_useDBShape(useDBShape),
       m_thresh(0.0) {
     fillCollection();
}


void ComponentShapeCollection::setEventSetup(const edm::EventSetup& evtSetup) {
  buildMe(&evtSetup);
}

void ComponentShapeCollection::buildMe(const edm::EventSetup* evtSetup) {
  fillCollection();
};


//These methods are to fill in what is done in Shape

void ComponentShapeCollection::fillCollection() {
  std::cout << "calling ComponentShapeCollection::fillCollection" << std::endl;
  //m_shapeArr->clear();
  for (int i=0; i<m_nDepthBins; ++i) {
    m_shapeArr[i] = new ComponentShape(i);
    std::cout << "filled collection for depth number " << i << std::endl;
  }
}

const ComponentShape* ComponentShapeCollection::at(int depthIndex) const {
  if (0 > toDepthBin(depthIndex) || toDepthBin(depthIndex) > m_nDepthBins) throw cms::Exception("ComponentShape:: invalid depth requested");
  return m_shapeArr[toDepthBin(depthIndex)];
}


int ComponentShapeCollection::toDepthBin(int index) {
  return index>>3;
}
