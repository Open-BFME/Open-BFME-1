// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// ScriptEngine::enableScript, retail 0x0033C560. ZH twin plus BFME
// listener at +0x1708C notified with canonicalFlagName.

#include "StringInline.h"

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

class ScriptAction
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_parameterCount)
			return m_parameters[index];
		return 0;
	}

private:
	char m_unknown[8];
	int m_parameterCount;
	Parameter *m_parameters[12];
};

class ScriptGroup
{
public:
	void setActive(bool value) { m_active = value; }

private:
	char m_pad[0xC];
	bool m_active;
};

class Script
{
public:
	void setActive(bool value) { m_active = value; }

private:
	char m_pad[0x14];
	bool m_active;
};

class ScriptEngine;

class BFMEScriptEngineFlagLookup
{
	friend class ScriptEngine;
	AsciiString canonicalFlagName(const AsciiString &name);
};

class BfmeEnableListener
{
public:
	bool notify(const AsciiString &name, const AsciiString &canonical, bool enabled);
};

class ScriptEngine
{
protected:
	ScriptGroup *findGroup(AsciiString name, AsciiString *canonicalOut);
	Script *findScript(AsciiString name, AsciiString *canonicalOut);
	void enableScript(ScriptAction *pAction);

private:
	char m_pad[0x1708C];
	BfmeEnableListener *m_listener;
};

// ?enableScript@ScriptEngine@@IAEXPAVScriptAction@@@Z
void ScriptEngine::enableScript(ScriptAction *pAction)
{
	AsciiString name = pAction->getParameter(0)->getString();
	ScriptGroup *pGroup = findGroup(name, 0);
	if (pGroup)
		pGroup->setActive(true);
	Script *pScript = findScript(name, 0);
	if (pScript)
		pScript->setActive(true);
	if (m_listener)
	{
		AsciiString canonical =
			((BFMEScriptEngineFlagLookup *)this)->canonicalFlagName(name);
		m_listener->notify(name, canonical, true);
	}
}
