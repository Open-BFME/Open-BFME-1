// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?ParseActionDataChunk@ScriptAction@@SA_NAAVDataChunkInput@@PAUDataChunkInfo@@PAX@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp
// Open-BFME7: isolated port of Scripts.cpp's ScriptAction::ParseActionDataChunk
// for retail 0x00358FE0. The shared Scripts.cpp TU already compiles this body to
// retail's exact instruction shape -- down to the alignment nop before the loop
// head -- and differs in one immediate: BFME's Script keeps m_action at this+0x20
// where the reference header puts it at +0x28.
//
// The packet ties this address between ParseActionDataChunk and its
// ParseActionFalseDataChunk twin, since masking the relocation sites hides the
// only byte that separates them. Scanning .text for the pair's shared prologue
// finds exactly two bodies -- 0x00358FE0 reading this+0x20 and 0x00359030
// reading this+0x24 -- and the reference declares m_action ahead of
// m_actionFalse, so the lower offset is m_action and this is the plain
// ParseActionDataChunk. Only the difference between the two offsets is proven
// here; where BFME's Script loses the eight bytes ahead of them is not, so
// nothing above m_action is named.

#define NULL 0

class DataChunkInput;
struct DataChunkInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class ScriptAction
{
public:
	static bool ParseActionDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData);

	ScriptAction *getNext(void) const { return m_nextAction; }
	void setNextAction(ScriptAction *pAct) { m_nextAction = pAct; }

protected:
	// Defined elsewhere; retail reaches it through the link thunk at 0x0001720B.
	static ScriptAction *ParseAction(DataChunkInput &file, DataChunkInfo *info, void *userData);

private:
	unsigned char _bfme_head[0x3C];
	ScriptAction *m_nextAction;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Script
{
public:
	ScriptAction *getAction(void) const { return m_action; }
	void setAction(ScriptAction *pAct) { m_action = pAct; }

private:
	unsigned char _bfme_head[0x20];
	ScriptAction *m_action;
};

bool ScriptAction::ParseActionDataChunk(DataChunkInput &file, DataChunkInfo *info, void *userData)
{
	Script *pScript = (Script *)userData;

	ScriptAction	*pScriptAction = ParseAction(file, info, userData);

	ScriptAction *pLast = pScript->getAction();
	while (pLast && pLast->getNext())
	{
		pLast = pLast->getNext();
	}

	if (pLast)
	{
		pLast->setNextAction(pScriptAction);
	}
	else
	{
		pScript->setAction(pScriptAction);
	}
	return true;
}
