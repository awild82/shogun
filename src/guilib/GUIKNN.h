/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#ifndef _GUIKNN_H__
#define _GUIKNN_H__ 

#include "lib/config.h"

#ifndef HAVE_SWIG

#include "base/SGObject.h"
#include "classifier/KNN.h"
#include "features/Labels.h"

class CGUI;

class CGUIKNN : public CSGObject
{

public:
	CGUIKNN(CGUI* g);
	~CGUIKNN();

	bool new_knn(CHAR* param);
	bool train(CHAR* param);
	bool test(CHAR* param);
	bool load(CHAR* param);
	bool save(CHAR* param);

 protected:
	CGUI* gui;
	CKNN* knn;
	int k;
};
#endif //HAVE_SWIG
#endif
