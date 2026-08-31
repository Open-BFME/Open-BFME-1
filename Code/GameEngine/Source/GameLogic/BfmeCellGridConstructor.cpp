// cl: /O2 /Ob2 /G6

void *__cdecl operator new[](unsigned int size);

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern "C" void * __cdecl memset(void *block, Int value, UnsignedInt bytes);
#pragma intrinsic(memset)

class CrashMessage
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual CrashMessage *setText(const char *text);
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18();
	virtual void show(bool visible);
};

class DebugManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void beginReport();
	virtual void slot25(); virtual void slot26();
	virtual CrashMessage *getCrashMessage(void *a, void *b);
};

void _bfme_debugRecordCallsite(Int kind);

#define TheDebugManager (*(DebugManager **)0x01336E5C)
#define CELL_GRID_ALLOCATION_FAILURE ((const char *)0x0109C958)

#define REPORT_CRASH(reason) do { \
	_bfme_debugRecordCallsite(1); \
	DebugManager *manager = TheDebugManager; \
	manager->beginReport(); \
	manager = TheDebugManager; \
	CrashMessage *message = manager->getCrashMessage(0, 0); \
	message->setText(reason)->show(true); \
} while (0)

class BfmeCell
{
public:
	BfmeCell();
	~BfmeCell();

	Real m_first[16];
	Real m_second[16];
	UnsignedInt m_firstMask;
	UnsignedInt m_secondMask;
};

class BfmeCellGrid
{
public:
	BfmeCellGrid(Int width, Int height, Real cellSize, Real offset);

private:
	Int m_width;
	Int m_height;
	UnsignedInt m_cellCount;
	Real m_cellSize;
	Real m_offset;
	BfmeCell *m_cells;
	UnsignedInt *m_cellValues;
};

BfmeCellGrid::BfmeCellGrid(Int width, Int height, Real cellSize, Real offset)
{
	m_width = width;
	m_height = height;
	m_cellCount = width * height;
	m_cellSize = cellSize;
	m_offset = offset;
	m_cells = 0;

	if (m_cellCount != 0)
	{
		m_cells = new BfmeCell[m_cellCount];

		for (UnsignedInt cellIndex = 0; cellIndex < m_cellCount; ++cellIndex)
		{
			for (UnsignedInt playerIndex = 0; playerIndex < 16; ++playerIndex)
			{
				m_cells[cellIndex].m_first[playerIndex] = 0.0f;
				m_cells[cellIndex].m_second[playerIndex] = 0.0f;
			}
			m_cells[cellIndex].m_firstMask = 0;
			m_cells[cellIndex].m_secondMask = 0;
		}

		if (m_cells == 0)
			REPORT_CRASH(CELL_GRID_ALLOCATION_FAILURE);

		m_cellValues = new UnsignedInt[m_cellCount];

		if (m_cellValues == 0)
			REPORT_CRASH(CELL_GRID_ALLOCATION_FAILURE);

		memset(m_cellValues, 0, m_cellCount * sizeof(*m_cellValues));
	}
}
