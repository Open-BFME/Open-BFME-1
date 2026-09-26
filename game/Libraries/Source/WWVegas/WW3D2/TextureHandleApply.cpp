// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BFME's render-state texture slots are four-byte owning handles.  The matched
// DX8Wrapper::Apply_Render_State_Changes caller passes the address of a slot,
// rather than the pointed-to texture, to this nonvirtual handle operation.

class TextureClass;
class SurfaceClass;
struct IDirect3DSurface8;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

template<class T>
class RefCountPtr
{
public:
	void Apply(unsigned int stage);
	SurfaceClass Rva0090DDC0_Get_Surface_Level(unsigned int level) const;
	unsigned int Get_Texture_Memory_Usage() const;

private:
	T *Referent;
};

// BFME's SurfaceClass is a four-byte owning wrapper around the COM surface.
// The level accessor returns it by value: retail passes a hidden destination
// pointer and destroys that local after querying its byte size.  The two
// RVA-named methods stay neutral because their call sites prove these ABIs but
// do not expose the original lexical method names.
class SurfaceClass
{
public:
	~SurfaceClass();
	unsigned int Rva008FCA30_Surface_Byte_Size() const;

private:
	IDirect3DSurface8 *m_d3dSurface;
};

class Debug_Statistics
{
public:
	static void Record_Texture(RefCountPtr<TextureClass> const &texture);
};

// The pointee at +0x14 and its slot-zero call are directly visible in retail.
// Its broader class identity is not, so keep this TU-local view neutral.
class TextureStateView0090E030
{
public:
	virtual void Apply(unsigned int stage) = 0;
};

// Only the portion of the retail texture ABI used here is exposed.  The three
// named slots are established by this body and the adjacent handle accessors:
// +0x28 tests initialization, +0x2c initializes, and +0x3c applies the
// texture-specific state after TextureD3DState::Apply.
class TextureClass
{
public:
	virtual void Slot_00() = 0;
	virtual void Slot_04() = 0;
	virtual void Slot_08() = 0;
	virtual void Slot_0C() = 0;
	virtual void Slot_10() = 0;
	virtual void Slot_14() = 0;
	virtual void Slot_18() = 0;
	virtual void Slot_1C() = 0;
	virtual void Slot_20() = 0;
	virtual void Slot_24() = 0;
	virtual bool Is_Initialized() = 0;
	virtual void Init() = 0;
	virtual void Slot_30() = 0;
	virtual void Slot_34() = 0;
	virtual void Slot_38() = 0;
	virtual void Slot_3C_Apply(unsigned int stage) = 0;

private:
	unsigned char m_beforeD3DState[0x10];
	TextureStateView0090E030 *m_state14;
	unsigned char m_beforeMipLevelCount[0x18];
	unsigned int m_mipLevelCount;

	friend class RefCountPtr<TextureClass>;
};

// This is the same Direct3D8 interface view and the same four globals already
// verified by Rva006C9270ResetTextureStages.cpp.  In this BFME interface,
// SetTexture is slot 65 (+0x104).
class Rva006C9270Texture
{
public:
	virtual void __stdcall QueryInterface() = 0;
	virtual void __stdcall AddRef() = 0;
	virtual void __stdcall Release() = 0;
};

#define BFME_D3D_SLOT(n) virtual void __stdcall Slot_##n() = 0
class Rva006C9270Device
{
public:
	BFME_D3D_SLOT(00); BFME_D3D_SLOT(01); BFME_D3D_SLOT(02); BFME_D3D_SLOT(03);
	BFME_D3D_SLOT(04); BFME_D3D_SLOT(05); BFME_D3D_SLOT(06); BFME_D3D_SLOT(07);
	BFME_D3D_SLOT(08); BFME_D3D_SLOT(09); BFME_D3D_SLOT(10); BFME_D3D_SLOT(11);
	BFME_D3D_SLOT(12); BFME_D3D_SLOT(13); BFME_D3D_SLOT(14); BFME_D3D_SLOT(15);
	BFME_D3D_SLOT(16); BFME_D3D_SLOT(17); BFME_D3D_SLOT(18); BFME_D3D_SLOT(19);
	BFME_D3D_SLOT(20); BFME_D3D_SLOT(21); BFME_D3D_SLOT(22); BFME_D3D_SLOT(23);
	BFME_D3D_SLOT(24); BFME_D3D_SLOT(25); BFME_D3D_SLOT(26); BFME_D3D_SLOT(27);
	BFME_D3D_SLOT(28); BFME_D3D_SLOT(29); BFME_D3D_SLOT(30); BFME_D3D_SLOT(31);
	BFME_D3D_SLOT(32); BFME_D3D_SLOT(33); BFME_D3D_SLOT(34); BFME_D3D_SLOT(35);
	BFME_D3D_SLOT(36); BFME_D3D_SLOT(37); BFME_D3D_SLOT(38); BFME_D3D_SLOT(39);
	BFME_D3D_SLOT(40); BFME_D3D_SLOT(41); BFME_D3D_SLOT(42); BFME_D3D_SLOT(43);
	BFME_D3D_SLOT(44); BFME_D3D_SLOT(45); BFME_D3D_SLOT(46); BFME_D3D_SLOT(47);
	BFME_D3D_SLOT(48); BFME_D3D_SLOT(49); BFME_D3D_SLOT(50); BFME_D3D_SLOT(51);
	BFME_D3D_SLOT(52); BFME_D3D_SLOT(53); BFME_D3D_SLOT(54); BFME_D3D_SLOT(55);
	BFME_D3D_SLOT(56); BFME_D3D_SLOT(57); BFME_D3D_SLOT(58); BFME_D3D_SLOT(59);
	BFME_D3D_SLOT(60); BFME_D3D_SLOT(61); BFME_D3D_SLOT(62); BFME_D3D_SLOT(63);
	BFME_D3D_SLOT(64);
	virtual long __stdcall SetTexture(unsigned int stage, Rva006C9270Texture *texture) = 0;
};
#undef BFME_D3D_SLOT

extern Rva006C9270Device *Rva01340534Device;
extern Rva006C9270Texture *Rva0133F478Textures[];
extern unsigned int Rva01340594DX8Calls;
extern unsigned int Rva01340560TextureChanges;

static __forceinline void Set_DX8_Texture(unsigned int stage, Rva006C9270Texture *texture)
{
	if (stage >= 8)
	{
		Rva01340534Device->SetTexture(stage, texture);
		++Rva01340594DX8Calls;
		return;
	}

	if (Rva0133F478Textures[stage] == texture)
		return;
	if (Rva0133F478Textures[stage] != 0)
		Rva0133F478Textures[stage]->Release();
	Rva0133F478Textures[stage] = texture;
	if (Rva0133F478Textures[stage] != 0)
		Rva0133F478Textures[stage]->AddRef();
	Rva01340534Device->SetTexture(stage, texture);
	++Rva01340594DX8Calls;
	++Rva01340560TextureChanges;
}

template<>
void RefCountPtr<TextureClass>::Apply(unsigned int stage)
{
	Debug_Statistics::Record_Texture(*this);
	TextureClass *texture = Referent;
	if (texture == 0)
	{
		Set_DX8_Texture(stage, 0);
		return;
	}

	if (!texture->Is_Initialized())
		texture->Init();
	texture->m_state14->Apply(stage);
	texture->Slot_3C_Apply(stage);
}

template<>
unsigned int RefCountPtr<TextureClass>::Get_Texture_Memory_Usage() const
{
	TextureClass *texture = Referent;
	if (texture == 0)
		return 0;
	if (!texture->Is_Initialized())
	{
		// This zero-code compiler fence keeps MSVC 7.1's shared guard epilogue
		// ahead of the EH-bearing surface path, as it is in the retail TU.
		_ReadWriteBarrier();
		return 0;
	}

	unsigned int size = Rva0090DDC0_Get_Surface_Level(0).Rva008FCA30_Surface_Byte_Size();
	if (texture->m_mipLevelCount != 1)
		size = static_cast<unsigned int>(static_cast<float>(size) * 1.3f);
	return size;
}
