// ?Rva00463E30@@YAXPBURva0045DD90FloatPair@@0PBD1@Z
// stlport
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /I. /Iinputs/vendor/stlport /DNDEBUG /DWIN32 /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Retail 0x00463E30, 466 bytes (ret at +0x1A5 and +0x1D1, INT3 after),
// reached only through ILT 0x0000ED59. Identity unproven, so the name keeps
// the address. The body proves: the record for the path leaf
// (bfmePathLeafAfterMarker 0x0046EE80) is looked up through Rva00462C10
// (0x00462C10) and, when absent, built by Rva00463850 (0x00463850) with the
// same four arguments; the record's +0xC name is refreshed when it differs;
// an empty +0x28 screen name is filled from the "_Init" parameter
// (bfmeGetParamVMZ 0x0046EFA0) through the screen-reference table at
// 0x012F1990 (TheBfmeObject_00C70090, the table _bfme_closeAptScreen erases
// from; _M_find 0x00460B30), whose mapped functor (+8, bfmeGo1043D
// 0x0045F200) is fired; finally a hidden window with status bit 0x10000000 is
// unhidden, a reused record gets rva0045DD90UpdateCoordinatePairs, the window
// is drawn (GameWindowManager::drawWindow 0x0047CBE0) and +0x24 is set.
// The record is viewed only at the offsets this body touches; its full layout
// lives with Rva00463850 in Rva00463850AptWindowCreate.cpp. StringBase<char>
// set(const char*) and isEmpty() are spelled inline as retail inlines them
// here (same specialisations as Win32BIGFileSetName.cpp and
// W3DTreeBufferRva00736940.cpp).
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include <hash_map>
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"
#pragma intrinsic(strcmp, strlen)
template<> inline void StringBase<char>::set(const char *str) { set(str, str ? strlen(str) : 0); }
template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

class BfmeStrVMZ;
char bfmeGetParamVMZ(const char *, const char *, BfmeStrVMZ *);
const char *bfmePathLeafAfterMarker(const char *);
void *Rva00462C10(const char *name);

class Rva0045EF90Object;
struct Rva0045DD90FloatPair;
struct Rva0045DD90Record;
Rva0045EF90Object *Rva00463850(const Rva0045DD90FloatPair *, const Rva0045DD90FloatPair *, const char *, const char *);
extern "C" void rva0045DD90UpdateCoordinatePairs(Rva0045DD90Record *, const Rva0045DD90FloatPair *, const Rva0045DD90FloatPair *);

struct Rva00463E30Record {
	char pad00[0xc];
	AsciiString m_second;
	GameWindow *m_handle;
	char pad14[0x10];
	unsigned char m_value24;
	char pad25[3];
	AsciiString m_last;
};

class BfmeJ1043 { public: void bfmeGo1043D(int a, int b, int c); };
struct Rva00460B30Value { AsciiString m_key; BfmeJ1043 m_functor; };
struct Rva00460B30ExtractKey { const AsciiString &operator()(const Rva00460B30Value &v) const { return v.m_key; } };
typedef _STL::hashtable<Rva00460B30Value, AsciiString, rts::hash<AsciiString>,
	Rva00460B30ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00460B30Value> > Rva00463E30ScreenTable;
class Gen_00C70090Target;
extern Gen_00C70090Target TheBfmeObject_00C70090;
struct Rva00463E30WindowManager : public GameWindowManager { using GameWindowManager::drawWindow; };

void Rva00463E30(const Rva0045DD90FloatPair *a, const Rva0045DD90FloatPair *b, const char *name, const char *params)
{
	const char *leaf = bfmePathLeafAfterMarker(name);
	bool created = false;
	Rva00463E30Record *record = (Rva00463E30Record *)Rva00462C10(leaf);
	if (!record) {
		record = (Rva00463E30Record *)Rva00463850(a, b, name, params);
		if (!record)
			return;
		created = true;
	}
	if (strcmp(record->m_second.str(), name) != 0)
		record->m_second.set(name);
	if (record->m_last.isEmpty()) {
		AsciiString screen;
		bfmeGetParamVMZ(params, "_Init", (BfmeStrVMZ *)&screen);
		Rva00463E30ScreenTable &table = *(Rva00463E30ScreenTable *)&TheBfmeObject_00C70090;
		Rva00463E30ScreenTable::iterator it = table.find(screen);
		if (it != table.end()) {
			(*it).m_functor.bfmeGo1043D((int)leaf, (int)params, (int)record->m_handle);
			record->m_last = (*it).m_key;
		} else if (created) {
			return;
		}
	}
	GameWindow *window = record->m_handle;
	if (!window)
		return;
	if (window->winIsHidden()) {
		if (!(window->winGetStatus() & 0x10000000))
			return;
		window->winHide(false);
	}
	if (!created)
		rva0045DD90UpdateCoordinatePairs((Rva0045DD90Record *)record, a, b);
	((Rva00463E30WindowManager *)TheWindowManager)->drawWindow(window);
	record->m_value24 = 1;
}
