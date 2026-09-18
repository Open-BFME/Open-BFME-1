// ?dup_007A5AB0@@YAXXZ
// partial score=0.93 date=2026-09-08
// Identity remains opaque: callers_of.py, vtable_lookup.py, and source search
// found no named caller, installed vtable slot, or declaration proving a
// semantic free-function name.  Keep the address-derived identity.  The
// owner and setter identities below are witnessed by
// WaterRenderObjReadSkyBoxSettings.cpp and existing pins.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);

	~BFMERetailAsciiString() { releaseBuffer(); }

	void *m_bfmeBufYV;

private:
	void releaseBuffer();
};

// Vector3 and SkyBoxRenderObject::setPosition are the slot-22/layout witness
// from WaterRenderObjReadSkyBoxSettings.cpp; this local view only exposes the
// three fields used by this body.
struct Vector3
{
	float X;
	float Y;
	float Z;
};

class SkyBoxRenderObject
{
public:
#define SKYBOX_SLOT(n) virtual void slot##n();
	SKYBOX_SLOT(0) SKYBOX_SLOT(1) SKYBOX_SLOT(2) SKYBOX_SLOT(3)
	SKYBOX_SLOT(4) SKYBOX_SLOT(5) SKYBOX_SLOT(6) SKYBOX_SLOT(7)
	SKYBOX_SLOT(8) SKYBOX_SLOT(9) SKYBOX_SLOT(10) SKYBOX_SLOT(11)
	SKYBOX_SLOT(12) SKYBOX_SLOT(13) SKYBOX_SLOT(14) SKYBOX_SLOT(15)
	SKYBOX_SLOT(16) SKYBOX_SLOT(17) SKYBOX_SLOT(18) SKYBOX_SLOT(19)
	SKYBOX_SLOT(20) SKYBOX_SLOT(21)
	virtual void setPosition(const Vector3 &position);
#undef SKYBOX_SLOT
};

class WaterSkyBoxSettingsOwner
{
public:
	void setSkyBoxScale(const float *p);
	void setSkyBoxRotation007A15A0(const float *p);
	void setSkyBoxTexture007A58C0(const class AsciiString *s);

	unsigned char m_beforeSkyBox[0x250];
	SkyBoxRenderObject *m_skyBox;
};

extern WaterSkyBoxSettingsOwner *TheWaterRenderObj;

void dup_007A5AB0()
{
	SkyBoxRenderObject *o = TheWaterRenderObj->m_skyBox;

	if (o != 0)
	{
		Vector3 zero;

		zero.X = 0.0f;
		zero.Y = 0.0f;
		zero.Z = 0.0f;

		o->setPosition(zero);
	}

	{
		float v = 1.0f;

		TheWaterRenderObj->setSkyBoxScale(&v);

		v = 0.0f;
		TheWaterRenderObj->setSkyBoxRotation007A15A0(&v);
	}

	{
		BFMERetailAsciiString name("DefaultSky");

		TheWaterRenderObj->setSkyBoxTexture007A58C0(
			reinterpret_cast<const AsciiString *>(&name));
	}
}

// Probe result: 189/192 bytes and 106 non-relocation bytes after EH and
// finite shape-family searches.  The remaining source-shape residue is the
// global load before the SEH prologue and the matching retail local-frame
// offsets; the Vector3 zero order and setter identities are verified.
