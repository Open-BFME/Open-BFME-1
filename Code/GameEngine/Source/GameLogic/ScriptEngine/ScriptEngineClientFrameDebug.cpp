// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

class ScriptEngine
{
public:
	bool _bfme_isClientFrameFrozen(void);

private:
	char m_unknown00[0x17638];
	bool m_useLogicDebugFrame;
};

#define TheScriptDebugWindowDLL (*(void **)0x012F0758)
#define ClientCanAppContinue (*(bool *)0x012F075C)

bool ScriptEngine::_bfme_isClientFrameFrozen(void)
{
	if (!m_useLogicDebugFrame && TheScriptDebugWindowDLL)
		return !ClientCanAppContinue;
	return false;
}
