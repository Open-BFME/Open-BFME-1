// ?Rva00462D40@@YAXPAX@Z
// ?Rva00462CB0@@YAXPAX@Z
// stlport
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /I. /Iinputs/vendor/stlport /DNDEBUG /DWIN32 /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Retail 0x00462D40, 126 bytes (RET at +0x7D, INT3 after): the cdecl Apt
// callback that matched registerAptCallbacks00464080 binds as
// "DisableComponents" through ILT 0x00049C47
// (targets/game/reverse/identity_evidence/00462d40-disablecomponents-callback.md).
// Its C++ spelling is unknown, so the name keeps the address. A non-empty
// component name runs the matched for_each 0x00462710 over the window table
// at 0x012F19A4 (TheBfmeObject_00C700A0) with a disabling Rva0045F0A0
// functor; otherwise g_bfmeDoneSJA is set and focus is cleared.
// The functor's name comes from the normalizer 0x0046F800, whose ledger name
// bfmeDoBSD returns the BFMERetailAsciiString placeholder type; it is spelled
// here as an AsciiString with that class name. The table is reached through
// inline begin()/end() members: calling hashtable::begin directly picks ECX
// instead of retail's EAX for the for_each result slot at +0x49.
#define _STLP_NO_EXCEPTIONS 1
#include "PreRTS.h"
#include <algorithm>
#include <hash_map>
#include "GameClient/GameWindowManager.h"

class BFMERetailAsciiString : public AsciiString {};
BFMERetailAsciiString bfmeDoBSD(void *what);

struct Rva0045F0A0Input
{
	AsciiString m_key;
	unsigned char m_padding00[0x0c];
	AsciiString m_name;
	void *m_unit;
};

class Rva0045F0A0
{
public:
	Rva0045F0A0(char enabled, void *name) : m_enabled(enabled), m_name(bfmeDoBSD(name)) {}
	Rva0045F0A0(const Rva0045F0A0 &other) : m_enabled(other.m_enabled), m_name(other.m_name) {}
	~Rva0045F0A0() {}

	void process(Rva0045F0A0Input *input);
	void operator()(Rva0045F0A0Input &input) { process(&input); }

private:
	char m_enabled;
	unsigned char m_padding01[3];
	BFMERetailAsciiString m_name;
};

struct Rva0045F0A0ExtractKey
{
	const AsciiString &operator()(const Rva0045F0A0Input &value) const { return value.m_key; }
};

typedef _STL::hashtable<Rva0045F0A0Input, AsciiString, rts::hash<AsciiString>,
	Rva0045F0A0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0045F0A0Input> > Rva0045F0A0Table;

struct Rva012F19A4Table
{
	Rva0045F0A0Table m_table;
	Rva0045F0A0Table::iterator begin() { return m_table.begin(); }
	Rva0045F0A0Table::iterator end() { return m_table.end(); }
};

class Gen_00C700A0Target;
extern Gen_00C700A0Target TheBfmeObject_00C700A0;
extern char g_bfmeDoneSJA;
extern GameWindowManager *TheWindowManager;

void Rva00462D40(void *name)
{
	if (name && *(const char *)name) {
		Rva012F19A4Table &table = *(Rva012F19A4Table *)&TheBfmeObject_00C700A0;
		_STL::for_each(table.begin(), table.end(), Rva0045F0A0(0, name));
	} else {
		g_bfmeDoneSJA = 1;
		TheWindowManager->winSetFocus(0);
	}
}

// Retail 0x00462CB0, 110 bytes (RETs at +0x62 and +0x6D, INT3 after): the
// "EnableComponents" twin that the same registerAptCallbacks00464080 binds
// through ILT 0x0003DCA3. Same walk with an enabling functor; an empty name
// clears g_bfmeDoneSJA and leaves focus alone.
void Rva00462CB0(void *name)
{
	if (name && *(const char *)name) {
		Rva012F19A4Table &table = *(Rva012F19A4Table *)&TheBfmeObject_00C700A0;
		_STL::for_each(table.begin(), table.end(), Rva0045F0A0(1, name));
	} else {
		g_bfmeDoneSJA = 0;
	}
}
