// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	int getInt() const { return m_integer; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
protected:
	bool *bfmeFlagForWrite(AsciiString name);
	bool *bfmeFlagForRead(AsciiString name);
	void setFlag(ScriptAction *action, bool copyFromFlag);
};

void ScriptEngine::setFlag(ScriptAction *action, bool copyFromFlag)
{
	ScriptAction *sourceAction = action;
	bool *flag = bfmeFlagForWrite(sourceAction->getParameter(0)->getString());
	bool value = false;
	if (copyFromFlag)
	{
		bool *source = bfmeFlagForRead(sourceAction->getParameter(1)->getString());
		if (source)
			value = *source;
	}
	else
	{
		value = sourceAction->getParameter(1)->getInt() != 0;
	}
	*flag = value;
}
