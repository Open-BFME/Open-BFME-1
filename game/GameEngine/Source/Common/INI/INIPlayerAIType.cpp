// cl: /DNDEBUG /MD /EHsc

// FILE: INIPlayerAIType.cpp //////////////////////////////////////////////////
//
// The PlayerAIType block, BFME-only, named by the INI block table in .data.
// Seventeen bytes: hand the INI straight to the subsystem.
//
// PlayerAITypeSet is a real name - game_engine_subsystems.h already carries the
// class and its initSubsystem<PlayerAITypeSet> registration, and the singleton
// this body loads is 0x012ED740. The member it calls has no recoverable name, so
// it is spelled for the call site: one INI pointer, thiscall, callee-cleaned.
//
///////////////////////////////////////////////////////////////////////////////

class INI;

class BfmePlayerAITypeSet
{
public:
	void parseBlock( INI *ini );
};

extern BfmePlayerAITypeSet *ThePlayerAITypeSet;		// 0x012ED740

// ?parsePlayerAIType@@YAXPAVINI@@@Z
void parsePlayerAIType( INI *ini )
{
	ThePlayerAITypeSet->parseBlock( ini );
}
