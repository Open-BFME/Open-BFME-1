// cl: /QIfist

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern "C" __declspec(dllimport) double __cdecl ceil(double value);

__forceinline Real bfmeFloatFloorSmallFill(Real value)
{
	return (Real)floor((double)value);
}

__forceinline Real bfmeFloatCeilSmallFill(Real value)
{
	return (Real)ceil((double)value);
}

__forceinline int bfmeFloatToIntSmallFill(Real value)
{
	int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class BfmeCoiSmallFill;

class BfmeCellSmallFill
{
public:
	BfmeCoiSmallFill *m_first;
	int m_data[25];
};

class BfmePartitionGridSmallFill
{
public:
	char m_head[4];
	Real m_originX;
	Real m_originY;
	char m_middle[20];
	Real m_scale;
	int m_width;
	int m_height;
	BfmeCellSmallFill *m_cells;

	BfmeCellSmallFill *getCellAt(int x, int y)
	{
		if (x < 0 || x >= m_width || y < 0 || y >= m_height)
			return 0;
		return &m_cells[y * m_width + x];
	}
};

class BfmeCoiSmallFill
{
public:
	BfmeCellSmallFill *m_cell;
	void *m_module;
	BfmeCellSmallFill *m_prev;
	BfmeCoiSmallFill *m_next;

	__forceinline bool addCoverage(BfmeCellSmallFill *cell)
	{
		m_cell = cell;
		BfmeCoiSmallFill *next = cell->m_first;
		m_next = next;
		if (next != 0)
			next->m_prev = (BfmeCellSmallFill *)&m_next;
		m_prev = (BfmeCellSmallFill *)cell;
		cell->m_first = this;
		return true;
	}
};

class BfmeSmallFillRange
{
public:
	BfmePartitionGridSmallFill *m_grid;
	BfmeCoiSmallFill *m_first;
	BfmeCoiSmallFill *m_next;
	bool rva008F80A0(int firstX, int lastX, int y);
};

extern bool bfmeFillSmall(int cellCenterX, int cellCenterY, int cellRadius,
	BfmeSmallFillRange range);

class PartitionData
{
private:
	bool doSmallFill(Real centerX, Real centerY, Real radius);

	BfmePartitionGridSmallFill *m_grid;
	char m_prefix[0x18];
	BfmeCoiSmallFill *m_coiArray;
	int m_coiInUseCount;
};

bool PartitionData::doSmallFill(Real centerX, Real centerY, Real radius)
{
	int cellCenterX = bfmeFloatToIntSmallFill(bfmeFloatFloorSmallFill(
		(centerX - m_grid->m_originX) * m_grid->m_scale));
	int cellCenterY = bfmeFloatToIntSmallFill(bfmeFloatFloorSmallFill(
		(centerY - m_grid->m_originY) * m_grid->m_scale));
	int cellRadius = bfmeFloatToIntSmallFill(bfmeFloatCeilSmallFill(
		radius * m_grid->m_scale));

	--cellRadius;
	if (cellRadius < 1)
	{
		BfmeCellSmallFill *cell = m_grid->getCellAt(cellCenterX, cellCenterY);
		if (cell != 0)
		{
			BfmeCoiSmallFill *coi = m_coiArray;
			coi->addCoverage(cell);
		}
		return true;
	}
	else
	{
		BfmeSmallFillRange range;
		range.m_grid = m_grid;
		range.m_first = m_coiArray;
		range.m_next = m_coiArray + m_coiInUseCount;
		if (!bfmeFillSmall(cellCenterX, cellCenterY, cellRadius, range))
		{
			_ReadWriteBarrier();
			return false;
		}
		return true;
	}
}

bool bfmeFillSmall(int cellCenterX, int cellCenterY, int cellRadius,
	BfmeSmallFillRange range)
{
	int x = 0;
	int y = cellRadius;
	int error = 2 - 2 * cellRadius;
	int leftX = cellCenterX;
	int rightX = cellCenterX;

	for (;;)
	{
		if (error + y > 0)
		{
			if (y == 0 && cellRadius == 1)
			{
				++x;
				++rightX;
				--leftX;
			}

			if (!range.rva008F80A0(leftX, rightX, cellCenterY + y))
				return false;
			if (y == 0)
				return true;
			if (!range.rva008F80A0(leftX, rightX, cellCenterY - y))
				return false;

			--y;
			error += 1 - 2 * y;
		}

		if (x > error)
		{
			++x;
			++rightX;
			--leftX;
			error += 2 * x + 1;
		}
	}
}
