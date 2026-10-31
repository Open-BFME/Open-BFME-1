// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline /Igame/Libraries/Include
// ScriptActions action body at retail RVA 0x002F22A0, 266 bytes (ret 4 at
// +0x105). executeAction (0x00303BF0) calls it; its incremental-link thunk is
// 0x00041E93. The former ledger name doPlaySoundEffect is CONTRADICTED by
// tools/ilt_oracle.py at that thunk, as is every other ScriptActions method
// name known to the repo with this signature, so the method keeps an
// address-derived name (targets/game/reverse/identity_evidence/
// 002f22a0-team-home-group.md).
//
// Body: look the team up by name, build an AI group from it, count its
// members (empty KindOf masks), take the team's home position, then send the
// group there: through the 0x0015A190 helper when the team has more than one
// member, otherwise straight through that helper's packet fallback.
#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "Lib/Coord3D.h"

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_words[6];
};
typedef BitFlags<116> KindOfMaskType;
// KINDOFMASK_NONE is defined once, as the 24-byte BitFlags<192> in
// Common/System/KindOf.cpp (data_rows.csv, 0x012ED8B8); this unit's narrower
// mask view reads that definition.
extern "C" const char __identifier("?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B")[24];
#define KINDOFMASK_NONE (*reinterpret_cast<const KindOfMaskType *>(__identifier("?KINDOFMASK_NONE@@3V?$BitFlags@$0MA@@@B")))

class AIGroup;

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual class Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};
extern ScriptEngine *TheScriptEngine;

class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
	Int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
	Coord3D *getHomePosition(Coord3D *pos);
};

class AI
{
public:
	AIGroup *createGroup();
};
extern AI *TheAI;

struct Rva0015A190Packet
{
	void *m_first;
	unsigned char m_flag;
	void *m_objA;
	void *m_objB;
};

class Rva0015A190Owner
{
public:
	void applyPacket(Rva0015A190Packet *packet, int b);
	void applyOrFallback(void *a, int b, void *c, void *d);
};

class ScriptActions
{
protected:
	void rva002F22A0(const AsciiString &teamName);
};

// ?rva002F22A0@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::rva002F22A0(const AsciiString &teamName)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	AIGroup *theGroup = TheAI->createGroup();
	if (!theGroup)
		return;

	theTeam->getTeamAsAIGroup(theGroup);
	Int count = theTeam->countObjects(KINDOFMASK_NONE, KINDOFMASK_NONE);
	Coord3D home;
	theTeam->getHomePosition(&home);
	if (count > 1)
	{
		((Rva0015A190Owner *)theGroup)->applyOrFallback(&home, 1, 0, (void *)1);
	}
	else
	{
		Rva0015A190Packet packet;
		packet.m_first = &home;
		packet.m_flag = 0;
		packet.m_objA = 0;
		packet.m_objB = 0;
		((Rva0015A190Owner *)theGroup)->applyPacket(&packet, 1);
	}
}
