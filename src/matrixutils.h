
/******************************************************************************
* Project:	PROJ
* Purpose:	Matrix class
* Author:	Sveinung Himle <sveinung.himle at kartverket.no>
*
*******************************************************************************
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
*
******************************************************************************/

#include <vector>
#include <iostream>

template <class M> class matrix
{
	int m_iRows = 0;
	int m_iCols = 0;  
	std::vector<M> m_data { };	
	 
	matrix()
	{}

	void inv()
	{
		assert(m_iRows == m_iCols && "No of rows is different from no of columns");

		if (m_iRows != m_iCols)
			return;

		if (m_iRows == 0 || m_iCols == 0)
			return;

		if (m_data.at(0) == (M)0)
			return;

		for (int i = 1; i < m_iRows; i++)
			m_data.at(i) = m_data.at(i) / m_data.at(0);

		for (int i = 1; i < m_iRows; i++)
		{
			for (int j = i; j < m_iCols; j++)
			{
				M sumvalue = 0;

				for (int k = 0; k < i; k++)
					sumvalue = sumvalue + m_data.at(j*m_iRows + k) * m_data.at(k*m_iRows + i);
		
				m_data.at(j*m_iRows + i) = m_data.at(j*m_iRows + i) - sumvalue;
			}
			if (i == m_iRows - 1)
				continue;

			for (int j = i + 1; j < m_iCols; j++)
			{
				M sumvalue = 0;

				for (int k = 0; k < i; k++)
					sumvalue = sumvalue + m_data.at(i*m_iRows + k) * m_data.at(k*m_iRows + j);

				if (m_data.at(i*m_iRows + i) == (M)0)
					continue;

				m_data.at(i*m_iRows + j) = (m_data.at(i*m_iRows + j) - sumvalue) / m_data.at(i*m_iRows + i);
			}
		}
		for (int i = 0; i < m_iRows; i++)
		{
			for (int j = i; j < m_iRows; j++)
			{
				M x = 1;
				if (i != j)
				{
					x = (M)0;
					for (int k = i; k < j; k++)
						x = x - m_data.at(j*m_iRows + k) * m_data.at(k*m_iRows + i);
				}

				if (m_data.at(j*m_iRows + j) == (M)0)
					continue;

				m_data.at(j*m_iRows + i) = x / m_data.at(j*m_iRows + j);
			}
		}
		for (int i = 0; i < m_iRows; i++)
		{
			for (int j = i; j < m_iRows; j++)
			{
				if (i == j)
					continue;

				M sumvalue = 0;

				for (int k = i; k < j; k++)
					sumvalue = sumvalue + m_data.at(k*m_iRows + j) * ((i == k) ? (M)1.0 : m_data.at(i*m_iRows + k));
				
				m_data.at(i*m_iRows + j) = (M)(-sumvalue);
			}
		}
		for (int i = 0; i < m_iRows; i++)
		{
			for (int j = 0; j < m_iRows; j++)
			{
				M sumvalue = 0;

				for (int k = ((i > j) ? i : j); k < m_iRows; k++)
					sumvalue = sumvalue + ((j == k) ? (M)1.0 : m_data.at(j*m_iRows + k)) * m_data.at(k*m_iRows + i);

				m_data.at(j*m_iRows + i) = sumvalue;
			}
		}
	}

	void trans()
	{
		if (m_iCols == 0 || m_iRows == 0)
			return;

		std::vector<M> v2;
		std::swap(m_data, v2);
		 
		for (int j = 0; j < m_iCols; j++)				
			for (int i = 0; i < m_iRows; i++)			
				 m_data.push_back(v2[i * m_iCols + j]);
		
		std::swap(m_iCols, m_iRows);
	}

public:
	matrix(int rows, int cols, std::vector<M> data) : m_data(data) 
	{
		m_iRows = rows;
		m_iCols = cols;
	}

	matrix(int rows, int cols)
	{
		m_iRows = rows;
		m_iCols = cols;

		m_data.resize(m_iRows * m_iCols);
	}

	~matrix()
	{
		m_iRows = 0;
		m_iCols = 0;
		
		// TODO: Testing clang_linux error
		// m_data.clear();
		
		//delete m_data;
	}

	const int &getRows() const { return m_iRows; }

	const int &getCols() const { return m_iCols; }
	
	bool isEqual(matrix& other)
	{
		if (m_iRows != other.getRows())
			return false;

		if (m_iCols != other.getCols())
			return false;

		for (int i = 0; i < m_iRows; i++)
		{
			for (int j = 0; j < m_iCols; j++)
			{
				M myValue = m_data.at(i*m_iCols + j);
				M targetValue;
				bool succeed;
				
				other.getvalue(i, j, targetValue, succeed);

				if (!succeed || myValue != targetValue)
					return false;				
			}
		}
		return true;
	}

	void copymatrix(matrix& source)
	{
		m_iRows = source.m_iRows;
		m_iCols = source.m_iCols;

		if (m_iRows == 0 || m_iCols == 0)
			return;

		if (m_iRows > 0 && m_iCols > 0)
			m_data.resize(m_iRows * m_iCols);
		else
			return;

		for (int i = 0; i < m_iRows; i++)
		{
			for (int j = 0; j < m_iCols; j++)
			{
				M value;
				bool success;
				source.getvalue(i, j, value, success);

				if (success)
					m_data.at(i * m_iCols + j) = value;
			}
		}
	}

	void getvalue(int row, int col, M& returnvalue, bool& success) const
	{
		if ((row >= m_iRows) || (col >= m_iCols) || (row < 0) || (col < 0))
		{
			success = false;
			return;
		}
		returnvalue = m_data.at(row * m_iCols + col);
		success = true;
	}

	bool setvalue(int row, int col, M newvalue)
	{
		if ((row >= m_iRows) || (col >= m_iCols) || (row < 0) || (col < 0))
			return false;

		m_data.at(row * m_iCols + col) = newvalue;
		return true;
	}

	static const matrix<M> ones(int row, int col)
	{
		matrix<M> copyM = matrix<M>(row, col);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				M value = 1;
				copyM.setvalue(i, j, value);
			}
		}
		return copyM;
	}

	static const matrix<M> zeros(int row, int col)
	{
		matrix<M> copyM = matrix<M>(row, col);

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				M value = 0;
				copyM.setvalue(i, j, value);
			}
		}
		return copyM;
	}

	matrix<M> inverse()
	{
		matrix<M> copyM = matrix<M>();

		copyM.copymatrix(*this);
		copyM.inv();

		return copyM;
	}

	matrix<M> transpose()
	{
		matrix<M> copyM = matrix<M>();

		copyM.copymatrix(*this);
		copyM.trans();

		return copyM;
	}

	M sum()
	{
		M sumvalue = (M)0;
		M value = (M)0;

		for (int i = 0; i < m_iRows; i++)
		{
			for (int j = 0; j < m_iCols; j++)
			{
				bool success;
				this->getvalue(i, j, value, success);
				if (success)
					sumvalue += value;
			}
		}
		return sumvalue;
	}

	M& operator()(int row, int col)
	{
		assert(col >= 0 && "Row index is negative");
		assert(row >= 0 && "Column index is negative");
		assert(!m_data.empty() && "Array is empty");
		 
		try
		{
			return m_data.at(row * m_iCols + col);
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Array index outside range: " << e.what() << std::endl;
			return m_data.front();
		}		
	}
	
	M& operator()(int index)
	{
		assert(index >= 0 && "Index is negative");
		assert(!m_data.empty() && "Array is empty");
		 
		try
		{
			return m_data.at(index);
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Array index outside range: " << e.what() << std::endl;
			return m_data.front();
		}
	}

	M& operator [](const int &index)
	{
		assert(index >= 0 && "Index is negative");
		assert(!m_data.empty() && "Array is empty");
		 
		try
		{
			return m_data.at(index);
		}		
		catch (const std::out_of_range& e)
		{
			std::cerr << "Array index outside range: " << e.what() << std::endl;
			return m_data.front();
		}
	}

	matrix<M> operator +(const matrix<M> &other) const
	{
		assert(m_iRows == other.m_iRows && "No of rows in LHS is different from no of rows RHS");
		assert(m_iCols == other.m_iCols && "No of columns in LHS is different from no of columns RHS");
		assert(m_iRows > 0 && "No of rows is less than zero");
		assert(m_iCols > 0 && "No of columns is less than zero");

		matrix<M> copyM = matrix<M>(m_iRows, m_iCols);

		for (int i = 0; i < m_iRows; i++)
			for (int j = 0; j < m_iCols; j++)
				copyM.m_data.at(i*m_iCols + j) = m_data.at(i*m_iCols + j) + other.m_data.at(i*m_iCols + j);

		return copyM;
	}

	matrix<M> operator +(const M &value) const
	{
		assert(m_iRows > 0 && "No of rows is less than zero");
		assert(m_iCols > 0 && "No of columns is less than zero");

		matrix<M> copyM = matrix<M>(m_iRows, m_iCols);

		for (int i = 0; i < m_iRows; i++)
			for (int j = 0; j < m_iCols; j++)
				copyM.m_data.at(i*m_iCols + j) = m_data.at(i*m_iCols + j) + value;

		return copyM;
	}

	matrix<M> operator -(const matrix<M> &other) const
	{
		assert(m_iRows == other.m_iRows && "No of rows in LHS is different from no of rows RHS");
		assert(m_iCols == other.m_iCols && "No of columns in LHS is different from no of columns RHS");
		assert(m_iRows > 0 && "No of rows is less than zero");
		assert(m_iCols > 0 && "No of columns is less than zero");

		matrix<M> copyM = matrix<M>(m_iRows, m_iCols);

		for (int i = 0; i < m_iRows; i++)
			for (int j = 0; j < m_iCols; j++)
				copyM.m_data.at(i*m_iCols + j) = m_data.at(i*m_iCols + j) - other.m_data.at(i*m_iCols + j);

		return copyM;
	}

	matrix<M> operator -(const M &value) const
	{
		assert(m_iRows > 0 && "No of rows is less than zero");
		assert(m_iCols > 0 && "No of columns is less than zero");

		matrix<M> copyM = matrix<M>(m_iRows, m_iCols);

		for (int i = 0; i < m_iRows; i++)
			for (int j = 0; j < m_iCols; j++)
				copyM.m_data.at(i*m_iCols + j) = m_data.at(i*m_iCols + j) - value;

		return copyM;
	}

	matrix<M> operator -() const
	{
		assert(m_iRows > 0 && "No of rows is less than zero");
		assert(m_iCols > 0 && "No of columns is less than zero");

		matrix<M> copyM = matrix<M>(m_iRows, m_iCols);

		for (int i = 0; i < m_iRows; i++)
			for (int j = 0; j < m_iCols; j++)
				copyM.m_data.at(i*m_iCols + j) = -m_data.at(i*m_iCols + j);

		return copyM;
	}

	matrix<M> operator *(const matrix<M> &other) const
	{
		assert(m_iCols == other.m_iRows && "No of columns in LHS is different from no of rows RHS");
		assert((m_iRows == other.m_iCols ||
			other.m_iCols == 1 ||
			m_iRows == 1) &&
			"No of rows in LHS is different from no of columns RHS");

		matrix<M> copyM = matrix<M>(m_iRows, other.m_iCols);

		for (int i = 0; i < m_iRows; i++)
			for (int j = 0; j < other.m_iCols; j++)
				for (int k = 0; k < m_iCols; k++)			 
					copyM.m_data.at(i * other.m_iCols + j) = copyM.m_data.at(i * other.m_iCols + j) +
						m_data.at(i * m_iCols + k) * other.m_data.at(k * other.m_iCols + j);				 
				
		return copyM;
	}

	matrix<M> operator *(const M &value) const
	{
		assert(m_iRows > 0 && "No of rows is less than zero");
		assert(m_iCols > 0 && "No of columns is less than zero");

		matrix<M> copyM = matrix<M>(m_iRows, m_iCols);

		for (int i = 0; i < m_iRows; i++)
			for (int j = 0; j < m_iCols; j++)
				copyM.m_data.at(i*m_iCols + j) = this->m_data.at(i*m_iCols + j) * value;

		return copyM;
	}
};

template <typename M, typename N>
matrix<M> operator +(const N &value, const matrix<M> &other)
{
	int m_iRows = other.getRows();
	int m_iCols = other.getCols();

	assert(m_iRows > 0 && "No of rows is less than zero");
	assert(m_iCols > 0 && "No of columns is less than zero");

	matrix<M> copyM = matrix<M>(m_iRows, m_iCols);

	for (int i = 0; i < m_iRows; i++)
	{
		for (int j = 0; j < m_iCols; j++)
		{
			M oldValue;
			bool succeed;

			other.getvalue(i, j, oldValue, succeed);

			if (!succeed)
				continue;

			copyM.setvalue(i, j, (M)value + oldValue);
		}
	}
	return copyM;
}

template <typename M, typename N>
matrix<M> operator -(const N &value, const matrix<M> &other)
{
	int m_iRows = other.getRows();
	int m_iCols = other.getCols();

	assert(m_iRows > 0 && "No of rows is less than zero");
	assert(m_iCols > 0 && "No of columns is less than zero");

	matrix<M> copyM = matrix<M>(m_iRows, m_iCols);

	for (int i = 0; i < m_iRows; i++)
	{
		for (int j = 0; j < m_iCols; j++)
		{
			M oldValue;
			bool succeed;

			other.getvalue(i, j, oldValue, succeed);

			if (!succeed)
				continue;

			copyM.setvalue(i, j, (M)value - oldValue);
		}
	}
	return copyM;
}

template <typename M, typename N>
matrix<M> operator *(const N &value, const matrix<M> &other)
{
	int m_iRows = other.getRows();
	int m_iCols = other.getCols();

	assert(m_iRows > 0 && "No of rows is less than zero");
	assert(m_iCols > 0 && "No of columns is less than zero");

	matrix<M> copyM = matrix<M>(m_iRows, m_iCols);

	for (int i = 0; i < m_iRows; i++)
	{
		for (int j = 0; j < m_iCols; j++)
		{
			M oldValue;
			bool succeed;
			
			other.getvalue(i, j, oldValue, succeed);			 

			if (!succeed)
				continue;

			copyM.setvalue(i, j, (M)value * oldValue);
		}
	}
	return copyM;
}
