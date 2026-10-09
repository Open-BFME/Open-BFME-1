// ?_bfme_initEngine@ScriptEngine@@UAEXXZ
// partial score=0.0 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc
typedef void *HMODULE;
typedef int (__stdcall *FARPROC)();
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char *name);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE module, const char *name);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE module);

class GlobalData
{
public:
    char m_pad0[0x29];
    bool m_windowed;
    char m_pad1[0xA90 - 0x2A];
    bool m_scriptDebug;
    bool m_particleEdit;
};
extern GlobalData *TheWritableGlobalData;
extern bool g_flag12ED4DA;
extern HMODULE TheScriptDebugWindowDLL;

class Gen_002F1B10
{
public:
    Gen_002F1B10();
    unsigned char m_storage[0x10];
};
class Rva00324490
{
public:
    Rva00324490();
    unsigned char m_storage[8];
};

class ScriptActionsInterface
{
public:
    virtual ~ScriptActionsInterface();
    virtual void init();
};
class ScriptConditionsInterface
{
public:
    virtual ~ScriptConditionsInterface();
    virtual void init();
};
extern ScriptActionsInterface *TheScriptActions;
extern ScriptConditionsInterface *TheScriptConditions;

template <class T> inline void swapValues(T &a, T &b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

class BfmeDualVtableReleaseBase
{
public:
    __forceinline ~BfmeDualVtableReleaseBase() {}
    virtual void bfmeKeepVtable() {}
};
class BfmeDualVtableReleaseDtor : public BfmeDualVtableReleaseBase
{
public:
    virtual ~BfmeDualVtableReleaseDtor();
    void swap(BfmeDualVtableReleaseDtor &that)
    {
        swapValues(m_guard, that.m_guard);
        swapValues(m_target, that.m_target);
    }
private:
    void *m_guard;
    void *m_target;
};
class __declspec(novtable) Rva0033AF00 : public BfmeDualVtableReleaseDtor
{
public:
    Rva0033AF00(int unused);
};

class Gen_00C6FE50Target;
extern Gen_00C6FE50Target TheBfmeObject_00C6FE50;
void _bfme_updateDebugWindowInputs();

class BfmeExcUA
{
public:
    BfmeExcUA(const BfmeExcUA &other);
};

class ScriptEngine
{
public:
    virtual ~ScriptEngine();
    virtual void _bfme_initEngine();
    virtual void slot2();
    virtual void slot3();
    virtual void reset();
    virtual void init();
    void initConditionTemplates();
    void Rva0033D8B0();
private:
    char m_pre[0x17640 - 8];
    double m_numFrames;
    double m_totalUpdateTime;
    double m_maxUpdateTime;
};

// Open BFME 2 donor: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_init.cpp.
// ?_bfme_initEngine@ScriptEngine@@UAEXXZ
void ScriptEngine::_bfme_initEngine()
{
    TheScriptActions = (ScriptActionsInterface *)new Gen_002F1B10;
    TheScriptConditions = (ScriptConditionsInterface *)new Rva00324490;
    if (TheWritableGlobalData->m_windowed)
    {
        if (TheWritableGlobalData->m_scriptDebug)
        {
            if (g_flag12ED4DA)
                TheScriptDebugWindowDLL = LoadLibraryA("DebugWindowLite.dll");
            else
                TheScriptDebugWindowDLL = LoadLibraryA("DebugWindow.dll");
        }
        else
            TheScriptDebugWindowDLL = 0;
        if (TheWritableGlobalData->m_particleEdit)
        {
            try
            {
                Rva0033AF00(0).swap((BfmeDualVtableReleaseDtor &)TheBfmeObject_00C6FE50);
            }
            catch (const BfmeExcUA &)
            {
            }
        }
        if (TheScriptDebugWindowDLL)
        {
            FARPROC proc = GetProcAddress(TheScriptDebugWindowDLL, "CreateDebugDialog");
            if (proc)
            {
                proc();
                _bfme_updateDebugWindowInputs();
            }
            else
            {
                FreeLibrary(TheScriptDebugWindowDLL);
                TheScriptDebugWindowDLL = 0;
            }
        }
    }
    m_numFrames = 0;
    m_totalUpdateTime = 0;
    m_maxUpdateTime = 0;
    if (TheScriptActions)
        TheScriptActions->init();
    if (TheScriptConditions)
        TheScriptConditions->init();
    ScriptEngine::init();
    initConditionTemplates();
    Rva0033D8B0();
    reset();
}
