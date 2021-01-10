#pragma once

#include "Includes.h"

class Matrix
{
public:
	Matrix(const size_t _rowNumber, const size_t _columnNumber);
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix) noexcept;

	Matrix& operator=(Matrix&& matrix) noexcept;

	~Matrix();

	struct Row
	{
	public:
		float& operator[](size_t columnId);

		Row(Matrix& _matrix, const size_t rowId);
		~Row() {};

	private:
		friend class Matrix;

		Row() = delete;

		size_t id;
		Matrix& matrix;
	};

	Matrix& operator+=(const Matrix& rightMatrix);
	friend Matrix operator+(Matrix leftMatrix, const Matrix& rightMatrix);

	Matrix& operator-=(const Matrix& rightMatrix);
	friend Matrix operator-(Matrix leftMatrix, const Matrix& rightMatrix);

	Matrix& operator*=(const Matrix& rightMatrix);
	friend Matrix operator*(Matrix leftMatrix, const Matrix& rightMatrix);
	Matrix& operator*=(const float rightValue);
	friend Matrix operator*(Matrix leftMatrix, const float rightValue);
	friend Matrix operator*(const float leftValue, Matrix rightMatrix);

	Matrix& operator/=(const float rightValue);
	friend Matrix operator/(Matrix leftMatrix, const float rightValue);

	Row operator[](size_t rowId);
	float& Get(size_t rowId, size_t columnId);

	const size_t GetRowNumber() const noexcept;
	const size_t GetColumnNumber() const noexcept;

	void Fill(const float number) noexcept;
	void FillRow(const float number, const size_t rowId) noexcept;
	void FillColumn(const float number, const size_t columnId) noexcept;

	const float Determinant() const;
	const float AlgebraicAdjunct(const size_t rowId, const size_t columnId) const;

	Matrix&& Multiply(const Matrix& matrix) const;
	Matrix&& Transpose() const;
	Matrix&& Inverse() const;

	Matrix&& Submatrix(const size_t upperRow, const size_t lowerRow, const size_t leftColumn, const size_t rightColumn) const;

	static Matrix&& Multiply(const Matrix& matrix0, const Matrix& matrix1);

private:
	Matrix() = delete;
	Matrix& operator=(const Matrix&) = delete;

	void RemoveData();
	void ResetData(const size_t _rowNumber, const size_t _columnNumber);

	float** data;

	size_t rowNumber;
	size_t columnNumber;
};
