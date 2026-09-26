// cl: /DNDEBUG /MD /EHsc
//
// BFME-only Object::updateTeam.  The matched Team relationship setters at
// 0x000F46D0 and 0x000F4780 call the ILT at 0x0000902F on each live Object
// that has a contain module; that ILT routes to this body at 0x001D0FA0.
// The body walks the contain module's real STLport Object list recursively,
// calls Object's virtual setTeam slot, and idles each contained Object's real
// AICommandInterface secondary subobject.

class Team;
class Object;

// Upstream enum layout:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT,
	CMD_FROM_AI
};

// Upstream STLport list node layout for ContainedItemsList<Object *>.
struct ContainedItemNode
{
	ContainedItemNode *m_next;
	ContainedItemNode *m_previous;
	Object *m_object;
};

struct ContainedItemsList
{
	ContainedItemNode *m_sentinel;
};

// Upstream interface order from ContainModule.h, with BFME's slot 65
// getContainedItemsList placement independently matched in Object.cpp.
#define CONTAIN_SLOT(n) virtual void containSlot##n() = 0;

class ContainModuleInterface
{
public:
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31)
	CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34) CONTAIN_SLOT(35)
	CONTAIN_SLOT(36) CONTAIN_SLOT(37) CONTAIN_SLOT(38) CONTAIN_SLOT(39)
	CONTAIN_SLOT(40) CONTAIN_SLOT(41) CONTAIN_SLOT(42) CONTAIN_SLOT(43)
	CONTAIN_SLOT(44) CONTAIN_SLOT(45) CONTAIN_SLOT(46) CONTAIN_SLOT(47)
	CONTAIN_SLOT(48) CONTAIN_SLOT(49) CONTAIN_SLOT(50) CONTAIN_SLOT(51)
	CONTAIN_SLOT(52) CONTAIN_SLOT(53) CONTAIN_SLOT(54) CONTAIN_SLOT(55)
	CONTAIN_SLOT(56) CONTAIN_SLOT(57) CONTAIN_SLOT(58) CONTAIN_SLOT(59)
	CONTAIN_SLOT(60) CONTAIN_SLOT(61) CONTAIN_SLOT(62) CONTAIN_SLOT(63)
	CONTAIN_SLOT(64)
	virtual const ContainedItemsList *getContainedItemsList() const = 0;
};

#undef CONTAIN_SLOT

// The upstream AIUpdateInterface inherits UpdateModule and AICommandInterface.
// BFME places the latter's vptr at +0x20 (the retail aiIdle receiver adjustment).
class AICommandParms;

class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
	void aiIdle(CommandSourceType commandSource);
};

class UpdateModule
{
public:
	virtual ~UpdateModule();

private:
	unsigned char m_unmodelled_004[0x1c];
};

class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
};

#define OBJECT_SLOT(n) virtual void objectSlot##n() = 0;

class Object
{
public:
	OBJECT_SLOT(00) OBJECT_SLOT(01) OBJECT_SLOT(02) OBJECT_SLOT(03)
	OBJECT_SLOT(04) OBJECT_SLOT(05) OBJECT_SLOT(06) OBJECT_SLOT(07)
	OBJECT_SLOT(08) OBJECT_SLOT(09) OBJECT_SLOT(10) OBJECT_SLOT(11)
	OBJECT_SLOT(12) OBJECT_SLOT(13) OBJECT_SLOT(14) OBJECT_SLOT(15)
	OBJECT_SLOT(16) OBJECT_SLOT(17) OBJECT_SLOT(18) OBJECT_SLOT(19)
	virtual void setTeam(Team *team) = 0;

	void updateTeam(Team *team);

	unsigned char m_unmodelled_004[0x1FC - 4];
	ContainModuleInterface *m_contain;
	unsigned char m_unmodelled_200[0x204 - 0x200];
	AIUpdateInterface *m_ai;
};

#undef OBJECT_SLOT

// ?updateTeam@Object@@QAEXPAVTeam@@@Z
void Object::updateTeam(Team *team)
{
	ContainModuleInterface *contain = m_contain;
	if (contain)
	{
		const ContainedItemsList *items = contain->getContainedItemsList();
		ContainedItemNode *node = items->m_sentinel->m_next;
		if (node != items->m_sentinel)
		{
			do
			{
				Object *object = node->m_object;
				if (object->m_contain)
					object->updateTeam(team);

				object->setTeam(team);

				AIUpdateInterface *ai = object->m_ai;
				if (ai)
					ai->AICommandInterface::aiIdle(CMD_FROM_AI);

				node = node->m_next;
			} while (node != items->m_sentinel);
		}
	}
}
