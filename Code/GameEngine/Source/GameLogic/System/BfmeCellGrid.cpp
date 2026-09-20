// cl: /O2 /Ob2 /G6

// One grid layout serves construction, storage reset, point lookup, object
// accumulation, and victory-threshold evaluation. The cell layout is 0x88 bytes:
// two sixteen-player sample arrays followed by their two masks.
// The constructor and lookup prove the unsigned count at +0x08 and the
// cell spacing/origin at +0x0C/+0x10; reset clears the same 0x1C-byte object.
// Keep the existing ABI names: these BFME-specific types have no ZH twin.
void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad000[0x38];
	Coord3D m_position;
};

class Gen_001de260
{
public:
	Int bfmeAbove(const Real *samples, Int index) const;
};

class VictorySystem
{
public:
	Gen_001de260 *bfmeParametersForPlayer(Int playerIndex);
};

extern VictorySystem *TheVictorySystem;

class BfmeCell
{
public:
	BfmeCell();
	~BfmeCell();
	void bfmeAdd(Real amount, Int firstIndex, Int secondIndex);

	void clear()
	{
		for (UnsignedInt index = 0; index < 16; ++index)
		{
			m_second[index] = 0.0f;
			m_first[index] = 0.0f;
		}
		m_secondMask = 0;
		m_firstMask = 0;
	}


	Real m_first[16];
	Real m_second[16];
	UnsignedInt m_firstMask;
	UnsignedInt m_secondMask;
};

BfmeCell::~BfmeCell()
{
}

struct BfmePoint1560
{
	Real X;
	Real Y;
};

class BfmeCellGrid
{
public:
	BfmeCellGrid(Int width, Int height, Real cellSize, Real offset);
	void _bfme_reset();
	Int bfmeEvaluateCells() const;
	void bfmeApplyAtObject(const Object *object,
		Real amount, Int firstIndex, Int secondIndex) const;
	UnsignedInt bfmePointIndex(const BfmePoint1560 &point);

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

void BfmeCellGrid::_bfme_reset()
{
	if (m_cells)
	{
		delete[] m_cells;
		m_cells = 0;
	}

	UnsignedInt *cellValues = m_cellValues;

	m_width = 0;
	m_height = 0;
	m_cellCount = 0;
	m_offset = 0.0f;
	m_cellSize = 0.0f;

	if (cellValues)
	{
		delete[] cellValues;
		m_cellValues = 0;
	}
}

UnsignedInt BfmeCellGrid::bfmePointIndex(const BfmePoint1560 &point)
{
	if (m_cellSize > 0.0f)
	{
		Int row = (Int)((point.Y - m_offset) / m_cellSize);
		Int index = row * m_width;
		index += (Int)((point.X - m_offset) / m_cellSize);
		if ((UnsignedInt)index < m_cellCount)
			return index;
	}
	return 0x7fffffff;
}

void BfmeCellGrid::bfmeApplyAtObject(const Object *object,
	Real amount, Int firstIndex, Int secondIndex) const
{
	const Coord3D *position = object->getPosition();
	if (m_cellSize > 0.0f)
	{
		Int row = (Int)((position->y - m_offset) / m_cellSize);
		Int index = row * m_width;
		index += (Int)((position->x - m_offset) / m_cellSize);

		if ((UnsignedInt)index < m_cellCount && index != 0x7fffffff)
			m_cells[index].bfmeAdd(amount, firstIndex, secondIndex);
	}
}

Int BfmeCellGrid::bfmeEvaluateCells() const
{
	Int affected = 0;
	for (UnsignedInt cellIndex = 0; cellIndex < m_cellCount; ++cellIndex)
	{
		m_cellValues[cellIndex] = 0;
		if (m_cells[cellIndex].m_firstMask != 0)
		{
			for (UnsignedInt playerIndex = 0; playerIndex < 16; ++playerIndex)
			{
				if ((m_cells[cellIndex].m_firstMask & (1 << playerIndex)) != 0)
				{
					Gen_001de260 *parameters =
						TheVictorySystem->bfmeParametersForPlayer((Int)playerIndex);
					if (parameters != 0 &&
						static_cast<unsigned char>(parameters->bfmeAbove(
							m_cells[cellIndex].m_first, (Int)playerIndex)) != 0)
					{
						m_cellValues[cellIndex] |= (1 << playerIndex);
						m_cells[cellIndex].clear();
						++affected;
					}
				}
			}
		}
	}
	return affected;
}
