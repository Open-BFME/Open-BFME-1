// cl: /DNDEBUG /MD /EHsc
// Retail 0x007D65E0: filter vtable 0x01128B24 slot 0 via ILT 0x004415A6.
// The matched Rva007D6B70 constructor installs this vtable; original class name unknown.
// Same EXVapor/ring.nvp resources as Rva007DB820::init; one sample vector.

struct Surface;
struct Texture;
struct Device;

struct TextureVtable {
	char p0[8];
	unsigned long (__stdcall *Release)(Texture *);
	char p1[0x48 - 12];
	long (__stdcall *GetSurfaceLevel)(Texture *, unsigned, Surface **);
};

struct Texture {
	TextureVtable *v;
};

struct DeviceVtable {
	char p[0x5c];
	long (__stdcall *CreateTexture)(
		Device *, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned,
		Texture **, void *);
};

struct Device {
	DeviceVtable *v;
};

extern Device *HighlightDevice;
extern unsigned HighlightVertexSupport;
extern unsigned HighlightPixelSupport;

int bfmeCheck986B();
void bfmeCopyCuSnap(void *, void *);

class TextureClass {
public:
	void Release_Ref();
};

class BFMEWaterTrackTexture {
public:
	void Release_Ref();
};

class BFMEWaterTrackTextureHandle {
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle()
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char *, int, int);

class Rva007D6B70TextureRef {
public:
	TextureClass *p;

	__forceinline void bind(const BFMEWaterTrackTextureHandle &t)
	{
		if (t.m_texture)
			++*(unsigned short *)((char *)t.m_texture + 4);
		if (p)
			((BFMEWaterTrackTexture *)p)->Release_Ref();
		p = t.m_texture;
	}
};

class BfmeShaderLoader16 {
public:
	static int LoadAndCreateD3DShader(const char *, unsigned *);
};

struct Rva007D6B70Sample {
	float float_0;
	float float_4;
	float weight;
};

struct Rva007D6B70Samples {
	Rva007D6B70Sample *begin;
	Rva007D6B70Sample *end;
	Rva007D6B70Sample *capacity;

	unsigned size()
	{
		return end - begin;
	}

	Rva007D6B70Sample &operator[](unsigned n)
	{
		return begin[n];
	}
};

struct Rva007D6B70Snap {
	int dword_0;
	int dword_4;
	float float_8;
	float float_C;
	float float_10;
	float float_14;
};

class Rva007D6B70;
// Retail 0x012F9CEC receives the address of the static instance at 0x01307228,
// whose atexit forwarder 0x00C70B50 runs ??1Rva007D6B70 (0x007D6AB0).
extern Rva007D6B70 *Rva007D6B70Slot012F9CEC;
extern Rva007D6B70 Rva007D6B70Instance01307228;

class Rva007D6B70 {
public:
	virtual int init();
	virtual int shutdown();
	unsigned shader[3];
	Rva007D6B70TextureRef vapor[2];
	Texture *texture0;
	Surface *surface0;
	unsigned dword_20[3];
	Rva007D6B70Samples samples;
	Texture *texture1;
	Texture *texture2;
	Surface *surface1;
	Surface *surface2;
};

int Rva007D6B70::init()
{
	shader[0] = 0;

	if (!HighlightVertexSupport || !HighlightPixelSupport)
		return 0;

	int chip = bfmeCheck986B();
	if (chip == 0)
		return 0;
	if (chip < 8)
		return 0;

	vapor[0].bind(BFMEGetWaterTrackTexture("EXVapor01.tga", 0, 0));
	vapor[1].bind(BFMEGetWaterTrackTexture("EXVapor02.tga", 0, 0));

	bool failed = false;
	if (HighlightDevice->v->CreateTexture(
			HighlightDevice, 512, 512, 1, 1, 21, 0, &texture0, 0) >= 0)
	{
		if (texture0->v->GetSurfaceLevel(texture0, 0, &surface0) < 0)
			failed = true;
	}
	if (HighlightDevice->v->CreateTexture(
			HighlightDevice, 512, 512, 1, 1, 21, 0, &texture1, 0) >= 0)
	{
		if (texture1->v->GetSurfaceLevel(texture1, 0, &surface1) < 0)
			failed = true;
	}
	if (HighlightDevice->v->CreateTexture(
			HighlightDevice, 512, 512, 1, 1, 21, 0, &texture2, 0) >= 0)
	{
		if (texture2->v->GetSurfaceLevel(texture2, 0, &surface2) < 0)
			failed = true;
	}

	if (failed || !surface2 || !surface1 || !surface0)
	{
		shutdown();
		return 0;
	}

	BfmeShaderLoader16::LoadAndCreateD3DShader("shaders\\ring.nvp", &shader[0]);
	BfmeShaderLoader16::LoadAndCreateD3DShader("shaders\\ring1.nvp", &shader[1]);
	BfmeShaderLoader16::LoadAndCreateD3DShader("shaders\\ring2.nvp", &shader[2]);

	Rva007D6B70Slot012F9CEC = &Rva007D6B70Instance01307228;

	Rva007D6B70Snap s;
	s.dword_0 = 1;
	s.dword_4 = 3;
	s.float_C = .06f;
	s.float_14 = .11f;
	s.float_8 = .18f;
	s.float_10 = 4.5f;
	bfmeCopyCuSnap(&samples, &s);

	float total = 0;
	for (unsigned i = 0; i < samples.size(); ++i)
		total += samples[i].weight;

	float inv = 1.0f / total;
	for (unsigned j = 0; j < samples.size(); ++j)
		samples[j].weight *= inv;

	return 1;
}
