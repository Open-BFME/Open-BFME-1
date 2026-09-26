// cl: /DNDEBUG /MD /EHsc

class Vector4
{
public:
	const float &operator[](int index) const { return (&X)[index]; }

private:
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	const Vector4 &operator[](int index) const { return m_row[index]; }

private:
	Vector4 m_row[3];
};

__forceinline bool operator==(const Matrix3D &a, const Matrix3D &b)
{
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 4; ++column) {
			if (a[row][column] != b[row][column]) {
				return false;
			}
		}
	}
	return true;
}

bool operator!=(const Matrix3D &a, const Matrix3D &b)
{
	return !(a == b);
}
