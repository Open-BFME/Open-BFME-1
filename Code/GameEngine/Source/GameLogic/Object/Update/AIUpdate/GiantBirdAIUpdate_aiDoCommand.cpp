// ?aiDoCommand@GiantBirdAIUpdate@@UAEXPBUAICommandParms@@@Z
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source
// stlport
// Constructor 0x002C2430 installs secondary vtable 0x010C7E68. Slot 0 resolves through ILT 0x00005DA8 to this body, and AICommandInterface names that slot aiDoCommand. This dispatcher calls the matched GiantBirdAIUpdate waypoint helper at 0x002C2C10 for commands 6, 7, 0x32, and 0x33.

#define _STLP_NO_EXCEPTIONS 1
#include "GameLogic/AI.h"

class Rva002C2E30CompleteView
{
public:
	virtual void unused000() = 0;
	virtual void unused001() = 0;
	virtual void unused002() = 0;
	virtual void unused003() = 0;
	virtual void unused004() = 0;
	virtual void unused005() = 0;
	virtual void unused006() = 0;
	virtual void unused007() = 0;
	virtual void unused008() = 0;
	virtual void unused009() = 0;
	virtual void unused010() = 0;
	virtual void unused011() = 0;
	virtual void unused012() = 0;
	virtual void unused013() = 0;
	virtual void unused014() = 0;
	virtual void unused015() = 0;
	virtual void unused016() = 0;
	virtual void unused017() = 0;
	virtual void unused018() = 0;
	virtual void unused019() = 0;
	virtual void unused020() = 0;
	virtual void unused021() = 0;
	virtual void unused022() = 0;
	virtual void unused023() = 0;
	virtual void unused024() = 0;
	virtual void unused025() = 0;
	virtual void unused026() = 0;
	virtual void unused027() = 0;
	virtual void unused028() = 0;
	virtual void unused029() = 0;
	virtual void unused030() = 0;
	virtual void unused031() = 0;
	virtual void unused032() = 0;
	virtual void unused033() = 0;
	virtual void unused034() = 0;
	virtual void unused035() = 0;
	virtual void unused036() = 0;
	virtual void unused037() = 0;
	virtual void unused038() = 0;
	virtual void handleCommand(CommandSourceType source) = 0;
	virtual void unused040() = 0;
	virtual void unused041() = 0;
	virtual void unused042() = 0;
	virtual void unused043() = 0;
	virtual void unused044() = 0;
	virtual void unused045() = 0;
	virtual void unused046() = 0;
	virtual void unused047() = 0;
	virtual void unused048() = 0;
	virtual void unused049() = 0;
	virtual void unused050() = 0;
	virtual void unused051() = 0;
	virtual void unused052() = 0;
	virtual void unused053() = 0;
	virtual void unused054() = 0;
	virtual void unused055() = 0;
	virtual void unused056() = 0;
	virtual void unused057() = 0;
	virtual void unused058() = 0;
	virtual void unused059() = 0;
	virtual void unused060() = 0;
	virtual void unused061() = 0;
	virtual void unused062() = 0;
	virtual void unused063() = 0;
	virtual void unused064() = 0;
	virtual void unused065() = 0;
	virtual void unused066() = 0;
	virtual void unused067() = 0;
	virtual void unused068() = 0;
	virtual void unused069() = 0;
	virtual void unused070() = 0;
	virtual void unused071() = 0;
	virtual void unused072() = 0;
	virtual void unused073() = 0;
	virtual void unused074() = 0;
	virtual void unused075() = 0;
	virtual void unused076() = 0;
	virtual void unused077() = 0;
	virtual void unused078() = 0;
	virtual void unused079() = 0;
	virtual void unused080() = 0;
	virtual void unused081() = 0;
	virtual void unused082() = 0;
	virtual void unused083() = 0;
	virtual void unused084() = 0;
	virtual void unused085() = 0;
	virtual void unused086() = 0;
	virtual void unused087() = 0;
	virtual void unused088() = 0;
	virtual void unused089() = 0;
	virtual void unused090() = 0;
	virtual void unused091() = 0;
	virtual void unused092() = 0;
	virtual void unused093() = 0;
	virtual void unused094() = 0;
	virtual void unused095() = 0;
	virtual void unused096() = 0;
	virtual void unused097() = 0;
	virtual void unused098() = 0;
	virtual void unused099() = 0;
	virtual void unused100() = 0;
	virtual void unused101() = 0;
	virtual void unused102() = 0;
	virtual void unused103() = 0;
	virtual void unused104() = 0;
	virtual void unused105() = 0;
	virtual void unused106() = 0;
	virtual void unused107() = 0;
	virtual void unused108() = 0;
	virtual void unused109() = 0;
	virtual void unused110() = 0;
	virtual void unused111() = 0;
	virtual void unused112() = 0;
	virtual void unused113() = 0;
	virtual void unused114() = 0;
	virtual void unused115() = 0;
	virtual void unused116() = 0;
	virtual void unused117() = 0;
	virtual void unused118() = 0;
	virtual void unused119() = 0;
	virtual void unused120() = 0;
	virtual void unused121() = 0;
	virtual void unused122() = 0;
	virtual void unused123() = 0;
	virtual void unused124() = 0;
	virtual void unused125() = 0;
	virtual void unused126() = 0;
	virtual void unused127() = 0;
	virtual void unused128() = 0;
	virtual void unused129() = 0;
	virtual void unused130() = 0;
	virtual void unused131() = 0;
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const = 0;
};

class Rva002BC470StateAction
{
public:
	void run(void *first, void *second);
};

class Rva002BC540StateAction
{
public:
	void run(void *first, void *second, unsigned char third);
};

class Rva002BC4E0StateAction
{
public:
	void run(void *first, void *second);
};

class Rva002BC670StateAction
{
public:
	void run(void *first, void *second);
};

class GiantBirdAIUpdate
{
public:
	void followWaypointPathRva002C2C10(const Waypoint *way, Bool asTeam,
		CommandSourceType source);
	virtual void aiDoCommand(const AICommandParms *parms);
};

class AIUpdateInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms);
};

void GiantBirdAIUpdate::aiDoCommand(const AICommandParms *parms)
{
	unsigned char *ownerBytes = (unsigned char *)this - 0x20;
	Rva002C2E30CompleteView *owner =
		(Rva002C2E30CompleteView *)ownerBytes;
	if (!owner->isAllowedToRespondToAiCommands(parms))
		return;

	if (*(Bool *)((char *)this + 0x470))
	{
		((AICommandParmsStorage *)((char *)this + 0x32c))->store(*parms);
		return;
	}

	*(Int *)((char *)this + 0x32c) = -1;
	switch (parms->m_cmd)
	{
	case (AICommandType)0:
		((Rva002BC470StateAction *)ownerBytes)->run(
			(void *)&parms->m_pos,
			(void *)parms->m_cmdSource);
		return;
	case (AICommandType)0x3f:
		((Rva002BC540StateAction *)ownerBytes)->run(
			parms->m_obj, (void *)parms->m_cmdSource, 1);
		return;
	case (AICommandType)0x0b:
	case (AICommandType)0x0c:
	case (AICommandType)0x39:
		((Rva002BC540StateAction *)ownerBytes)->run(
			parms->m_obj, (void *)parms->m_cmdSource, 0);
		return;
	case (AICommandType)0x23:
		((Rva002BC670StateAction *)ownerBytes)->run(
			(void *)parms->m_polygon, (void *)parms->m_cmdSource);
		return;
	case (AICommandType)0x12:
		owner->handleCommand(parms->m_cmdSource);
		return;
	case (AICommandType)6:
	case (AICommandType)0x32:
		((GiantBirdAIUpdate *)ownerBytes)->followWaypointPathRva002C2C10(
			parms->m_waypoint, false, parms->m_cmdSource);
		return;
	case (AICommandType)7:
	case (AICommandType)0x33:
		((GiantBirdAIUpdate *)ownerBytes)->followWaypointPathRva002C2C10(
			parms->m_waypoint, true, parms->m_cmdSource);
		return;
	case (AICommandType)0x0f:
		((Rva002BC4E0StateAction *)ownerBytes)->run(
			(void *)&parms->m_pos, (void *)parms->m_cmdSource);
		return;
	case (AICommandType)0x0e:
	case (AICommandType)0x40:
		return;
	default:
		*(unsigned int *)(ownerBytes + 0x3f0) &= 0xfffffffe;
		((AIUpdateInterface *)this)->AIUpdateInterface::aiDoCommand(parms);
		return;
	}
}
