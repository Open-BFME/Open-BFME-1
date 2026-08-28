// ?d_008fb5f0@@YAXXZ
// partial score=0.82 date=2026-08-28
// cl: /DNDEBUG /MD /EHsc /QIfist
// stlport

#include <deque>

typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

void *operator new[](unsigned int bytes);
void operator delete[](void *pointer);

__forceinline Real shroudFloor(Real value)
{
	return (Real)floor((double)value);
}

__forceinline Real shroudCeil(Real value)
{
	return (Real)ceil((double)value);
}

__forceinline int shroudFloatToLong(Real value)
{
	volatile Real materialized = value;
	return (int)materialized;
}

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
	void prepareForReconfigure();
	void detachCellLinks();
	void finishReconfigure();

private:
	int unknown00[4];
	ShroudManagerImpl008FBA40Node *next;
	friend class ShroudManagerImpl008FBA40;
};

class ShroudManagerImpl008FBA40;

class PartitionData
{
public:
	void unlink();

private:
	void updateCellsTouched();
	friend class ShroudManagerImpl008FBA40;
};

#pragma pack(push, 2)
struct ShroudPlayerState008FBA40
{
	int state;
	short count;
};
#pragma pack(pop)

class ShroudManagerImpl008FBA40Element
{
public:
	ShroudManagerImpl008FBA40Element();
	~ShroudManagerImpl008FBA40Element();
	void updatePlayerCells008FC3B0(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);
	void updatePlayerCells008FC450(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);

private:
	__forceinline void copyPlayerStatesFrom(
		const ShroudManagerImpl008FBA40Element &other)
	{
		for (int i = 0; i < 16; ++i)
			playerStates[i] = other.playerStates[i];
	}

	int unknown00;
	ShroudPlayerState008FBA40 playerStates[16];
	int unknown64;
	friend class ShroudManagerImpl008FBA40;
};

class ShroudManagerImpl008FBA40
{
public:
	ShroudManagerImpl008FBA40();
	~ShroudManagerImpl008FBA40();
	void drainPending();
	void updatePlayerCells008FB010(int playerIndex);
	void updatePlayerCells008FB060(int playerIndex);
	void reset();
	void setRegion(const Region3D *region, Real cellSize);
	void configure(Region3D region, Real cellSize);

private:
	int mode;
	Region3D region;
	Real defaultCellSize;
	Real inverseCellSize;
	int width;
	int height;
	ShroudManagerImpl008FBA40Element *elements;
	ShroudManagerImpl008FBA40Node *nodes;
	PartitionData *pendingPartitionData;
	int unknown38;
	_STL::deque<Gen_t_008fb350_p12pod, _STL::allocator<Gen_t_008fb350_p12pod> > records;
	int unknown64;
	bool enabled;
	char padding69[3];
	void *refreshCallback;

	void processPending(bool drainAll);
	void refreshAfterConfigure();
};

ShroudManagerImpl008FBA40::ShroudManagerImpl008FBA40()
	: mode(2),
	  defaultCellSize(1.0f),
	  width(0),
	  height(0),
	  elements(0),
	  nodes(0),
	  pendingPartitionData(0),
	  unknown38(0),
	  records(),
	  unknown64(-1),
	  enabled(true),
	  refreshCallback(0)
{
	region.lo.zero();
	region.hi.zero();
	configure(region, 1.0f);
}

ShroudManagerImpl008FBA40::~ShroudManagerImpl008FBA40()
{
	while (nodes)
		delete nodes;

	delete[] elements;
}

void ShroudManagerImpl008FBA40::drainPending()
{
	++unknown38;
	while (pendingPartitionData)
	{
		PartitionData *partitionData = pendingPartitionData;
		partitionData->unlink();
		partitionData->updateCellsTouched();
	}

	processPending(true);
}

void ShroudManagerImpl008FBA40::updatePlayerCells008FB010(int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 16)
	{
		processPending(false);

		ShroudManagerImpl008FBA40Element *end =
			elements + width * height;
		for (ShroudManagerImpl008FBA40Element *element = elements;
			element != end; ++element)
		{
			element->updatePlayerCells008FC3B0(this, playerIndex);
		}
	}
}

void ShroudManagerImpl008FBA40::updatePlayerCells008FB060(int playerIndex)
{
	if (playerIndex >= 0 && playerIndex < 16)
	{
		processPending(false);

		ShroudManagerImpl008FBA40Element *end =
			elements + width * height;
		for (ShroudManagerImpl008FBA40Element *element = elements;
			element != end; ++element)
		{
			element->updatePlayerCells008FC450(this, playerIndex);
		}
	}
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

void ShroudManagerImpl008FBA40::configure(Region3D newRegion, Real cellSize)
{
	drainPending();

	for (ShroudManagerImpl008FBA40Node *node = nodes;
		node != 0; node = node->next)
	{
		node->prepareForReconfigure();
		node->detachCellLinks();
		node->finishReconfigure();
	}

	processPending(false);

	if (newRegion.width() < 1.0f)
		newRegion.hi.x = newRegion.lo.x + 1.0f;
	if (newRegion.height() < 1.0f)
		newRegion.hi.y = newRegion.lo.y + 1.0f;

	Real newInverseCellSize = 1.0f / cellSize;
	int newWidth = shroudFloatToLong(shroudCeil(
		newRegion.width() * newInverseCellSize));
	if (newWidth < 1)
		newWidth = 1;
	int newHeight = shroudFloatToLong(shroudCeil(
		newRegion.height() * newInverseCellSize));
	if (newHeight < 1)
		newHeight = 1;

	ShroudManagerImpl008FBA40Element *newElements =
		new ShroudManagerImpl008FBA40Element[newWidth * newHeight];
	ShroudManagerImpl008FBA40Element *newElement = newElements;
	for (unsigned int y = 0; y < (unsigned int)newHeight; ++y)
	{
		int oldY = shroudFloatToLong(shroudFloor(
			((Real)y * cellSize + newRegion.lo.y - region.lo.y)
				* inverseCellSize));
		if (oldY >= 0 && oldY < height)
		{
			for (unsigned int x = 0; x < (unsigned int)newWidth;
				++x, ++newElement)
			{
				int oldX = shroudFloatToLong(shroudFloor(
					((Real)x * cellSize + newRegion.lo.x - region.lo.x)
						* inverseCellSize));
				if (oldX >= 0 && oldX < width)
				{
					newElement->copyPlayerStatesFrom(
						elements[oldY * width + oldX]);
				}
			}
		}
		else
		{
			newElement += newWidth;
		}
	}

	delete[] elements;
	elements = newElements;
	region = newRegion;
	inverseCellSize = newInverseCellSize;
	width = newWidth;
	height = newHeight;
	defaultCellSize = cellSize;

	if (nodes)
	{
		drainPending();
		refreshAfterConfigure();
	}
	else
	{
		unknown38 = 0;
	}
}
