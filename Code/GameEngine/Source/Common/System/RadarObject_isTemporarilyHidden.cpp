// readable body of ?isTemporarilyHidden@RadarObject@@QBE_NXZ: Code/GameEngine/Source/Common/System/Radar.cpp
// BFME retail RadarObject visibility predicate, 0x00106B90.
// Identity is fixed by W3DRadar::renderObjectList: its matched body calls this
// helper at the source loop's isTemporarilyHidden() test.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	bool isDrawableEffectivelyHidden() const;

	unsigned char m_pad[0x15c];
	int m_stealthLook;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual Drawable *getDrawable() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Radar.h
class RadarObject
{
public:
	bool isTemporarilyHidden() const;

private:
	RadarObject *m_next;
	Object *m_object;
};

// ?isTemporarilyHidden@RadarObject@@QBE_NXZ
bool RadarObject::isTemporarilyHidden() const
{
	Drawable *draw = m_object->getDrawable();
	if (draw->m_stealthLook == 5 || draw->isDrawableEffectivelyHidden())
		return true;

	return false;
}
