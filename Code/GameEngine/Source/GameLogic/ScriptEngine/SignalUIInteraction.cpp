// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text);
	~AsciiString();

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void anchor00(); virtual void anchor04(); virtual void anchor08(); virtual void anchor0C();
	virtual void anchor10(); virtual void anchor14(); virtual void anchor18(); virtual void anchor1C();
	virtual void anchor20(); virtual void anchor24(); virtual void anchor28(); virtual void anchor2C();
	virtual void anchor30(); virtual void anchor34(); virtual void anchor38(); virtual void anchor3C();
	virtual void anchor40(); virtual void anchor44(); virtual void anchor48(); virtual void anchor4C();
	virtual void anchor50(); virtual void anchor54(); virtual void anchor58(); virtual void anchor5C();
	virtual void anchor60(); virtual void anchor64(); virtual void anchor68(); virtual void anchor6C();
	virtual void anchor70(); virtual void anchor74(); virtual void anchor78(); virtual void anchor7C();
	virtual void anchor80(); virtual void anchor84(); virtual void anchor88(); virtual void anchor8C();
	virtual void anchor90(); virtual void anchor94(); virtual void anchor98(); virtual void anchor9C();
	virtual void signalUIInteract(const AsciiString &interaction);
};

extern ScriptEngine *TheScriptEngine;
extern const char *TheShellHookNames[];

void SignalUIInteraction(int interaction)
{
	if (TheScriptEngine) {
		const char *hookName = TheShellHookNames[interaction];
		TheScriptEngine->signalUIInteract(hookName);
	}
}
