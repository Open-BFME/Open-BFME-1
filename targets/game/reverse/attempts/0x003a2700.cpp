// ?finalize@Rva002BC260Goal@@QAEXXZ
// partial score=0.17 date=2026-09-17
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// The matched goal setup at 0x002BC260 calls this address-derived goal
// finalizer through ILT 0x00049AE9.  The retail body walks 0xB8-byte records,
// evaluates the four-point cubic between each consecutive window, stores ten
// samples at +0x2C, and accumulates the segment length at +0x38.

typedef float Real;

#include <math.h>
#include <vector>

extern const Real BfmeZeroRange;
extern const Real g_bfmeK1266A;
extern const Real g_bfmeK1266B;
extern const Real g_bfmeK1266C;
extern const Real g_bfmeK1266D;
extern const Real g_bfmeScaleBK;

struct Rva002BC260Coord3D
{
	Real x;
	Real y;
	Real z;

	Rva002BC260Coord3D(void)
	{
	}

	Rva002BC260Coord3D(const Rva002BC260Coord3D &value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
	}

	Rva002BC260Coord3D(Real ax, Real ay, Real az)
	{
		x = ax;
		y = ay;
		z = az;
	}

	Rva002BC260Coord3D &operator=(const Rva002BC260Coord3D &value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
		return *this;
	}

	void add(const Rva002BC260Coord3D *value)
	{
		x += value->x;
		y += value->y;
		z += value->z;
	}

	void sub(const Rva002BC260Coord3D *value)
	{
		x -= value->x;
		y -= value->y;
		z -= value->z;
	}

	void scale(Real value)
	{
		x *= value;
		y *= value;
		z *= value;
	}

	void set(const Rva002BC260Coord3D *value)
	{
		x = value->x;
		y = value->y;
		z = value->z;
	}

	Rva002BC260Coord3D &operator+=(const Rva002BC260Coord3D &value)
	{
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}

	Rva002BC260Coord3D &operator-=(const Rva002BC260Coord3D &value)
	{
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}

	Rva002BC260Coord3D &operator*=(Real value)
	{
		x = x * value;
		y = y * value;
		z = z * value;
		return *this;
	}
};

static __forceinline Rva002BC260Coord3D operator*(
	const Rva002BC260Coord3D &value, Real scale)
{
	return Rva002BC260Coord3D(value.x * scale, value.y * scale,
		value.z * scale);
}

static __forceinline Rva002BC260Coord3D operator*(
	Real scale, const Rva002BC260Coord3D &value)
{
	return Rva002BC260Coord3D(value.x * scale, value.y * scale,
		value.z * scale);
}

static __forceinline Rva002BC260Coord3D operator+(
	const Rva002BC260Coord3D &left, const Rva002BC260Coord3D &right)
{
	return Rva002BC260Coord3D(left.x + right.x, left.y + right.y,
		left.z + right.z);
}

static __forceinline Rva002BC260Coord3D operator-(
	const Rva002BC260Coord3D &left, const Rva002BC260Coord3D &right)
{
	return Rva002BC260Coord3D(left.x - right.x, left.y - right.y,
		left.z - right.z);
}

struct Rva002BC260GoalRecord
{
	Real length;
	Real sampleLength;
	unsigned char gap008[0x24];
	Rva002BC260Coord3D samples[10];
	Rva002BC260Coord3D controlPoint;
	unsigned char gap0b0[8];
};

class Rva002BC260Goal
{
public:
	virtual void unused000();
	virtual void unused004();
	virtual void configure(int, int, int, int, int, int);
	void finalize();

private:
	unsigned char gap00c[0x28];
	_STL::vector<Rva002BC260GoalRecord> records;
	Real totalLength;
	unsigned char gap03c[0x18];
	Rva002BC260Coord3D finalPoint;
};

static __forceinline void rva002BC260EvaluatePoint(
	const Rva002BC260Coord3D *p0,
	const Rva002BC260Coord3D *p1,
	const Rva002BC260Coord3D *p2,
	const Rva002BC260Coord3D *p3,
	Real t, Rva002BC260Coord3D *result)
{
	Rva002BC260Coord3D p0Value = *p0;
	Rva002BC260Coord3D p1Value = *p1;
	Rva002BC260Coord3D p2Value = *p2;
	Rva002BC260Coord3D p3Value = *p3;
	Real tSquared = t * t;
	Real tCubed = tSquared * t;
	Rva002BC260Coord3D d = 2.0f * p1Value;
	Rva002BC260Coord3D c = (p2Value - p0Value) * t;
	Rva002BC260Coord3D b = 2.0f * p0Value - g_bfmeK1266C * p1Value
		+ g_bfmeK1266B * p2Value - p3Value;
	Rva002BC260Coord3D a = g_bfmeK1266A * p1Value - p0Value
		- g_bfmeK1266A * p2Value + p3Value;
	Rva002BC260Coord3D value = a * tCubed + b * tSquared + c * t + d;
	value *= g_bfmeK1266D;
	*result = value;
}

// ?finalize@Rva002BC260Goal@@QAEXXZ
void Rva002BC260Goal::finalize()
{
	int segmentCount = records.size() - 3;
	if (segmentCount > 0)
	{
		unsigned int offset = 0;
		int segment = segmentCount;
		do
		{
			*(Real *)((char *)records.begin() + offset) = 0;

			Rva002BC260Coord3D previous;
			rva002BC260EvaluatePoint(
				(Rva002BC260Coord3D *)((char *)records.begin() + offset + 0xa4),
				(Rva002BC260Coord3D *)((char *)records.begin() + offset + 0x15c),
				(Rva002BC260Coord3D *)((char *)records.begin() + offset + 0x214),
				(Rva002BC260Coord3D *)((char *)records.begin() + offset + 0x2cc),
				BfmeZeroRange, &previous);

			int sample = 0;
			unsigned int sampleOffset = 0;
			do
			{
				int sampleNumber = sample + 1;
				Real t = sampleNumber * g_bfmeScaleBK;
				Rva002BC260Coord3D current;
				rva002BC260EvaluatePoint(
					(Rva002BC260Coord3D *)((char *)records.begin() + offset + 0xa4),
					(Rva002BC260Coord3D *)((char *)records.begin() + offset + 0x15c),
					(Rva002BC260Coord3D *)((char *)records.begin() + offset + 0x214),
					(Rva002BC260Coord3D *)((char *)records.begin() + offset + 0x2cc),
					t, &current);

				Real dx = current.x - previous.x;
				Real dy = current.y - previous.y;
				Real dz = current.z - previous.z;
				Real distance = sqrt(dx * dx + dy * dy + dz * dz);
				*(Real *)((char *)records.begin() + offset) += distance;
				*(Real *)((char *)records.begin() + offset + 4) = distance;
				*(Rva002BC260Coord3D *)((char *)records.begin() + offset + 0x2c + sampleOffset) = current;
				previous = current;
				sample = sampleNumber;
				sampleOffset += 0x0c;
			}
			while (sampleOffset < 0x78);

			totalLength += *(Real *)((char *)records.begin() + offset);
			offset += sizeof(Rva002BC260GoalRecord);
		}
		while (--segment > 0);
	}

	int pointCount = records.size();
	Rva002BC260GoalRecord *last = records.begin() + pointCount - 4;
	finalPoint = (last + 2)->controlPoint;
}
