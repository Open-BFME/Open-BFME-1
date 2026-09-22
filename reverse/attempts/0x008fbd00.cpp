// ?d_008fbd00@@YAXXZ
// partial score=0.2 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// stlport
// Retail coordinate search at 0x008FBD00.

#define _STLP_NO_EXCEPTIONS 1
#define private public
#include <vector>
#undef private

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum ValueOrThreat
{
	VOT_CashValue = 0,
	VOT_ThreatValue = 1
};

struct Gen_t_008fbc70_p8cd
{
	Int a[2];
};

struct PartitionCell;

namespace _STL
{
	template <class Type>
	struct DequeIterator
	{
		Type *current;
		Type *first;
		Type *last;
		Type **node;
	};

	template <class Type>
	struct DequeLayout
	{
		DequeIterator<Type> start;
		DequeIterator<Type> finish;
		Type **map;
		unsigned int mapSize;
	};

	template <class Type, class Allocator>
	class _Deque_base
	{
	public:
		void _M_initialize_map(unsigned int count);

		DequeLayout<Type> layout;
	};

	template <class Type, class Allocator>
	class deque
	{
		DequeLayout<Type> layout;

		DequeLayout<Type> &state()
		{
			return layout;
		}

	public:
		~deque();

		deque()
		{
			DequeLayout<Type> &q = state();
			q.start.current = 0;
			q.start.first = 0;
			q.start.last = 0;
			q.start.node = 0;
			q.finish.current = 0;
			q.finish.first = 0;
			q.finish.last = 0;
			q.finish.node = 0;
			q.map = 0;
			q.mapSize = 0;
			typedef _Deque_base<PartitionCell *, allocator<PartitionCell *> >
				MapBase;
			reinterpret_cast<MapBase *>(this)->_M_initialize_map(0);
		}

		void push_back(const Type &value);

		bool empty() const
		{
			const DequeLayout<Type> &q =
				*reinterpret_cast<const DequeLayout<Type> *>(this);
			return q.finish.current == q.start.current;
		}

		Type &front()
		{
			return *state().start.current;
		}

		void pop_front()
		{
			DequeLayout<Type> &q = state();
			if (q.start.current != q.start.last - 1)
			{
				++q.start.current;
			}
			else
			{
				__node_alloc<true, 0>::_M_deallocate(q.start.first, 0x80);
				++q.start.node;
				q.start.first = *q.start.node;
				q.start.last = q.start.first + 0x80 / sizeof(Type);
				q.start.current = q.start.first;
			}
		}
	};
}

class Gen_008F7CD0
{
public:
	Int bfmeCellX(Real value) const;
	Int bfmeCellY(Real value) const;
};

struct ShroudManagerImpl008FBA40Element
{
	void *cellNodes;
	unsigned short playerStates[16][3];
	Int unknown64;
};

class ShroudManagerImpl008FBA40
{
public:
	bool rva008FBD00(const Coord3D *sourceLocation,
		UnsignedInt allowedPlayers, ValueOrThreat valueType,
		Int valueRequired, Coord3D *outLocation);

private:
	Int mode;
	char region[24];
	Real defaultCellSize;
	Real inverseCellSize;
	UnsignedInt width;
	UnsignedInt height;
	ShroudManagerImpl008FBA40Element *elements;
};

bool ShroudManagerImpl008FBA40::rva008FBD00(
	const Coord3D *sourceLocation, UnsignedInt allowedPlayers,
	ValueOrThreat valueType, Int valueRequired, Coord3D *outLocation)
{
	if (allowedPlayers == 0)
		return false;
	if (valueType < VOT_CashValue || valueType >= 2)
		return false;

	valueRequired &= 0xffff;
	const Gen_008F7CD0 *grid = (const Gen_008F7CD0 *)this;
	Int cellX = grid->bfmeCellX(sourceLocation->x);
	Int cellY = grid->bfmeCellY(sourceLocation->y);
	if (cellX < 0)
		cellX = 0;
	else if ((UnsignedInt)cellX >= width)
		cellX = width - 1;
	if (cellY < 0)
		cellY = 0;
	else if ((UnsignedInt)cellY >= height)
		cellY = height - 1;

	Int cellCount = width * height;
	_STL::vector<bool> bitField(cellCount, false);
	_STL::deque<Gen_t_008fbc70_p8cd,
		_STL::allocator<Gen_t_008fbc70_p8cd> > cellQ;
	Gen_t_008fbc70_p8cd start;
	start.a[0] = cellX;
	start.a[1] = cellY;
	cellQ.push_back(start);

	while (!cellQ.empty())
	{
		Gen_t_008fbc70_p8cd current = cellQ.front();
		cellQ.pop_front();
		cellX = current.a[0];
		cellY = current.a[1];
		Int cellIndex = cellY * width + cellX;

		if (cellX != 0 && !bitField[cellIndex - 1])
		{
			bitField[cellIndex - 1] = true;
			Gen_t_008fbc70_p8cd next;
			next.a[0] = cellX - 1;
			next.a[1] = cellY;
			cellQ.push_back(next);
		}
		if ((UnsignedInt)cellX < width - 1 && !bitField[cellIndex + 1])
		{
			bitField[cellIndex + 1] = true;
			Gen_t_008fbc70_p8cd next;
			next.a[0] = cellX + 1;
			next.a[1] = cellY;
			cellQ.push_back(next);
		}
		if (cellY != 0 && !bitField[cellIndex - width])
		{
			bitField[cellIndex - width] = true;
			Gen_t_008fbc70_p8cd next;
			next.a[0] = cellX;
			next.a[1] = cellY - 1;
			cellQ.push_back(next);
		}
		if ((UnsignedInt)cellY < height - 1 &&
			!bitField[cellIndex + width])
		{
			bitField[cellIndex + width] = true;
			Gen_t_008fbc70_p8cd next;
			next.a[0] = cellX;
			next.a[1] = cellY + 1;
			cellQ.push_back(next);
		}

		UnsignedInt value = 0;
		const ShroudManagerImpl008FBA40Element *element =
			elements + cellIndex;
		const unsigned short *valuePtr =
			&element->playerStates[0][valueType + 1];
		for (UnsignedInt mask = allowedPlayers; mask != 0;
			mask >>= 1, valuePtr += 3)
		{
			if (mask & 1)
				value += *valuePtr;
		}
		if (value >= (UnsignedInt)valueRequired)
		{
			outLocation->x = cellX * defaultCellSize;
			outLocation->y = cellY * defaultCellSize;
			outLocation->z = 0;
			return true;
		}
	}

	return false;
}
