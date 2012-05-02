/*
 * Derived from:
 *
 * NormalEstimator.java
 * Copyright (C) 1999 University of Waikato, Hamilton, New Zealand
 *
 */

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __WEKACPP_ESTIMATORS_NORMALESTIMATOR__
#define __WEKACPP_ESTIMATORS_NORMALESTIMATOR__

#include <weka/core/Instances.h>
#include <weka/core/Instance.h>
#include <cmath>
#include <stdexcept>

namespace weka {

	namespace estimators {

using namespace std;

class NormalEstimator : public Estimator
{
 public:
	double m_SumOfWeights;
	double m_SumOfValues;
	double m_SumOfValuesSq;
	double m_Mean;
	double m_Precision;
	double m_StandardDev;

 public:
	NormalEstimator(double precision) :
		m_Precision(precision),
		m_StandardDev(precision / (2 * 3))
	{
	}

	virtual ~NormalEstimator();

	double
	round (double data)
	{
		return rint(data / m_Precision) * m_Precision;
	}

	void addValue(double data, double weight);
	double getProbability(double data);
};

} // namespace estimators
} // namespace weka

#endif /* __WEKACPP_ESTIMATORS_NORMALESTIMATOR__ */

// Local variables:
//  mode: C++
//  c-indent-level: 4
//  c-basic-offset: 4
//  tab-width: 4
// End:
//
// vim:tabstop=4:shiftwidth=4:smarttab:

