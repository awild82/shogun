/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _LDA_H___
#define _LDA_H___

#include "lib/common.h"

#ifdef HAVE_LAPACK
#include "features/Features.h"
#include "classifier/LinearClassifier.h"

class CLDA : public CLinearClassifier
{
	public:
		CLDA(DREAL gamma=0);
		CLDA(DREAL gamma, CRealFeatures* traindat, CLabels* trainlab);
		virtual ~CLDA();

		inline void set_gamma(DREAL gamma)
		{
			m_gamma=gamma;
		}

		inline DREAL get_gamma()
		{
			return m_gamma;
		}

		virtual bool train();

		inline virtual EClassifierType get_classifier_type()
		{
			return CT_LDA;
		}
	protected:
		DREAL m_gamma;
};
#endif
#endif
