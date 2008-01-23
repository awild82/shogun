/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 1999-2008 Soeren Sonnenburg
 * Written (W) 1999-2008 Gunnar Raetsch
 * Written (W) 2006-2007 Mikio L. Braun
 * Copyright (C) 1999-2008 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#include "lib/config.h"
#include "lib/common.h"

#if defined(HAVE_LAPACK) && defined(DARWIN)
#include "lib/lapack.h"
#include "lib/io.h"

int clapack_dpotrf(const enum CBLAS_ORDER Order, const enum CBLAS_UPLO Uplo,
			                   const int N, double *A, const int LDA)
{
	ASSERT(Order==CblasColMajor);
        //call dgemm ( 'T', 'T', alpha, B, ldb, A, lda, beta, C, ldc )
	char uplo = 'U';
	int info=0;
	int n=N;
	int lda=LDA;

	if (Uplo==CblasLower)
		uplo='L';
	dpotrf_(&uplo, &n, A, &lda, &info);
	return info;
}

#endif

/*
 * Wrapper files for LAPACK
 *
 * 
 * automatically generated by fortranwrapper
 * hacked together by Mikio L. Braun on December 29, 2006
 */

#ifdef HAVE_LAPACK
#include "lib/lapack.h"

void dsymv(char UPLO, int N, double ALPHA, double* A, int LDA, double* X, int INCX, double BETA, double* Y, int INCY)
{
  dsymv_(&UPLO, &N, &ALPHA, A, &LDA, X, &INCX, &BETA, Y, &INCY);
}

void dgemv(char TRANS, int M, int N, double ALPHA, double* A, int LDA, double* X, int INCX, double BETA, double* Y, int INCY)
{
  dgemv_(&TRANS, &M, &N, &ALPHA, A, &LDA, X, &INCX, &BETA, Y, &INCY);
}

int dposv(char UPLO, int N, int NRHS, double* A, int LDA, double* B, int LDB)
{
  int INFO;
  dposv_(&UPLO, &N, &NRHS, A, &LDA, B, &LDB, &INFO);
  return INFO;
}

#endif
