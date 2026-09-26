// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /G6 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// VictorySystem::xfer, retail RVA 0x001E05F0.

#include <vector>
#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned char UnsignedByte;

struct XferVersionFields
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

union XferVersion
{
	XferVersionFields m_fields;
	UnsignedInt m_value;
};

class Snapshot;

class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual void slot03();
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, UnsignedInt size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void xferAsciiString(AsciiString *value);
	virtual void xferReal(Real *value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

class VictoryScoreData
{
public:
	void xfer(Xfer *xfer);

private:
	unsigned char m_data[0x88];
};

class BfmeCellGrid
{
public:
	Bool xfer(Xfer *xfer);
};

class VictorySystemPrimary
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void newMap();
};

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
	virtual void slot20();
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
	virtual BfmeAwakenLog *slot4C(Int result);
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
	virtual BfmeAwakenLog *slot6C(Int first, Int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(Int kind);

struct FactionVictoryParameters
{
	FactionVictoryParameters() : m_name()
	{
		m_allyDeathScaleFactor = 0.0f;
		m_enemyKillScaleFactor = 0.0f;
		m_mapToCellVictoryRatio = 0.0f;
		m_victoryThreshold = 0.0f;
		m_majorUnitValue = 0.0f;
	}

	AsciiString m_name;
	Real m_allyDeathScaleFactor;
	Real m_enemyKillScaleFactor;
	Real m_mapToCellVictoryRatio;
	Real m_victoryThreshold;
	Real m_majorUnitValue;
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	void *m_name;
};

class Snapshot
{
public:
	Snapshot();
	virtual ~Snapshot();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

class VictorySystem : public SubsystemInterface, public Snapshot
{
public:
	VictorySystem();
	virtual ~VictorySystem();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void crc(Xfer *xfer);
	void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	Real m_cellSize;
	UnsignedInt m_field10;
	Real m_firstScale;
	Real m_secondScale;
	Real m_field1c;
	Real m_field20;
	Int m_playerParameterIndex[16];
	VictoryScoreData m_rootCell;
	_STL::vector<FactionVictoryParameters> m_factionVictoryParameters;
	BfmeCellGrid *m_cellGrids[2];
	Bool m_initialized;
	unsigned char m_padding[3];
	UnsignedInt m_activeGrid;
	UnsignedInt m_currentPlayer;
};

void VictorySystem::xfer(Xfer *xfer)
{
	UnsignedInt gridCount;
	{
		XferVersion version;
		version.m_fields.m_version = 1;
		version.m_fields.m_currentVersion = 1;
		xfer->xferVersion(&version);
	}

	xfer->xferBool(&m_initialized);
	xfer->xferReal(&m_cellSize);
	xfer->xferUnsignedInt(&m_field10);
	xfer->xferReal(&m_firstScale);
	xfer->xferReal(&m_secondScale);
	xfer->xferReal(&m_field1c);
	xfer->xferReal(&m_field20);

	m_rootCell.xfer(xfer);
	xfer->xferUser(m_playerParameterIndex, 0x40);

	if (xfer->IsLightCRC())
		return;

	if (xfer->IsLoading())
	{
		m_factionVictoryParameters.erase(
			m_factionVictoryParameters.begin(), m_factionVictoryParameters.end());

		UnsignedInt parameterCount = 0;
		xfer->xferUnsignedInt(&parameterCount);
		for (UnsignedInt index = 0; index < parameterCount; ++index)
		{
			FactionVictoryParameters parameters;
			xfer->xferAsciiString(&parameters.m_name);
			xfer->xferReal(&parameters.m_allyDeathScaleFactor);
			xfer->xferReal(&parameters.m_enemyKillScaleFactor);
			xfer->xferReal(&parameters.m_mapToCellVictoryRatio);
			xfer->xferReal(&parameters.m_victoryThreshold);
			m_factionVictoryParameters.push_back(parameters);
		}
	}

	else if (xfer->IsStoring())
	{
		UnsignedInt parameterCount = m_factionVictoryParameters.size();
		xfer->xferUnsignedInt(&parameterCount);
		for (UnsignedInt index = 0;
				index < m_factionVictoryParameters.size(); ++index)
		{
			FactionVictoryParameters &parameters =
				m_factionVictoryParameters[index];
			xfer->xferAsciiString(&parameters.m_name);
			xfer->xferReal(&parameters.m_allyDeathScaleFactor);
			xfer->xferReal(&parameters.m_enemyKillScaleFactor);
			xfer->xferReal(&parameters.m_mapToCellVictoryRatio);
			xfer->xferReal(&parameters.m_victoryThreshold);
		}
	}

	gridCount = 2;
	xfer->xferUnsignedInt(&gridCount);
	if (gridCount != 2)
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		TheBfmeAwakenDebug->slot6C(0, 0)->slot38(
			"Cell Grid count != VS_CELL_GRID_COUNT, DoXFer failed!")->slot4C(1);
	}

	if (xfer->IsLoading())
	{
		Bool anyGrid = false;
		for (UnsignedInt index = 0; index < gridCount; ++index)
		{
			if (m_cellGrids[index] != 0)
				anyGrid |= m_cellGrids[index]->xfer(xfer);
		}

		if (anyGrid)
			((VictorySystemPrimary *)this)->newMap();
	}
	else if (xfer->IsStoring())
	{
		for (UnsignedInt index = 0; index < gridCount; ++index)
		{
			if (m_cellGrids[index] != 0)
				m_cellGrids[index]->xfer(xfer);
		}
	}
}
