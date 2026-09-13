// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2 /G6 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// stlport

#include <vector>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot();
	virtual void crc(void *xfer) = 0;
	virtual void xfer(void *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

struct FactionVictoryParameters
{
	AsciiString m_name;
	float m_allyDeathScaleFactor;
	float m_enemyKillScaleFactor;
	float m_mapToCellVictoryRatio;
	float m_victoryThreshold;
	float m_majorUnitValue;
};

class BfmeCell
{
public:
	BfmeCell()
	{
		for (unsigned int i = 0; i < 16; ++i)
		{
			m_second[i] = 0.0f;
			m_first[i] = 0.0f;
		}
		m_secondMask = 0;
		m_firstMask = 0;
	}

private:
	float m_first[16];
	float m_second[16];
	unsigned int m_firstMask;
	unsigned int m_secondMask;
};

class BfmeCellGrid;

class VictorySystem : public SubsystemInterface, public Snapshot
{
public:
	VictorySystem();
	virtual ~VictorySystem();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void crc(void *xfer);
	virtual void xfer(void *xfer);
	virtual void loadPostProcess();

private:
	int m_cellSize;
	unsigned int m_field10;
	float m_firstScale;
	float m_secondScale;
	float m_field1c;
	float m_field20;
	int m_playerParameterIndex[16];
	BfmeCell m_rootCell;
	_STL::vector<FactionVictoryParameters> m_factionVictoryParameters;
	BfmeCellGrid *m_cellGrids[2];
	bool m_initialized;
	unsigned int m_activeGrid;
	unsigned int m_currentPlayer;
};

VictorySystem::VictorySystem()
	: m_cellSize(0)
	, m_field10(0)
	, m_firstScale(0.0f)
	, m_secondScale(0.0f)
	, m_field1c(0.0f)
	, m_field20(1.0f)
	, m_initialized(false)
	, m_activeGrid(0)
	, m_currentPlayer(2)
{
	int playerZero = 0;
	for (int g = 0; g < 2; ++g)
		m_cellGrids[g] = 0;
	for (int i = 0; i < 16; ++i)
		m_playerParameterIndex[i] = playerZero;
	m_factionVictoryParameters.clear();
}
