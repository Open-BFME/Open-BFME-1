// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
//
// BFME W3DView::initHeightForMap, retail 0x00743520.
//
// Identity: the Zero Hour twin (reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp:2378) has the
// same spine -- ground height from TheTerrainLogic, a MAX_GROUND_LEVEL clamp,
// the camera offsets, m_cameraConstraintValid = false, setCameraTransform().
// The landed neighbours W3DViewResetCameraBfme.cpp (0x00743640) and
// W3DViewBuildCameraTransformBfme.cpp witness the same W3DView offsets
// (m_pos 0x0C, m_positionState 0x28, m_cameraScale 0xA0, m_cameraValueA 0x23D8,
// m_cameraValueB 0x23DC, m_groundLevel 0x23F8, the 0x240C flag byte and the
// CameraResetAux sub-object at 0x24B8).  name_oracle witnesses m_groundLevel
// at 0x23F8 and m_cameraConstraintValid at 0x240C.

#include "StringInline.h"

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// The embedded scalar field at this+0x2448.  The ledger spells its two entry
// points on two different address-derived classes, so both are declared here
// and the object is cast to whichever one owns the call:
//   ?initialize@Rva0045A000@@QAEXPBGHHHH@Z  0x0045A000 (ILT 0x00021549)
//   ?bfmeReset@Gen_00459F00@@QAEXXZ         0x00459F00 (ILT 0x0002386C)
// The parameter names come from the landed callee,
// Code/GameEngine/Source/Common/Rva0045A000ScalarField.cpp.
class Rva0045A000
{
public:
	void initialize(const unsigned short *source, int unused,
		int sourceWidth, int sourceHeight, int state);

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

class Gen_00459F00
{
public:
	void bfmeReset();
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

// Retail pushes the five map fields right to left, so the field each one
// feeds is fixed by the callee's own parameter list: +0x24 is the sample
// source (the only pointer in the decorated ABI), +0x20 the ignored second
// argument, +0x08 the source width, +0x0C the source height, +0x10 the state.
class BfmeHeightMap
{
public:
	unsigned char m_padding00[0x08];
	int m_width;
	int m_height;
	int m_state;
	unsigned char m_padding14[0x20 - 0x14];
	int m_unused;
	const unsigned short *m_source;
};

class BfmeA1087
{
public:
	unsigned char m_padding00[0x2FF4];
	BfmeHeightMap *m_map;
};

// Slot 6 (+0x18) and slot 36 (+0x90) are the two this body calls; the landed
// Code/GameEngine/Source/Common/Rva006DF650TriggerArea.cpp already names the
// +0x90 virtual getTriggerAreaByName and calls it on this same singleton.
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
	virtual void *getTriggerAreaByName(AsciiString name);
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
	void *m_altCameraTrigger;
	unsigned char m_padding24B0[0x24B8 - 0x24B0];
	CameraResetAux m_cameraAux;

	void setCameraTransform();
};

void W3DView::initHeightForMap()
{
	reinterpret_cast<Gen_00459F00 *>(&m_heightField)->bfmeReset();

	BfmeHeightMap *map = g_bfmeA1087->m_map;
	if (map != 0)
	{
		m_heightField.initialize(map->m_source, map->m_unused, map->m_width,
			map->m_height, map->m_state);
	}

	m_groundLevel = TheTerrainLogic->getGroundHeight(m_pos.x, m_pos.y, 0);
	static const Real maxGroundLevel = 700.0f;
	if (m_groundLevel > maxGroundLevel)
		m_groundLevel = maxGroundLevel;

	m_cameraAux.slot17();
	m_cameraAux.slot18(&m_cameraValueA, &m_positionState);
	m_cameraValueA *= m_cameraScale;
	m_cameraValueB = m_cameraScale * m_cameraValueB;
	m_cameraConstraintValid = false;
	setCameraTransform();

	// 0x01121748 is the retail literal "AltCamera".
	m_altCameraTrigger = TheTerrainLogic->getTriggerAreaByName(
		AsciiString((const char *)0x01121748));
}
