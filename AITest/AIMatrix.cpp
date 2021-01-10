#include "AIMatrix.h"

Matrix::Matrix(const size_t _rowNumber, const size_t _columnNumber)
	: rowNumber(_rowNumber), columnNumber(_columnNumber), data(nullptr)
{
	if (rowNumber == 0 || columnNumber == 0)
		throw std::exception("Matrix must not have one of the dimensins or both equal to zero!");
	
	data = new float* [rowNumber];

	for(size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		data[rowId] = new float[columnNumber];
	}

	Fill(0);
}

Matrix::Matrix(const Matrix& matrix)
{
	ResetData(rowNumber, columnNumber);

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			data[rowId][columnId] = matrix.data[rowId][columnId];
		}
	}
}

Matrix::Matrix(Matrix&& matrix) noexcept
{
	RemoveData();

	std::swap(rowNumber, matrix.rowNumber);
	std::swap(columnNumber, matrix.columnNumber);
	std::swap(data, matrix.data);
}

Matrix& Matrix::operator=(Matrix&& matrix) noexcept
{
	RemoveData();

	std::swap(rowNumber, matrix.rowNumber);
	std::swap(columnNumber, matrix.columnNumber);
	std::swap(data, matrix.data);

	return *this;
}

Matrix::~Matrix()
{
	RemoveData();
}

Matrix& Matrix::operator+=(const Matrix& rightMatrix)
{
	if (rowNumber != rightMatrix.rowNumber || columnNumber != rightMatrix.columnNumber)
		throw std::exception("Matrices must have the same dimension!");

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			data[rowId][columnId] += rightMatrix.data[rowId][columnId];
		}
	}

	return *this;
}

Matrix operator+(Matrix leftMatrix, const Matrix& rightMatrix)
{
	leftMatrix += rightMatrix;

	return leftMatrix;
}

Matrix& Matrix::operator-=(const Matrix& rightMatrix)
{
	if (rowNumber != rightMatrix.rowNumber || columnNumber != rightMatrix.columnNumber)
		throw std::exception("Matrices must have the same dimension!");

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			data[rowId][columnId] -= rightMatrix.data[rowId][columnId];
		}
	}

	return *this;
}

Matrix operator-(Matrix leftMatrix, const Matrix& rightMatrix)
{
	leftMatrix -= rightMatrix;

	return leftMatrix;
}

Matrix& Matrix::operator*=(const Matrix& rightMatrix)
{
	Matrix tempMatrix = Multiply(rightMatrix);

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			data[rowId][columnId] = tempMatrix.data[rowId][columnId];
		}
	}

	return *this;
}

Matrix operator*(Matrix leftMatrix, const Matrix& rightMatrix)
{
	leftMatrix *= rightMatrix;

	return leftMatrix;
}

Matrix& Matrix::operator*=(const float rightValue)
{
	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			data[rowId][columnId] *= rightValue;
		}
	}

	return *this;
}

Matrix operator*(Matrix leftMatrix, const float rightValue)
{
	leftMatrix *= rightValue;

	return leftMatrix;
}

Matrix operator*(const float leftValue, Matrix rightMatrix)
{
	rightMatrix *= leftValue;

	return rightMatrix;
}

Matrix& Matrix::operator/=(const float rightValue)
{
	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			data[rowId][columnId] /= rightValue;
		}
	}

	return *this;
}

Matrix operator/(Matrix leftMatrix, const float rightValue)
{
	leftMatrix /= rightValue;

	return leftMatrix;
}

Matrix::Row Matrix::operator[](size_t rowId)
{
	return Row(*this, rowId);
}

float& Matrix::Get(size_t rowId, size_t columnId)
{
	if (rowId >= rowNumber || columnId >= columnNumber)
		throw std::exception("Array out of bounds!");

	return data[rowId][columnId];
}

const size_t Matrix::GetRowNumber() const noexcept
{
	return rowNumber;
}

const size_t Matrix::GetColumnNumber() const noexcept
{
	return columnNumber;
}

void Matrix::Fill(const float number) noexcept
{
	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			data[rowId][columnId] = number;
		}
	}
}

void Matrix::FillRow(const float number, const size_t rowId) noexcept
{
	for (size_t columnId = 0; columnId < columnNumber; columnId++)
	{
		data[rowId][columnId] = number;
	}
}

void Matrix::FillColumn(const float number, const size_t columnId) noexcept
{
	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		data[rowId][columnId] = number;
	}
}

const float Matrix::Determinant() const
{
	if (rowNumber != columnNumber)
		throw std::exception("Matrix must be square to find the determinant!");

	if (rowNumber == 1)
		return data[0][0];

	if (rowNumber == 2)
		return data[0][0] * data[1][1] - data[0][1] * data[1][0];

	float additivePart = 0.0f;

	for (size_t rowOffset = 0; rowOffset < rowNumber; rowOffset++)
	{
		for (size_t elementId = 0; elementId < columnNumber; elementId++)
		{
			additivePart += data[(elementId + rowOffset) % rowNumber][elementId];
		}
	}

	float subtractivePart = 0.0f;

	for (size_t rowOffset = 0; rowOffset < rowNumber; rowOffset++)
	{
		for (size_t elementId = 0; elementId < columnNumber; elementId++)
		{
			subtractivePart += data[(elementId + rowOffset) % rowNumber][columnNumber - elementId - 1];
		}
	}

	return additivePart - subtractivePart;
}

const float Matrix::AlgebraicAdjunct(const size_t rowId, const size_t columnId) const
{
	if (rowNumber != columnNumber)
		throw std::exception("Matrix must be square to find the determinant!");

	if ((rowNumber - 1) == 1)
		return data[0][0];

	if ((rowNumber - 1) == 2)
		return data[0][0] * data[1][1] - data[0][1] * data[1][0];

	float additivePart = 0.0f;

	for (size_t rowOffset = 0; rowOffset < rowNumber; rowOffset++)
	{
		for (size_t elementId = 0; elementId < columnNumber; elementId++)
		{
			size_t rowElementId = (elementId + rowOffset) % rowNumber;

			if (rowElementId != rowId && elementId != columnId)
				additivePart += data[rowElementId][elementId];
		}
	}

	float subtractivePart = 0.0f;

	for (size_t rowOffset = 0; rowOffset < rowNumber; rowOffset++)
	{
		for (size_t elementId = 0; elementId < columnNumber; elementId++)
		{
			size_t rowElementId = (elementId + rowOffset) % rowNumber;
			size_t columnElementId = columnNumber - elementId - 1;

			if (rowElementId != rowId && columnElementId != columnId)
				subtractivePart += data[rowElementId][columnElementId];
		}
	}

	return additivePart - subtractivePart;
}

Matrix&& Matrix::Multiply(const Matrix& matrix) const
{
	if (columnNumber != matrix.rowNumber)
		throw std::exception("Dimensions of matrices are not suitable for multiplication!");

	Matrix resultMatrix(rowNumber, matrix.columnNumber);

	for (size_t rowId = 0; rowId < resultMatrix.rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < resultMatrix.columnNumber; columnId++)
		{
			float dotSumm = 0.0f;

			for (size_t elementId = 0; elementId < columnNumber; elementId++)
			{
				dotSumm += data[rowId][elementId] * matrix.data[elementId][columnId];
			}

			resultMatrix.data[rowId][columnId] = dotSumm;
		}
	}

	return std::move(resultMatrix);
}

Matrix&& Matrix::Transpose() const
{
	Matrix resultMatrix(columnNumber, rowNumber);

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			resultMatrix.data[columnId][rowId] = data[rowId][columnId];
		}
	}

	return std::move(resultMatrix);
}

Matrix&& Matrix::Inverse() const
{
	float determinant = Determinant();

	if (determinant == 0.0)
		throw std::exception("Inverse matrix does not exist since determinant is zero!");

	Matrix resultMatrix(rowNumber, columnNumber);

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			resultMatrix.data[rowId][columnId] = AlgebraicAdjunct(rowId, columnId);
		}
	}

	resultMatrix /= determinant;

	return std::move(resultMatrix);
}

Matrix&& Matrix::Submatrix(const size_t upperRow, const size_t lowerRow, const size_t leftColumn, const size_t rightColumn) const
{
	if (lowerRow >= rowNumber || rightColumn >= columnNumber || upperRow > lowerRow || leftColumn > rightColumn)
		throw std::exception("Submatrix boundaries are incorrect!");

	Matrix resultMatrix(lowerRow - upperRow, rightColumn - leftColumn);

	for (size_t rowId = upperRow; rowId <= lowerRow; rowId++)
	{
		for (size_t columnId = leftColumn; columnId <= rightColumn; columnId++)
		{
			resultMatrix.data[rowId - upperRow][columnId - leftColumn] = data[rowId][columnId];
		}
	}

	return std::move(resultMatrix);
}

Matrix&& Matrix::Multiply(const Matrix& matrix0, const Matrix& matrix1)
{
	if (matrix0.columnNumber != matrix1.rowNumber)
		throw std::exception("Dimensions of matrices are not suitable for multiplication!");

	Matrix resultMatrix(matrix0.rowNumber, matrix1.columnNumber);

	for (size_t rowId = 0; rowId < resultMatrix.rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < resultMatrix.columnNumber; columnId++)
		{
			float dotSumm = 0.0f;

			for (size_t elementId = 0; elementId < matrix0.columnNumber; elementId++)
			{
				dotSumm += matrix0.data[rowId][elementId] * matrix1.data[elementId][columnId];
			}

			resultMatrix.data[rowId][columnId] = dotSumm;
		}
	}

	return std::move(resultMatrix);
}

void Matrix::RemoveData()
{
	if (data != nullptr)
	{
		for (size_t rowId = 0; rowId < rowNumber; rowId++)
		{
			if (data[rowId] != nullptr)
			{
				delete[] data[rowId];

				data[rowId] = nullptr;
			}
		}

		delete[] data;
	}

	data = nullptr;

	rowNumber = 0;
	columnNumber = 0;
}

void Matrix::ResetData(const size_t _rowNumber, const size_t _columnNumber)
{
	RemoveData();

	rowNumber = _rowNumber;
	columnNumber = _columnNumber;

	data = new float* [rowNumber];

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		data[rowId] = new float[columnNumber];
	}
}

Matrix::Row::Row(Matrix& _matrix, const size_t rowId)
	: matrix(_matrix), id(rowId)
{

}

float& Matrix::Row::operator[](size_t columnId)
{
	if (id >= matrix.rowNumber || columnId >= matrix.columnNumber)
		throw std::exception("Array out of bounds!");

	return matrix.data[id][columnId];
}
