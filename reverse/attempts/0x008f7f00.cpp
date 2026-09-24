// ?doRectFill@PartitionData@@AAE_NMMMMM@Z
// partial score=0.88 date=2026-09-24
// cl: /O2 /FAsc /Fabuild/doRectFill.cod

typedef float Real;
typedef int Int;

extern const Real g_bfmeK1253;
extern const Real g_bfmeK1266B;
extern const Real g_rva003D2B80NegHalf;
extern "C" Real __cdecl cosf(Real angle);
extern "C" Real __cdecl sinf(Real angle);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

__forceinline Int bfmeFloatToIntRectFill(Real value)
{
	Int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class CellAndObjectIntersection;

class BfmeCellFD
{
public:
	CellAndObjectIntersection *m_first;
	Int m_data[25];
};

class Gen_008F7CD0
{
public:
	BfmeCellFD *bfmeAt(Real x, Real y) const;

	unsigned char m_prefix[0x1c];
	Real m_cellSize;
	Real m_scale;
};

class CellAndObjectIntersection
{
public:
	BfmeCellFD *m_cell;
	void *m_partitionData;
	CellAndObjectIntersection **m_previous;
	CellAndObjectIntersection *m_next;
};

class PartitionData
{
private:
	bool doRectFill(Real centerX, Real centerY, Real halfsizeX,
		Real halfsizeY, Real angle);

	Gen_008F7CD0 *m_grid;
	unsigned char m_prefix[0x18];
	CellAndObjectIntersection *m_coiArray;
};

bool PartitionData::doRectFill(Real centerX, Real centerY, Real halfsizeX,
	Real halfsizeY, Real angle)
{
	Real c = cosf(angle);
	Real s = sinf(angle);
	Real xStep = c * m_grid->m_cellSize;
	Real xdx = xStep * g_bfmeK1253;
	Real xdy = s * m_grid->m_cellSize;
	xdy *= g_bfmeK1253;
	Real ydx = s * m_grid->m_cellSize;
	ydx *= g_bfmeK1253;
	Real ydy = xStep * -0.5f;
	register Real scaleX = m_grid->m_scale;
	Real roundedStepsX = (Real)ceil((double)(scaleX * halfsizeX * 4.0f));
	Int numStepsX = bfmeFloatToIntRectFill(roundedStepsX);
	register Real scaleY = m_grid->m_scale;
	Real roundedStepsY = (Real)ceil((double)(scaleY * halfsizeY * 4.0f));
	Int numStepsY = bfmeFloatToIntRectFill(roundedStepsY);
	register Int rows = numStepsY;
	Real tl_x = centerX - halfsizeX * c - halfsizeY * s;
	Int nextCellStamp;
	nextCellStamp = *(volatile Int *)0x0133F408;
	Real tl_y = centerY + halfsizeY * c - halfsizeX * s;
	CellAndObjectIntersection *coi = m_coiArray;
	++nextCellStamp;
	*(volatile Int *)0x0133F408 = nextCellStamp;

	if (rows > 0)
	{
		do
		{
			Real x = tl_x;
			Real y = tl_y;
			if (numStepsX > 0)
			{
				Int columns = numStepsX;
				do
				{
					BfmeCellFD *cell = m_grid->bfmeAt(x, y);
					if (cell != 0)
					{
						Int cellStamp = *(volatile Int *)0x0133F408;
						if (cellStamp != cell->m_data[24])
						{
							cell->m_data[24] = cellStamp;
							coi->m_cell = cell;
							CellAndObjectIntersection *next = cell->m_first;
							coi->m_next = next;
							if (next != 0)
								next->m_previous = &coi->m_next;
							coi->m_previous = (CellAndObjectIntersection **)&cell->m_first;
							cell->m_first = coi;
							++coi;
						}
					}
					--columns;
					x += xdx;
					y += xdy;
				} while (columns != 0);
			}
			--rows;
			tl_x += ydx;
			tl_y += ydy;
		} while (rows != 0);
	}
	return true;
}
