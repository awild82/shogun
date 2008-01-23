/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _POLYKERNEL_H___
#define _POLYKERNEL_H___

#include "lib/common.h"
#include "kernel/SimpleKernel.h"
#include "features/RealFeatures.h"

class CPolyKernel: public CSimpleKernel<DREAL>
{
public:
	CPolyKernel(CRealFeatures* l, CRealFeatures* r, INT d, bool inhom, bool use_norm, INT size=10);
	CPolyKernel(INT size, INT degree, bool inhomogene=true, bool use_normalization=true);
	virtual ~CPolyKernel();
	
	virtual bool init(CFeatures* l, CFeatures* r);
	virtual void cleanup();

	/// load and save kernel init_data
	virtual bool load_init(FILE* src);
	virtual bool save_init(FILE* dest);

	// return what type of kernel we are Linear,Polynomial, Gaussian,...
	virtual EKernelType get_kernel_type() { return K_POLY; }

	// return the name of a kernel
	virtual const CHAR* get_name() { return "Poly"; };

protected:
	/// compute kernel function for features a and b
	/// idx_{a,b} denote the index of the feature vectors
	/// in the corresponding feature object
	virtual DREAL compute(INT idx_a, INT idx_b);

protected:
	INT degree;
	bool inhomogene;

	double* sqrtdiag_lhs;
	double* sqrtdiag_rhs;

	bool initialized;
	bool use_normalization;
};

#endif /* _POLYKERNEL_H__ */
