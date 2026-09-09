// ??1ScriptActions@@UAE@XZ
// partial score=0.99 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: ScriptActions::~ScriptActions, retail 0x002F1B80, 108 bytes.

typedef bool Bool;

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface(void);
};

class ScriptActionsInterface : public SubsystemInterface
{
public:
	virtual ~ScriptActionsInterface(void) {}
};

class AsciiString
{
public:
	~AsciiString(void) { releaseBuffer(); }

private:
	void releaseBuffer(void);
	char *m_data;
};

struct BfmeTerrainLogic
{
	unsigned char m_unmodelled_0000[0x18F4];
	unsigned char m_scriptWindowOpen;
};

extern BfmeTerrainLogic *TheTerrainLogic;

class ScriptActions : public ScriptActionsInterface
{
public:
	virtual ~ScriptActions(void);

private:
	unsigned char m_unmodelled_004[4];
	volatile unsigned char m_suppressNewWindows;
	unsigned char m_unmodelled_009[3];
	AsciiString m_unnamedUnit;
};

ScriptActions::~ScriptActions(void)
{
	unsigned int zero = 0;
	m_suppressNewWindows = (unsigned char)zero;
	BfmeTerrainLogic *terrain = TheTerrainLogic;
	if (terrain != 0)
		terrain->m_scriptWindowOpen = (unsigned char)zero;
	m_suppressNewWindows = (unsigned char)zero;
}
