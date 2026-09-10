// ?doSmallFill@PartitionData@@AAEXMMM@Z
// partial score=0.35 date=2026-09-10
// cl: /QIfist /DNDEBUG /MD /EHsc

typedef float Real;
typedef unsigned char Bool;

extern "C" __declspec(dllimport) double __cdecl floor(double value);
extern volatile const Real g_bfmeK1253;
extern const char g_bfmeEmptyAscii[];

extern "C" Bool __cdecl _bfme_debugReportingEnabled(void);
extern "C" void __cdecl _bfme_debugRecordCallsite(int kind);

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual BfmeAwakenLog *slot20(Real value);
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;

class BFMERetailAsciiString
{
public:
	struct Data
	{
		unsigned short m_references;
		unsigned short m_allocated;
		unsigned short m_length;
		unsigned short m_reserved;
		char m_text[1];
	};

	BFMERetailAsciiString(const char *text);
	BFMERetailAsciiString(const BFMERetailAsciiString &that);
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

	const char *str(void) const
	{
		return m_data ? m_data->m_text : g_bfmeEmptyAscii;
	}

private:
	void releaseBuffer(void);
	Data *m_data;
};

class BfmeObjectSmallFill
{
public:
	virtual BFMERetailAsciiString getDebugName(void);
};

class BfmeCellSmallFillVoid;

class BfmePartitionGridSmallFillVoid
{
public:
	char m_head[4];
	Real m_originX;
	Real m_originY;
	char m_middle[16];
	Real m_cellSize;
	Real m_scale;
	int m_width;
	int m_height;
	BfmeCellSmallFillVoid *m_cells;

	BfmeCellSmallFillVoid *getCellAt(int x, int y);
};

class BfmeCoiSmallFillVoid
{
public:
	BfmeCellSmallFillVoid *m_cell;
	void *m_module;
	BfmeCellSmallFillVoid *m_prev;
	BfmeCoiSmallFillVoid *m_next;

	__forceinline void addCoverage(BfmeCellSmallFillVoid *cell);
};

class BfmeCellSmallFillVoid
{
public:
	BfmeCoiSmallFillVoid *m_first;
	int m_data[25];
};

BfmeCellSmallFillVoid *BfmePartitionGridSmallFillVoid::getCellAt(int x, int y)
{
	if (x < 0 || x >= m_width || y < 0 || y >= m_height)
		return 0;
	return &m_cells[y * m_width + x];
}

__forceinline void BfmeCoiSmallFillVoid::addCoverage(BfmeCellSmallFillVoid *cell)
{
	m_cell = cell;
	BfmeCoiSmallFillVoid *next = cell->m_first;
	m_next = next;
	if (next != 0)
		next->m_prev = (BfmeCellSmallFillVoid *)&m_next;
	m_prev = (BfmeCellSmallFillVoid *)cell;
	cell->m_first = this;
}

__forceinline Real bfmeFloorSmallFillVoid(Real value)
{
	return (Real)floor((double)value);
}

__forceinline int bfmeFloorToIntSmallFillVoid(Real value)
{
	int result;
	__asm
	{
		fld [value]
		fistp [result]
	}
	return result;
}

class PartitionData
{
private:
	void doSmallFill(Real centerX, Real centerY, Real radius);

	BfmePartitionGridSmallFillVoid *m_grid;
	BfmeObjectSmallFill *m_object;
	char m_prefix[0x14];
	BfmeCoiSmallFillVoid *m_coiArray;
};

// ?doSmallFill@PartitionData@@AAEXMMM@Z
void PartitionData::doSmallFill(Real centerX, Real centerY, Real radius)
{
	BfmePartitionGridSmallFillVoid *grid = m_grid;
	Real maximumRadius = grid->m_cellSize;
	maximumRadius *= g_bfmeK1253;
	if (radius > maximumRadius)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			BFMERetailAsciiString objectName = m_object ?
				m_object->getDebugName() : BFMERetailAsciiString("*unknown*");
			BfmeAwakenLog *report = TheBfmeAwakenDebug->slot6C(0, 0);
			report->slot38("Object ")
				->slot38(objectName.str())
				->slot38(" is too large for 'small geometry. Radius given is ")
				->slot20(radius)
				->slot38(" but maximum radius for small geometry is ")
				->slot20(maximumRadius)
				->slot38("; truncating. In order to fix this problem either set the geometry of the given object\n"
					"to non-small or reduce the geometry major radius.\n")
				->slot4C(2);
		}
		radius = maximumRadius;
	}

	int x1 = bfmeFloorToIntSmallFillVoid(bfmeFloorSmallFillVoid(
		(centerX - radius - grid->m_originX) * grid->m_scale));
	int y1 = bfmeFloorToIntSmallFillVoid(bfmeFloorSmallFillVoid(
		(centerY - radius - grid->m_originY) * grid->m_scale));
	int x2 = bfmeFloorToIntSmallFillVoid(bfmeFloorSmallFillVoid(
		(centerX + radius - grid->m_originX) * grid->m_scale));
	int y2 = bfmeFloorToIntSmallFillVoid(bfmeFloorSmallFillVoid(
		(centerY + radius - grid->m_originY) * grid->m_scale));

	BfmeCoiSmallFillVoid *coi = m_coiArray;
	for (int y = y1; y <= y2; ++y)
	{
		for (int x = x1; x <= x2; ++x)
		{
			BfmeCellSmallFillVoid *cell = grid->getCellAt(x, y);
			if (cell != 0)
			{
				coi->addCoverage(cell);
				++coi;
			}
		}
	}
}
