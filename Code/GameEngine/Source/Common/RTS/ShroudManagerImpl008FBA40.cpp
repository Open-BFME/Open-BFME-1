// cl: /DNDEBUG /MD /EHsc
// stlport

#include <deque>

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

class ShroudManagerImpl008FBA40Element;

struct ShroudManagerImpl008FBA40CellObject
{
	char padding00[0x24];
	int playerState[16];
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

class PartitionData
{
public:
	void unlink();

private:
	void updateCellsTouched();
	friend class ShroudManagerImpl008FBA40;
};

struct ShroudManagerImpl008FBA40PlayerState
{
	unsigned short status;
	unsigned short counters[2];
};

typedef void (__cdecl *ShroudManagerImpl008FBA40RefreshCallback)(
	int x, int y, int status);

class ShroudManagerImpl008FBA40Element
{
public:
	ShroudManagerImpl008FBA40Element();
	~ShroudManagerImpl008FBA40Element();
	void adjustPlayerCounter008FC1F0(int playerIndex, int counterIndex,
		int amount);
	void updatePlayerCells008FC3B0(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);
	void updatePlayerCells008FC450(ShroudManagerImpl008FBA40 *manager,
		int playerIndex);

private:
	ShroudManagerImpl008FBA40Node *cellNodes;
	ShroudManagerImpl008FBA40PlayerState playerStates[16];
	int unknown64;
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
	unsigned int width;
	unsigned int height;
	ShroudManagerImpl008FBA40Element *elements;
	ShroudManagerImpl008FBA40Node *nodes;
	PartitionData *pendingPartitionData;
	int unknown38;
	_STL::deque<Gen_t_008fb350_p12pod, _STL::allocator<Gen_t_008fb350_p12pod> > records;
	int unknown64;
	bool enabled;
	char padding69[3];
	ShroudManagerImpl008FBA40RefreshCallback refreshCallback;

	void processPending(bool drainAll);
	friend class ShroudManagerImpl008FBA40Element;
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
