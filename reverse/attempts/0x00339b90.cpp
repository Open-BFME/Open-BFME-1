// ?_bfme_updateClientDebugFrame@ScriptEngine@@QAEXXZ
// partial score=0.9815 date=2026-08-27
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

class ScriptEngine
{
public:
	void _bfme_updateClientDebugFrame(void);
	bool _bfme_isClientFrameFrozen(void);

private:
	char m_unknown00[0x17638];
	bool m_useLogicDebugFrame;
};

typedef int (__stdcall *FarProc)(void);
extern "C" __declspec(dllimport) FarProc __stdcall GetProcAddress(
	void *module, const char *name);

class GameClient
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void);
	virtual unsigned int getFrame(void);
};

extern void _bfme_updateDebugWindowInputs(void);

#define TheScriptDebugWindowDLL (*(void **)0x012F0758)
#define ClientCanAppContinue (*(bool *)0x012F075C)
#define TheGameClient (*(GameClient **)0x012F1464)

void ScriptEngine::_bfme_updateClientDebugFrame(void)
{
	if (m_useLogicDebugFrame)
		return;

	void *module = TheScriptDebugWindowDLL;
	if (module)
	{
		_bfme_updateDebugWindowInputs();
		module = TheScriptDebugWindowDLL;
		typedef void (__cdecl *SetFrameNumberProc)(unsigned int frame);
		FarProc proc = GetProcAddress(module, "SetFrameNumber");
		if (proc)
		{
			unsigned int frame = TheGameClient->getFrame();
			((SetFrameNumberProc)proc)(frame);
		}

		module = TheScriptDebugWindowDLL;
		if (module)
		{
			typedef bool (__cdecl *CanAppContinueProc)(void);
			proc = GetProcAddress(module, "CanAppContinue");
			if (proc)
			{
				ClientCanAppContinue = ((CanAppContinueProc)proc)();
				return;
			}
			return;
		}
	}

	ClientCanAppContinue = true;
}

bool ScriptEngine::_bfme_isClientFrameFrozen(void)
{
	if (!m_useLogicDebugFrame && TheScriptDebugWindowDLL)
		return !ClientCanAppContinue;
	return false;
}
