// cl: /DNDEBUG /MD /EHsc

// FILE: ScriptEngineGetCurrentPlayer.cpp /////////////////////////////////////
//
// ScriptEngine::getCurrentPlayer, retail 0x0033DA70.
//
// No port of ScriptEngine.cpp exists under Code/.  Found by the literal it
// pushes: "***Unexpected NULL player:***" appears in exactly one reference
// source and inside exactly one function there.
//
// The body is Zero Hour's three lines.  What the bytes add is the offset:
// m_currentPlayer is at +0x170ac, read twice -- once for the null test and
// again for the return, because AppendDebugMessage may have changed it.
//
///////////////////////////////////////////////////////////////////////////////

typedef bool Bool;

template <class Type>
class StringBase
{
private:
	// Private so the symbol is AAE, which is how the ledger names this body.
	StringBase(const char *s);
	friend class AsciiString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:

	// Visible delegation, not a bare declaration: see
	// docs/lessons-archive.md on the by-value temporary transposition.
	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	AsciiString(const AsciiString &that);
	~AsciiString();

private:

	void *m_text;

};

class Player;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:

	Player *getCurrentPlayer(void);

	// Public, not private as the reference header declares it: the ledger
	// already names the body behind this thunk QAE, and AAE is a different
	// symbol that appears nowhere.
	void AppendDebugMessage(const AsciiString &strToAdd, Bool forcePause);

private:

	char m_bfmeHead[0x170ac];
	Player *m_currentPlayer;										// @0x170ac

};

Player *ScriptEngine::getCurrentPlayer(void)
{
	if (m_currentPlayer==0)
		AppendDebugMessage("***Unexpected NULL player:***", false);
	return m_currentPlayer;
}  // end getCurrentPlayer
