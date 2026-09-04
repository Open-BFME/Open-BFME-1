// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX

typedef int (__stdcall *FarProc)(void);
extern "C" __declspec(dllimport) FarProc __stdcall GetProcAddress(
	void *module, const char *name);

class ScriptEngine;
class AudioManager;
class GlobalData;
class NameKeyGenerator;
class View;
class TerrainLogic;
class GameLogic;

extern void *TheScriptDebugWindowDLL;
extern ScriptEngine *TheScriptEngine;
extern AudioManager *TheAudio;
extern GlobalData *TheWritableGlobalData;
extern NameKeyGenerator *TheNameKeyGenerator;
extern View *TheTacticalView;
extern TerrainLogic *TheTerrainLogic;
// 0x012EF1D8 has only address-derived pins so far (placeBuildAvailable casts
// it to a thing factory); keep the untyped pin rather than invent a class.
extern void *g_global12EF1D8;
extern GameLogic *TheGameLogic;

void _bfme_updateDebugWindowInputs(void)
{
	if (!TheScriptDebugWindowDLL)
		return;

	typedef void (__cdecl *SetTheSidesListProc)(
		void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
	FarProc proc = GetProcAddress(TheScriptDebugWindowDLL, "SetTheSidesList");
	if (proc)
	{
		((SetTheSidesListProc)proc)(
			// no symbols.csv pin names this global yet; the export name
			// suggests TheSidesList but nothing in the ledger proves it
			*(void **)0x012EF428,
			TheScriptEngine,
			TheAudio,
			TheWritableGlobalData,
			TheNameKeyGenerator,
			0,
			0,
			TheTacticalView,
			TheTerrainLogic,
			g_global12EF1D8,
			TheGameLogic);
	}
}
