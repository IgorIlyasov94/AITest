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
	: rowNumber(matrix.rowNumber), columnNumber(matrix.columnNumber)
{
	data = new float* [rowNumber];

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		data[rowId] = new float[columnNumber];
	}

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			data[rowId][columnId] = matrix.data[rowId][columnId];
		}
	}
}

Matrix::Matrix(Matrix&& matrix) noexcept
	: rowNumber(0), columnNumber(0), data(nullptr)
{
	std::swap(rowNumber, matrix.rowNumber);
	std::swap(columnNumber, matrix.columnNumber);
	std::swap(data, matrix.data);
}

Matrix& Matrix::operator=(Matrix&& matrix) noexcept
{
	if (this == &matrix)
		return *this;

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

Matrix operator+(const Matrix& leftMatrix, const Matrix& rightMatrix)
{
	if (leftMatrix.rowNumber != rightMatrix.rowNumber || leftMatrix.columnNumber != rightMatrix.columnNumber)
		throw std::exception("Matrices must have the same dimension!");

	Matrix resultMatrix(leftMatrix.rowNumber, leftMatrix.columnNumber);

	for (size_t rowId = 0; rowId < resultMatrix.rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < resultMatrix.columnNumber; columnId++)
		{
			resultMatrix.data[rowId][columnId] = leftMatrix.data[rowId][columnId] + rightMatrix.data[rowId][columnId];
		}
	}

	return resultMatrix;
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

Matrix operator-(const Matrix& leftMatrix, const Matrix& rightMatrix)
{
	if (leftMatrix.rowNumber != rightMatrix.rowNumber || leftMatrix.columnNumber != rightMatrix.columnNumber)
		throw std::exception("Matrices must have the same dimension!");

	Matrix resultMatrix(leftMatrix.rowNumber, leftMatrix.columnNumber);

	for (size_t rowId = 0; rowId < resultMatrix.rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < resultMatrix.columnNumber; columnId++)
		{
			resultMatrix.data[rowId][columnId] = leftMatrix.data[rowId][columnId] - rightMatrix.data[rowId][columnId];
		}
	}

	return resultMatrix;
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

Matrix operator*(const Matrix& leftMatrix, const Matrix& rightMatrix)
{
	return Matrix::Multiply(leftMatrix, rightMatrix);
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

Matrix operator*(const Matrix& leftMatrix, const float rightValue)
{
	Matrix resultMatrix(leftMatrix.rowNumber, leftMatrix.columnNumber);

	for (size_t rowId = 0; rowId < resultMatrix.rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < resultMatrix.columnNumber; columnId++)
		{
			resultMatrix.data[rowId][columnId] = leftMatrix.data[rowId][columnId] * rightValue;
		}
	}

	return resultMatrix;
}

Matrix operator*(const float leftValue, const Matrix& rightMatrix)
{
	Matrix resultMatrix(rightMatrix.rowNumber, rightMatrix.columnNumber);

	for (size_t rowId = 0; rowId < resultMatrix.rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < resultMatrix.columnNumber; columnId++)
		{
			resultMatrix.data[rowId][columnId] = rightMatrix.data[rowId][columnId] * leftValue;
		}
	}

	return resultMatrix;
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

Matrix operator/(const Matrix& leftMatrix, const float rightValue)
{
	Matrix resultMatrix(leftMatrix.rowNumber, leftMatrix.columnNumber);

	for (size_t rowId = 0; rowId < resultMatrix.rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < resultMatrix.columnNumber; columnId++)
		{
			resultMatrix.data[rowId][columnId] = leftMatrix.data[rowId][columnId] / rightValue;
		}
	}

	return resultMatrix;
}

bool operator==(const Matrix& leftMatrix, const Matrix& rightMatrix)
{
	if (leftMatrix.rowNumber != rightMatrix.rowNumber || leftMatrix.columnNumber != rightMatrix.columnNumber)
		return false;

	for (size_t rowId = 0; rowId < leftMatrix.rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < leftMatrix.columnNumber; columnId++)
		{
			if (leftMatrix.data[rowId][columnId] != rightMatrix.data[rowId][columnId])
				return false;
		}
	}

	return true;
}

Matrix::Row Matrix::operator[](size_t rowId)
{
	return Row(*this, rowId);
}

float& Matrix::Cell(size_t rowId, size_t columnId)
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
		float products = 1.0f;

		for (size_t elementId = 0; elementId < columnNumber; elementId++)
		{
			products *= data[(elementId + rowOffset) % rowNumber][elementId];
		}

		additivePart += products;
	}

	float subtractivePart = 0.0f;

	for (size_t rowOffset = 0; rowOffset < rowNumber; rowOffset++)
	{
		float products = 1.0f;

		for (size_t elementId = 0; elementId < columnNumber; elementId++)
		{
			products *= data[(elementId + rowOffset) % rowNumber][columnNumber - elementId - 1];
		}

		subtractivePart += products;
	}

	return additivePart - subtractivePart;
}

const float Matrix::AlgebraicAdjunct(const size_t rowId, const size_t columnId) const
{
	if (rowNumber != columnNumber)
		throw std::exception("Matrix must be square to find the determinant!");

	if (rowNumber == 1)
		return 0.0f;

	float resultSign = 1.0f - 2.0f * static_cast<float>((rowId + columnId) % 2);

	if (rowNumber == 2)
		return data[rowNumber - rowId - 1][columnNumber - columnId - 1] * resultSign;

	if (rowNumber == 3)
	{
		size_t row0 = (rowId == 0) ? 1 : 0;
		size_t row1 = (rowId == 2) ? 1 : 2;
		size_t column0 = (columnId == 0) ? 1 : 0;
		size_t column1 = (columnId == 2) ? 1 : 2;

		float additivePart = data[row0][column0] * data[row1][column1];
		float subtractivePart = data[row0][column1] * data[row1][column0];

		return (additivePart - subtractivePart) * resultSign;
	}

	float additivePart = 0.0f;

	for (size_t rowOffset = 0; rowOffset < rowNumber; rowOffset++)
	{
		float products = 1.0f;

		for (size_t elementId = 0; elementId < columnNumber; elementId++)
		{
			size_t rowElementId = (elementId + rowOffset) % rowNumber;

			if (rowElementId != rowId && elementId != columnId)
				products *= data[rowElementId][elementId];
		}

		additivePart += products;
	}

	float subtractivePart = 0.0f;

	for (size_t rowOffset = 0; rowOffset < rowNumber; rowOffset++)
	{
		float products = 1.0f;

		for (size_t elementId = 0; elementId < columnNumber; elementId++)
		{
			size_t rowElementId = (elementId + rowOffset) % rowNumber;
			size_t columnElementId = columnNumber - elementId - 1;

			if (rowElementId != rowId && columnElementId != columnId)
				products *= data[rowElementId][columnElementId];
		}

		subtractivePart += products;
	}

	return (additivePart - subtractivePart) * resultSign;
}

Matrix Matrix::Multiply(const Matrix& matrix) const
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

	return resultMatrix;
}

Matrix Matrix::Transpose() const
{
	Matrix resultMatrix(columnNumber, rowNumber);

	for (size_t rowId = 0; rowId < rowNumber; rowId++)
	{
		for (size_t columnId = 0; columnId < columnNumber; columnId++)
		{
			resultMatrix.data[columnId][rowId] = data[rowId][columnId];
		}
	}

	return resultMatrix;
}

Matrix Matrix::Inverse() const
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

	resultMatrix = resultMatrix.Transpose() / determinant;

	return resultMatrix;
}

Matrix Matrix::Submatrix(const size_t upperRow, const size_t lowerRow, const size_t leftColumn, const size_t rightColumn) const
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

	return resultMatrix;
}

Matrix Matrix::Multiply(const Matrix& matrix0, const Matrix& matrix1)
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

	return resultMatrix;
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
