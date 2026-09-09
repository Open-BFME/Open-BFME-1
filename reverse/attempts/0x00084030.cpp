// ??1GlobalData@@UAE@XZ
// partial score=0.86 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x00084030: GlobalData::~GlobalData().
//
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
// upstream body: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/GlobalData.cpp (~GlobalData)
//   if (m_weaponBonusSet) m_weaponBonusSet->deleteInstance();
//   if (m_theOriginal == this) { m_theOriginal = NULL; TheWritableGlobalData = NULL; }
// Retail inlines deleteInstance() into a direct ::operator delete(ptr) (no
// vtable call before it), so m_weaponBonusSet's pointee needs no destructor
// modelled here.
//
// Everything below m_weaponBonusSet is the compiler-generated member
// destructor chain (hence the SEH frame with per-member unwind states); only
// the destructible members are modelled by real type, byte gaps between them
// are raw padding. Several members are destroyed through retail's
// incremental-link ILT thunks rather than the real callee address, so they
// are modelled as declare-only wrapper types pinned directly to the thunk
// RVA (same technique BFMERetailAsciiString already uses for its own
// releaseBuffer/dtor thunks).

// Minimal local SubsystemInterface stand-in (vtable + 4-byte AsciiString
// name = 8 bytes, matching subsystem_interface.h) -- avoided including the
// real header so it does not pull in the real ascii_string.h/string_base.h
// and collide with the hand-rolled StringBase shim below.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	void *m_name;
};

// BFMERetailAsciiString/UnicodeString mirror the shim used across this
// project (e.g. BfmeAptScreenLanLobbyDestructor.cpp) -- their releaseBuffer
// and dtor route through retail's ILT thunks, not AsciiString's real body.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();
private:
	void *m_data;
};

// The m_arr9c[4] array's element dtor is called through the vector destructor
// iterator (??_M), which needs the REAL ??1BFMERetailAsciiString@@QAE@XZ ILT
// thunk address (0xD828), not releaseBuffer's own address -- so this element
// spelling stays declare-only and is pinned to that thunk directly, instead
// of sharing BFMERetailAsciiString's inline releaseBuffer() body.
class GdAsciiStringElem
{
public:
	~GdAsciiStringElem();
private:
	void *m_data;
};

// StringBase<unsigned short>::~StringBase() (private) is ICF-folded onto
// releaseBuffer@StringBase<G> in retail (reverse/symbols.csv:
// ??1?$StringBase@G@@AAE@XZ,0x008881D0), which is exactly what this member's
// cleanup site calls directly.
template <typename T> class StringBase
{
	friend class UnicodeString;

private:
	StringBase();
	~StringBase();

	void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	~UnicodeString() {}
};

// Declare-only wrappers: each destructor is pinned straight to the ILT
// thunk retail calls at this member's cleanup site (reverse/symbols.csv),
// not to the real callee body.
class GdAttrHandleSlot
{
public:
	~GdAttrHandleSlot();
private:
	int m_handle;
};

class GdUpgradeVecSlot
{
public:
	~GdUpgradeVecSlot();
private:
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
};

class GdCoordSlot
{
public:
	~GdCoordSlot();
private:
	float m_x, m_y, m_z;
};

class GdElemSlot
{
public:
	~GdElemSlot();
private:
	char m_pad[36];
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;				///< retail [0x012ED5C8]
extern GlobalData *g_bfmeGlobalDataOriginal;			///< retail [0x012ED5CC] (static GlobalData::m_theOriginal)

class GlobalData : public SubsystemInterface
{
public:
	virtual ~GlobalData();

private:
	BFMERetailAsciiString m_s08, m_s0c, m_s10, m_s14;			// +0x08..+0x18
	unsigned char m_pad18[0x94 - 0x18];
	BFMERetailAsciiString m_s94;								// +0x94
	unsigned char m_pad98[0x9c - 0x98];
	GdAsciiStringElem m_arr9c[4];								// +0x9c (16 bytes)
	unsigned char m_padAc[0x200 - 0xac];
	BFMERetailAsciiString m_s200;								// +0x200
	unsigned char m_pad204[0x20c - 0x204];
	BFMERetailAsciiString m_s20c;								// +0x20c
	unsigned char m_pad210[0x224 - 0x210];
	GdElemSlot m_elemD0[18], m_elemD1[18], m_elemD2[18];		// +0x224, +0x4ac, +0x734 (0x288 each)
	unsigned char m_pad9bc[0xa04 - 0x9bc];
	GdCoordSlot m_coords[3];									// +0xa04 (0x24)
	unsigned char m_padA28[0xaa4 - 0xa28];
	BFMERetailAsciiString m_sAa4, m_sAa8;						// +0xaa4, +0xaa8
	unsigned char m_padAac[0xab8 - 0xaac];
	BFMERetailAsciiString m_sAb8, m_sAbc;						// +0xab8, +0xabc
	unsigned char m_padAc0[0xac4 - 0xac0];
	BFMERetailAsciiString m_sAc4, m_sAc8;						// +0xac4, +0xac8
	unsigned char m_padAcc[0xad0 - 0xacc];
	BFMERetailAsciiString m_sAd0, m_sAd4;						// +0xad0, +0xad4
	unsigned char m_padAd8[0xadc - 0xad8];
	BFMERetailAsciiString m_sAdc, m_sAe0;						// +0xadc, +0xae0
	unsigned char m_padAe4[0xae8 - 0xae4];
	BFMERetailAsciiString m_sAe8, m_sAec;						// +0xae8, +0xaec
	unsigned char m_padAf0[0xaf4 - 0xaf0];
	BFMERetailAsciiString m_sAf4, m_sAf8;						// +0xaf4, +0xaf8
	unsigned char m_padAfc[0xb00 - 0xafc];
	BFMERetailAsciiString m_sB00, m_sB04;						// +0xb00, +0xb04
	unsigned char m_padB08[0xb80 - 0xb08];
	BFMERetailAsciiString m_sB80, m_sB84;						// +0xb80, +0xb84
	unsigned char m_padB88[0xb94 - 0xb88];
	void *m_weaponBonusSet;									// +0xb94
	unsigned char m_padB98[0xbb0 - 0xb98];
	BFMERetailAsciiString m_sBb0;								// +0xbb0
	unsigned char m_padBb4[0xc40 - 0xbb4];
	BFMERetailAsciiString m_sC40;								// +0xc40
	GdUpgradeVecSlot m_vecC44;									// +0xc44 (0xc)
	unsigned char m_padC50[0xd8c - 0xc50];
	BFMERetailAsciiString m_sD8c, m_sD90;						// +0xd8c, +0xd90
	unsigned char m_padD94[0xdb8 - 0xd94];
	BFMERetailAsciiString m_sDb8;								// +0xdb8
	unsigned char m_padDbc[0xdc0 - 0xdbc];
	BFMERetailAsciiString m_sDc0, m_sDc4;						// +0xdc0, +0xdc4
	unsigned char m_padDc8[0xdd0 - 0xdc8];
	BFMERetailAsciiString m_sDd0;								// +0xdd0
	unsigned char m_padDd4[0xedc - 0xdd4];
	GdAttrHandleSlot m_attrEdc;									// +0xedc (4)
	unsigned char m_padEe0[0x11e0 - 0xee0];
	GdUpgradeVecSlot m_vec11e0;									// +0x11e0 (0xc)
	unsigned char m_pad11ec[0x1200 - 0x11ec];
	BFMERetailAsciiString m_s1200, m_s1204;					// +0x1200, +0x1204
	GdUpgradeVecSlot m_vec1208;									// +0x1208 (0xc)
	unsigned char m_pad1214[0x121c - 0x1214];
	GdAttrHandleSlot m_attr121c;								// +0x121c (4)
	unsigned char m_pad1220[0x127c - 0x1220];
	BFMERetailAsciiString m_s127c;								// +0x127c
	UnicodeString m_u1280;										// +0x1280
	BFMERetailAsciiString m_s1284, m_s1288;					// +0x1284, +0x1288
};

// ??1GlobalData@@UAE@XZ
GlobalData::~GlobalData()
{
	if (m_weaponBonusSet)
		::operator delete(m_weaponBonusSet);
	m_weaponBonusSet = 0;

	if (g_bfmeGlobalDataOriginal == this)
	{
		g_bfmeGlobalDataOriginal = 0;
		TheWritableGlobalData = 0;
	}
}
