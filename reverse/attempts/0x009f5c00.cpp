// ?bfmeFwd1050@BfmeP1050@@QAEPAXHHHHH@Z
// partial score=0.15 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

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

class BfmeFilterChain1050
{
public:
	int getMask(void);
	bool allow(void *object);
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
extern BfmeDistanceProc1050 bfmeDistanceProcs1050[];

typedef _STL::vector<BfmeNode1050> BfmeOffsetVec1050;

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

class BfmeP1050
{
public:
void *bfmeFwd1050(int position, int maxDistance, int bounds,
        int distanceType, int filters);

	int mapX1050(float value);
	int mapY1050(float value);

	float m_originX;
	float m_originY;
	unsigned char m_bfmePad08[0x10];
	BfmeOffsetVec1050 m_radiusVec[17];
	void *m_moduleList;
	float m_cellSize;
	unsigned int m_cellCount;
	void *m_dirtyModules;
};

__forceinline int bfmeInlineCellX1050(BfmeP1050 *manager, float value)
{
	float scaled = (value - manager->m_originX) * manager->m_cellCount;
	scaled *= manager->m_cellSize;
	return bfmeFloatToInt1050((float)floor((double)scaled));
}

void *BfmeP1050::bfmeFwd1050(int position, int maxDistance, int bounds,
	int distanceType, int filters)
{
	BfmeP1050 *manager = this;
	BfmeFilterChain1050 *filterChain = (BfmeFilterChain1050 *)filters;
	BfmeOffsetVec1050 *radius;
	int filterMask;
	if (distanceType != 0 && distanceType != 2 &&
		distanceType != 1 && distanceType != 3)
		distanceType = 0;
	BfmeDistanceProc1050 distanceProc = bfmeDistanceProcs1050[distanceType];

	if (filterChain)
		filterMask = filterChain->getMask() * 2 + 1;
	else
		filterMask = -1;

	radius = manager->m_radiusVec;
	_STL::vector<S4SortElem24> work;

	for (int radiusCount = 17; radiusCount; --radiusCount)
	{
		if (filterMask & 1)
		{
			BfmeNode1050 *first = radius->begin();
			int offsetCount = manager->m_radiusVec->size() / 4;
			S4SortElem24 value;
			value.m_key = 0;
			value.m_values[0] = (int)first;
			value.m_values[1] = offsetCount;
			value.m_values[2] = 0;
			value.m_values[3] = 0;
			value.m_values[4] = manager->m_cellCount;
			work.push_back(value);
		}
		++radius;
		filterMask >>= 1;
	}

	float &maxDistanceReal = *(float *)&maxDistance;

	if (maxDistanceReal < 0.00001f)
		return 0;

	{
		float cellExtent;
		void *closestObject;
		float maxDistanceSquared;

		cellExtent = manager->m_cellCount * manager->m_cellSize;
		if (maxDistanceReal * cellExtent > 32766.0f)
			maxDistanceReal = 32766.0f / cellExtent;

		maxDistanceSquared = maxDistanceReal * maxDistanceReal;
		closestObject = 0;
		cellExtent *= maxDistanceReal;
		int maxRadius = bfmeFloatToInt1050((float)ceil(cellExtent)) + 1;
		int maxRadiusSquared = maxRadius * maxRadius;

		BfmeCoord3D1050 *source = (BfmeCoord3D1050 *)position;
		int cellCenterX = manager->mapX1050(source->m_x);
		int cellCenterY = manager->mapY1050(source->m_y);

		BfmeRegion1050 *region = (BfmeRegion1050 *)bounds;
		int regionX0 = 0;
		int regionX1 = 0;
		int regionY0 = 0;
		int regionY1 = 0;
		if (region)
		{
			regionX0 = manager->mapX1050(region->m_x0);
			regionX1 = manager->mapX1050(region->m_x1);
			regionY0 = manager->mapY1050(region->m_y0);
			regionY1 = manager->mapY1050(region->m_y1);
		}

		S4Cmp009F4BF0 compare;
		while (work.begin() != work.end())
		{
			S4SortElem24 current;
			if (work.begin()->m_key > maxRadiusSquared)
				break;

			_STL::pop_heap(work.begin(), work.end(), compare);
			current = *(work.end() - 1);

			BfmeNode1050 *node = (BfmeNode1050 *)current.m_values[0];
			for (BfmeLink1050 *link = node->m_firstLink; link;
				link = link->m_next)
			{
				BfmeCandidate1050 *candidate = link->m_candidate;
				float distance;
				distance = distanceProc(source, candidate, 0);
				if (distance > maxDistanceSquared)
					continue;

				BfmeCoord3D1050 *candidatePosition;
				if (region)
				{
					candidatePosition = candidate->getPosition();
					if (candidatePosition->m_x < region->m_x0)
						continue;
					if (candidatePosition->m_y < region->m_y0)
						continue;
					if (candidatePosition->m_x > region->m_x1)
						continue;
					if (candidatePosition->m_y > region->m_y1)
						continue;
				}

				void *object = candidate->getObject();
				if (!object)
					continue;
				if (filterChain && !filterChain->allow(object))
					continue;

				maxDistanceSquared = distance;
				closestObject = object;
				BfmeGeometry1050 *geometry = candidate->getGeometry();
				candidatePosition = candidate->getPosition();
				float radiusValue = geometry->m_radius;

				float xMinimumValue = candidatePosition->m_x - radiusValue;
				int xMinimum = bfmeInlineCellX1050(manager, xMinimumValue);
				if (xMinimum < 0)
					xMinimum = 0;
				else if (manager->m_cellCount <= xMinimum)
					xMinimum = manager->m_cellCount - 1;

				int xMaximum = bfmeInlineCellX1050(manager,
					candidatePosition->m_x + radiusValue);
				if (xMaximum < 0)
					xMaximum = 0;
				else if (manager->m_cellCount <= xMaximum)
					xMaximum = manager->m_cellCount - 1;
				int xDistance = xMinimum - cellCenterX;
				int xDistanceMaximum = xMaximum - cellCenterX;

				int yMinimum = manager->mapY1050(candidatePosition->m_y - radiusValue);
				int yMaximum = manager->mapY1050(candidatePosition->m_y + radiusValue);
				int yDistance = yMinimum - cellCenterY;
				int yDistanceMaximum = yMaximum - cellCenterY;

				if (xDistanceMaximum > xDistance)
					xDistance = xDistanceMaximum;
				if (yDistanceMaximum > yDistance)
					yDistance = yDistanceMaximum;
					current.m_key = xDistance * xDistance +
						yDistance * yDistance;
			}

			if (!node->m_hasChildren)
				continue;

				int half = current.m_values[4] / 2;
			BfmeNode1050 *group = node + 1;
			for (unsigned int groupIndex = 0; groupIndex < 4; ++groupIndex)
			{
				if (group->m_firstLink || group->m_hasChildren)
				{
						int x = current.m_values[2] +
						((groupIndex & 1) ? half : 0);
						int y = current.m_values[3] +
						((groupIndex & 2) ? half : 0);

					int xDistance;
					if (cellCenterX < x)
					{
						int delta = x - cellCenterX - 1;
						xDistance = delta * delta;
					}
					else if (cellCenterX >= x + half)
					{
						int delta = cellCenterX - x - half;
						xDistance = delta * delta;
					}
					else
						xDistance = 0;

					int yDistance;
					if (cellCenterY < y)
					{
						int delta = y - cellCenterY - 1;
						yDistance = delta * delta;
					}
					else if (cellCenterY >= y + half)
					{
						int delta = cellCenterY - y - half;
						yDistance = delta * delta;
					}
					else
						yDistance = 0;

					int key = xDistance + yDistance;
					if (key <= current.m_key)
					{
						if (!region || (x <= regionX1 && y <= regionY1 &&
							x + half >= regionX0 && y + half >= regionY0))
						{
							S4SortElem24 child;
							child.m_key = key;
							child.m_values[0] = (int)group;
							child.m_values[1] = current.m_values[1] / 4;
							child.m_values[2] = x;
							child.m_values[3] = y;
							child.m_values[4] = half;
							work.push_back(child);
							_STL::push_heap(work.begin(), work.end(), compare);
						}
					}
				}
				group += current.m_values[1];
			}
		}
		return closestObject;
	}
}
