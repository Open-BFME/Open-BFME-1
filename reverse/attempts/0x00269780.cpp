// ?d_00269780@@YAXXZ
// partial score=0.37 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x00269780 consumes special-power target records from a result vector.

#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef float Real;
typedef int NameKeyType;

class Module;
class Player;
class AttributeModifierPoolUpdate;

class GameLogic
{
public:
	UnsignedInt getFrame() const
	{
		return *(const UnsignedInt *)((const char *)this + 0x3c);
	}
};

extern GameLogic *TheBfmeGameLogic;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class AttributeModifierDefinitionStore
{
public:
	Int indexOf(Int key) const;
	Int valueAt(Int index) const;
};

extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;
};

class Rva00269780SpecialPowerOverride
{
public:
	void *vtable;
	Rva00269780SpecialPowerOverride *m_nextOverride;
	const Rva00269780SpecialPowerOverride *getFinalOverride() const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Module *findModule(NameKeyType key) const;
	Bool applyAttributeModifier(const AsciiString &name, Int duration);
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
	Int getRelationship(const Object *other) const;
};

class Rva00269780ExperienceTracker
{
public:
	Bool gainExpForLevel(Int levels, Bool canScaleForBonus, Bool provideFeedback);
};

class BfmeThing932D
{
public:
	char go();
};

class Rva00269780AttributeModifierPool
{
public:
	void set(Int index, UnsignedInt value);
};

class FXList
{
public:
	Bool isEmpty() const;
	void doFXObj(const Object *primary, const Object *secondary) const;
};

class Rva00269780Helper
{
public:
	void run(Int value);
};

#pragma comment(linker, "/alternatename:?nameToKey@NameKeyGenerator@@QAE?AW4NameKeyType@@PBD@Z=?j_0003add7@@YAXXZ")
#pragma comment(linker, "/alternatename:?indexOf@AttributeModifierDefinitionStore@@QBEHH@Z=?j_000268e6@@YAXXZ")
#pragma comment(linker, "/alternatename:?valueAt@AttributeModifierDefinitionStore@@QBEHH@Z=?j_0001e281@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")
#pragma comment(linker, "/alternatename:?getFinalOverride@Rva00269780SpecialPowerOverride@@QBEPBV1@XZ=?j_00048c61@@YAXXZ")
#pragma comment(linker, "/alternatename:?getControllingPlayer@Object@@QBEPAVPlayer@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?findModule@Object@@IBEPAVModule@@W4NameKeyType@@@Z=?j_0002ae23@@YAXXZ")
#pragma comment(linker, "/alternatename:?applyAttributeModifier@Object@@QAE_NABVAsciiString@@H@Z=?j_00037a56@@YAXXZ")
#pragma comment(linker, "/alternatename:?findAttributeModifierPoolUpdate@Object@@ABEPAVAttributeModifierPoolUpdate@@XZ=?j_000202ed@@YAXXZ")
#pragma comment(linker, "/alternatename:?getRelationship@Object@@QBE?AW4Relationship@@PBV1@@Z=?j_0004a719@@YAXXZ")
#pragma comment(linker, "/alternatename:?gainExpForLevel@Rva00269780ExperienceTracker@@QAE_NH_N0@Z=?j_0004a12e@@YAXXZ")
#pragma comment(linker, "/alternatename:?go@BfmeThing932D@@QAEDXZ=?j_0001fde3@@YAXXZ")
#pragma comment(linker, "/alternatename:?set@Rva00269780AttributeModifierPool@@QAEXII@Z=?j_0001c0da@@YAXXZ")
#pragma comment(linker, "/alternatename:?isEmpty@FXList@@QBE_NXZ=?j_00011f77@@YAXXZ")
#pragma comment(linker, "/alternatename:?doFXObj@FXList@@QBEXPBVObject@@0@Z=?j_00022bba@@YAXXZ")
#pragma comment(linker, "/alternatename:?run@Rva00269780Helper@@QAEXH@Z=?j_0003b5b1@@YAXXZ")

struct Rva00269780StringData
{
	Int refCount;
	unsigned short length;
	unsigned short capacity;
};

struct Rva00269780Pair
{
	Int first;
	Int second;
};

struct Rva00269780Payload
{
	Rva00269780Pair *begin;
	Rva00269780Pair *end;
	Rva00269780Pair *storageEnd;
	Rva00269780Pair *cursor;
	Int refCount;
};

struct Rva009F3C70Result
{
	Rva00269780Payload *value;
};

struct Rva00269780Data
{
	unsigned char pad000[0x1d0];
	AsciiString attributeModifier;
	Real attributeModifierRange;
	Bool attributeModifierAffectsSelf;
	unsigned char pad1d9[0x1e0 - 0x1d9];
	FXList *attributeModifierFX;
	unsigned char pad1e4[4];
	UnsignedInt antiCategory;
	Bool targetEnemy;
	Bool targetAllSides;
	Bool reEnableAntiCategory;
	unsigned char pad1ef[0x1f0 - 0x1ef];
	FXList *initiateFX;
	FXList *triggerFX;
	FXList *antiFX;
	Int setModelCondition;
	Real setModelConditionTime;
	Int giveLevels;
	Bool disableDuringAnimDuration;
	Bool idleWhenStartingPower;
	Bool affectGood;
	Bool affectEvil;
	Bool affectAllies;
	Bool availableAtStart;
};

static Rva00269780StringData *stringData(const AsciiString &value)
{
	return *(Rva00269780StringData *const *)&value;
}

static const char *stringText(const AsciiString &value)
{
	Rva00269780StringData *data = stringData(value);
	return data ? (const char *)data + 8 : (const char *)0x0107388b;
}

class Rva00269780Owner
{
public:
	void apply(Rva009F3C70Result *result);

private:
	unsigned char pad000[4];
	Rva00269780Data *m_data;
	Object *m_object;
};

void Rva00269780Owner::apply(Rva009F3C70Result *result)
{
	register Rva00269780Data *data = m_data;
	register Object *owner = m_object;

	Rva00269780SpecialPowerOverride *powerTemplate =
		*(Rva00269780SpecialPowerOverride **)((char *)data + 8);
	Rva00269780SpecialPowerOverride *powerOverride = powerTemplate->m_nextOverride;
	if (powerOverride == 0)
		return;
	Rva00269780SpecialPowerOverride *powerOverrideNext = powerOverride->m_nextOverride;
	if (powerOverrideNext == 0)
		return;
	const Rva00269780SpecialPowerOverride *templateFinal =
		powerOverrideNext->getFinalOverride();
	if (*(Int *)((const char *)templateFinal + 0x14) != 0x6b)
		return;

	if ((*(UnsignedInt *)((const char *)owner + 0x130) & 0x800) == 0)
		return;

	volatile UnsignedInt *keyGuard = (volatile UnsignedInt *)0x012efd64;
	volatile NameKeyType *keyStorage = (volatile NameKeyType *)0x012efd60;
	if ((*keyGuard & 1) == 0)
	{
		*keyGuard |= 1;
		*keyStorage = TheNameKeyGenerator->nameToKey(
			"AttributeModifierPoolUpdate");
	}

	Module *module = owner->findModule(*keyStorage);
	if (module != 0)
		((Rva00269780Helper *)module)->run(0);

	Rva00269780StringData *attribute = stringData(data->attributeModifier);
	Bool hasAttribute = attribute != 0 && attribute->length != 0;
	UnsignedInt frame = 0;
	UnsignedInt category = 7;
	if (data->antiCategory != 0)
	{
		if (hasAttribute)
		{
			frame = TheBfmeGameLogic->getFrame();
			NameKeyType attrKey = TheNameKeyGenerator->nameToKey(
				stringText(data->attributeModifier));
			Int attrIndex = TheAttributeModifierDefinitionStore->indexOf(attrKey);
			Int attrValue = TheAttributeModifierDefinitionStore->valueAt(attrIndex);
			frame += attrValue > 0 ? attrValue : 0xf423f;
		}
		category = data->antiCategory;
	}

	for (;;)
	{
		Rva00269780Payload *payload = result->value;
		Rva00269780Pair *cursor = payload->cursor;
		if (cursor == payload->end)
			break;
		register Object *target = (Object *)(unsigned int)cursor->first;
		payload->cursor = cursor + 1;
		if (target == 0)
			continue;

		Overridable *targetTemplate = *(Overridable **)((char *)target + 4);
		if (targetTemplate == 0)
			continue;
		const Overridable *targetFinal = targetTemplate->getFinalOverride();
		if (*(Bool *)((const char *)targetFinal + 0xcd))
			continue;

		if (!data->attributeModifierAffectsSelf && target == owner)
			continue;
		if (data->affectGood)
		{
			Player *player = target->getControllingPlayer();
			void *team = player ? *(void **)((char *)player + 4) : 0;
			if (team && *(Bool *)((char *)team + 0x118))
				continue;
		}
		if (data->affectEvil)
		{
			Player *player = target->getControllingPlayer();
			void *team = player ? *(void **)((char *)player + 4) : 0;
			if (!team || !*(Bool *)((char *)team + 0x118))
				continue;
		}
		if (!data->affectAllies &&
			target->getControllingPlayer() != owner->getControllingPlayer())
			continue;

		Rva00269780ExperienceTracker *tracker =
			*(Rva00269780ExperienceTracker **)((char *)target + 0x210);
		if (tracker && data->giveLevels > 0)
		{
			Int levels = data->giveLevels;
			while (levels > 0)
			{
				if (!((BfmeThing932D *)tracker)->go())
					break;
				tracker->gainExpForLevel(1, true, false);
				--levels;
			}
		}

		if (hasAttribute)
		{
			AsciiString temporary(stringText(data->attributeModifier));
			target->applyAttributeModifier(temporary, -1);
		}

		if (frame != 0 && category != 7)
		{
			Rva00269780AttributeModifierPool *pool =
				(Rva00269780AttributeModifierPool *)
				target->findAttributeModifierPoolUpdate();
			Bool applyAnti = false;
			if (*(Bool *)((char *)data + 0x1ee))
			{
				if (data->affectEvil)
				{
					Player *player = target->getControllingPlayer();
					void *team = player ? *(void **)((char *)player + 4) : 0;
					if (team && *(Bool *)((char *)team + 0x118))
						applyAnti = true;
				}
				if (data->affectGood)
				{
					Player *player = target->getControllingPlayer();
					void *team = player ? *(void **)((char *)player + 4) : 0;
					if (team && !*(Bool *)((char *)team + 0x118))
						applyAnti = true;
				}
			}
			if (!data->affectEvil && !data->affectGood &&
				owner->getRelationship(target) == 2)
				applyAnti = true;
			if (applyAnti)
				pool->set((Int)category, frame);
		}

		FXList *antiFX = data->antiFX;
		if (antiFX && !antiFX->isEmpty())
			antiFX->doFXObj(target, 0);

		FXList *modifierFX = data->attributeModifierFX;
		if (modifierFX)
		{
			Overridable *finalTargetTemplate = *(Overridable **)((char *)target + 4);
			if (finalTargetTemplate != 0)
			{
				finalTargetTemplate = (Overridable *)
					finalTargetTemplate->getFinalOverride();
				if (!(*(unsigned char *)((char *)finalTargetTemplate + 0xd5) & 0x10) &&
					!modifierFX->isEmpty())
					modifierFX->doFXObj(target, 0);
			}
		}
	}
}
