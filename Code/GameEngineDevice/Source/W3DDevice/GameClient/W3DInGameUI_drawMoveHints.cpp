// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

// W3DInGameUI::drawMoveHints, retail 0x006FC5A0 (650 B).
// Identity: slot +0x1bc of the W3DInGameUI vftable VA 0x01120590 (installed by
// the matched constructor 0x006FBE10) holds ILT RVA 0x0002432F -> 0x006FC5A0, and
// the matched W3DInGameUI::draw (0x006FBFF0) calls that slot once per view in
// the ZH twin's drawMoveHints position. The body is the ZH loop over 25 hints
// with the BFME additions (early-frame guard, per-hint skip byte,
// hide-on-create). These are declaration-only facades; no vtable is emitted.

#include "ascii_string.h"

extern const char g_bfmeEmptyAscii[];

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#define NULL 0

class View;

class Matrix3D
{
	Real Row[3][4];
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

#define DECLARE_TEN(prefix) \
	virtual void prefix##0(); virtual void prefix##1(); \
	virtual void prefix##2(); virtual void prefix##3(); \
	virtual void prefix##4(); virtual void prefix##5(); \
	virtual void prefix##6(); virtual void prefix##7(); \
	virtual void prefix##8(); virtual void prefix##9();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class HAnimClass
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		NumRefs--;
		if (NumRefs == 0)
			Delete_This();
	}

private:
	Int NumRefs;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rendobj.h
class RenderObjClass
{
public:
	enum AnimMode { ANIM_MODE_MANUAL = 0, ANIM_MODE_LOOP, ANIM_MODE_ONCE };

	DECLARE_TEN(slotA)                        // 0..9
	DECLARE_TEN(slotB)                        // 10..19
	virtual void slotC0();                    // 20
	virtual void Set_Transform(const Matrix3D &m);            // 21, +0x54
	virtual void slotC2(); virtual void slotC3();
	virtual void slotC4(); virtual void slotC5();
	virtual void slotC6(); virtual void slotC7();
	virtual void slotC8(); virtual void slotC9();
	DECLARE_TEN(slotD)                        // 30..39
	virtual void slotE0(); virtual void slotE1();
	virtual void slotE2(); virtual void slotE3();
	virtual void Set_Animation(HAnimClass *anim, Real frame, Int mode); // 44, +0xb0
	virtual void slotE5(); virtual void slotE6();
	virtual void slotE7(); virtual void slotE8(); virtual void slotE9();
	DECLARE_TEN(slotF)                        // 50..59
	DECLARE_TEN(slotG)                        // 60..69
	DECLARE_TEN(slotH)                        // 70..79
	DECLARE_TEN(slotI)                        // 80..89
	virtual void slotJ0(); virtual void slotJ1();
	virtual void slotJ2(); virtual void slotJ3();
	virtual void slotJ4(); virtual void slotJ5();
	virtual void slotJ6(); virtual void slotJ7();
	virtual void slotJ8();                    // 90..98
	virtual Int Is_Hidden() const;            // 99, +0x18c
	virtual void Set_Hidden(Int onoff);       // 100, +0x190
};

// W3DDisplay::m_3DScene (0x012F8058); slots +0x08 / +0x0c
class RTS3DScene
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void Add_Render_Object(RenderObjClass *obj);
	virtual void Remove_Render_Object(RenderObjClass *obj);
};

class W3DDisplay
{
public:
	static RTS3DScene *m_3DScene;
};

class GameClient
{
public:
	DECLARE_TEN(slotA)                        // 0..9
	DECLARE_TEN(slotB)                        // 10..19
	virtual void slotC0(); virtual void slotC1();
	virtual void slotC2(); virtual void slotC3();
	virtual void slotC4(); virtual void slotC5();
	virtual UnsignedInt getFrame();           // 26, +0x68
};

class TerrainLogic
{
public:
	DECLARE_TEN(slotA)                        // 0..9
	virtual void slotB0(); virtual void slotB1();
	virtual void slotB2(); virtual void slotB3();
	virtual void slotB4(); virtual void slotB5();
	virtual void slotB6(); virtual void slotB7();
	virtual PathfindLayerEnum alignOnTerrain(Real angle, const Coord3D &pos, Bool stickToGround, Matrix3D &mtx); // 18, +0x48
	virtual Bool isUnderwater(Real x, Real y, Real *waterZ = NULL, Real *terrainZ = NULL); // 19, +0x4c
};

class GlobalData
{
public:
	unsigned char m_unmodelled_00[0x0c];
	AsciiString m_moveHintName;               // +0x0c
};

#undef DECLARE_TEN

extern GameClient *TheGameClient;
extern GlobalData *TheWritableGlobalData;
extern TerrainLogic *TheTerrainLogic;

extern RenderObjClass *Create_Render_Obj(const char *name);
extern HAnimClass *Get_HAnim(const char *name);
extern void makeAlignToNormalMatrix(Real angle, const Coord3D &pos, const Coord3D &normal, Matrix3D &mtx);

// Retail inlines AsciiString::str(): the text follows an 8-byte header and an
// empty string reads the shared 0x0107388B literal.
inline const char *asciiText(const AsciiString &s)
{
	const char *const &data = *(const char *const *)&s;
	return data ? data + 8 : g_bfmeEmptyAscii;
}

#define REF_PTR_RELEASE(x) { if (x) { (x)->Release_Ref(); (x) = NULL; } }

enum { MAX_MOVE_HINTS = 25 };

struct MoveHintStruct
{
	Coord3D pos;
	UnsignedInt frame;
	Bool byte_10;
};

class W3DInGameUI
{
protected:
	virtual void drawMoveHints(View *view);                    // vftable +0x1bc

private:
	unsigned char m_unmodelled_04[0x38 - 0x04];
	MoveHintStruct m_moveHint[MAX_MOVE_HINTS];                 // +0x38
	unsigned char m_unmodelled_22c[0x13ac - 0x22c];
	RenderObjClass *m_moveHintRenderObj[MAX_MOVE_HINTS];      // +0x13ac
	HAnimClass *m_moveHintAnim[MAX_MOVE_HINTS];               // +0x1410
};

void W3DInGameUI::drawMoveHints(View * /*view*/)
{
	Int i;

	for (i = 0; i < MAX_MOVE_HINTS; i++)
	{
		Int elapsed = TheGameClient->getFrame() - m_moveHint[i].frame;
		if (TheGameClient->getFrame() <= 40)
			elapsed = 41;

		if (!m_moveHint[i].byte_10 && elapsed <= 40)
		{
			if (m_moveHintRenderObj[i] == NULL)
			{
				RenderObjClass *hint;
				HAnimClass *anim;

				hint = Create_Render_Obj(asciiText(TheWritableGlobalData->m_moveHintName));

				AsciiString animName;
				animName.format("%s.%s", asciiText(TheWritableGlobalData->m_moveHintName),
					asciiText(TheWritableGlobalData->m_moveHintName));
				anim = Get_HAnim(asciiText(animName));

				if (hint == NULL)
					return;

				hint->Set_Hidden(1);
				m_moveHintRenderObj[i] = hint;

				REF_PTR_RELEASE(m_moveHintAnim[i]);
				m_moveHintAnim[i] = anim;
			}

			if (m_moveHintRenderObj[i]->Is_Hidden() == 1)
			{
				m_moveHintRenderObj[i]->Set_Hidden(0);
				W3DDisplay::m_3DScene->Add_Render_Object(m_moveHintRenderObj[i]);
				if (m_moveHintAnim[i])
					m_moveHintRenderObj[i]->Set_Animation(m_moveHintAnim[i], 0, RenderObjClass::ANIM_MODE_ONCE);
			}

			Matrix3D transform;
			const Coord3D &pos = m_moveHint[i].pos;
			PathfindLayerEnum layer = TheTerrainLogic->alignOnTerrain(0, pos, true, transform);

			Real waterZ;
			if (layer == LAYER_GROUND && TheTerrainLogic->isUnderwater(m_moveHint[i].pos.x, m_moveHint[i].pos.y, &waterZ))
			{
				Coord3D tmp;
				tmp.x = pos.x;
				tmp.y = pos.y;
				tmp.z = waterZ;
				Coord3D normal;
				normal.x = 0;
				normal.y = 0;
				normal.z = 1;
				makeAlignToNormalMatrix(0, tmp, normal, transform);
			}

			m_moveHintRenderObj[i]->Set_Transform(transform);
		}
		else
		{
			if (m_moveHintRenderObj[i])
				if (m_moveHintRenderObj[i]->Is_Hidden() == 0)
				{
					m_moveHintRenderObj[i]->Set_Hidden(1);
					W3DDisplay::m_3DScene->Remove_Render_Object(m_moveHintRenderObj[i]);
				}
		}
	}
}
