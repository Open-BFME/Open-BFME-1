// ?doDrawModule@W3DPoliceCarDraw@@UAEXPBVMatrix3D@@@Z
// partial score=0.76 date=2026-09-25
// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// BFME W3DPoliceCarDraw body at retail RVA 0x00758EF0.

typedef float Real;

class Matrix3D;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

};

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;

	Vector3(void) { }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}
};

class Drawable
{
public:
	const Coord3D *getPosition(void) const;
};

class HAnimClass
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual int Get_Num_Frames(void) const;
};

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
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void Set_Position(const Vector3 &position);
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
	virtual void Set_Animation(HAnimClass *animation, Real frame, int mode);
	virtual void slot45();
	virtual HAnimClass *Peek_Animation(void);
};

class W3DDynamicLight : public RenderObjClass
{
public:
	void Set_Ambient(const Vector3 &color) { m_ambient = color; }
	void Set_Diffuse(const Vector3 &color) { m_diffuse = color; }
	void Set_Far_Attenuation_Range(Real start, Real end)
	{
		m_farAttenStart = start;
		m_farAttenEnd = end;
	}

private:
	char m_renderObjectTail[0xD4];
	Vector3 m_ambient;
	Vector3 m_diffuse;
	char m_specularAndNearTail[0x14];
	Real m_farAttenStart;
	Real m_farAttenEnd;
};

class W3DTruckDraw
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
	virtual RenderObjClass *getRenderObject(void);
	virtual void doDrawModule(const Matrix3D *transformMtx);

	void *m_moduleData;
	Drawable *m_drawable;
	char m_baseTail[0x3E0];

	Drawable *getDrawable(void) const { return m_drawable; }
};

class W3DPoliceCarDraw : public W3DTruckDraw
{
public:
	virtual void doDrawModule(const Matrix3D *transformMtx);

protected:
	W3DDynamicLight *createDynamicLight(void);

private:
	W3DDynamicLight *m_light;
	Real m_curFrame;
};

#define BFME_FRAME_STEP (*(const Real *)0x01083B6C)
#define BFME_ONE (*(const Real *)0x01075334)
#define BFME_FRAME_3 (*(const Real *)0x01075338)
#define BFME_FRAME_6 (*(const Real *)0x010828C4)
#define BFME_FRAME_7 (*(const Real *)0x0109C34C)
#define BFME_FRAME_9 (*(const Real *)0x010BA66C)
#define BFME_HALF (*(const double *)0x0109B3F0)
#define BFME_FRAME_5 (*(const Real *)0x01075344)
#define BFME_FRAME_11 (*(const Real *)0x01123060)
#define BFME_FRAME_14 (*(const Real *)0x01123064)
#define BFME_ONE_THIRD (*(const Real *)0x01097120)
#define BFME_ONE_SIXTH (*(const Real *)0x010EC714)
#define BFME_HALF_FLOAT (*(const Real *)0x0107533C)
#define BFME_FRAME_12 (*(const Real *)0x010F693C)
#define BFME_HEIGHT (*(const Real *)0x010A265C)

// ?doDrawModule@W3DPoliceCarDraw@@UAEXPBVMatrix3D@@@Z
void W3DPoliceCarDraw::doDrawModule(const Matrix3D *transformMtx)
{
	RenderObjClass *policeCarRenderObj = getRenderObject();
	if (policeCarRenderObj == 0)
		return;

	HAnimClass *anim = policeCarRenderObj->Peek_Animation();
	if (anim)
	{
		Real frames = (Real)anim->Get_Num_Frames();
		m_curFrame += BFME_FRAME_STEP;
		if (m_curFrame > frames - BFME_ONE)
			m_curFrame = 0;
		policeCarRenderObj->Set_Animation(anim, m_curFrame, 0);
	}

	Real red = 0;
	Real green = 0;
	Real blue = 0;
	if (m_curFrame < BFME_FRAME_3)
	{
		red = 1.0f;
		green = 0.5f;
	}
	else if (m_curFrame < BFME_FRAME_6)
	{
		red = 1.0f;
	}
	else if (m_curFrame < BFME_FRAME_7)
	{
		red = 1.0f;
		green = 0.5f;
	}
	else if (m_curFrame < BFME_FRAME_9)
	{
		red = BFME_HALF + (BFME_FRAME_9 - m_curFrame) * BFME_FRAME_STEP;
		blue = (m_curFrame - BFME_FRAME_5) * BFME_ONE_SIXTH;
	}
	else if (m_curFrame < BFME_FRAME_12)
	{
		blue = 1.0f;
	}
	else if (m_curFrame <= BFME_FRAME_14)
	{
		green = (m_curFrame - BFME_FRAME_11) * BFME_ONE_THIRD;
		blue = (BFME_FRAME_14 - m_curFrame) * BFME_HALF_FLOAT;
		red = (m_curFrame - BFME_FRAME_11) * BFME_ONE_THIRD;
	}

	if (m_light == 0)
		m_light = createDynamicLight();
	if (m_light)
	{
		const Coord3D *position = getDrawable()->getPosition();
		Coord3D pos;
		pos.x = position->x;
		pos.y = position->y;
		pos.z = position->z;
		m_light->Set_Diffuse(Vector3(red, green, blue));
		m_light->Set_Ambient(Vector3(red / 2, green / 2, blue / 2));
		m_light->Set_Far_Attenuation_Range(3, 20);
		m_light->Set_Position(Vector3(pos.x, pos.y, pos.z + BFME_HEIGHT));
	}
	W3DTruckDraw::doDrawModule(transformMtx);
}
