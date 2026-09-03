// BFME drawable/template predicate at retail 0x00419E40.
//
// The first virtual call is Object::getDrawable (slot 10).  The remaining
// object and drawable offsets are kept in local views because this helper's
// original source identity is not recovered.  The predicate reached through
// the final template is likewise address-derived at ILT 0x00007DF6.

typedef unsigned int UnsignedInt;

enum KindOfType
{
	KINDOF_SMALL_MISSILE = 47
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_unreconstructed_008[0x45C - 8];
	UnsignedInt m_field045C;

	bool bfmeTemplatePredicate() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_unreconstructed_008[0x3B0 - 8];
	unsigned char m_flag03B0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	virtual void bfmeSlot00();
	virtual void bfmeSlot01();
	virtual void bfmeSlot02();
	virtual void bfmeSlot03();
	virtual void bfmeSlot04();
	virtual void bfmeSlot05();
	virtual void bfmeSlot06();
	virtual void bfmeSlot07();
	virtual void bfmeSlot08();
	virtual void bfmeSlot09();
	virtual Drawable *getDrawable() const;

	bool isKindOf(KindOfType kind) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	bool query(Object *viewer, int extra);

	unsigned char m_unreconstructed_004[0x344 - 4];
	unsigned char m_privateStatus;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList
{
private:
	unsigned char m_unreconstructed_000[0x0C];

public:
	Object *m_localPlayer;
};

extern PlayerList *ThePlayerList;

class Rva00419E40Context
{
public:
	Drawable *m_drawable;
	UnsignedInt m_field04;
};

int bfmeDrawableFilter00419E40(Object *object, Rva00419E40Context *context)
{
	Drawable *drawable;
	ThingTemplate *thingTemplate;
	ThingTemplate *finalTemplate;

	if (object == 0)
		goto failure;

	drawable = object->getDrawable();
	if (drawable == context->m_drawable || drawable == 0)
		goto failure;

	if (drawable->m_flag03B0 != 0)
		goto failure;

	thingTemplate = drawable->m_template;
	if (thingTemplate == 0)
		goto failure;

	if (thingTemplate->m_nextOverride != 0)
		finalTemplate = (ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
	else
		finalTemplate = thingTemplate;

	if (finalTemplate == 0)
		goto failure;
	if (!finalTemplate->bfmeTemplatePredicate())
		goto failure;
	if (finalTemplate->m_field045C != context->m_field04)
		goto failure;
	if ((object->m_privateStatus & 1) != 0)
		goto failure;
	if (!object->query(ThePlayerList->m_localPlayer, 1))
		goto failure;
	if (object->isKindOf(KINDOF_SMALL_MISSILE))
		goto failure;

	return false;

failure:
	return true;
}
