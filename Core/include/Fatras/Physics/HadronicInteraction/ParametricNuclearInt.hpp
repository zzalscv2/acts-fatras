// This file is part of the ACTS project.
//
// Copyright (C) 2018 ACTS project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef FATRAS_SAMPLER_PARAMETRICNI_HPP
#define FATRAS_SAMPLER_PARAMETRICNI_HPP

#include "Fatras/Kernel/FatrasDefinitions.hpp"
#include "Fatras/Kernel/RandomNumberDistributions.hpp"

namespace Fatras {
      
  const double log_2 =  std::log(2.);    
  
  /// The struct for the physics list
  /// 
  ///
  struct ParametricNuclearInt {
    
    double scaleFactor = 1.;
    
    /// Call operator
    /// 
    /// @tparam generator_t is a random number generator type 
    /// @tparam detector_t is the detector information type
    /// @tparam particle_t is the particle information type 
    ///
    /// @param[in] generator is the random number generator
    /// @param[in] detector the detector information 
    /// @param[in] particle the particle which is being scattered
    /// 
    /// @return eventually produced photons
    template <typename generator_t, typename detector_t, typename particle_t>
    std::vector<particle_t>
    operator()(generator_t& generator,
               const detector_t& detector,
               particle_t& particle) const 
    {      

      // todo return photons
      return {};
      
    }
          
  };

} // end of namespace Fatras

#endif // FATRAS_SAMPLER_PARAMETRICNI_HPP