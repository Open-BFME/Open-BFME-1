// Five __thiscall constructors of classes whose only work is one base
// constructor at +8, their own vptr, and a single zeroed member at +0x70:
//
//     push esi / mov esi,ecx / lea ecx,[esi+8] / call <REL32>
//     mov dword ptr [esi],<VFTABLE> / mov <dword|byte> ptr [esi+70h],0
//     mov eax,esi / pop esi / ret
//
// WHAT THE BYTES SHOW.  The base runs FIRST and the vptr store follows it, and
// MSVC 7.1 always writes the vptr after the base constructors and before any
// member initialiser -- so the thing constructed at +8 is a BASE SUB-OBJECT,
// not a member.  A base that does not start at offset 0 means the vptr at 0 was
// introduced by the derived class itself and pushed the bases down; the four
// bytes between the vptr and the base at +8 are a second, constructor-less base
// whose contents the bytes do not describe.  The trailing store is a `dword` in
// three members and a `byte` in two, which is the only thing separating them.
//
// ONE BASE, FIVE VFTABLES.  Every site calls the same thunk 0x0000F0A6, already
// pinned in targets/game/reverse/symbols.csv as the UpgradeModuleData sub-object constructor,
// and each member stores a different vftable address -- five distinct types.
//
// IDENTITY IS NOT RECOVERED.  Derived names are address-derived.  The base's
// size is fixed at 0x68 only because the derived member lands at 0x70.

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	char m_body[ 0x68 ];
};

class GenUpgradeSubLead
{
public:
	void *m_slot;
};

#define BFME_UPGRADE_SUB_CTOR( NAME, TAIL )                               \
	class NAME : public GenUpgradeSubLead, public UpgradeModuleDataSub    \
	{                                                                     \
	public:                                                               \
		NAME();                                                           \
		virtual void keep();                                              \
		TAIL m_tail;                                                      \
	};                                                                    \
	NAME::NAME()                                                          \
	{                                                                     \
		m_tail = 0;                                                       \
	}

// @??0Rva0012B140@@QAE@XZ 0x0012B140
BFME_UPGRADE_SUB_CTOR( Rva0012B140, int )
// @??0Rva0012B880@@QAE@XZ 0x0012B880
BFME_UPGRADE_SUB_CTOR( Rva0012B880, int )
// @??0Rva0012B9B0@@QAE@XZ 0x0012B9B0
BFME_UPGRADE_SUB_CTOR( Rva0012B9B0, int )
// @??0Rva0012B380@@QAE@XZ 0x0012B380
BFME_UPGRADE_SUB_CTOR( Rva0012B380, bool )
// @??0Rva0012B480@@QAE@XZ 0x0012B480
BFME_UPGRADE_SUB_CTOR( Rva0012B480, bool )
