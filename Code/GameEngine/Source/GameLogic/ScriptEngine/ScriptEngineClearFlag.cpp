class AsciiString;

template<class T> class StringBase
{
private:
	friend class AsciiString;
	struct Data
	{
		int refs;
		int length;
		T data[1];
	};

	Data *m_data;
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase &other);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() { m_data = 0; }
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString();
	void __cdecl format(AsciiString format, ...);
	const char *str() const { return m_data ? m_data->data : ""; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void clearFlag(const AsciiString &name);
};

// Retail's helper name is unknown, so keep the proven this/by-value ABI local
// instead of assigning an unsupported canonical identity to its 0x00344E10 body.
class BFMEScriptEngineFlagLookup
{
public:
	bool *findFlag(AsciiString name);
};

void ScriptEngine::clearFlag(const AsciiString &name)
{
	for (int player = 0; player < 32; ++player) {
		AsciiString modifiedName;
		modifiedName.format("%s%d", name.str(), player);
		bool *flag = ((BFMEScriptEngineFlagLookup *)this)->findFlag(modifiedName);
		if (flag != 0)
			*flag = false;
	}
}
