// cl: /DNDEBUG /MD /EHsc

typedef float Real;

void *operator new[](unsigned int bytes);
void operator delete[](void *pointer);

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
};

struct Region3D
{
	__forceinline Region3D() {}

	__forceinline Region3D(const Region3D &other)
	{
		lo.x = other.lo.x;
		lo.y = other.lo.y;
		lo.z = other.lo.z;
		hi.x = other.hi.x;
		hi.y = other.hi.y;
		hi.z = other.hi.z;
	}

	__forceinline ~Region3D() {}

	Real width() const { return hi.x - lo.x; }
	Real height() const { return hi.y - lo.y; }

	Coord3D lo;
	Coord3D hi;
};

struct Gen_t_008fb350_p12pod
{
	int value[3];
};

class ShroudManagerImpl008FBA40Node
{
public:
	~ShroudManagerImpl008FBA40Node();
};

class ShroudManagerImpl008FBA40Element
{
public:
	ShroudManagerImpl008FBA40Element();
	~ShroudManagerImpl008FBA40Element();

private:
	char state[0x68];
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class deque
{
public:
	~deque();

private:
	char state[0x28];
};
}

class ShroudManagerImpl008FBA40
{
public:
	~ShroudManagerImpl008FBA40();
	void reset();
	void setRegion(const Region3D *region, Real cellSize);
	void configure(Region3D region, Real cellSize);

private:
	Region3D region;
	Real unknown18;
	Real defaultCellSize;
	int width;
	int height;
	void *unknown28;
	ShroudManagerImpl008FBA40Element *elements;
	ShroudManagerImpl008FBA40Node *nodes;
	char unknown34[8];
	_STL::deque<Gen_t_008fb350_p12pod, _STL::allocator<Gen_t_008fb350_p12pod> > records;
};

ShroudManagerImpl008FBA40::~ShroudManagerImpl008FBA40()
{
	while (nodes)
		delete nodes;

	delete[] elements;
}

void ShroudManagerImpl008FBA40::reset()
{
	Region3D emptyRegion;
	emptyRegion.lo.zero();
	emptyRegion.hi.zero();
	setRegion(&emptyRegion, 0.0f);

	delete[] elements;
	elements = new ShroudManagerImpl008FBA40Element[1];
}

void ShroudManagerImpl008FBA40::setRegion(const Region3D *newRegion, Real cellSize)
{
	if (cellSize <= 0.0f)
		cellSize = defaultCellSize;

	if (!(newRegion->width() < 0.0f)
		&& !(newRegion->height() < 0.0f))
	{
		configure(*newRegion, cellSize);
	}
}
