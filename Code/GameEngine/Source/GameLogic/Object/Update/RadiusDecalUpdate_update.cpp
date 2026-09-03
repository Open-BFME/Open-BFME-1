// cl: /DNDEBUG /MD /EHsc
// RadiusDecalUpdate::update, retail 0x002A0840. ZH body in
// RadiusDecalUpdate.cpp: if kill-when-not-attacking and the object is not
// attacking, clear the decal and sleep forever; otherwise pulse the decal.
// `this` is the UpdateModule interface at +0x10, so the object pointer is at
// this-8 and the RadiusDecal subobject is at this+0x10.

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	unsigned char m_pad[0x90];
	unsigned int m_status;	// +0x90
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/RadiusDecal.h
class RadiusDecal
{
public:
	void clear();
	void update();

private:
	const void *m_template;
	void *m_decal;
	int m_empty;
	int m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RadiusDecalUpdate.h
class RadiusDecalUpdate
{
public:
	UpdateSleepTime update();

private:
	unsigned char m_pad10[0x10];
	RadiusDecal m_deliveryDecal;			// +0x10
	bool m_killWhenNoLongerAttacking;		// +0x20
};

// ?update@RadiusDecalUpdate@@QAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime RadiusDecalUpdate::update()
{
	Object *obj = *(Object **)((char *)this - 8);

	if (m_killWhenNoLongerAttacking && (obj->m_status & 0x400000) == 0)
	{
		m_deliveryDecal.clear();
		return UPDATE_SLEEP_FOREVER;
	}

	m_deliveryDecal.update();
	return UPDATE_SLEEP_NONE;
}
