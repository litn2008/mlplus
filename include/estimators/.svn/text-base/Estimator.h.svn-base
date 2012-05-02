/*
 * Derived from:
 *
 * Estimator.java
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

#ifndef __WEKACPP_ESTIMATORS_ESTIMATOR__
#define __WEKACPP_ESTIMATORS_ESTIMATOR__

#include <weka/core/Instances.h>
#include <weka/core/Instance.h>
#include <stdexcept>

namespace weka {
	namespace estimators {

using namespace std;

class Estimator
{
	double m_classValueIndex;
	bool m_noClass;

	int getMinMax(Instances * instances, int attrIndex, double minMax[2]);
	double getInstancesFromClass(Instances * data, int attrIndex,
		int classIndex, double classValue, Instances * workData);

 public:
	static const int BAYES = 0;
	static const int BDeu = 1;
	static const int MDL = 2;
	static const int AIC = 3;
	static const int ENTROPY = 4;

	static void buildEstimator(Estimator * est, Instances * instances,
			int attrIndex, int classIndex, int classValueIndex,
			bool isIncremental);

	Estimator() :
		m_classValueIndex(-1.0), m_noClass(true)
	{
	}

	virtual ~Estimator();

	virtual void addValues(Instances * data, int attrIndex);
	virtual void addValues(Instances * data, int attrIndex, double min,
		double max, double factor);
	virtual void addValues(Instances * data, int attrIndex, int classIndex,
		int classValue);
	virtual void addValues(Instances * data, int attrIndex, int classIndex,
		int classValue, double min, double max);

	virtual void addValue(double data, double weight) = 0;
	virtual double getProbability(double data) = 0;

	virtual double logScore(int nType);
};

} // namespace estimators
} // namespace weka

#endif /* __WEKACPP_ESTIMATORS_ESTIMATOR__ */

// Local variables:
//  mode: C++
//  c-indent-level: 4
//  c-basic-offset: 4
//  tab-width: 4
// End:
//
// vim:tabstop=4:shiftwidth=4:smarttab:

