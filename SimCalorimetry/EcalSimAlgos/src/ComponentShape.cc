#include <cmath>

#include "SimCalorimetry/EcalSimAlgos/interface/ComponentShape.h"


// #define component_shape_debug 1

void ComponentShape::fillShape(float& time_interval,
                         double& m_thresh,
                         EcalShapeBase::DVec& aVec,
                         const edm::EventSetup* es) const {

#ifdef component_shape_debug
  std::cout << "ComponentShape::fillShape called with m_useDBShape = " << m_useDBShape << " m_thresh = " << m_thresh  << " time_interval = " << time_interval << std::endl;
#endif
  if (m_useDBShape) {
#ifdef component_shape_debug
      std::cout << ("[ComponentShape] about to check if es == nullptr") << std::endl;
#endif
    
    if (es == nullptr) {
      throw cms::Exception("[ComponentShape] DB conditions are not available, const edm::EventSetup* es == nullptr ");
    }
#ifdef component_shape_debug
    std::cout << "ComponentShape::fillShape about to call es->getData(espsToken_)" << m_useDBShape << std::endl;
#endif
    auto const& esps = es->getData(espsToken_);

    aVec = esps.barrel_shapes.at(m_shapeIndex);
    time_interval = esps.time_interval;
    m_thresh = esps.barrel_thresh;

#ifdef component_shape_debug
    std::cout << " time_interval = " << time_interval << " m_thresh = " << m_thresh << std::endl;
#endif

  } 

  else   { // fill with dummy values, since this does nothing
  
#ifdef component_shape_debug
      std::cout << ("[ComponentShape] calling fillShape with m_useDBShape==false, this should do nothing?");
#endif

  m_thresh = 0.00013;
  time_interval = 1.0;
  aVec.reserve(500);
  for (unsigned int i(0); i != 500; ++i)
    aVec.push_back(0.0);
  }
}

double ComponentShape::timeToRise() const { return 0.0; }

void ComponentShape::test() const {
  char filename [50];
  sprintf(filename, "component_shape_%d.txt", m_shapeIndex);
  m_shape_print(filename);
}
