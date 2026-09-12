// ??1Rva00592640Owner@@UAE@XZ
// partial score=0.90 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Address-derived: retail 0x005927F0, size 240, dump d_0058b1f0.asm.
// A prior gpt-5.6 attempt (reverse/re_attempts.log, filed under the name
// "Rva00592640/GameClientMember488") recovered this same shape and reached
// 219/240 bytes with the wrong prologue (push ecx + delayed edi save
// instead of retail's sub esp,8 + early esi/edi save + a spilled `this` at
// [esp+0xc]). Real class identity is not recovered here; field names are
// address-derived.
//
//   callees: TheManager (0x012F12CC) vtable slot +0x28 x5 -> release(handle)
//            0x00888BC0 -> ??0BFMERetailAsciiString@@QAE@PBD@Z, matched
//            0x000347D9 (ILT to unmatched FUN_0086def0) x1 -> pinned here as
//              Rva00579160Manager::registerHelpBoxText
//            0x00887940 x1 -> releaseBuffer, matched
//            0x0003FA7B (ILT to unmatched FUN_0098c4c0) x2 -> pinned here as
//              Rva00592640Member::~Rva00592640Member
//            0x00881EB0 -> operator delete, matched
//   string: 0x00D0BFE0 -> "HelpBoxText" (verified against the retail image)
//   globals: 0x012F12CC -> Rva0048EC80TheManager (already pinned)
//            0x012F19E8 -> Rva00579160TheManager (already pinned)

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	unsigned char m_pad[4];
};

// Unrecovered member type shared by m_member1/m_member2; only its destructor
// is ever reached here, through a plain call+operator-delete pair (not a
// scalar deleting destructor), so the type is not polymorphic.
class Rva00592640Member
{
public:
	~Rva00592640Member();
};

// Unrecovered manager type; only the +0x28 virtual slot used here is real.
class Rva0048EC80Manager
{
public:
	virtual void _s00();
	virtual void _s01();
	virtual void _s02();
	virtual void _s03();
	virtual void _s04();
	virtual void _s05();
	virtual void _s06();
	virtual void _s07();
	virtual void _s08();
	virtual void _s09();
	virtual void release(int handle);		// +0x28
};

extern Rva0048EC80Manager *Rva0048EC80TheManager;

class Rva00579160Manager
{
public:
	void registerHelpBoxText(BFMERetailAsciiString *text);
};

extern Rva00579160Manager *Rva00579160TheManager;

class Rva00592640Owner
{
public:
	virtual ~Rva00592640Owner();

private:
	unsigned char m_unreconstructed_04[4];		// +0x04
	Rva00592640Member *m_member8;			// +0x08, deleted second
	Rva00592640Member *m_memberC;			// +0x0c, deleted first
	unsigned char m_unreconstructed_10[4];		// +0x10
	int m_drop1;					// +0x14
	int m_drop2;					// +0x18
	int m_drop3;					// +0x1c
	int m_drop4;					// +0x20
	int m_drop5;					// +0x24
};

Rva00592640Owner::~Rva00592640Owner()
{
	Rva0048EC80TheManager->release(m_drop1);
	Rva0048EC80TheManager->release(m_drop2);
	Rva0048EC80TheManager->release(m_drop3);
	Rva0048EC80TheManager->release(m_drop4);
	Rva0048EC80TheManager->release(m_drop5);

	{
		BFMERetailAsciiString text("HelpBoxText");
		Rva00579160TheManager->registerHelpBoxText(&text);
	}

	delete m_memberC;
	delete m_member8;
}
