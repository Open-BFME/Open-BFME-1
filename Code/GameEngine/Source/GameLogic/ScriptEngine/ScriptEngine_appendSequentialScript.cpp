// cl: /DNDEBUG /MD /O2 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/stringinline
// stlport

#include "StringInline.h"
#include <vector>

typedef bool Bool;
typedef int Int;

class Script;

class Bfme5CtorA0
{
public:
	enum MagicEnum { GLUE_NOT_IMPLEMENTED = 0 };
	static void *operator new(unsigned int size, MagicEnum, const char *)
	{
		return ::operator new(size);
	}
	static void operator delete(void *pointer, MagicEnum, const char *)
	{
		::operator delete(pointer);
	}

	Bfme5CtorA0();
	virtual ~Bfme5CtorA0();
	Bfme5CtorA0 &operator=(const Bfme5CtorA0 &other);

	void *m_base;
	Int m_objectID;
	AsciiString m_nameA;
	AsciiString m_nameB;
	Script *m_scriptToExecuteSequentially;
	Int m_currentInstruction;
	Int m_timesToLoop;
	Int m_framesToWait;
	Bool m_dontAdvanceInstruction;
	Bfme5CtorA0 *m_nextScriptInSequence;
};

Bfme5CtorA0::Bfme5CtorA0()
	: m_base(0),
	  m_objectID(0),
	  m_scriptToExecuteSequentially(0),
	  m_currentInstruction(-1),
	  m_timesToLoop(0),
	  m_framesToWait(-1),
	  m_dontAdvanceInstruction(false),
	  m_nextScriptInSequence(0)
{
}

class ScriptEngine
{
public:
	void appendSequentialScript(Bfme5CtorA0 *scriptToSequence);

private:
	void *m_vptr;
	char m_gap0[8];
	_STL::vector<Bfme5CtorA0 *> m_sequentialScripts;
};

// ?appendSequentialScript@ScriptEngine@@QAEXPAVBfme5CtorA0@@@Z
void ScriptEngine::appendSequentialScript(Bfme5CtorA0 *scriptToSequence)
{
	Bfme5CtorA0 *newSequentialScript =
		new(Bfme5CtorA0::GLUE_NOT_IMPLEMENTED, "") Bfme5CtorA0;
	(*newSequentialScript) = (*scriptToSequence);
	newSequentialScript->m_nextScriptInSequence = 0;
	newSequentialScript->m_currentInstruction = -1;

	Bool found = false;
	for (_STL::vector<Bfme5CtorA0 *>::iterator it = m_sequentialScripts.begin();
		it != m_sequentialScripts.end(); ++it)
	{
		Bfme5CtorA0 *seqScript = *it;
		if (!seqScript)
			continue;

		if ((scriptToSequence->m_objectID &&
			scriptToSequence->m_objectID == seqScript->m_objectID) ||
			(scriptToSequence->m_base &&
			scriptToSequence->m_base == seqScript->m_base))
		{
			found = true;
			while (seqScript->m_nextScriptInSequence)
				seqScript = seqScript->m_nextScriptInSequence;
			seqScript->m_nextScriptInSequence = newSequentialScript;
			break;
		}
	}

	if (!found)
		m_sequentialScripts.push_back(newSequentialScript);
}
