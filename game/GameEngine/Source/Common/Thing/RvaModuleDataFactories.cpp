// cl: /DNDEBUG /MD /EHsc
//
// Two 107-byte module-data factories whose module this repository cannot name.
//
// WHAT THE BYTES SHOW.  Each allocates exactly one block, default-constructs it
// through a __thiscall constructor the ledger already carries, and then, only
// when its one pointer argument is non-null, hands the fresh object and a
// field-parse forwarder to INI::initFromINIMultiProc before returning the
// object.  The `-EHsc` fs:[0] frame and the two unwind-state stores are what
// the `new` expression needs while the constructor may throw.
//
// THE CONSTRUCTORS ARE THE LEDGER'S OWN.  0x00114B50 allocates twelve bytes and
// calls Rva001FABC0 through ILT 0x0001FEB0; 0x00114D70 allocates thirty-two and
// calls Rva001F7810 through ILT 0x0004A426.  Both sizes are exactly the object
// each of those constructors writes, so the classes here are declared with
// those layouts and those names rather than fresh ones -- a REL32 operand is
// copied from retail and proves nothing on its own, so the call has to spell
// the symbol it reaches.
//
// IDENTITY IS NOT RECOVERED.  Both constructors are themselves address-derived,
// and the field-parse forwarders (0x001FABE0, 0x001F7840) are the
// address-derived table registrars in MidTableRegisterForwarders.cpp, so
// nothing in either body names a module.  Do not read the neighbouring named
// factories as evidence: the data and instance factories in this stretch are
// NOT laid out in a fixed order -- CastleMemberBehavior's data factory at
// 0x001145D0 FOLLOWS its instance factory while EnragedBehavior's precedes it,
// and the two module-data constructors those neighbours actually name live at
// 0x00291950 and 0x00205F60, not here.  Each name below is derived from its own
// address.

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class MultiIniFieldParse;
class Gen00850920;

void Rva001FABE0(Gen00850920 *table);
void Rva001F7840(Gen00850920 *table);

class Rva001FABC0
{
public:
	Rva001FABC0();
	virtual void handle();
	char m_gap[4];
	float m_value;
};

class Rva001F7810
{
public:
	Rva001F7810();
	int *m_vtable;
	int m_04;
	int m_08, m_0C, m_10, m_14, m_18, m_1C;
};

// Retail's module-data factories reach INI through initFromINIMultiProc
// (0x00852130), which takes the class's buildFieldParse proc.
class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

// ?rva00114B50@@YAPAXPAVINI@@@Z
void *rva00114B50(INI *ini)
{
	Rva001FABC0 *data = new Rva001FABC0;
	if (ini)
		ini->initFromINIMultiProc(data,
			(void (__cdecl *)(MultiIniFieldParse &))&Rva001FABE0);
	return data;
}

// ?rva00114D70@@YAPAXPAVINI@@@Z
void *rva00114D70(INI *ini)
{
	Rva001F7810 *data = new Rva001F7810;
	if (ini)
		ini->initFromINIMultiProc(data,
			(void (__cdecl *)(MultiIniFieldParse &))&Rva001F7840);
	return data;
}
