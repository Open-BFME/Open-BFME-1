// cl: /O2 /Ob1 /EHsc /GR- /MD /DWIN32 /DNDEBUG
// stlport

struct TreeSwayVector
{
	float x;
	float y;
	float z;

	TreeSwayVector() {}
	TreeSwayVector(const TreeSwayVector &other) : x(other.x), y(other.y), z(other.z) {}
	TreeSwayVector(float x_value, float y_value, float z_value) :
		x(x_value), y(y_value), z(z_value) {}
};

static inline TreeSwayVector operator-(const TreeSwayVector &a, const TreeSwayVector &b)
{
	return TreeSwayVector(a.x - b.x, a.y - b.y, a.z - b.z);
}

static inline TreeSwayVector operator*(const TreeSwayVector &a, float factor)
{
	return TreeSwayVector(a.x * factor, a.y * factor, a.z * factor);
}

static inline TreeSwayVector operator+(const TreeSwayVector &a, const TreeSwayVector &b)
{
	return TreeSwayVector(a.x + b.x, a.y + b.y, a.z + b.z);
}

TreeSwayVector __stdcall interpolateTreeSwayStep(TreeSwayVector a, TreeSwayVector b)
{
	return a + (b - a) * 0.0625f;
}
