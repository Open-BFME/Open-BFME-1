// cl: /DNDEBUG /MD /EHsc

// W3DLaserDrawModuleData's constructor, retail 0x00757960, 115 bytes.
//
// The ModuleFactory registration at 0x006C0112 pushes the literal
// "W3DLaserDraw" at 0x00D1D298 beside the data factory 0x006BF1D0. That factory
// allocates 0x74 bytes and calls this body through ILT 0x0000B997, so this body
// constructs W3DLaserDrawModuleData and the class is 0x74 bytes long. The last
// dword this body writes is at +0x70, which confirms the size.
//
// The same factory pushes ILT 0x000388BB for INI::initFromINIMultiProc, which
// reaches the field-parse forwarder at 0x00756C50. That forwarder registers the
// FieldParse table at 0x01122858, and every field name and member offset below
// is read straight out of that table. Only the members the table does not cover
// carry offset-derived names.
//
// Retail makes no call and builds no exception frame, so every member
// constructor here has to be inline and nothing may throw.
//
// MSVC 7.1 holds each repeated constant in one register (0 in ECX, -1 in EDI,
// 1.0f in ESI, 1 in EDX) and emits the stores grouped by register, keeping
// source order inside each group. That is why the two 1.0f body assignments
// climb to sit beside the envelope's three, and why the constructor reads out
// of order in the listing while the source below is in plain order.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int Color;
typedef float Real;

// The base supplies the vptr at +0x00 and one dword at +0x04 that retail never
// stores to, so the derived members start at +0x08.
class BfmeModuleDataBase
{
public:
	virtual void slot();

private:
	char m_bfmePad[0x08 - 0x04];
};

// The Texture field parses through INI::parseAsciiStringVectorAppend, so the
// member at +0x2C is a vector of AsciiString. Its three pointers zero with no
// call.
class AsciiStringVector
{
public:
	AsciiStringVector() : m_begin(0), m_end(0), m_capacity(0) {}

private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
};

// The table's last field, Envelope, sits at +0x4C and runs to the end of the
// object at +0x74. Its parser is a separate function, so the field names inside
// it are not proven and these carry their offsets instead.
struct BfmeEnvelope
{
	BfmeEnvelope() :
		m_bfme00(1.0f),
		m_bfme04(1.0f),
		m_bfme08(1.0f),
		m_bfme0C(0.0f),
		m_bfme10(1),
		m_bfme14(1),
		m_bfme18(1),
		m_bfme1C(-1),
		m_bfme20(-1),
		m_bfme24(0)
	{}

	void reset()
	{
		m_bfme0C = 0.0f;
		m_bfme24 = 0;
	}

	Real m_bfme00;
	Real m_bfme04;
	Real m_bfme08;
	Real m_bfme0C;
	Int m_bfme10;
	Int m_bfme14;
	Int m_bfme18;
	Int m_bfme1C;
	Int m_bfme20;
	Int m_bfme24;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DLaserDraw.h
class W3DLaserDrawModuleData : public BfmeModuleDataBase
{
public:
	W3DLaserDrawModuleData();

	virtual void slot();

	Color m_innerColor;			// +0x08  InnerColor
	Color m_outerColor;			// +0x0C  OuterColor
	Real m_innerBeamWidth;			// +0x10  InnerBeamWidth
	Real m_outerBeamWidth;			// +0x14  OuterBeamWidth
	Real m_scrollRate;			// +0x18  ScrollRate
	bool m_tile;				// +0x1C  Tile
	UnsignedInt m_numBeams;			// +0x20  NumBeams
	UnsignedInt m_maxIntensityFrames;	// +0x24  MaxIntensityLifetime
	UnsignedInt m_fadeFrames;		// +0x28  FadeLifetime
	AsciiStringVector m_textureName;	// +0x2C  Texture
	UnsignedInt m_segments;			// +0x38  Segments
	Real m_arcHeight;			// +0x3C  ArcHeight
	Real m_segmentOverlapRatio;		// +0x40  SegmentOverlapRatio
	Real m_tilingScalar;			// +0x44  TilingScalar
	Real m_fanWidth;			// +0x48  FanWidth
	BfmeEnvelope m_envelope;		// +0x4C  Envelope
};

// ??0W3DLaserDrawModuleData@@QAE@XZ
W3DLaserDrawModuleData::W3DLaserDrawModuleData() :
	m_innerColor(0xFFFFFFFF),
	m_outerColor(0xFFFFFFFF)
{
	m_innerBeamWidth = 0.0f;
	m_outerBeamWidth = 1.0f;
	m_numBeams = 1;
	m_maxIntensityFrames = 0;
	m_fadeFrames = 0;
	m_scrollRate = 0.0f;
	m_tile = false;
	m_segments = 1;
	m_arcHeight = 0.0f;
	m_segmentOverlapRatio = 0.0f;
	m_tilingScalar = 1.0f;
	m_fanWidth = 0.0f;
	m_envelope.reset();
}
