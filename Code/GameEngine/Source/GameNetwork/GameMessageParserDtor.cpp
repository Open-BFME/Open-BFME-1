// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

class GameMessageParserArgumentType
{
public:
	virtual ~GameMessageParserArgumentType();

	GameMessageParserArgumentType *m_next;
};

class GameMessageParser
{
protected:
	virtual ~GameMessageParser();

	GameMessageParserArgumentType *m_first;
	GameMessageParserArgumentType *m_last;
	int m_argTypeCount;
};

// ??1GameMessageParser@@MAE@XZ
GameMessageParser::~GameMessageParser()
{
	while (m_first != 0)
	{
		GameMessageParserArgumentType *next = m_first->m_next;
		delete m_first;
		m_first = next;
	}
}
