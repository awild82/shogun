/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2007-2008 Vojtech Franc
 * Written (W) 2007-2008 Soeren Sonnenburg
 * Copyright (C) 2007-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _WDSVMOCAS_H___
#define _WDSVMOCAS_H___

#include "lib/common.h"
#include "classifier/Classifier.h"
#include "classifier/svm/SVMOcas.h"
#include "features/StringFeatures.h"
#include "features/Labels.h"

class CWDSVMOcas : public CClassifier
{
	public:
		CWDSVMOcas(E_SVM_TYPE);
		CWDSVMOcas(DREAL C, INT d, INT from_d, CStringFeatures<BYTE>* traindat, CLabels* trainlab);
		virtual ~CWDSVMOcas();

		virtual inline EClassifierType get_classifier_type() { return CT_WDSVMOCAS; }
		virtual bool train();

		inline void set_C(DREAL c1, DREAL c2) { C1=c1; C2=c2; }

		inline DREAL get_C1() { return C1; }
		inline DREAL get_C2() { return C2; }

		inline void set_epsilon(DREAL eps) { epsilon=eps; }
		inline DREAL get_epsilon() { return epsilon; }

		inline void set_features(CStringFeatures<BYTE>* feat) { features=feat; }
		inline CStringFeatures<BYTE>* get_features() { return features; }

		inline void set_bias_enabled(bool enable_bias) { use_bias=enable_bias; }
		inline bool get_bias_enabled() { return use_bias; }

		inline void set_bufsize(INT sz) { bufsize=sz; }
		inline INT get_bufsize() { return bufsize; }

		inline void set_degree(INT d, INT from_d) { degree=d; from_degree=from_d;}
		inline INT get_degree() { return degree; }

		CLabels* classify(CLabels* output);

		inline virtual DREAL classify_example(INT num)
		{
			ASSERT(features);
			if (!wd_weights)
				set_wd_weights();

			INT len=0;
			DREAL sum=0;
			BYTE* vec = features->get_feature_vector(num, len);
			ASSERT(len == string_length);

			for (INT j=0; j<string_length; j++)
			{
				INT offs=w_dim_single_char*j;
				INT val=0;
				for (INT k=0; (j+k<string_length) && (k<degree); k++)
				{
					val=val*alphabet_size + vec[j+k];
					sum+=wd_weights[k] * w[offs+val];
					offs+=w_offsets[k];
				}
			}
			return sum/normalization_const;
		}

		inline void set_normalization_const()
		{
			ASSERT(features);
			normalization_const=0;
			for (INT i=0; i<degree; i++)
				normalization_const+=(string_length-i)*wd_weights[i]*wd_weights[i];

			normalization_const=CMath::sqrt(normalization_const);
			SG_DEBUG("normalization_const:%f\n", normalization_const);
		}

		inline DREAL get_normalization_const() { return normalization_const; }


	protected:

		INT set_wd_weights();
		static void compute_W( double *sq_norm_W, double *dp_WoldW, double *alpha, uint32_t nSel, void* ptr );
		static double update_W(double t, void* ptr );
		static void* add_new_cut_helper(void* ptr);
		static void add_new_cut( double *new_col_H, uint32_t *new_cut, uint32_t cut_length, uint32_t nSel, void* ptr );
		static void* compute_output_helper(void* ptr);
		static void compute_output( double *output, void* ptr );
		static void sort( double* vals, uint32_t* idx, uint32_t size);


	protected:
		CStringFeatures<BYTE>* features;
		bool use_bias;
		INT bufsize;
		DREAL C1;
		DREAL C2;
		DREAL epsilon;
		E_SVM_TYPE method;

		INT degree;
		INT from_degree;
		SHORTREAL* wd_weights;
		INT num_vec;
		INT string_length;
		INT alphabet_size;

		DREAL normalization_const;

		DREAL bias;
		INT* w_offsets;
		INT w_dim;
		INT w_dim_single_char;
		SHORTREAL* w;
		SHORTREAL* old_w;
		DREAL* tmp_a_buf; /// nDim big
		DREAL* lab;

		SHORTREAL** cuts;
};
#endif
