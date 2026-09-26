// ?flash@Rva0041A2E0@@QAEXPBURGBColor@@@Z
// partial score=0.3 date=2026-09-24
// Address-qualified reconstruction of retail 0x0041A2E0. This does not claim
// Drawable::flashAsSelected, which is already assigned to 0x0076E4F0.
#include <list>
#include "../../Code/Libraries/Source/WWVegas/WWMath/color.h"

typedef unsigned int UnsignedInt;
enum KindOfType { RvaSelectionHordeKind = 0x6c };

class TintEnvelope
{
public:
	void play(const RGBColor *, UnsignedInt, UnsignedInt, UnsignedInt);
};

// The verified retail constructor allocates and initializes a 0x50-byte body.
class Rva00412140
{
	unsigned char m_layout[0x50];
public:
	Rva00412140();
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_next;
	unsigned char m_beforeFlags[0xc4];
	const Overridable *getFinalOverride() const;
	unsigned int m_flags;
};

class RvaSelectionOverrideLink
{
public:
	void *m_vtable;
	Overridable *m_next;
};

class Drawable;
class Thing
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09();
	virtual Drawable *getDrawable() const;
	bool isKindOf(KindOfType) const;
};

class Object : public Thing
{
	unsigned char m_toProducer[0x78 - 4];
public:
	unsigned int m_producerID;
	unsigned char m_toContain[0x1fc - 0x7c];
	class RvaSelectionContain *m_contain;
	unsigned int getIndicatorColor() const;
};

class RvaSelectionHorde
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56();
	virtual void slot57(); virtual void slot58(); virtual void slot59();
virtual void getContainedObjects(std::list<Object *> *);
};

class RvaSelectionContain
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual RvaSelectionHorde *getHorde();
};

class Rva0041A2E0
{
	unsigned int m_vtable;
public:
	RvaSelectionOverrideLink *m_gate;
	unsigned char m_toEnvelope[0x64 - 8];
	TintEnvelope *m_selectionEnvelope;
	unsigned char m_toObject[0xfc - 0x68];
	Object *m_object;
	void flash(const RGBColor *);
};

struct Rva006C9270GlobalData
{
	unsigned char m_beforeSaturation[0xbf0];
public:
	float m_selectionSaturation;
	unsigned char m_selectionHouseColor;
};
extern Rva006C9270GlobalData *TheWritableGlobalData;
extern const float g_bfmeK1253;

void Rva0041A2E0::flash(const RGBColor *color)
{
	Rva0041A2E0 *self = this;
	RvaSelectionOverrideLink *link = self->m_gate;
	Overridable *overrideState = (Overridable *)link;
	if (link && link->m_next)
		overrideState = (Overridable *)link->m_next->getFinalOverride();
	if (overrideState->m_flags & 0x08000000)
		return;

	Object *object = self->m_object;
	if (object && object->isKindOf(RvaSelectionHordeKind) && object->m_contain)
	{
		RvaSelectionHorde *horde = object->m_contain->getHorde();
		if (horde)
		{
			std::list<Object *> contained;
			horde->getContainedObjects(&contained);
			for (std::list<Object *>::iterator it = contained.begin();
				it != contained.end(); ++it)
			{
				Object *child = *it;
				if (child)
				{
					Drawable *childDrawable = child->getDrawable();
					if (childDrawable)
						((Rva0041A2E0 *)childDrawable)->flash(color);
				}
			}
			return;
		}
	}

	if (self->m_selectionEnvelope == 0)
	{
		Rva00412140 *created = new Rva00412140;
		self->m_selectionEnvelope = (TintEnvelope *)created;
	}

	if (color)
	{
		self->m_selectionEnvelope->play(color, 0, 4, 1);
		return;
	}
	// Retail reloads Drawable+0xfc after recursive calls, which may mutate it.
	object = self->m_object;
	if (object == 0)
		return;

	RGBColor selectedColor;
	if (TheWritableGlobalData->m_selectionHouseColor)
		selectedColor.setFromInt(object->getIndicatorColor());
	else
		selectedColor.setFromInt(-1);

	float saturation = TheWritableGlobalData->m_selectionSaturation;
	selectedColor.red *= saturation;
	selectedColor.green *= saturation;
	selectedColor.blue *= saturation;
	float halfSaturation = saturation * g_bfmeK1253;
	selectedColor.red -= halfSaturation;
	selectedColor.green -= halfSaturation;
	selectedColor.blue -= halfSaturation;
	self->m_selectionEnvelope->play(&selectedColor, 0, 4, 1);
}
