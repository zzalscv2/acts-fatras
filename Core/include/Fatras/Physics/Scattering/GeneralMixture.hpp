// This file is part of the Acts project.
//
// Copyright (C) 2018 CERN for the benefit of the Acts project
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "Acts/Propagator/detail/InteractionFormulas.hpp"
#include "Fatras/Kernel/detail/RandomNumberDistributions.hpp"

namespace Fatras {

/// This scatter emulated core and tail scattering
///
/// General mixture model Fruehwirth, M. Liendl.
/// Comp. Phys. Comm. 141 (2001) 230-246
struct GeneralMixture {

  /// Steering parameter
  bool log_include = true;

  //- Scale the mixture level
  double genMixtureScalor = 1.;

  /// The Highland formula as a fallback for electrons
  Acts::detail::HighlandScattering highlandForumla;

  /// @brief Call operator to perform this scattering
  ///
  /// @tparam generator_t is a random number generator type
  /// @tparam detector_t is the detector information type
  /// @tparam particle_t is the particle information type
  ///
  /// @param[in] generator is the random number generator
  /// @param[in] detector the detector information
  /// @param[in] particle the particle which is being scattered
  ///
  /// @return a scattering angle in 3D
  template <typename generator_t, typename detector_t, typename particle_t>
  double operator()(generator_t &generator, const detector_t &detector,
                    particle_t &particle) const {

    // scale the path length to the radiation length
    // @todo path correction factor
    double tInX0 = detector.thickness() / detector.material().X0();

    // material properties
    double Z = detector.material().Z(); // charge layer material

    double theta(0.);

    if (std::abs(particle.pdg()) != 11) {

      /// Uniform distribution, will be sampled with generator
      UniformDist uniformDist = UniformDist(0., 1.);

      //----------------------------------------------------------------------------
      // see Mixture models of multiple scattering: computation and simulation.
      // -
      // R.Fruehwirth, M. Liendl. -
      // Computer Physics Communications 141 (2001) 230â246
      //----------------------------------------------------------------------------
      std::array<double, 4> scattering_params;
      // Decide which mixture is best
      double beta2 = (particle.beta() * particle.beta());
      double tob2 = tInX0 / beta2;
      if (tob2 > 0.6 / std::pow(Z, 0.6)) {
        // Gaussian mixture or pure Gaussian
        if (tob2 > 10) {
          scattering_params = getGaussian(particle.beta(), particle.p(), tInX0,
                                          genMixtureScalor);
        } else {
          scattering_params =
              getGaussmix(particle.beta(), particle.p(), tInX0,
                          detector.material().Z(), genMixtureScalor);
        }
        // Simulate
        theta = gaussmix(uniformDist, generator, scattering_params);
      } else {
        // Semigaussian mixture - get parameters
        auto scattering_params_sg =
            getSemigauss(particle.beta(), particle.p(), tInX0,
                         detector.material().Z(), genMixtureScalor);
        // Simulate
        theta = semigauss(uniformDist, generator, scattering_params_sg);
      }
    } else {

      /// Gauss distribution, will be sampled with generator
      GaussDist gaussDist = GaussDist(0., 1.);

      // for electrons we fall back to the Highland (extension)
      // return projection factor times sigma times gauss random
      theta = highlandForumla(particle.p(), particle.beta(), tInX0, true) *
              gaussDist(generator);
    }
    // return scaled by sqare root of two
    return M_SQRT2 * theta;
  }

  // helper methods for getting parameters and simulating

  std::array<double, 4> getGaussian(double beta, double p, double tInX0,
                                    double scale) const {
    std::array<double, 4> scattering_params;
    // Total standard deviation of mixture
    scattering_params[0] = 15. / beta / p * std::sqrt(tInX0) * scale;
    scattering_params[1] = 1.0; // Variance of core
    scattering_params[2] = 1.0; // Variance of tails
    scattering_params[3] = 0.5; // Mixture weight of tail component
    return scattering_params;
  }

  std::array<double, 4> getGaussmix(double beta, double p, double tInX0,
                                    double Z, double scale) const {
    std::array<double, 4> scattering_params;
    scattering_params[0] = 15. / beta / p * std::sqrt(tInX0) *
                           scale; // Total standard deviation of mixture
    double d1 = std::log(tInX0 / (beta * beta));
    double d2 = std::log(std::pow(Z, 2.0 / 3.0) * tInX0 / (beta * beta));
    double epsi;
    double var1 = (-1.843e-3 * d1 + 3.347e-2) * d1 + 8.471e-1; // Variance of
                                                               // core
    if (d2 < 0.5)
      epsi = (6.096e-4 * d2 + 6.348e-3) * d2 + 4.841e-2;
    else
      epsi = (-5.729e-3 * d2 + 1.106e-1) * d2 - 1.908e-2;
    scattering_params[1] = var1;                           // Variance of core
    scattering_params[2] = (1 - (1 - epsi) * var1) / epsi; // Variance of tails
    scattering_params[3] = epsi; // Mixture weight of tail component
    return scattering_params;
  }

  std::array<double, 6> getSemigauss(double beta, double p, double tInX0,
                                     double Z, double scale) const {
    std::array<double, 6> scattering_params;
    double N = tInX0 * 1.587E7 * std::pow(Z, 1.0 / 3.0) / (beta * beta) /
               (Z + 1) / std::log(287 / std::sqrt(Z));
    scattering_params[4] = 15. / beta / p * std::sqrt(tInX0) *
                           scale; // Total standard deviation of mixture
    double rho = 41000 / std::pow(Z, 2.0 / 3.0);
    double b = rho / std::sqrt(N * (std::log(rho) - 0.5));
    double n = std::pow(Z, 0.1) * std::log(N);
    double var1 = (5.783E-4 * n + 3.803E-2) * n + 1.827E-1;
    double a =
        (((-4.590E-5 * n + 1.330E-3) * n - 1.355E-2) * n + 9.828E-2) * n +
        2.822E-1;
    double epsi = (1 - var1) / (a * a * (std::log(b / a) - 0.5) - var1);
    scattering_params[3] =
        (epsi > 0) ? epsi : 0.0; // Mixture weight of tail component
    scattering_params[0] = a;    // Parameter 1 of tails
    scattering_params[1] = b;    // Parameter 2 of tails
    scattering_params[2] = var1; // Variance of core
    scattering_params[5] = N;    // Average number of scattering processes
    return scattering_params;
  }

  /// @brief Retrieve the gaussian mixture
  ///
  /// @tparam generator_t Type of the generator
  ///
  /// @param udist The uniform distribution handed over by the call operator
  /// @param scattering_params the tuned parameters for the generation
  ///
  /// @return a double value that represents the gaussian mixture
  template <typename generator_t>
  double gaussmix(UniformDist &udist, generator_t &generator,
                  const std::array<double, 4> &scattering_params) const {
    double sigma_tot = scattering_params[0];
    double var1 = scattering_params[1];
    double var2 = scattering_params[2];
    double epsi = scattering_params[3];
    bool ind = udist(generator) > epsi;
    double u = udist(generator);
    if (ind)
      return std::sqrt(var1) * std::sqrt(-2 * std::log(u)) * sigma_tot;
    else
      return std::sqrt(var2) * std::sqrt(-2 * std::log(u)) * sigma_tot;
  }

  /// @brief Retrieve the semi-gaussian mixture
  ///
  /// @tparam generator_t Type of the generator
  ///
  /// @param udist The uniform distribution handed over by the call operator
  /// @param scattering_params the tuned parameters for the generation
  ///
  /// @return a double value that represents the gaussian mixture
  template <typename generator_t>
  double semigauss(UniformDist &udist, generator_t &generator,
                   const std::array<double, 6> &scattering_params) const {
    double a = scattering_params[0];
    double b = scattering_params[1];
    double var1 = scattering_params[2];
    double epsi = scattering_params[3];
    double sigma_tot = scattering_params[4];
    bool ind = udist(generator) > epsi;
    double u = udist(generator);
    if (ind)
      return std::sqrt(var1) * std::sqrt(-2 * std::log(u)) * sigma_tot;
    else
      return a * b * std::sqrt((1 - u) / (u * b * b + a * a)) * sigma_tot;
  }
};

} // namespace Fatras
