/*****************************************************************************
* Project:	PROJ
* Purpose:	Matrix class
* Author:	Sveinung Himle <sveinung.himle at kartverket.no>
*
******************************************************************************
* Copyright (c) 2020, Sveinung Himle <sveinung.himle at kartverket.no>
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
******************************************************************************/

#include "gtest_include.h"

#include "..\src\matrixutils.h"

namespace
{
	TEST(matrixtest, addDoubleMatrixWithDoubleMatrix)
	{
		matrix<double> Expected(2, 2, { 2, 2, 2, 2 });

		matrix<double> A(2, 2, { 1, 1, 1, 1 });
		matrix<double> B(2, 2, { 1, 1, 1, 1 });

		matrix<double> Actual = A + B; 
		
		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, addDoubleMatrixWithDoubleType)
	{
		matrix<double> Expected(2, 2, { 4, 4, 4, 4 });

		matrix<double> A(2, 2, { 1, 1, 1, 1 });
		double B = 3;

		matrix<double> Actual = A + B;

		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, addDoubleTypeWithDoubleMatrix)
	{
		matrix<double> Expected(2, 2, { 4, 4, 4, 4 });

		matrix<double> A(2, 2, { 1, 1, 1, 1 });
		double B = 3;

		matrix<double> Actual = B + A;

		EXPECT_TRUE(Actual.isEqual(Expected));
	};
	
	TEST(matrixtest, substractDoubleMatrixWithDoubleMatrix)
	{
		matrix<double> Expected(2, 2, { 1, 1, 1, 1 });

		matrix<double> A(2, 2, { 2, 2, 2, 2 });
		matrix<double> B(2, 2, { 1, 1, 1, 1 });

		matrix<double> Actual = A - B;
		 
		EXPECT_TRUE(Actual.isEqual(Expected));
	};
 
	TEST(matrixtest, substractDoubleMatrixWithDoubleType)
	{
		matrix<double> Expected(2, 2, { 1, 1, 1, 1 });

		matrix<double> A(2, 2, { 2, 2, 2, 2 });
		double B = 1;

		matrix<double> Actual = A - B;

		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, substractDoubleTypeWithDoubleMatrix)
	{
		matrix<double> Expected(2, 2, { 3, 3, 3, 3 });

		matrix<double> A(2, 2, { 2, 2, 2, 2 });
		double B = 5;

		matrix<double> Actual = B - A;

		EXPECT_TRUE(Actual.isEqual(Expected));
	};
	
	TEST(matrixtest, multiplyDoubleMatrixWithDoubleMatrix)
	{
		matrix<double> Expected(2, 1, { 2, 2 });

		matrix<double> A(2, 2, { 1, 1, 1, 1 });
		matrix<double> B(2, 1, { 1, 1 });

		matrix<double> Actual = A * B;

		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, multiplyDoubleMatrixWithDoubleType)
	{
		matrix<double> Expected(3, 1, { 3, 3, 9 });

		matrix<double> A(3, 1, { 1, 1, 3 });
		double B = 3;

		matrix<double> Actual = A * B;

		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, multiplyDoubleTypeWithDoubleMatrix)
	{
		matrix<double> Expected(2, 2, { 2, 2, 2, 2 });

		matrix<double> A(2, 2, { 1, 1, 1, 1 });
		double B = 2;

		matrix<double> Actual = B * A;

		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, invertMatrix)
	{
		matrix<double> Expected(2, 2, { -1, 1, 2, -1 });

		matrix<double> A(2, 2, { 1, 1, 2, 1 });
	
		matrix<double> Actual = A.inverse();

		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, transposeDiagonalMatrix)
	{
		matrix<double> Expected(2, 2, { 1, 3, 2, 4 }); 

		matrix<double> A(2, 2, { 1, 2, 3, 4 });

		matrix<double> Actual = A.transpose();

		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, transposeRectangularMatrix)
	{
		matrix<double> Expected(2, 4, { 1,	3,	5,	7,	2,	4,	6,	8 });
		 
		matrix<double> A(4, 2, { 1, 2, 3, 4, 5, 6, 7, 8 });

		matrix<double> Actual = A.transpose();

		EXPECT_TRUE(Actual.isEqual(Expected));
	};


	TEST(matrixtest, transposeVector)
	{
		matrix<double> Expected(1, 8, { 1, 2, 3, 4, 5, 6, 7, 8 });

		matrix<double> A(8, 1, { 1, 2, 3, 4, 5, 6, 7, 8 });

		matrix<double> Actual = A.transpose();

		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, sumMatrix)
	{
		matrix<double> A(2, 2, { 1, 2, 3, 4 });		 

		EXPECT_EQ(A.sum(), 10);
	};

	TEST(matrixtest, onesMatrix)
	{
		matrix<double> Expected(2, 2, { 1, 1, 1, 1 });

		matrix<double> Actual = matrix<double>::ones(2, 2);
		
		EXPECT_TRUE(Actual.isEqual(Expected));
	};

	TEST(matrixtest, zerosMatrix)
	{
		matrix<double> Expected(2, 2, { 0, 0, 0, 0 });

		matrix<double> Actual = matrix<double>::zeros(2, 2);

		EXPECT_TRUE(Actual.isEqual(Expected));
	};
}