// cl: /DNDEBUG /MD /EHsc

// W3DInGameUI::drawPlaceAngle, retail 0x006FC0D0.
// The owner is established by the W3DInGameUI constructor/destructor field
// layout, the draw() caller's slot, and the upstream placement implementation.
// These are declaration-only facades; no new vtable is emitted by this TU.

#include <math.h>

typedef float Real;
typedef int Int;
typedef bool Bool;

#define NULL 0
#define TRUE true
#define FALSE false

class View {};
class Matrix3D {};
class SceneClass;

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length(void) const
	{
		return (Real)sqrt(x * x + y * y + z * z);
	}
};

class Drawable {};

// The retail call at 0x00417512 is the existing generated thunk, whose
// machine ABI leaves the Drawable in ECX and returns the matrix in EAX.  Keep
// the thunk's real COFF identity and type the call locally rather than using
// the conflicting candidate pin for Drawable::getTransformMatrix.
extern void j_00017512(void);
typedef const Matrix3D *(__fastcall *GetTransformMatrixThunk)(Drawable *);

class RenderObjClass
{
public:
	virtual void slot00();
	virtual void slot01();
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
	virtual SceneClass *Peek_Scene(void);
	virtual void slot19();
	virtual void slot20();
	virtual void Set_Transform(const Matrix3D &transform);
};

class BfmeGlobPB
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void Add_Render_Object(RenderObjClass *object);
	virtual void Remove_Render_Object(RenderObjClass *object);
};

extern BfmeGlobPB *g_bfmeGlobPB;
extern const Real g_bfmeK1266C;
extern RenderObjClass *Create_Render_Obj(const char *name);

class W3DInGameUISlots
{
public:
	virtual void slot00();
	virtual void slot01();
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
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual Bool isPlacementAnchored(void);
	virtual void getPlacementPoints(ICoord2D *start, ICoord2D *end);
};

class W3DInGameUI : public W3DInGameUISlots
{
public:
	void drawPlaceAngle(View *view);

private:
	unsigned char m_unmodelled_04[0x538];
	Drawable **m_placeIcon;
	unsigned char m_unmodelled_540[0x1474 - 0x540];
	RenderObjClass *m_buildingPlacementAnchor;
	RenderObjClass *m_buildingPlacementArrow;
};

void W3DInGameUI::drawPlaceAngle(View * /*view*/)
{
	if (!m_buildingPlacementAnchor)
	{
		m_buildingPlacementAnchor = Create_Render_Obj("W_Arrow");
		if (!m_buildingPlacementAnchor)
			return;
	}
	if (!m_buildingPlacementArrow)
	{
		m_buildingPlacementArrow = Create_Render_Obj("W_Arrow");
		if (!m_buildingPlacementArrow)
			return;
	}

	Bool arrowInScene;
	Bool anchorInScene = m_buildingPlacementAnchor->Peek_Scene() != NULL;
	arrowInScene = m_buildingPlacementArrow->Peek_Scene() != NULL;

	if (isPlacementAnchored() == FALSE)
	{
		if (anchorInScene)
			g_bfmeGlobPB->Remove_Render_Object(m_buildingPlacementAnchor);
		if (arrowInScene)
			g_bfmeGlobPB->Remove_Render_Object(m_buildingPlacementArrow);
		return;
	}

	ICoord2D start, end;
	getPlacementPoints(&start, &end);

	Coord3D vector;
	vector.x = end.x - start.x;
	vector.y = end.y - start.y;
	vector.z = 0.0f;
	Real length = vector.length();
	Bool showArrow = length >= g_bfmeK1266C;

	if (showArrow)
	{
		if (anchorInScene)
			g_bfmeGlobPB->Remove_Render_Object(m_buildingPlacementAnchor);
		if (!arrowInScene)
		{
			g_bfmeGlobPB->Add_Render_Object(m_buildingPlacementArrow);
			arrowInScene = TRUE;
		}
	}
	else
	{
		if (arrowInScene)
			g_bfmeGlobPB->Remove_Render_Object(m_buildingPlacementArrow);
		if (!anchorInScene)
		{
			g_bfmeGlobPB->Add_Render_Object(m_buildingPlacementAnchor);
			anchorInScene = TRUE;
		}
	}

	if (anchorInScene)
	{
		if (m_placeIcon[0])
			m_buildingPlacementAnchor->Set_Transform(
				*((GetTransformMatrixThunk)j_00017512)(m_placeIcon[0]));
	}
	else if (arrowInScene)
	{
		if (m_placeIcon[0])
			m_buildingPlacementArrow->Set_Transform(
				*((GetTransformMatrixThunk)j_00017512)(m_placeIcon[0]));
	}
}
