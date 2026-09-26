// cl: /DNDEBUG /MD /EHsc
// Constructor 0x007A4FD0 and initializer 0x007A4D40 pass the same 0x80-byte
// polygon object here. Its original class and method spelling are unproven;
// the address-derived owner distinguishes it from the larger water renderer.

typedef int Int;
typedef char Char;
typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTexture
{
public:
	void Release_Ref(void);
};

class BFMEWaterTrackTextureHandle
{
public:
	TextureClass *m_texture;

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			((BFMEWaterTrackTexture *)m_texture)->Release_Ref();
	}
};

extern BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(
	Char *name, Int mipCount, Int format);

class TextureHolder
{
public:
	void bind(const BFMEWaterTrackTextureHandle &texture);
};

static inline void BFMEAssignWaterTrackTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((char *)texture.m_texture + 4);
	if (destination)
		((BFMEWaterTrackTexture *)destination)->Release_Ref();
	destination = texture.m_texture;
}

enum WW3DFormat
{
	WW3D_FORMAT_UNKNOWN = 0
};

enum WaterTextureIndex
{
	WATER_TEXTURE_0 = 0
};

class W3DRadarFormatCaps
{
public:
	Bool supportTextureFormat(WW3DFormat format);
};

extern W3DRadarFormatCaps *TheW3DRadarFormatCaps;

static __forceinline Bool BFMEWaterTrackIndexInRange(Int index)
{
	return (unsigned)index < 6;
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Char *m_data;

	AsciiString();
	~AsciiString();

	AsciiString &operator=(const AsciiString &other);

	Char *str(void) const
	{
		if (m_data)
			return m_data + 8;
		return (Char *)0x0107388b;
	}

	Bool isEmpty(void) const
	{
		return m_data == 0 || *(unsigned short *)(m_data + 4) == 0;
	}
};

template <class T>
class RefCountPtr
{
	friend class Rva007A1230ArrayOwner;
public:
	RefCountPtr(void);
	~RefCountPtr(void);

private:
	T *m_referent;
};

class Rva007A1230ArrayOwner
{
public:
	Rva007A1230ArrayOwner(void *source);
	virtual ~Rva007A1230ArrayOwner(void);
	void setTexture(const AsciiString &name, WaterTextureIndex index);

private:
	void releaseOwnedState(void);
	unsigned char m_flag04;
	unsigned char m_padding05[3];
	void *m_field08;
	AsciiString m_textureNames[6];
	RefCountPtr<TextureClass> m_textureReferences[6];
	unsigned char m_flag3c;
	unsigned char m_padding3d[0x0f];
	unsigned int m_value4c;
	unsigned int m_value50;
	// The initializer passes these raw values to AABoxClass(Vector3 *, int).
	unsigned int m_pointStorage;
	unsigned int m_pointCount;
	unsigned int m_value5c;
	unsigned int m_value60;
	unsigned char m_boundsValid;
	unsigned char m_padding65[3];
	// Initializer 0x007A4D40 copies the AABoxClass result to +0x68..+0x7F.
	unsigned char m_bounds[0x18];
};

typedef char WaterPolygonSize[(sizeof(Rva007A1230ArrayOwner) == 0x80) ? 1 : -1];

// The initializer is still a generic dump row.  Keep its call target named by
// that existing row until the adjacent body is converted; the cast supplies
// the recovered thiscall/one-argument ABI without inventing a second address.
extern void d_007a4d40(void);

// VC7.1 reserves __thiscall in a free-function-pointer typedef.  A fastcall
// cast with the source duplicated gives the same ECX object and stack argument
// while leaving the otherwise-unused EDX copy harmless at the target.
typedef void (__fastcall *WaterPolygonInitializeCall)(
	Rva007A1230ArrayOwner *, void *, void *);

Rva007A1230ArrayOwner::Rva007A1230ArrayOwner(void *source)
	: m_flag04(0), m_field08(0)
{
	m_flag3c = 0;
	m_value4c = 0;
	m_value50 = 0;
	m_pointStorage = 0;
	m_pointCount = 0;
	m_value5c = 0;
	m_value60 = 0;
	m_boundsValid = 0;
	((WaterPolygonInitializeCall)d_007a4d40)(this, source, source);
}

Rva007A1230ArrayOwner::~Rva007A1230ArrayOwner()
{
	releaseOwnedState();
}

void Rva007A1230ArrayOwner::setTexture(
	const AsciiString &name, WaterTextureIndex index)
{
	register Rva007A1230ArrayOwner *self = this;
	Int indexValue = (Int)index;
	if (!BFMEWaterTrackIndexInRange(indexValue))
		return;

	self->m_textureNames[indexValue] = name;
	if (self->m_textureNames[indexValue].isEmpty())
		return;

	if (!self->m_flag04 && indexValue == 4)
	{
		Int format = 0;
		if (TheW3DRadarFormatCaps->supportTextureFormat(
			(WW3DFormat)0x3c))
			format = 0x3c;
		else if (TheW3DRadarFormatCaps->supportTextureFormat(
			(WW3DFormat)0x3e))
			format = 0x3e;
		else if (TheW3DRadarFormatCaps->supportTextureFormat(
			(WW3DFormat)0x3d))
			format = 0x3d;

		((TextureHolder *)((char *)self + 0x34))->bind(
			BFMEGetWaterTrackTexture(
				self->m_textureNames[4].str(), 1, format));
	}
	else
	{
		BFMEAssignWaterTrackTexture(
			self->m_textureReferences[indexValue].m_referent,
			BFMEGetWaterTrackTexture(
				self->m_textureNames[indexValue].str(), 0, 0));
	}
}
