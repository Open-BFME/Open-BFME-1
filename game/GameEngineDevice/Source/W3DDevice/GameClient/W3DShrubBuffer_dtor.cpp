// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// W3DShrubBuffer destructor, retail 0x007206E0: clearAllTrees (0x0071C7E0), freeTreeBuffers
// (0x0071C2D0), then the members at +0x1450 to +0x1E3914 unwind in reverse order.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref(void);
};

class Rva007206E0TextureRef
{
public:
	Rva007206E0TextureRef(void) : m_p(0) {}
	~Rva007206E0TextureRef(void)
	{
		if (m_p)
			m_p->Release_Ref();
	}

	TextureBaseClass *m_p;
};

// The BFME reset-list object is 0x28 bytes here.  Its destructor is the
// already matched 0x0094CDF0 body; the larger opaque tail preserves the
// W3DShrubBuffer offsets without inventing its node representation.
class Gen_uwm_0094cdf0
{
public:
	~Gen_uwm_0094cdf0(void);

private:
	unsigned char m_body[0x28];
};

// The tree-type element destructor is reached through the existing ILT at
// 0x00432CF9 (which targets the matched 0x0071EA00 destructor).
class TTreeType
{
public:
	~TTreeType(void);

private:
	unsigned char m_body[0x5C];
};

// The base class is retail's Snapshot.  Its vtable is pinned at 0x00C73744
// (deleting destructor, crc, xfer, loadPostProcess; symbols.csv, 63
// byte-verified references) and its virtual destructor is the matched 7-byte
// body at 0x0005C520.  Naming the class is what removes the old
// `_bfmeVftSnapshot` stand-in: the compiler's own base-vtable store in
// ~W3DShrubBuffer then targets `??_7Snapshot@@6B@` by itself, and the scalar
// deleting destructor calls `??1Snapshot@@UAE@XZ`.  The inline destructor keeps
// that call inlined, exactly as retail has it.  This TU therefore emits its own
// COMDAT copies of `??1Snapshot@@UAE@XZ`, `??_GSnapshot@@UAEPAXI@Z` and
// `??_7Snapshot@@6B@`, byte-identical to
// game/GameEngine/Source/Common/SubsystemSnapshotStateOwnerConstructor.cpp,
// which stays their ledger source.
class Snapshot
{
public:
	virtual ~Snapshot(void) {}

	virtual void crc(void) = 0;
	virtual void xfer(void) = 0;
	virtual void loadPostProcess(void) = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DTreeBuffer.h
class W3DShrubBuffer : public Snapshot
{
public:
	virtual ~W3DShrubBuffer(void);
	void clearAllTrees(void);
	void freeTreeBuffers(void);

private:
	unsigned char m_pad0004[0x1450 - 4];
	Rva007206E0TextureRef m_texture1450;
	Rva007206E0TextureRef m_texture1454;
	Gen_uwm_0094cdf0 m_resetList1458;
	Gen_uwm_0094cdf0 m_resetList1480;
	unsigned char m_pad14A8[0x1E1CD4 - 0x14A8];
	TTreeType m_treeTypes[64];
	unsigned char m_pad1E33D4[0x1E3914 - 0x1E33D4];
	Rva007206E0TextureRef m_treeTexture;
};

// The 64-element m_treeTypes array is destroyed through the CRT array-dtor
// helper, which takes the ELEMENT DESTRUCTOR'S ADDRESS as a 32-bit immediate
// (`push offset ??1TTreeType@@QAE@XZ; push 40h; push 5Ch; lea; push; call
// ??_M@YGXPAXIHP6EX0@Z@Z`, at +0x4b and again in the funclet).  The compiler
// always materialises that address from the element type's own mangled
// destructor name, so no clean C++ can make it the ILT at 0x00432CF9, and the
// alternate name stays.  Removing it would need a hand-written push of the
// thunk plus a call to the CRT helper, which no declaration can name.
#pragma comment(linker, "/alternatename:??1TTreeType@@QAE@XZ=?j_00032cf9@@YAXXZ")
// ??1W3DShrubBuffer@@UAE@XZ
W3DShrubBuffer::~W3DShrubBuffer(void)
{
	clearAllTrees();
	freeTreeBuffers();
}
