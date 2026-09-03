// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// readable body of ??1GameMessageParser@@MAE@XZ: Code/GameEngine/Source/GameNetwork/GameMessageParser.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
class GameMessageParserArgumentType
{
public:
	virtual ~GameMessageParserArgumentType();

	GameMessageParserArgumentType *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameMessageParser.h
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
