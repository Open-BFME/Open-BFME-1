// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// SpecialPowerModule::initiateIntentToDoSpecialPower. Retail 0x0026A2E0, 488 bytes.
//
// Zero Hour twin: SpecialPowerModule.cpp initiateIntentToDoSpecialPower -- walk
// the object's behaviour modules and hand the intent to the first special power
// update that takes this power (SpecialPowerUpdateInterface slot 0 with the
// module's template and the caller's arguments), then stop. The landed callers
// doSpecialPower 0x0026A550, doSpecialPowerAtObject 0x0026A5B0,
// doSpecialPowerAtLocation 0x0026A620 and doSpecialPowerUsingWaypoints 0x0026A690
// (SpecialPowerModuleInterface slots 11-14) call it where Zero Hour calls
// initiateIntentToDoSpecialPower.
//
// Read off the bytes, BFME departs from Zero Hour:
//  - it returns nothing: no path sets al before `ret 0x10`;
//  - the third argument is the command options (tested against 0x40000, the
//    bit every caller tests on its own commandOptions before passing it here)
//    and the fourth is only passed through to the update interface;
//  - it records the target's ID, special-cases three power types first,
//    idles the AI when the module data says IdleWhenStartingPower, and on
//    success plays the template's PalantirMovie and the module's InitiateFX.
#include "ascii_string.h"

// retail inlines the emptiness test here (m_data, then the length word at +4);
// the out-of-line copy is 0x0005E4C0
template<> inline bool StringBase<char>::isEmpty() const { return m_data == 0 || m_data->length == 0; }

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int ObjectID;

// retail SpecialPower name table 0x00EA8D40 (targets/game/reverse/name_tables.tsv), in index order
enum SpecialPowerType
{
	SPECIAL_GIVE_UPGRADE = 0x34,				// index 52
	SPECIAL_GIVE_UPGRADE_NEAREST = 0x6e,		// index 110
	SPECIAL_HARVEST = 0x73						// index 115
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class Object;
class Player;
class BfmeE5B30Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride(void)
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

	const Overridable *friend_getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

private:
	Overridable *m_nextOverride;						// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SpecialPower.h
class SpecialPowerTemplate : public Overridable
{
public:
	SpecialPowerType getSpecialPowerType(void) const { return getFO()->m_type; }
	AsciiString getPalantirMovie(void) const;

private:
	const SpecialPowerTemplate *getFO(void) const { return (const SpecialPowerTemplate *)friend_getFinalOverride(); }

	unsigned char m_unmodelled_008[0x14 - 8];
	SpecialPowerType m_type;							// +0x14 layout_witness
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	// BFME keeps an out-of-line copy at 0x00065DE0; here it is inlined.
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary)
	{
		if (fx)
		{
			if (!fx->bfmeIsBlocked())
				fx->doFXObj(primary, secondary);
		}
	}
	bool bfmeIsBlocked(void) const;
	void doFXObj(const Object *primary, const Object *secondary) const;
};

// Field offsets from the retail FieldParse table
// (SpecialPowerModuleData_buildFieldParse.cpp).
class SpecialPowerModuleData
{
public:
	unsigned char m_unmodelled_000[8];
	const SpecialPowerTemplate *m_specialPowerTemplate;	// +0x008 SpecialPowerTemplate
	unsigned char m_unmodelled_00c[0x1f0 - 0xc];
	const FXList *m_initiateFX;							// +0x1f0 InitiateFX
	unsigned char m_unmodelled_1f4[0x209 - 0x1f4];
	Bool m_idleWhenStartingPower;						// +0x209 IdleWhenStartingPower
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
	void aiBfmeCommand19(const Coord3D *pos, CommandSourceType cmdSource);
};

// The AI command interface sits at +0x20 of the object's AI (ILT 0x00024D70 pin).
struct Rva0026A2E0AIHead
{
	unsigned char m_unmodelled_000[0x20];
};

class AIUpdateInterface : public Rva0026A2E0AIHead, public AICommandInterface
{
public:
	unsigned char m_unmodelled_020[0x33a - 0x20];
	Bool m_byte33a;										// +0x33a unwitnessed
};

class SpecialAbilityUpdate;

// address-derived name of the SpecialAbilityUpdate method at 0x0025E450
class Rva0025E450Cleanup
{
public:
	void cleanup();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerUpdateModule.h
class SpecialPowerUpdateInterface
{
public:
	virtual Bool initiateIntentToDoSpecialPower(const SpecialPowerTemplate *specialPowerTemplate,
		const Object *targetObj, const Coord3D *targetPos, UnsignedInt commandOptions,
		UnsignedInt arg4) = 0;							// slot 0
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual Bool rva0026A2E0Slot07(const SpecialPowerTemplate *specialPowerTemplate) = 0;	// +0x1c
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual SpecialPowerUpdateInterface *getSpecialPowerUpdateInterface() = 0;	// slot 24, +0x60 (ObjectSpecialPowers.cpp)
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	void *m_moduleData;									// +0x04
	Object *m_object;									// +0x08
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class Player
{
public:
	unsigned char m_unmodelled_000[0x228];
	void *m_dword228;									// +0x228 unwitnessed
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ObjectID getID(void) const { return m_id; }
	Player *getControllingPlayer(void) const;
	AIUpdateInterface *getAI(void) const { return m_dword204; }
	BehaviorModule **getBehaviorModules(void) const { return m_behaviors; }
	SpecialAbilityUpdate *findSpecialAbilityUpdate(SpecialPowerType type) const;

private:
	unsigned char m_unmodelled_000[0x74];
	ObjectID m_id;										// +0x074 layout_witness
	unsigned char m_unmodelled_078[0x1f0 - 0x78];
	BehaviorModule **m_behaviors;						// +0x1f0 layout_witness
	unsigned char m_unmodelled_1f4[0x204 - 0x1f4];
	AIUpdateInterface *m_dword204;						// +0x204 unwitnessed
};

// address-derived: retail 0x000E5B30, stdcall (object, out position)
bool __stdcall rva000E5B30(BfmeE5B30Object *object, Coord3D *pos);

// address-derived global at 0x012F4B98 and its 0x00592D60 method (ILT 0x00043E4B)
class Glo012F4B98Type
{
public:
	void show00592D60(AsciiString *movie, void (*callback)(bool));
};
extern Glo012F4B98Type *Glo012F4B98;

class SpecialPowerModule : public ObjectModule
{
protected:
	void initiateIntentToDoSpecialPower(const Object *targetObj, const Coord3D *targetPos,
		UnsignedInt commandOptions, UnsignedInt arg4);

	Object *getObject(void) const { return m_object; }
	const SpecialPowerModuleData *getSpecialPowerModuleData(void) const
	{
		return (const SpecialPowerModuleData *)m_moduleData;
	}

private:
	unsigned char m_unmodelled_00c[0x24 - 0xc];
	Bool m_byte24;										// +0x24 unwitnessed
	ObjectID m_dword28;									// +0x28 unwitnessed
};

void SpecialPowerModule::initiateIntentToDoSpecialPower(const Object *targetObj,
	const Coord3D *targetPos, UnsignedInt commandOptions, UnsignedInt arg4)
{
	if (targetObj)
		m_dword28 = targetObj->getID();

	const SpecialPowerModuleData *data = getSpecialPowerModuleData();
	switch (data->m_specialPowerTemplate->getSpecialPowerType())
	{
		// Each upgrade power aborts the OTHER one's ability: retail's 0x34 case
		// pushes 0x6e and its 0x6e case pushes 0x34.
		case SPECIAL_GIVE_UPGRADE:
		{
			SpecialAbilityUpdate *update = getObject()->findSpecialAbilityUpdate(SPECIAL_GIVE_UPGRADE_NEAREST);
			if (update)
				((Rva0025E450Cleanup *)update)->cleanup();
			break;
		}
		case SPECIAL_GIVE_UPGRADE_NEAREST:
		{
			SpecialAbilityUpdate *update = getObject()->findSpecialAbilityUpdate(SPECIAL_GIVE_UPGRADE);
			if (update)
				((Rva0025E450Cleanup *)update)->cleanup();
			break;
		}
		case SPECIAL_HARVEST:
		{
			Object *obj = getObject();
			if (AIUpdateInterface *ai = obj->getAI())
			{
				Player *player = obj->getControllingPlayer();
				if (player->m_dword228)
				{
					Coord3D pos;
					if (rva000E5B30((BfmeE5B30Object *)obj, &pos))
					{
						ai->aiBfmeCommand19(&pos, CMD_FROM_AI);
						ai->m_byte33a = false;
					}
				}
			}
			break;
		}
	}

	Bool valid = false;
	for (BehaviorModule **u = getObject()->getBehaviorModules(); *u; ++u)
	{
		SpecialPowerUpdateInterface *spu = (*u)->getSpecialPowerUpdateInterface();
		if (spu && spu->rva0026A2E0Slot07(getSpecialPowerModuleData()->m_specialPowerTemplate))
		{
			spu->initiateIntentToDoSpecialPower(getSpecialPowerModuleData()->m_specialPowerTemplate,
				targetObj, targetPos, commandOptions, arg4);
			valid = true;
			break;
		}
	}

	if (getSpecialPowerModuleData()->m_idleWhenStartingPower)
	{
		AIUpdateInterface *ai = getObject()->getAI();
		if (ai)
			ai->aiIdle(CMD_FROM_AI);
	}

	if (valid)
	{
		const SpecialPowerTemplate *tmpl = getSpecialPowerModuleData()->m_specialPowerTemplate;
		AsciiString movie = tmpl->getPalantirMovie();
		if (!movie.isEmpty())
			Glo012F4B98->show00592D60(&movie, 0);

		if (commandOptions & 0x40000)	// BFME CommandOption name table: "---DO-NOT-USE---"
			m_byte24 = true;

		Object *obj = getObject();
		if (obj)
			FXList::doFXObj(data->m_initiateFX, obj, targetObj);
	}
}
