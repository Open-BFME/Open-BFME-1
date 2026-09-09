// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2
//
// BFME W3DTreeBuffer destructor variant at retail 0x00736590 (260 bytes).
//
// Identity evidence is the complete owner boundary, not the generated label:
// the 30-byte scalar deleting destructor at 0x007366F0 calls ILT 0x00031052,
// which jumps to this scalar destructor.  The sibling constructor at
// 0x00736720 installs vtable 0x01121608.  Its four emitted slots are the
// deleting destructor 0x007366F0, Snapshot::loadPostProcess at 0x00733E00
// through ILT 0x0001A7D5, Snapshot::getSnapshotName at 0x007366E0 through
// ILT 0x000312BE, and Snapshot::xfer(Xfer *) at 0x007371D0 through ILT
// 0x00049481.  The destructor restores the proven four-slot Snapshot/BfmeBase table
// 0x01073744.  The class spelling remains address-derived because the
// existing destructor identity at 0x007206E0 belongs to W3DShrubBuffer.
//
// The object layout follows the constructor/destructor bytes and the
// established BaseHeightMap reset records: two BfmeHandleCX owning texture references at +b8/+bc,
// 0x28-byte reset-list members at +c0/+e8, 12000 0xe8-byte tree records at
// +1b0, and 64 0x5c-byte type records at +2a7cbc.  The type record's first
// pointer is released inline before the existing BfmeOwnVVC destructor ILT;
// its remaining cleanup is the established 0x00735CC0 body.  The tree-record
// destructor callback is the one-byte retail boundary at 0x00732950.

class TextureClass
{
public:
	void Release_Ref(void);
};

// Canonical owning texture handle; its destructor body is already landed at 0x0005CC00.
class BfmeHandleCX
{
public:
	BfmeHandleCX(void) : m_p(0) {}
	~BfmeHandleCX(void)
	{
		if (m_p != 0)
			m_p->Release_Ref();
	}

	TextureClass *m_p;
};

class Gen_uwm_0094cdf0
{
public:
	~Gen_uwm_0094cdf0(void);

private:
	unsigned char m_body[0x28];
};

class Rva00736590TreeRecord
{
public:
	~Rva00736590TreeRecord(void);

private:
	unsigned char m_body[0xe8];
};

class Rva00736590RefCount
{
public:
	virtual void Delete_This(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

private:
	int m_refCount;
};

class Rva00736590TreeType
{
public:
	~Rva00736590TreeType(void);

	Rva00736590RefCount *m_mesh;

private:
	unsigned char m_body[0x58];
};

// Retail EH state 0 routes through Snapshot's existing destructor body at
// 0x0005C520 via ILT 0x00001C80. The retail base table at 0x01073744 has
// four entries (destructor plus three pure virtual slots), so this local
// facade preserves that ABI count; it is not a new emitted retail table claim.
class Xfer;

// BFME retail Snapshot ABI: virtual destructor, then post-load, name, transfer.
// The public ZH Snapshot.h ordering (crc/xfer/loadPostProcess) is not this
// image's vtable order; the 0x01121608 target bodies prove these three roles.
// The existing BFME base table is pinned as ??_7BfmeBaseVUQ@@6B@ at
// VA 0x01073744.  This C-linkage array is only a typed TU-local view of that
// existing table; its linker alternate name does not define a new table.
extern "C" void *bfmeVftSnapshotBase[4];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshotBase=??_7BfmeBaseVUQ@@6B@")

// novtable suppresses a second local Snapshot vftable.  The base destructor
// restores the proven four-slot BFME base table through the typed external
// view, matching the retail scalar-dtor tail without inventing a Snapshot
// production owner.
class __declspec(novtable) Snapshot
{
public:
	virtual ~Snapshot(void) { *(void **)this = bfmeVftSnapshotBase; }

protected:
	virtual void loadPostProcess(void) = 0;
	virtual const char *getSnapshotName(void) const = 0;
	virtual void xfer(Xfer *xfer) = 0;
};

extern void j_00018403(void);

class Rva00736590W3DTreeBuffer
	: public Snapshot
{
public:
	virtual ~Rva00736590W3DTreeBuffer(void);
	virtual void loadPostProcess(void);
	virtual const char *getSnapshotName(void) const;
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_pad0004[0xb8 - 4];
	BfmeHandleCX m_textureB8;
	BfmeHandleCX m_textureBC;
	Gen_uwm_0094cdf0 m_resetListC0;
	Gen_uwm_0094cdf0 m_resetListE8;
	unsigned char m_pad0110[0x1b0 - 0x110];
	Rva00736590TreeRecord m_trees[0x2ee0];
	unsigned char m_pad2a7cb0[0xc];
	Rva00736590TreeType m_treeTypes[64];
	unsigned char m_pad2a93bc[0x2a9904 - 0x2a93bc];
	BfmeHandleCX m_treeTexture;
};

// Every indirect vtable relocation below is to the retail ILT entry, rather
// than to a new neutral alias or an invented implementation.  The two array
// callbacks are the exact compiler ABI used by the retail vector helpers.
#pragma comment(linker, "/alternatename:??1Rva00736590TreeRecord@@QAE@XZ=?j_0003a495@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00736590TreeType@@QAE@XZ=?j_00008247@@YAXXZ")
#pragma comment(linker, "/alternatename:?loadPostProcess@Rva00736590W3DTreeBuffer@@UAEXXZ=?j_0001a7d5@@YAXXZ")
#pragma comment(linker, "/alternatename:?getSnapshotName@Rva00736590W3DTreeBuffer@@UBEPBDXZ=?j_000312be@@YAXXZ")
#pragma comment(linker, "/alternatename:?xfer@Rva00736590W3DTreeBuffer@@UAEXPAVXfer@@@Z=?j_00049481@@YAXXZ")
// The compiler emits a 30-byte scalar deleting destructor (strong G symbol).
// Its weak vector-deleting E symbol falls back to that G body; the retail
// vtable reaches the scalar deleting destructor through ILT 0x0003CECA.
// This body is verified and claimed at 0x007366F0 alongside the destructor.

// ??1Rva00736590W3DTreeBuffer@@UAE@XZ
Rva00736590W3DTreeBuffer::~Rva00736590W3DTreeBuffer(void)
{
	typedef void (Rva00736590W3DTreeBuffer::*FreeThunk)(void);
	union {
		void (*function)(void);
		FreeThunk member;
	} freeCast;
	freeCast.function = j_00018403;
	(this->*freeCast.member)();

	for (int i = 0; i < 64; ++i) {
		Rva00736590TreeType *type = m_treeTypes + i;
		if (type->m_mesh != 0) {
			type->m_mesh->Release_Ref();
			type->m_mesh = 0;
		}
	}
}
