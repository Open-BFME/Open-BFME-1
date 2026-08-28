// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?canUseSpecialPower@SpecialPowerStore@@: Code/GameEngine/Source/Common/RTS/SpecialPower.cpp
// Lift the SpecialPowerStore::canUseSpecialPower naked dump to clean C++.
//
// Zero Hour's SpecialPower.cpp body plus one BFME addition: where ZH ends with
// `return TRUE`, retail asks the controlling player one more question about the
// template and returns that. Two of the callees were already pinned and confirm
// the middle of the body outright -- Object::getSpecialPowerModule and
// Player::hasScience -- and the controlling-player accessor reads the team at
// obj+0x23C and forwards, which is what makes its result a Player.
//
// getRequiredScience is not a plain field read. The template derives from the
// overridable chain, and retail walks it with one level unrolled: if there is
// an override it steps to it, and only if that one also has an override does it
// call the out-of-line walker, which loops to the end. So a single-entry chain
// costs no call at all.
//
// The last callee is not identified. It takes the template, reads a global at
// 0x012F0FF8 and forwards to it with a subobject at player+0x274, returning
// false when that global is null. Only that shape is proven, so it keeps a
// _bfme_ name rather than an invented one.
//
// Retail pins the layout: the override link is at +0x04 of the chain base and
// the required science at template+0x1C.

typedef int Int;
typedef bool Bool;

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

enum ScienceType { SCIENCE_INVALID = -1 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();								///< the vtable pointer occupies +0x00

	// non-const, matching the pin already in symbols.csv
	Overridable *friend_getFinalOverride(void);			///< ILT thunk at 0x00048C61

	Overridable *m_nextOverride;						///< retail this+0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Bool hasScience(ScienceType science) const;			///< ILT thunk at 0x0000943F

	// Shape only: forwards the template to the global at 0x012F0FF8 together
	// with a subobject at this+0x274, and answers false when that global is
	// absent. Not identified beyond that.
	unsigned char _bfme_allowsSpecialPower(const SpecialPowerTemplate *tmpl);	///< ILT thunk at 0x0000226B
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	ScienceType getRequiredScience(void) const
	{
		const SpecialPowerTemplate *self;
		Overridable *o = m_nextOverride;
		if (o)
		{
			if (o->m_nextOverride)
				o = o->m_nextOverride->friend_getFinalOverride();
			self = (const SpecialPowerTemplate *)o;
		}
		else
			self = this;
		return self->m_requiredScience;
	}

private:
	unsigned char m_unreconstructed_08[0x1C - 8];
	ScienceType m_requiredScience;						///< retail this+0x1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *tmpl) const;	///< ILT thunk at 0x000401BF
	Player *getControllingPlayer(void) const;			///< ILT thunk at 0x00020824
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerStore
{
public:
	Bool canUseSpecialPower(Object *obj, const SpecialPowerTemplate *specialPowerTemplate);
};

// ?canUseSpecialPower@SpecialPowerStore@@QAE_NPAVObject@@PBVSpecialPowerTemplate@@@Z
Bool SpecialPowerStore::canUseSpecialPower( Object *obj, const SpecialPowerTemplate *specialPowerTemplate )
{

	// sanity
	if( obj == 0 || specialPowerTemplate == 0 )
		return false;

	// as a first sanity check, the object must have a module capable of executing the power
	if( obj->getSpecialPowerModule( specialPowerTemplate ) == 0 )
		return false;

	// check for requried science
	ScienceType requiredScience = specialPowerTemplate->getRequiredScience();
	if( requiredScience != SCIENCE_INVALID )
	{
		Player *player = obj->getControllingPlayer();

		if( player->hasScience( requiredScience ) == false )
			return false;

	}  // end if

	// the callee answers with a byte, so narrowing it to the bool this function
	// returns is what produces the test/setne rather than a plain passthrough
	return obj->getControllingPlayer()->_bfme_allowsSpecialPower( specialPowerTemplate );

}
