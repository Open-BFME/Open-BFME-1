#pragma once
// TU-scoped stand-in for the real GameLogic/ScriptEngine.h (which is huge, and
// whose ZH-reference field layout does not match BFME's -- see
// ScriptEngineFields.cpp for the two accessors that proved this: retail writes
// m_freezeByScript at offset 0x17624, 27240 bytes further out than the ZH
// header places it, meaning BFME's ScriptEngine grew substantially somewhere
// among the earlier fields).
//
// Reconstructing the full BFME layout (like reference/shims/gamewindow/) is
// not warranted for two one-field accessors, so this shim only pins the one
// offset those accessors touch and nothing else. Scoped to this TU via a
// private /Ireference/shims/scriptengine include -- every other TU still
// resolves GameLogic/ScriptEngine.h to the real header.
class ScriptEngine
{
public:
	char m_padBeforeFreezeByScript[0x17624];
	Bool m_freezeByScript;

	void doFreezeTime(void);
	void doUnfreezeTime(void);
};
