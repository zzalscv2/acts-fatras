// This file is part of the Acts project.
//
// Copyright (C) 2018-2019 Acts project team
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <map>

namespace Fatras {
namespace detail{

const double sqrt2pi = std::sqrt(2. * M_PI);

constexpr std::array<int, 5> pdgCodes = {-211, 111, 211, 2112, 2212};

/// Look-up table for particles
/// @note The structure is std::map<PDG id, std::pair<mass, charge>>
const std::map<int, std::pair<double, double>> particleData =
{
// pi-
	{-211, std::make_pair(0.1395701 * Acts::units::_GeV, -1.)},
// pi0
	{111, std::make_pair(0.1349766 * Acts::units::_GeV, 0.)},
// K0long
	{130, std::make_pair(0.497614 * Acts::units::_GeV, 0.)},
// pi+
	{211, std::make_pair(0.1395701 * Acts::units::_GeV, 1.)},
// K+
	{321, std::make_pair(0.493677 * Acts::units::_GeV, 1.)},
// neutron
	{2112, std::make_pair(939.56563 * Acts::units::_MeV, 0.)},
// proton
	{2212, std::make_pair(938.27231 * Acts::units::_MeV, 1.)}
};
	
struct Parameters
{
	Parameters(const std::array<double, 6>& nuclIntProb,
			   const std::array<double, 7>& mult,
			   const std::list<std::pair<double, int>>& partTypes,
			   const std::array<double, 10>& eScaling,
			   const std::pair<double, double>& eScalingEpol,
			   const std::array<double, 6>& thAngle) : nuclearInteractionProbability(nuclIntProb), multiplicity(mult), particleTypes(partTypes), energyScaling(eScaling), 
													   energyScalingExtrapolation(eScalingEpol), thetaAngle(thAngle) 
	{}
	
	/// Fit parameters for the probability of nulear interaction
	const std::array<double, 6> nuclearInteractionProbability;
	/// Fit parameters for the multiplicity distribution
	const std::array<double, 7> multiplicity;
	/// Probabilities to produce certain particles
	const std::list<std::pair<double, int>> particleTypes;
	/// Fit parameters for the energy of the first 10 outgoing particles
	const std::array<double, 10> energyScaling;
	/// Fit parameters for the energy of all other outgoing particles
	const std::pair<double, double> energyScalingExtrapolation;
	/// Fit parameters for the distribution of the theta angles
	const std::array<double, 6> thetaAngle;
};

constexpr std::array<double, 6> nuclIntProbPiMinus = {-0.85589, 1.0763, -0.028606, 0.01827, 1.3097, 0.081749};
constexpr std::array<double, 6> nuclIntProbPiPlus = {-0.904434, 0.985991, -0.015039, 0.036966, 1.31977, 0.12179};
constexpr std::array<double, 6> nuclIntProbNeutron = {-1.04484, 0.67312, 0.079093, 0.42005, 1.8368, 0.92685};
constexpr std::array<double, 6> nuclIntProbProton = {-1.01212, 0.717381, 0.075032, 0.35375, 1.89725, 0.83433};

constexpr std::array<double, 7> multPiMinus = {1.9677, -0.399229, -0.0405634, 0.915227, 1.39859, 0.130268, 0.0292009};
constexpr std::array<double, 7> multPiPlus = {1.22082, -0.661119, 0., 0.880236, 1.28554, 0.18008, 0.};
constexpr std::array<double, 7> multNeutron = {1.8136, -0.453892, 0., 0.900732, 1.187129, 0.125797, 0.};
constexpr std::array<double, 7> multProton = {0.679744, -1.18508, 0.157405, 1.07033, 1.09336, -0.119505, 0.0505715};

const std::list<std::pair<double, int>> partTypesPiMinus = {
	std::make_pair(0.58345, -211),
	std::make_pair(0.585245, 130),
	std::make_pair(0.612815, 211),
	std::make_pair(0.614008, 321),
	std::make_pair(0.949433, 2112),
	std::make_pair(0.996385, 2212)
	};
const std::list<std::pair<double, int>> partTypesPiPlus = {
	std::make_pair(0.037348, -211),
	std::make_pair(0.0384697, 130),
	std::make_pair(0.634316, 211),
	std::make_pair(0.636931, 321),
	std::make_pair(0.926136, 2112),
	std::make_pair(0.996833, 2212)
	};
const std::list<std::pair<double, int>> partTypesNeutron = {
	std::make_pair(0.0381688, -211),
	std::make_pair(0.0516587, 211),
	std::make_pair(0.91314, 2112),
	std::make_pair(0.99883, 2212)
	};
const std::list<std::pair<double, int>> partTypesProton = {
	std::make_pair(0.0170427, -211),
	std::make_pair(0.0457174, 211),
	std::make_pair(0.378015, 2112),
	std::make_pair(0.998838, 2212)
	};

constexpr std::array<double, 10> eScalingPiMinus = {1.43911, 3.03515, 6.24957, 13.4978, 35.7948, 53.0301, 63.4815, 72.3156, 80.5419, 88.7695};
constexpr std::array<double, 10> eScalingPiPlus = {1.48089, 3.11388, 6.53058, 14.2392, 38.2195, 54.059, 63.3495, 71.2761, 78.8044, 86.3353};
constexpr std::array<double, 10> eScalingNeutron = {0.984621, 2.5168, 5.44376, 12.6065, 41.0249, 58.18, 69.3694, 79.4628, 88.9836, 98.8031};
constexpr std::array<double, 10> eScalingProton = {1.06923, 2.75259, 5.86034, 13.6034, 42.9559, 58.9314, 69.3068, 78.6077, 87.4014, 95.5143};

constexpr std::pair<double, double> eScalingFitPiMinus(4.80037, 8.40903);
constexpr std::pair<double, double> eScalingFitPiPlus(9.92848, 7.64857);
constexpr std::pair<double, double> eScalingFitNeutron(1.00611, 9.78219);
constexpr std::pair<double, double> eScalingFitProton(8.40378, 8.74162);

constexpr std::array<double, 6> thAnglePiMinus = {0.28118, 0.226549, 0.027127, 0.15234, 0.17351, 0.106461};
constexpr std::array<double, 6> thAnglePiPlus = {0.280964, 0.230181, 0.0207953, 0.134091, 0.18035, 0.122065};
constexpr std::array<double, 6> thAngleNeutron = {0.246799, 0.201138, 0.0291222, 0.142521, 0.204159, 0.141606};
constexpr std::array<double, 6> thAngleProton = {0.248282, 0.197624, 0.0174567, 0.135244, 0.213525, 0.151874};

const std::map<int, Parameters> parametrizations =
{
// pi-
	{-211, Parameters(nuclIntProbPiMinus, multPiMinus, partTypesPiMinus, eScalingPiMinus, eScalingFitPiMinus, thAnglePiMinus)},
// pi+
	{211, Parameters(nuclIntProbPiPlus, multPiPlus, partTypesPiPlus, eScalingPiPlus, eScalingFitPiPlus, thAnglePiPlus)},
// neutron	
	{2112, Parameters(nuclIntProbNeutron, multNeutron, partTypesNeutron, eScalingNeutron, eScalingFitNeutron, thAngleNeutron)},
// proton
	{2212, Parameters(nuclIntProbProton, multProton, partTypesProton, eScalingProton, eScalingFitProton, thAngleProton)},
};

/// Parameters used to estimate the probability for a nuclear interaction
const std::map<int, std::array<double, 6>> probability =
{
// pi-
	{-211, {-0.85589, 1.0763, -0.028606, 0.01827, 1.3097, 0.081749}},
// pi0
	{111, {0,0,0,0,0,0}},
// pi+
	{211, {-0.904434, 0.985991, -0.015039, 0.036966, 1.31977, 0.12179}},
// neutron
	{2112, {-1.04484, 0.67312, 0.079093, 0.42005, 1.8368, 0.92685}},
// proton
	{2212, {-1.01212, 0.717381, 0.075032, 0.35375, 1.89725, 0.83433}}
};

/// Parameters used to estimate the multiplicity in a nuclear interaction
const std::map<int, std::array<double, 7>> multiplicity =
{
// pi-
	{-211, {1.9677, -0.399229, -0.0405634, 0.915227, 1.39859, 0.130268, 0.0292009}},
// pi0
	{111, {0,0,0,0,0,0}},
// pi+
	{211, {1.22082, -0.661119, 0., 0.880236, 1.28554, 0.18008, 0.}},
// neutron
	{2112, {1.8136, -0.453892, 0., 0.900732, 1.187129, 0.125797, 0.}},
// proton
	{2212, {0.679744, -1.18508, 0.157405, 1.07033, 1.09336, -0.119505, 0.0505715}}
};

/// Cumulative probabilities for the production of resulting particle in a nuclear interaction
const std::map<int, std::list<std::pair<double, int>>> particleTypes = 
{
// pi-
	{-211, {
	std::make_pair(0.58345, -211),
	std::make_pair(0.585245, 130),
	std::make_pair(0.612815, 211),
	std::make_pair(0.614008, 321),
	std::make_pair(0.949433, 2112),
	std::make_pair(0.996385, 2212)
	}},
// pi0
	{111, {
	std::make_pair(0.0745813, -211),
	std::make_pair(0.129518, 211),
	std::make_pair(0.86305, 2112),
	std::make_pair(0.997921, 2212)
	}},
// pi+
	{211, {
	std::make_pair(0.037348, -211),
	std::make_pair(0.0384697, 130),
	std::make_pair(0.634316, 211),
	std::make_pair(0.636931, 321),
	std::make_pair(0.926136, 2112),
	std::make_pair(0.996833, 2212)
	}},
// neutron
	{2112, {
	std::make_pair(0.0381688, -211),
	std::make_pair(0.0516587, 211),
	std::make_pair(0.91314, 2112),
	std::make_pair(0.99883, 2212)
	}},
// proton
	{2212, {
	std::make_pair(0.0170427, -211),
	std::make_pair(0.0457174, 211),
	std::make_pair(0.378015, 2112),
	std::make_pair(0.998838, 2212)
	}}
};

/// Scaling factors of the energy distribution function
const std::map<int, std::array<double, 10>> energyScaling =
{
// pi-
	{-211,
	{1.43911, 3.03515, 6.24957, 13.4978, 35.7948, 53.0301, 63.4815, 72.3156, 80.5419, 88.7695}},
// pi0
	{111,
	{0., 0., 0., 0., 0., 0., 0., 0., 0., 0.}},
// pi+
	{211,
	{1.48089, 3.11388, 6.53058, 14.2392, 38.2195, 54.059, 63.3495, 71.2761, 78.8044, 86.3353}},
// neutron
	{2112,
	{0.984621, 2.5168, 5.44376, 12.6065, 41.0249, 58.18, 69.3694, 79.4628, 88.9836, 98.8031}},
// proton
	{2212, 
	{1.06923, 2.75259, 5.86034, 13.6034, 42.9559, 58.9314, 69.3068, 78.6077, 87.4014, 95.5143}}
};

/// Scaling factors of the energy distribution function fitted extrapolation parameters for higher multiplicities
const std::map<int, std::pair<double, double>> energyScalingFit =
{
// pi-
	{-211, std::make_pair(4.80037, 8.40903)},
// pi0
	{111, std::make_pair(0., 0.)},
// pi+
	{211, std::make_pair(9.92848, 7.64857)},
// neutron
	{2112, std::make_pair(1.00611, 9.78219)},
// proton
	{2212, std::make_pair(8.40378, 8.74162)}
};

const std::map<int, std::array<double, 6>> thetaParameters =
{
// pi-
	{-211, {0.28118, 0.226549, 0.027127, 0.15234, 0.17351, 0.106461}},
// pi0
	{111, {0., 0., 0., 0., 0., 0.}},
// pi+
	{211, {0.280964, 0.230181, 0.0207953, 0.134091, 0.18035, 0.122065}},
// neutron
	{2112, {0.246799, 0.201138, 0.0291222, 0.142521, 0.204159, 0.141606}},
// proton
	{2212, {0.248282, 0.197624, 0.0174567, 0.135244, 0.213525, 0.151874}}
};

} // namespace detail

template<typename generator_t>
std::vector<int>
ParametricNuclearInt::particleComposition(generator_t& generator, const int pdg, const unsigned int nParticles) const
{
	// Setup of result container
	std::vector<int> result;
	result.reserve(nParticles);
	double dice;

	// Find the list of probabilities
	const std::list<std::pair<double, int>>& particleLookUp = detail::particleTypes.at(pdg);
	std::list<std::pair<double, int>>::const_iterator cit;

	// Loop and insert PDG codes
	while(result.size() < nParticles)
	{
		dice = generator();
		// Search for fitting PDG code
		for(cit = particleLookUp.begin(); cit != particleLookUp.end(); cit++)
		{
			// Insert PGD code
			if(dice < cit->first)
			{
				result.push_back(cit->second);
				break;
			}
		}
	}
	
	return result;
}

template<typename generator_t>
std::vector<double>
ParametricNuclearInt::energyFractions(generator_t& generator, const int pdg, const unsigned int nParticles) const
{
	// Storage of the resulting energies
	std::vector<double> result;
	result.resize(nParticles);

	double eFraction = 0.;
		
	// Extract the fit parameters
	const std::array<double, 10>& scalingFactors = detail::energyScaling.at(pdg);

	// Repeat sampling as long as the energies are too big
	while(true)
	{
		double sumFractions = 0.;

		// Sample the energies from distribution and store them
		for(unsigned int n = 0; n < nParticles; n++)
		{
			if(nParticles <= 10)
			{
				eFraction = energyFraction(generator(), scalingFactors[n], n + 1);
			}
			else
			{
				// TODO: Might be a performance issue if this is extracted many times
				// Extract the fit parameters to estimate the fit parameters for sampling
				const std::pair<double, double>& fitParameters = detail::energyScalingFit.at(pdg);
				eFraction = energyFraction(generator(), fitParameters.first + (n + 1) * fitParameters.second, n + 1);
			}
			result[n] = eFraction;
			sumFractions += eFraction;
		}
		
		// Test if energies are <= the initial energy
		if(sumFractions <= 1.)
			break;
	}
	
	return result;
}

template<typename generator_t, typename particle_t>
std::vector<particle_t>
ParametricNuclearInt::kinematics(generator_t& generator, particle_t& particle, const std::vector<int>& particlesPDGs) const
{
	// Evaluate the energy of each outgoing particle
	const std::vector<double> energy = energyFractions(generator, particle.pdg(), particlesPDGs.size());

	// Produce the particles
	std::vector<particle_t> outgoingParticles;
	outgoingParticles.reserve(particlesPDGs.size());

	const std::array<double, 6>& thetaFitParameters = detail::thetaParameters.at(particle.pdg());
	
	for(unsigned int i = 0; i < particlesPDGs.size(); i++)
	{
		const double phi = -M_PI + 2. * M_PI * generator();
		const double theta = sampleTheta(generator, thetaFitParameters);
		Acts::Vector3D momentum = {std::sin(theta) * std::cos(phi), std::sin(theta) * std::sin(phi), std::cos(theta)};
		
		//~ Acts::Vector3D momentum = particle.momentum().normalized();
		
		const double kinEnergy = energy[i] * particle.E();
		momentum *= kinEnergy;
		
		const std::pair<double, double>& pData = detail::particleData.at(particlesPDGs[i]);

		outgoingParticles.push_back(particle_t(particle.position(), 
											 momentum, 
											 pData.first,
											 pData.second,
											 particlesPDGs[i],
											 0, // TODO: barcode
											 particle.time()));
	}

  return outgoingParticles;
}

template <typename generator_t, typename detector_t, typename particle_t>
std::vector<particle_t> 
ParametricNuclearInt::operator()(generator_t& generator,
                                     const detector_t& detector,
                                     particle_t& particle) const
{
	// Test applicable PDG codes
	for(const auto& pc : detail::pdgCodes)
		if(particle.pdg() == pc)
		{
			const double thicknessInL0 = detector.thickness() / detector.averageL0();
			
			// If a nuclear interaction occurs ...
			if (generator() < nuclearInteractionProb(particle.p(), thicknessInL0, particle.pdg()))
				// ... calculate the final state hadrons
				return finalStateHadrons(generator, thicknessInL0, particle);
				
			break;
		}
	// No hadronic interactions occured
	return {particle};
}
} // namespace Fatras
