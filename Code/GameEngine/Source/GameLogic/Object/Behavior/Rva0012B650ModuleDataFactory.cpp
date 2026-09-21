// cl: /DNDEBUG /MD /EHs-c-
//
// The module-data factory at retail 0x0012B650, a complete carved extent.
//
// WHAT THE BYTES SHOW.  It allocates 0x88 bytes, constructs the class whose
// out-of-line constructor is the matched Rva0012B580ModuleData at 0x0012B580 --
// same 0x0108F4F0 vftable, same UpgradeModuleDataSub subobject at +8 through
// ILT 0x0000F0A6, same two three-float runs at +0x70 and +0x7C -- and then,
// only when its INI argument is non-null, hands the object and a field-parse
// proc to initFromINIMultiProc.  The constructor is inlined here; the shared
// subobject's is not, which is what fixes the base at +8.
//
// The frame has no fs:[0] registration, so this translation unit is -EHs-c-,
// unlike the 107-byte factories that new a class whose constructor can throw.
//
// IDENTITY IS NOT RECOVERED, and the reason is worth recording.  The field-parse
// proc it passes is 0x002D7DA0, which the ledger names
// ?buildFieldParse@StatusBitsUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// and 0x0108F4F0 is the vftable the ledger names ??_7StatusBitsUpgradeModuleData.
// Both point at StatusBitsUpgrade.  Against that, the subobject constructor this
// body calls at +8 is itself ledger-named ??0StatusBitsUpgradeModuleData@@QAE@XZ
// (0x00129C10, and noted there as ICF-folded with StealthUpgradeModuleData), so
// the outer class cannot also be that class and one of the two names is wrong.
// The constructor of this very class at 0x0012B580 was landed under an
// address-derived name on the same evidence, so this follows it.  Note also that
// ?friend_newModuleData@StatusBitsUpgrade@@SAPAVModuleData@@PAVINI@@@Z currently
// sits on 0x00118020 as an ICF alias of DozerAIUpdate's factory and claims no
// bytes of its own; if the conflict above is ever resolved, this body is where
// that name belongs.

#include <string.h>

class MultiIniFieldParse;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class __declspec(novtable) Rva0012B580PrimaryBase
{
public:
	virtual void primarySlot();

private:
	int m_primaryData;
};

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();

private:
	char m_upgradeData[0x68];
};

struct Rva0012B580Vector
{
	float x;
	float y;
	float z;
};

class Rva0012B580ModuleData : public Rva0012B580PrimaryBase, public UpgradeModuleDataSub
{
public:
	Rva0012B580ModuleData();
	virtual void primarySlot();

private:
	Rva0012B580Vector m_first;
	Rva0012B580Vector m_second;
};

Rva0012B580ModuleData::Rva0012B580ModuleData()
{
	memset(&m_first, 0, sizeof(m_first));
	memset(&m_second, 0, sizeof(m_second));
}

class StatusBitsUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

class INI
{
public:
	void initFromINIMultiProc(void *what,
		void (__cdecl *buildFieldParse)(MultiIniFieldParse &));
};

// ?rva0012B650@@YAPAXPAVINI@@@Z
void *rva0012B650(INI *ini)
{
	Rva0012B580ModuleData *data = new Rva0012B580ModuleData;
	if (ini)
		ini->initFromINIMultiProc(data,
			&StatusBitsUpgradeModuleData::buildFieldParse);
	return data;
}
