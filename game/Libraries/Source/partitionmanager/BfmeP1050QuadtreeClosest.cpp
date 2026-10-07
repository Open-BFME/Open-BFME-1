// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

// Open-BFME: retail 0x009F5C00, 1995 bytes, ret 0x14 at +0x7C8.
//
// Identity: the matched wrappers in BfmeConv1050.cpp (0x009F26A0, 0x009F26D0,
// bfmeGo1050C) call this body as PartitionManagerImpl::GetClosestObject with five stack
// arguments. Retail loads the chosen pointer into EAX before ret, so the
// method returns a pointer; no caller reads it.
//
// Behaviour the bytes prove: a best-first walk over seventeen quadtrees kept
// in 8-byte node vectors at +0x18. A filter mask (bit 0 always set) selects
// the trees. Candidates are ordered by squared cell distance in a 24-byte
// STL heap. The distance callback comes from the table at retail 0x00EDBD60,
// which PartitionManager_bfmeDistanceBoundary3D.cpp also indexes. Each
// accepted candidate lowers the float distance bound and the integer
// cell-radius bound that prunes the heap. The owner class and every member
// name stay address-scoped, because nothing proves the BFME class name.
//
// Shape notes: one Rva009F56C0Element local serves both as the seed element
// and as the popped heap entry. The X cell index is an inline copy of the
// indexer, with count scaling before the cell scale; the Y index calls the
// out-of-line indexer.

#define _STLP_NO_EXCEPTIONS 1
#include <algorithm>
#include <vector>

extern "C" __declspec(dllimport) double __cdecl ceil(double value);
extern "C" __declspec(dllimport) double __cdecl floor(double value);

struct BfmeCoord3D1050
{
	float m_x;
	float m_y;
	float m_z;
};

struct BfmeGeometry1050
{
	unsigned char m_bfmePad00[0x10];
	float m_radius;
};

class BfmeCandidate1050;

struct BfmeNode1050
{
	int m_hasChildren;
	class BfmeLink1050 *m_firstLink;
};

class BfmeLink1050
{
public:
	int m_bfmePad00;
	BfmeCandidate1050 *m_candidate;
	int m_bfmePad08[3];
	BfmeLink1050 *m_next;
};

class BfmeCandidate1050
{
public:
	virtual BfmeGeometry1050 *getGeometry(void) = 0;
	virtual BfmeCoord3D1050 *getPosition(void) = 0;
	virtual int getUnused(void) = 0;
	virtual void *getObject(void) = 0;
};

struct BfmeRegion1050
{
	float m_x0;
	float m_y0;
	float m_bfmePad08;
	float m_x1;
	float m_y1;
};

struct Rva009F56C0Element
{
	int m_key;
	struct BfmeNode1050 *m_node;
	unsigned int m_stride;
	int m_x;
	int m_y;
	int m_size;
};

class BfmeHostER
{
public:
	unsigned int bfmeIndexER(float value);
};

class BfmeHostES
{
public:
	unsigned int bfmeIndexES(float value);
};

class Rva009F2AB0Mask
{
public:
	int getMask(void);
};

class BfmeThingEQ
{
public:
	unsigned char bfmeAskEQ(void *object);
};

struct S4SortElem24
{
	int m_key;
	int m_values[5];
};

struct S4Cmp009F4BF0
{
	char m_bfmeUnused;

	S4Cmp009F4BF0(void) : m_bfmeUnused(0) {}

	bool operator()(const S4SortElem24 &left, const S4SortElem24 &right) const
	{
		return left.m_key < right.m_key;
	}
};

typedef float (__cdecl *BfmeDistanceProc1050)(const void *, const void *, int);
extern BfmeDistanceProc1050 g_rva00EDBD60DistanceProcs[];

typedef _STL::vector<BfmeNode1050> BfmeNodeVec1050;

__forceinline int bfmeFloatToInt1050(float value)
{
	int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class PartitionManagerImpl
{
public:
	void *GetClosestObject(int position, int maxDistance, int bounds,
		int distanceType, int filters);

	float m_originX;
	float m_originY;
	unsigned char m_bfmePad08[0x10];
	BfmeNodeVec1050 m_trees[17];
	unsigned char m_bfmePadE4[0x4];
	float m_cellScale;
	unsigned int m_cellCount;
};

__forceinline unsigned int bfmeInlineCellX1050(PartitionManagerImpl *manager, float value)
{
	float t = (float)floor((double)((value - manager->m_originX) *
		(float)manager->m_cellCount * manager->m_cellScale));
	int i = bfmeFloatToInt1050(t);
	if (i < 0)
		return 0;
	return (unsigned int)i >= manager->m_cellCount ? manager->m_cellCount - 1 : i;
}

void *PartitionManagerImpl::GetClosestObject(int position, int maxDistance, int bounds,
	int distanceType, int filters)
{
	unsigned int filterMask;
	if (distanceType != 0 && distanceType != 2 &&
		distanceType != 1 && distanceType != 3)
		distanceType = 0;
	BfmeDistanceProc1050 distanceProc = g_rva00EDBD60DistanceProcs[distanceType];

	if (filters)
		filterMask = ((Rva009F2AB0Mask *)filters)->getMask() * 2 + 1;
	else
		filterMask = 0xffffffff;

	Rva009F56C0Element current;
	_STL::vector<Rva009F56C0Element> work;
	BfmeNodeVec1050 *tree = m_trees;

	for (int treeCount = 17; treeCount; --treeCount)
	{
		if (filterMask & 1)
		{
			current.m_key = 0;
			current.m_node = tree->begin();
			current.m_stride = m_trees[0].size() / 4;
			current.m_y = 0;
			current.m_x = 0;
			current.m_size = m_cellCount;
			work.push_back(current);
		}
		++tree;
		filterMask >>= 1;
	}

	float &maxDistanceReal = *(float *)&maxDistance;

	if (maxDistanceReal < 0.00001f)
		return 0;

	float cellExtent = m_cellCount * m_cellScale;
	if (maxDistanceReal * cellExtent > 32766.0f)
		maxDistanceReal = 32766.0f / cellExtent;

	float maxDistanceSquared = maxDistanceReal * maxDistanceReal;
	void *closestObject = 0;
	cellExtent *= maxDistanceReal;
	int maxRadius = bfmeFloatToInt1050((float)ceil(cellExtent));
	int maxRadiusSquared = (maxRadius + 1) * (maxRadius + 1);

	BfmeCoord3D1050 *source = (BfmeCoord3D1050 *)position;
	int cellCenterX = ((BfmeHostER *)this)->bfmeIndexER(source->m_x);
	int cellCenterY = ((BfmeHostES *)this)->bfmeIndexES(source->m_y);

	BfmeRegion1050 *region = (BfmeRegion1050 *)bounds;
	int regionX0;
	int regionX1;
	int regionY0;
	int regionY1;
	if (region)
	{
		regionX0 = ((BfmeHostER *)this)->bfmeIndexER(region->m_x0);
		regionX1 = ((BfmeHostER *)this)->bfmeIndexER(region->m_x1);
		regionY0 = ((BfmeHostES *)this)->bfmeIndexES(region->m_y0);
		regionY1 = ((BfmeHostES *)this)->bfmeIndexES(region->m_y1);
	}

	while (!work.empty())
	{
		if (work.front().m_key > maxRadiusSquared)
			break;

		_STL::pop_heap((S4SortElem24 *)work.begin(), (S4SortElem24 *)work.end(), S4Cmp009F4BF0());
		current = work.back();
		work.pop_back();

		for (BfmeLink1050 *link = current.m_node->m_firstLink; link;
			link = link->m_next)
		{
			float distance = distanceProc(source, link->m_candidate, 0);
			if (distance > maxDistanceSquared)
				continue;

			if (region)
			{
				BfmeCoord3D1050 *where = link->m_candidate->getPosition();
				if (where->m_x < region->m_x0)
					continue;
				if (where->m_y < region->m_y0)
					continue;
				if (where->m_x > region->m_x1)
					continue;
				if (where->m_y > region->m_y1)
					continue;
			}

			void *object = link->m_candidate->getObject();
			if (!object)
				continue;
			if (filters && !((BfmeThingEQ *)filters)->bfmeAskEQ(object))
				continue;

			maxDistanceSquared = distance;
			closestObject = object;
			BfmeGeometry1050 *geometry = link->m_candidate->getGeometry();
			BfmeCoord3D1050 *candidatePosition = link->m_candidate->getPosition();
			float radiusValue = geometry->m_radius;

			unsigned int xDistance =
				bfmeInlineCellX1050(this, candidatePosition->m_x - radiusValue) - cellCenterX;
			unsigned int xDistanceMaximum =
				bfmeInlineCellX1050(this, candidatePosition->m_x + radiusValue) - cellCenterX;
			unsigned int yDistance = ((BfmeHostES *)this)->bfmeIndexES(
				candidatePosition->m_y - radiusValue) - cellCenterY;
			unsigned int yDistanceMaximum = ((BfmeHostES *)this)->bfmeIndexES(
				candidatePosition->m_y + radiusValue) - cellCenterY;

			if (xDistanceMaximum > xDistance)
				xDistance = xDistanceMaximum;
			if (yDistanceMaximum > yDistance)
				yDistance = yDistanceMaximum;
			maxRadiusSquared = yDistance * yDistance + xDistance * xDistance;
		}

		if (!current.m_node->m_hasChildren)
			continue;

		int half = current.m_size / 2;
		current.m_node = current.m_node + 1;
		for (unsigned int groupIndex = 0; groupIndex < 4;
			++groupIndex, current.m_node += current.m_stride)
		{
			BfmeNode1050 *group = current.m_node;
			if (group->m_firstLink || group->m_hasChildren)
			{
				Rva009F56C0Element child;
				child.m_x = ((groupIndex & 1) ? half : 0) + current.m_x;
				child.m_y = current.m_y + ((groupIndex & 2) ? half : 0);

				int xDistance;
				if (cellCenterX < child.m_x)
				{
					int delta = child.m_x - cellCenterX - 1;
					xDistance = delta * delta;
				}
				else if (cellCenterX >= child.m_x + half)
				{
					int delta = cellCenterX - child.m_x - half;
					xDistance = delta * delta;
				}
				else
					xDistance = 0;

				int yDistance;
				if (cellCenterY < child.m_y)
					yDistance = (child.m_y - cellCenterY - 1) * (child.m_y - cellCenterY - 1);
				else if (cellCenterY >= child.m_y + half)
					yDistance = (cellCenterY - child.m_y - half) * (cellCenterY - child.m_y - half);
				else
					yDistance = 0;

				child.m_key = yDistance + xDistance;
				if (child.m_key <= maxRadiusSquared)
				{
					if (!region || (child.m_x <= regionX1 && child.m_y <= regionY1 &&
						child.m_x + half >= regionX0 && child.m_y + half >= regionY0))
					{
						child.m_node = group;
						child.m_size = half;
						child.m_stride = current.m_stride / 4;
						work.push_back(child);
						_STL::push_heap((S4SortElem24 *)work.begin(), (S4SortElem24 *)work.end(), S4Cmp009F4BF0());
					}
				}
			}
		}
	}
	return closestObject;
}
