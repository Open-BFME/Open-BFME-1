// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath
//
// BFME's W3DDebrisDraw layout predates the Zero Hour headers used by the
// readable source tree.  Keep the retail layout and virtual slots local to
// this translation unit while retaining the canonical implementation.

#include "matrix3d.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Thing
{
public:
	Real getHeightAboveTerrain() const;

	__forceinline Bool isAboveTerrain() const
	{
		return getHeightAboveTerrain() > 0.0f;
	}
};

class Object : public Thing
{
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	const Coord3D *getPosition() const;

	__forceinline Object *getObject() const
	{
		return m_object;
	}

	__forceinline Real getInstanceScale() const
	{
		return m_instanceScale;
	}

private:
	unsigned char m_gap00[0xfc];
	Object *m_object;
	unsigned char m_gap100[0xf8];
	Real m_instanceScale;
};

class HAnimClass;

class RenderObjClass
{
public:
	enum AnimMode
	{
		ANIM_MODE_MANUAL = 0,
		ANIM_MODE_LOOP = 1,
		ANIM_MODE_ONCE = 2
	};

	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual Int Class_ID();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
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
	virtual void Set_Transform(const Matrix3D &transform);
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
	virtual void Set_Animation(HAnimClass *animation, Real frame, AnimMode mode);
	virtual void slot45();
	virtual HAnimClass *Peek_Animation();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void Set_ObjectScale(Real scale);
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void slot118();
	virtual void slot119();
	virtual void slot120();
	virtual void slot121();
	virtual void slot122();
	virtual void slot123();
	virtual void slot124();
	virtual void slot125();
	virtual void slot126();
	virtual void slot127();
	virtual void slot128();
	virtual void slot129();
	virtual void slot130();
	virtual void slot131();
	virtual Bool Is_Animation_Complete();
};

class HAnimClass
{
};

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *position,
		const Matrix3D *transform, Real speed, const Coord3D *secondary);
};

class W3DDebrisDraw
{
public:
	virtual void doDrawModule(const Matrix3D *transformMtx);

	__forceinline Drawable *getDrawable() const
	{
		return m_drawable;
	}

private:
	void *m_moduleData;
	Drawable *m_drawable;
	unsigned char m_gap0c[0x18];
	RenderObjClass *m_renderObject;
	HAnimClass *m_anims[3];
	const FXList *m_fxFinal;
	Int m_state;
	Int m_frames;
	Bool m_finalStop;
};

static __forceinline Bool isAnimationComplete(RenderObjClass *renderObject)
{
	if (renderObject->Class_ID() == 0x19)
		return renderObject->Is_Animation_Complete();
	return true;
}

// ?doDrawModule@W3DDebrisDraw@@UAEXPBVMatrix3D@@@Z
void W3DDebrisDraw::doDrawModule(const Matrix3D *transformMtx)
{
	if (m_renderObject)
	{
		Matrix3D scaledTransform;
		if (getDrawable()->getInstanceScale() != 1.0f)
		{
			scaledTransform = *transformMtx;
			scaledTransform.Scale(getDrawable()->getInstanceScale());
			transformMtx = &scaledTransform;
			m_renderObject->Set_ObjectScale(getDrawable()->getInstanceScale());
		}
		m_renderObject->Set_Transform(*transformMtx);

		static const RenderObjClass::AnimMode TheAnimModes[3] =
		{
			RenderObjClass::ANIM_MODE_ONCE,
			RenderObjClass::ANIM_MODE_LOOP,
			RenderObjClass::ANIM_MODE_ONCE
		};

		Int oldState = m_state;
		Object *object = getDrawable()->getObject();
		if (m_state != 2 && object != 0 && !object->isAboveTerrain() && m_frames > 3)
		{
			m_state = 2;
		}
		else if (m_state < 2 && isAnimationComplete(m_renderObject))
		{
			++m_state;
		}

		HAnimClass *animation = m_anims[m_state];
		if (animation != 0 &&
			(animation != m_renderObject->Peek_Animation() || oldState != m_state))
		{
			RenderObjClass::AnimMode mode = TheAnimModes[m_state];
			if (m_state == 2)
			{
				if (m_fxFinal != 0)
				{
					FXList::doFXPos(m_fxFinal, getDrawable()->getPosition(),
						getDrawable()->getTransformMatrix(), 0.0f, 0);
				}
				if (m_finalStop)
					mode = RenderObjClass::ANIM_MODE_MANUAL;
			}
			m_renderObject->Set_Animation(animation, 0.0f, mode);
		}
		++m_frames;
	}
}
