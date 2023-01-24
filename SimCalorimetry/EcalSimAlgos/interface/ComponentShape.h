#ifndef EcalSimAlgos_ComponentShape_h
#define EcalSimAlgos_ComponentShape_h

#include "FWCore/Framework/interface/ConsumesCollector.h"
#include "SimCalorimetry/EcalSimAlgos/interface/EcalShapeBase.h"

class ComponentShape : public EcalShapeBase {
public:
  // useDB = false
  ComponentShape(int shapeIndex) : EcalShapeBase(false), m_shapeIndex(shapeIndex) { buildMe(nullptr, false); }
  // useDB = true, buildMe is executed when setEventSetup and DB conditions are available
  ComponentShape(int shapeIndex, edm::ConsumesCollector iC) : EcalShapeBase(false), espsToken_(iC.esConsumes()), m_shapeIndex(shapeIndex) {  buildMe(nullptr, false); } // TODO change this to actually use database

  double timeToRise() const override; // need to stop default EcalShapeBase from aligning component shapes to same peaking time

  void test() const;

protected:
  void fillShape(float& time_interval,
                 double& m_thresh,
                 EcalShapeBase::DVec& aVec,
                 const edm::EventSetup* es) const override;

private:
  edm::ESGetToken<EcalSimPulseShape, EcalSimPulseShapeRcd> espsToken_;
  int m_shapeIndex;
};

#endif
