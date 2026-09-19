// ?find@Rva003A2270Owner@@QAE_NABUCoord3D@@M@Z
// cl: /DNDEBUG /MD /EHsc

#include <math.h>
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct Rva003A2270Coord2D
{
	Rva003A2270Coord2D(Real initialX, Real initialY)
		: x(initialX), y(initialY), unused(0.0f) {}

	Real x;
	Real y;
	Real unused;

	Real length() const
	{
		return (Real)sqrt(x * x + y * y);
	}
};

struct Rva003A2270Element
{
	char pad00[0xa4];
	Coord3D point;
	char padb0[8];
};

struct Rva003A2270Range
{
	Rva003A2270Element *first;
	Rva003A2270Element *last;

	Rva003A2270Element *begin()
	{
		return first;
	}

	Rva003A2270Element *end()
	{
		return last;
	}

	unsigned int size()
	{
		return (unsigned int)(last - first);
	}
};

class Rva003A2270Owner
{
public:
	Bool find(const Coord3D &position, Real distance);

private:
	char pad00[0x2c];
	Rva003A2270Range entries;
};

Bool Rva003A2270Owner::find(const Coord3D &position, Real distance)
{
	for (Rva003A2270Element *it = entries.begin() + 2;
		it != entries.end(); ++it)
	{
		if (it == entries.begin() + entries.size() - 2)
			return false;
		Rva003A2270Coord2D delta(it->point.x, it->point.y);
		delta.x -= position.x;
		delta.y -= position.y;
		if (delta.length() < distance)
		{
			it->point = position;
			return true;
		}
	}
	return false;
}
