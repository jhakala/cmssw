#ifndef EcalSimAlgos_ComponentShapeCollection_h
#define EcalSimAlgos_ComponentShapeCollection_h

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "SimCalorimetry/EcalSimAlgos/interface/EcalShapeBase.h"
#include "SimCalorimetry/EcalSimAlgos/interface/ComponentShape.h"

class ComponentShapeCollection {

public:
  // useDB = false
  ComponentShapeCollection(bool);
  ComponentShapeCollection() : ComponentShapeCollection(false) {buildMe();}
  // useDB = true, buildMe is executed when setEventSetup and DB conditions are available
  //ComponentShapeCollection(edm::ConsumesCollector iC) : ComponentShapeCollection(true), espsToken_(iC.esConsumes()) {} // TODO JCH
  ~ComponentShapeCollection() {}


  void setEventSetup(const edm::EventSetup& evtSetup);

  const ComponentShape* at(int depthIndex) const;
  static int toDepthBin(int index);

protected:
  void buildMe(const edm::EventSetup* es = nullptr);
  void fillCollection();

  bool m_useDBShape;
  double m_thresh;

private:
  const static int m_nDepthBins = 23; // dictated by SimG4CMS/Calo/src/ECalSD.cc, 230 mm / 10 mm
  //edm::ESGetToken<EcalSimPulseShape, EcalSimPulseShapeRcd> espsToken_;
  const ComponentShape* m_shapeArr[m_nDepthBins];
};

#endif
