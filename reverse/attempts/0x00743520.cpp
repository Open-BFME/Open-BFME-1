// ?initHeightForMap@W3DView@@UAEXXZ
// partial score=0.99 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Scratch only.  BFME W3DView::initHeightForMap, retail 0x00743520.


typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Rva0045A000
{
public:
	void initialize(const unsigned short *source, int unused,
		int sourceWidth, int sourceHeight, int state);
	void bfmeReset();

private:
	void *m_begin;
	void *m_finish;
	void *m_end;
	int m_width;
	int m_height;
	Real m_scale;
	int m_state;
	Bool m_ready;
};

// The retail caller evaluates these five values in this order while the
// callee's ABI receives them as (source, unused, width, height, state).
class Rva0045A000InitOrder
{
public:
	void initialize(int state, int height, int width, int unused,
		const unsigned short *source);
};

class CameraResetAux
{
public:
	virtual void slot00();
	virtual Real slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18(Real *value, unsigned *position);
};

class BfmeHeightMap
{
public:
	unsigned char m_padding00[0x08];
	int m_width;
	int m_unused;
	const unsigned short *m_source;
	unsigned char m_padding14[0x20 - 0x14];
	int m_height;
	int m_state;
};

class BfmeA1087
{
public:
	unsigned char m_padding00[0x2FF4];
	BfmeHeightMap *m_map;
};

template <typename T>
class StringBase
{
protected:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);

private:
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString(const char *text) : StringBase<char>(text) {}
	~BFMERetailAsciiString() {}
};

class TerrainLogic
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, void *normal = 0) const;
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void *getTriggerAreaByName(class BFMERetailAsciiString name);
};

extern BfmeA1087 *g_bfmeA1087;
extern TerrainLogic *TheTerrainLogic;

class W3DView
{
public:
	virtual void initHeightForMap();

private:
	unsigned char m_padding0004[0x0C - 0x04];
	Coord3D m_pos;
	unsigned char m_padding0018[0x28 - 0x18];
	unsigned m_positionState;
	unsigned char m_padding002C[0xA0 - 0x2C];
	Real m_cameraScale;
	unsigned char m_padding00A4[0x23D8 - 0xA4];
	Real m_cameraValueA;
	Real m_cameraValueB;
	unsigned char m_padding23E0[0x23F8 - 0x23E0];
	Real m_groundLevel;
	unsigned char m_padding23FC[0x240C - 0x23FC];
	Bool m_cameraConstraintValid;
	unsigned char m_padding240D[0x2448 - 0x240D];
	Rva0045A000 m_heightField;
	unsigned char m_padding2468[0x24AC - 0x2468];
	int m_field24AC;
	unsigned char m_padding24B0[0x24B8 - 0x24B0];
	CameraResetAux m_cameraAux;

	void setCameraTransform();
};

#pragma comment(linker, "/alternatename:?bfmeReset@Rva0045A000@@QAEXXZ=?bfmeReset@Gen_00459F00@@QAEXXZ")
#pragma comment(linker, "/alternatename:?setCameraTransform@W3DView@@AAEXXZ=?j_000312a0@@YAXXZ")

void W3DView::initHeightForMap()
{
	m_heightField.bfmeReset();

	BfmeHeightMap *map = g_bfmeA1087->m_map;
	if (map != 0)
	{
		reinterpret_cast<Rva0045A000InitOrder *>(&m_heightField)->initialize(
			map->m_state, map->m_height, map->m_width, map->m_unused,
			map->m_source);
	}

	m_groundLevel = TheTerrainLogic->getGroundHeight(m_pos.x, m_pos.y, 0);
	static const Real maxGroundLevel = 700.0f;
	if (m_groundLevel > maxGroundLevel)
		m_groundLevel = maxGroundLevel;

	m_cameraAux.slot17();
	m_cameraAux.slot18(&m_cameraValueA, &m_positionState);
	volatile Real *cameraScale = &m_cameraScale;
	m_cameraConstraintValid = false;
	m_cameraValueA = m_cameraValueA * m_cameraScale;
	m_cameraValueB = *cameraScale * m_cameraValueB;
	setCameraTransform();

	m_field24AC = (int)TheTerrainLogic->getTriggerAreaByName(
		BFMERetailAsciiString((const char *)0x01121748));
}
