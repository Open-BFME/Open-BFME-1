// cl: /DNDEBUG /MD /EHsc
// W3DWaypointBuffer constructor at retail RVA 0x007468B0 (297 bytes).
//
// IDENTITY.  The lift carried the truncated decoration ??0W3DWaypointBuffer@@;
// the constructor is ??0W3DWaypointBuffer@@QAE@XZ (__thiscall, no arguments,
// void) -- the class has exactly one, it is called from
// ??0BaseHeightMapRenderObjClass@@QAE@XZ through an ILT thunk, and the two
// already-converted members of the class sit either side of it and agree on
// the layout used here: ?1W3DWaypointBuffer@@QAE@XZ at 0x00746800 releases
// this+0, this+4 inline and this+8 through the out-of-line texture release,
// and ?drawWaypoints@W3DWaypointBuffer@@QAEXAAVRenderInfoClass@@@Z at
// 0x00746A30 reads this+0 and this+4.  So RenderObjClass *m_waypointNodeRobj
// sits at +0, SegmentedLineClass *m_line at +4 and the owning TextureRef
// m_texture at +8.  The Zero Hour twin W3DWaypointBuffer.cpp has the same
// constructor body; BFME changed the node model to "SCMoveHintSml", the line
// texture to BFMEGetWaterTrackTexture("EXLaser.tga",0,0), and the line colour
// to (0.97,0.64,0.15).  The shader is _PresetAdditiveShader (the DIR32 at
// 0x012D6E0C) with its depth compare forced to PASS_ALWAYS -- `or edx,7' over
// bits 0-2 -- and Set_Shader takes that 4-byte ShaderClass by value.
//
// LOCAL LAYOUTS.  SegmentedLineClass is modelled only as far as this
// constructor reaches: the setters, and the 0x130 bytes operator new asks for.
// The line style is applied through the renderer sub-object at +0xE0, whose
// Set_Texture retail reaches through the offset tail thunk at 0x0094F960 --
// see Rva0094F960 below.  The texture handle ABI follows
// W3DWaterTracks.cpp / RoadTypeLoadTexture.cpp: a four-byte owning handle whose
// 16-bit retain sits at +4 of the texture and whose release is the
// RVA 0x009EB7A0 leaf.
typedef int Int;
typedef char Char;

// only ever used as a pointer here; the anchor member keeps it a distinct type
class RenderObjClass
{
public:
	void anchor(void);
};

// ?Create_Render_Obj@@YAPAVRenderObjClass@@PBD@Z
RenderObjClass *Create_Render_Obj(const char *name);

class TextureClass
{
public:
	void Release_Ref(void);
};

// The owning four-byte handle BFME's texture lookups return: constructed in
// place through a hidden return pointer, so the value arrives in eax as the
// address of the caller's slot (retail 0x007468B0 +0x82).
class BFMEWaterTrackTextureHandle
{
public:
	BFMEWaterTrackTextureHandle(void) : m_texture(0) {}
	BFMEWaterTrackTextureHandle(const BFMEWaterTrackTextureHandle &source)
		: m_texture(source.m_texture)
	{
	}

	~BFMEWaterTrackTextureHandle(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}

	TextureClass *m_texture;
};

BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(Char *name, Int mipCount, Int format);

static inline void BFMEAssignWaterTrackTexture(
	TextureClass *&destination,
	const BFMEWaterTrackTextureHandle &texture)
{
	if (texture.m_texture)
		++*(unsigned short *)((Char *)texture.m_texture + 4);
	if (destination)
		destination->Release_Ref();
	destination = texture.m_texture;
}

class ShaderClass
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/shader.h
	// (ShaderBits is the only member, and the depth compare owns bits 0-2)
	enum DepthCompareType
	{
		PASS_NEVER = 0,
		PASS_LESS,
		PASS_EQUAL,
		PASS_LEQUAL,
		PASS_GREATER,
		PASS_NOTEQUAL,
		PASS_GEQUAL,
		PASS_ALWAYS,
		PASS_MAX
	};

	ShaderClass(void) : m_bits(0) {}

	ShaderClass(const ShaderClass &source) : m_bits(source.m_bits) {}

	void Set_Depth_Compare(DepthCompareType compare)
	{
		m_bits &= ~7u;
		m_bits |= (unsigned int)compare;
	}

	unsigned int m_bits;

	// ?_PresetAdditiveShader@ShaderClass@@2V1@A
	static ShaderClass _PresetAdditiveShader;
};

class Vector3
{
public:
	Vector3(void) {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }

	float X;
	float Y;
	float Z;
};

class SegLineRendererClass
{
public:
	enum TextureMapMode
	{
		UNIFORM_WIDTH_TEXTURE_MAP = 0,
		UNIFORM_LENGTH_TEXTURE_MAP = 1,
		TILED_TEXTURE_MAP = 2
	};
};

// The nine/eleven-byte offset tail thunk at 0x0094F960 (add ecx,0xE0 ; jmp
// SegLineRendererClass::Set_Texture at 0x00960050) is what retail CALLS from
// here, not the renderer body, so this call goes through the address-derived
// name the ledger already pins that thunk under
// (?apply@Rva0094F960@@QAEXABQAVTextureClass@@@Z, symbols.csv) and hands it the
// ADDRESS of the texture slot, which the thunk's target dereferences.
class Rva0094F960
{
public:
	void apply(TextureClass *const &texture);
};

class SegmentedLineClass
{
public:
	SegmentedLineClass(void);

	void Set_Shader(ShaderClass shader);
	void Set_Width(float width);
	void Set_Color(const Vector3 &color);
	void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode mode);

	// operator new(0x130) at retail +0x3d, so the object is 0x130 bytes
	unsigned char m_unreconstructed[0x130];
};

class TextureRef
{
public:
	TextureRef(void) : m_ptr(0) {}

	~TextureRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	TextureClass *m_ptr;
};

class W3DWaypointBuffer
{
public:
	W3DWaypointBuffer(void);

private:
	RenderObjClass *m_waypointNodeRobj;
	SegmentedLineClass *m_line;
	TextureRef m_texture;
};

// ??0W3DWaypointBuffer@@QAE@XZ
W3DWaypointBuffer::W3DWaypointBuffer(void) : m_texture()
{
	m_waypointNodeRobj = Create_Render_Obj("SCMoveHintSml");
	m_line = new SegmentedLineClass;
	BFMEAssignWaterTrackTexture(m_texture.m_ptr, BFMEGetWaterTrackTexture("EXLaser.tga", 0, 0));
	reinterpret_cast<Rva0094F960 *>(m_line)->apply(m_texture.m_ptr);
	ShaderClass lineShader = ShaderClass::_PresetAdditiveShader;
	lineShader.Set_Depth_Compare(ShaderClass::PASS_ALWAYS);
	m_line->Set_Shader(lineShader);
	m_line->Set_Width(1.5f);
	m_line->Set_Color(Vector3(0.97f, 0.64f, 0.15f));
	m_line->Set_Texture_Mapping_Mode(SegLineRendererClass::TILED_TEXTURE_MAP);
}
