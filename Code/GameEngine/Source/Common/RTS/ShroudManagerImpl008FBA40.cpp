// cl: /DNDEBUG /MD /EHsc
// stlport

#include <deque>

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum CellShroudStatus
{
	CELLSHROUD_CLEAR,
	CELLSHROUD_FOGGED,
	CELLSHROUD_SHROUDED
};

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_PARTIAL_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern const Real g_bfmeK1253;
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

__forceinline Int shroudFloatToLong(Real value)
{
	long result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

__forceinline Real shroudFloor(Real value)
{
	return (Real)floor((double)value);
}

__forceinline Real shroudCeil(Real value)
{
	return (Real)ceil((double)value);
}

void *operator new[](unsigned int bytes);
void operator delete[](void *pointer);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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
	unsigned int timestamp;
	int x;
	int y;
	int radius;
	int playerMask;
};

class ShroudManagerImpl008FBA40;
class PartitionManager;
struct ShroudManagerImpl008FBA40ElementLayout;
__forceinline ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
	const ShroudManagerImpl008FBA40 *manager, Int x, Int y);

class BfmePartVRA;

class BfmeShroudVRA
{
public:
	char bfmeUpdateVRA(int x, int y, int radius);
	BfmePartVRA *m_bfme00;
	int m_bfme04;
};

bool processShroudRevealCircle008F9A70(Int cellX, Int cellY, Int cellRadius,
	ShroudManagerImpl008FBA40 *manager, Int playerMask);
bool processShroudRevealCircle008F9B10(Int cellX, Int cellY, Int cellRadius,
	ShroudManagerImpl008FBA40 *manager, Int playerMask);

class ShroudManagerImpl008FBA40Element;

struct ShroudManagerImpl008FBA40CellObject
{
	char padding00[0x24];
	int playerState[16];
};

class BfmeThingCDE
{
public:
	void d_008f7ec0();
	void d_008f7990();

	char unknown00[0x10];
	BfmeThingCDE *next;
};

class ShroudManagerImpl008FBA40Node
{
public:
	~ShroudManagerImpl008FBA40Node();

private:
	int unknown00;
	ShroudManagerImpl008FBA40CellObject *object;
	int unknown08;
	ShroudManagerImpl008FBA40Node *next;
	friend class ShroudManagerImpl008FBA40Element;
};

class ShroudManagerImpl008FBA40;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionData
{
public:
	void unlink();
	void makeDirty();

private:
	void updateCellsTouched();
	friend class ShroudManagerImpl008FBA40;
};

struct ShroudManagerImpl008FBA40PlayerState
{
	unsigned short status;
	unsigned short counters[2];
};

__forceinline int shroudStatusFromCount(unsigned short status)
{
	return status == 0xffff ? 2 : status == 0;
}

__forceinline int shroudStatusFromRaw(unsigned short status)
{
	if (status == 0xffff)
		return CELLSHROUD_SHROUDED;
	return status == 0;
}

typedef void (__cdecl *ShroudManagerImpl008FBA40RefreshCallback)(
	int x, int y, int status);

class ShroudManagerImpl008FBA40Element
{
public:
	ShroudManagerImpl008FBA40Element();
	~ShroudManagerImpl008FBA40Element();
	void adjustPlayerCounter008FC1F0(int playerIndex, int counterIndex,
		int amount);
	void updatePlayerCells008FC300(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);
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

	ShroudManagerImpl008FBA40Node *cellNodes;
	ShroudManagerImpl008FBA40PlayerState playerStates[16];
	int unknown64;
	friend class ShroudManagerImpl008FBA40;
};

class ShroudManagerImpl008FBA40
{
public:
	ShroudManagerImpl008FBA40();
	~ShroudManagerImpl008FBA40();
	__declspec(noinline) CellShroudStatus getShroudStatusForPlayer(
		Int playerIndex, Int x, Int y) const;
	ObjectShroudStatus getPropShroudStatusForPlayer(Int playerIndex,
		const Coord3D *loc) const;
	void drainPending();
	void updatePlayerCells008FB010(int playerIndex);
	void updatePlayerCells008FB060(int playerIndex);
	void reset();
	void setRegion(const Region3D *region, Real cellSize);
	void configure(Region3D region, Real cellSize);
	__declspec(noinline) void notify();
	__declspec(noinline) void doShroudReveal(Int cellX, Int cellY,
		Int cellRadius, UnsignedInt playerMask);
	__declspec(noinline) void undoShroudReveal(Int cellX, Int cellY,
		Int cellRadius, UnsignedInt playerMask);

private:
	int mode;
	Region3D region;
	Real defaultCellSize;
	Real inverseCellSize;
	unsigned int width;
	unsigned int height;
	ShroudManagerImpl008FBA40Element *elements;
	ShroudManagerImpl008FBA40Node *nodes;
	PartitionData *pendingPartitionData;
	int unknown38;
	_STL::deque<Gen_t_008fb350_p12pod,
		_STL::allocator<Gen_t_008fb350_p12pod> > records;
	int unknown64;
	bool enabled;
	char padding69[3];
	ShroudManagerImpl008FBA40RefreshCallback refreshCallback;

	void processPending(bool drainAll);
	friend class ShroudManagerImpl008FBA40Element;
	friend class PartitionManager;
	friend ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
		const ShroudManagerImpl008FBA40 *manager, Int x, Int y);
};

bool processShroudRevealCircle008F9A70(Int cellX, Int cellY, Int cellRadius,
	ShroudManagerImpl008FBA40 *manager, Int playerMask)
{
	Int touched = 0;
	Int currentRadius = cellRadius;
	Int error = 2;
	error -= currentRadius * 2;
	Int left = cellX;
	Int right = cellX;

	for (;;)
	{
		if (error + currentRadius > 0)
		{
			if (currentRadius == 0 && cellRadius == 1)
			{
				++touched;
				++right;
				--left;
			}

			if (!reinterpret_cast<BfmeShroudVRA *>(&manager)->bfmeUpdateVRA(
				left, right, cellY + currentRadius))
				return false;

			if (currentRadius == 0)
				return true;

			if (!reinterpret_cast<BfmeShroudVRA *>(&manager)->bfmeUpdateVRA(
				left, right, cellY - currentRadius))
				return false;

			--currentRadius;
			error += 1 - currentRadius * 2;
		}

		if (touched > error)
		{
			++touched;
			++right;
			--left;
			error += touched * 2 + 1;
		}
	}

	return true;
}

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

	for (BfmeThingCDE *node = reinterpret_cast<BfmeThingCDE *>(nodes);
		node != 0; node = node->next)
	{
		node->d_008f7ec0();
		node->d_008f7990();
		reinterpret_cast<PartitionData *>(node)->makeDirty();
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
		if (oldY >= 0 && oldY < (int)height)
		{
			for (unsigned int x = 0; x < (unsigned int)newWidth;
				++x, ++newElement)
			{
				int oldX = shroudFloatToLong(shroudFloor(
					((Real)x * cellSize + newRegion.lo.x - region.lo.x)
						* inverseCellSize));
				if (oldX >= 0 && oldX < (int)width)
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

	if (!nodes)
	{
		unknown38 = 0;
	}
	else
	{
		drainPending();
		notify();
	}
}

void ShroudManagerImpl008FBA40Element::adjustPlayerCounter008FC1F0(
	int playerIndex, int counterIndex, int amount)
{
	unsigned short *counter =
		&playerStates[playerIndex].counters[counterIndex];
	amount += *counter;
	if (amount < 0)
		amount = 0;
	else if (amount > 0xffff)
		amount = 0xffff;
	*counter = (unsigned short)amount;
}

void ShroudManagerImpl008FBA40Element::updatePlayerCells008FC450(
	ShroudManagerImpl008FBA40 *manager, int playerIndex)
{
	ShroudManagerImpl008FBA40PlayerState &playerState =
		playerStates[playerIndex];
	if (playerState.status == 0)
	{
		playerState.status = 0xffff;
		for (ShroudManagerImpl008FBA40Node *node = cellNodes;
			node; node = node->next)
		{
			node->object->playerState[playerIndex] = 0;
		}

		if (playerIndex == manager->unknown64)
		{
			int index = this - manager->elements;
			manager->refreshCallback(index % manager->width,
				index / manager->width, 2);
		}
	}
}

void ShroudManagerImpl008FBA40Element::updatePlayerCells008FC3B0(
	ShroudManagerImpl008FBA40 *manager, int playerIndex)
{
	ShroudManagerImpl008FBA40PlayerState &playerState =
		playerStates[playerIndex];
	int oldStatus = playerState.status == 0xffff
		? 2 : playerState.status == 0;
	--playerState.status;
	int newStatus = playerState.status == 0xffff
		? 2 : playerState.status == 0;
	if (newStatus != oldStatus)
	{
		for (ShroudManagerImpl008FBA40Node *node = cellNodes;
			node; node = node->next)
		{
			node->object->playerState[playerIndex] = 0;
		}

		if (playerIndex == manager->unknown64)
		{
			int index = this - manager->elements;
			manager->refreshCallback(index % manager->width,
				index / manager->width, newStatus);
		}
	}
}

void ShroudManagerImpl008FBA40Element::updatePlayerCells008FC300(
	ShroudManagerImpl008FBA40 *manager, int playerIndex)
{
	ShroudManagerImpl008FBA40PlayerState &playerState =
		playerStates[playerIndex];
	int oldStatus = shroudStatusFromCount(playerState.status);
	++playerState.status;
	if (playerState.status == 0)
		playerState.status = 1;
	int newStatus = shroudStatusFromCount(playerState.status);
	if (newStatus != oldStatus)
	{
		for (ShroudManagerImpl008FBA40Node *node = cellNodes;
			node; node = node->next)
		{
			node->object->playerState[playerIndex] = 0;
		}

		if (playerIndex == manager->unknown64)
		{
			int index = this - manager->elements;
			manager->refreshCallback(index % manager->width,
				index / manager->width, newStatus);
		}
	}
}

void ShroudManagerImpl008FBA40::doShroudReveal(Int cellX, Int cellY,
	Int cellRadius, UnsignedInt playerMask)
{
	if (playerMask != 0 && cellRadius >= 0)
		processShroudRevealCircle008F9A70(cellX, cellY, cellRadius, this,
			playerMask & 0xffff);
}

void ShroudManagerImpl008FBA40::undoShroudReveal(Int cellX, Int cellY,
	Int cellRadius, UnsignedInt playerMask)
{
	if (playerMask != 0 && cellRadius >= 0)
		processShroudRevealCircle008F9B10(cellX, cellY, cellRadius, this,
			playerMask & 0xffff);
}

struct ShroudManagerImpl008FBA40ElementLayout
{
	ShroudManagerImpl008FBA40Node *cellNodes;
	unsigned short playerStates[16][3];
	int unknown64;
};

__forceinline ShroudManagerImpl008FBA40ElementLayout *shroudElementAt(
	const ShroudManagerImpl008FBA40 *manager, Int x, Int y)
{
	if (x < 0 || x >= (Int)manager->width || y < 0 ||
		y >= (Int)manager->height)
		return 0;

	return reinterpret_cast<ShroudManagerImpl008FBA40ElementLayout *>(
		manager->elements + manager->width * y + x);
}

// ?getShroudStatusForPlayer@ShroudManagerImpl008FBA40@@QBE?AW4CellShroudStatus@@HHH@Z present-unmatched
__declspec(noinline) CellShroudStatus
ShroudManagerImpl008FBA40::getShroudStatusForPlayer(
	Int playerIndex, Int x, Int y) const
{
	CellShroudStatus result;
	ShroudManagerImpl008FBA40ElementLayout *element =
		shroudElementAt(this, x, y);
	if (element)
	{
		unsigned short status = element->playerStates[playerIndex][0];
		result = (CellShroudStatus)shroudStatusFromRaw(status);
	}
	else
		result = CELLSHROUD_SHROUDED;

	if (result == CELLSHROUD_FOGGED && !enabled)
		result = CELLSHROUD_CLEAR;
	return (CellShroudStatus)result;
}

ObjectShroudStatus ShroudManagerImpl008FBA40::getPropShroudStatusForPlayer(
	Int playerIndex, const Coord3D *loc) const
{
	if (playerIndex < 0 || playerIndex >= 16)
		return OBJECTSHROUD_SHROUDED;

	Int x = shroudFloatToLong((Real)floor((loc->x - defaultCellSize *
		0.5f - region.lo.x) *
		inverseCellSize));
	Int y = shroudFloatToLong((Real)floor((loc->y - defaultCellSize *
		0.5f - region.lo.y) *
		inverseCellSize));

	CellShroudStatus cellStatus = getShroudStatusForPlayer(playerIndex, x, y);
	if (cellStatus != getShroudStatusForPlayer(playerIndex, x + 1, y))
		return OBJECTSHROUD_PARTIAL_CLEAR;
	if (cellStatus != getShroudStatusForPlayer(playerIndex, x, y + 1))
		return OBJECTSHROUD_PARTIAL_CLEAR;
	if (cellStatus != getShroudStatusForPlayer(playerIndex, x + 1, y + 1))
		return OBJECTSHROUD_PARTIAL_CLEAR;
	switch (cellStatus)
	{
	case CELLSHROUD_CLEAR:
		_ReadWriteBarrier();
		return OBJECTSHROUD_CLEAR;
	case CELLSHROUD_SHROUDED:
		_ReadWriteBarrier();
		return OBJECTSHROUD_SHROUDED;
	default:
		_ReadWriteBarrier();
		return OBJECTSHROUD_FOGGED;
	}
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PartitionManager.h
class PartitionManager
{
public:
	void doShroudReveal(const Coord3D *position, Real radius,
		UnsignedInt playerMask);
	void undoShroudReveal(const Coord3D *position, Real radius,
		UnsignedInt playerMask);

private:
	char m_unmodelled_00[0x0C];
	ShroudManagerImpl008FBA40 *m_impl;
};

void PartitionManager::doShroudReveal(const Coord3D *position, Real radius,
	UnsignedInt playerMask)
{
	Real radiusInCells = (Real)ceil(radius * m_impl->inverseCellSize);
	Int cellRadius = shroudFloatToLong(radiusInCells);
	Real yInCells = (Real)floor((position->y - m_impl->region.lo.y) *
		m_impl->inverseCellSize);
	Int cellY = shroudFloatToLong(yInCells);
	Real xInCells = (Real)floor((position->x - m_impl->region.lo.x) *
		m_impl->inverseCellSize);
	Int cellX = shroudFloatToLong(xInCells);

	m_impl->doShroudReveal(cellX, cellY, cellRadius, playerMask);
}

void PartitionManager::undoShroudReveal(const Coord3D *position, Real radius,
	UnsignedInt playerMask)
{
	Real radiusInCells = (Real)ceil(radius * m_impl->inverseCellSize);
	Int cellRadius = shroudFloatToLong(radiusInCells);
	Real yInCells = (Real)floor((position->y - m_impl->region.lo.y) *
		m_impl->inverseCellSize);
	Int cellY = shroudFloatToLong(yInCells);
	Real xInCells = (Real)floor((position->x - m_impl->region.lo.x) *
		m_impl->inverseCellSize);
	Int cellX = shroudFloatToLong(xInCells);

	m_impl->undoShroudReveal(cellX, cellY, cellRadius, playerMask);
}
