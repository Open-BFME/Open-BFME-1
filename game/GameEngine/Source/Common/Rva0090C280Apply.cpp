// cl: /DNDEBUG /MD /EHsc

// The matched constructor at 0x0090C280 and the file-loader witness establish
// the opaque 0x48-byte owner behind vtable 0x0113A56C.  The vtable gives Apply
// slot 0 and Init slot 2.  The SetTexture helper below is the independently
// inspected WW3D2 cache/device sequence, kept inline so its nullable
// parameter retains the retail AddRef guard.

struct Rva006C9270TextureVtbl
{
	void *QueryInterface;
	unsigned long (__stdcall *AddRef)(void *self);
	unsigned long (__stdcall *Release)(void *self);
};

struct Rva006C9270Texture
{
	Rva006C9270TextureVtbl *lpVtbl;
};

struct Rva01340534DeviceVtbl
{
	void *reserved[65];
	long (__stdcall *SetTexture)(void *self, unsigned int stage,
		Rva006C9270Texture *texture);
};

struct Rva01340534Device
{
	Rva01340534DeviceVtbl *lpVtbl;
};

extern unsigned char Rva012D6D90Byte;
extern Rva01340534Device *Rva01340534DeviceGlobal;
extern unsigned int Rva01340594DX8Calls;
extern unsigned int Rva01340560TextureChanges;
extern Rva006C9270Texture *Rva0133F478Textures[8];

static __forceinline void Rva0090C280SetTexture(unsigned int stage,
	Rva006C9270Texture *texture)
{
	if (stage >= 8)
	{
		Rva01340534DeviceGlobal->lpVtbl->SetTexture(
			Rva01340534DeviceGlobal, stage, texture);
		++Rva01340594DX8Calls;
		return;
	}
	if (Rva0133F478Textures[stage] != texture)
	{
		if (Rva0133F478Textures[stage])
			Rva0133F478Textures[stage]->lpVtbl->Release(
				Rva0133F478Textures[stage]);
		Rva0133F478Textures[stage] = texture;
		if (texture)
			texture->lpVtbl->AddRef(texture);
		Rva01340534DeviceGlobal->lpVtbl->SetTexture(
			Rva01340534DeviceGlobal, stage, texture);
		++Rva01340594DX8Calls;
		++Rva01340560TextureChanges;
	}
}

class Rva0090C280
{
public:
	virtual void Apply(unsigned int stage);
	virtual void slot04(unsigned int flags);
	virtual void Init();

	unsigned char Initialized;
	unsigned char m_pad05[3];
	Rva006C9270Texture *m_d3dBaseTexture;
};

void Rva0090C280::Apply(unsigned int stage)
{
	if (!Initialized)
		Init();

	if (Rva012D6D90Byte && m_d3dBaseTexture != 0)
		Rva0090C280SetTexture(stage, m_d3dBaseTexture);
	else
		Rva0090C280SetTexture(stage, 0);
}
