// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?aiDoCommand@AIUpdateInterface@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate.cpp
// Open-BFME: AIUpdateInterface::aiDoCommand, retail 0x00277780, 1953 bytes.
//
// The BFME dispatcher is reached through AICommandInterface's secondary vtable
// at AIUpdateInterface+0x20.  Its primary vtable has BFME-only virtuals before
// the Zero Hour command surface, so the slot-only base below is intentional.

typedef bool Bool;
typedef int Int;

class Object;
class Team;
class Waypoint;
class PolygonTrigger;
class CommandButton;
class Path;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
struct AICommandParms
{
	Int m_cmd;                              // +0x00
	CommandSourceType m_cmdSource;         // +0x04
	Coord3D m_pos;                         // +0x08
	Object *m_obj;                         // +0x14
	Object *m_otherObj;                    // +0x18
	const Team *m_team;                    // +0x1c
	char m_coords[0x0c];                    // +0x20, STLport vector
	const Waypoint *m_waypoint;             // +0x2c
	const PolygonTrigger *m_polygon;        // +0x30
	Int m_intValue;                         // +0x34
	char m_damage[0x5c];                    // +0x38
	const CommandButton *m_commandButton;  // +0x94
	Path *m_path;                           // +0x98
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandParmsStorage
{
public:
	AICommandParmsStorage(const AICommandParms &parms);
	static void *operator new(unsigned int size, void *place)
	{
		__assume(place != 0);
		return place;
	}

	char m_payload[0xa0];
};

#pragma comment(linker, "/alternatename:??0AICommandParmsStorage@@QAE@ABUAICommandParms@@@Z=?j_00019e2a@@YAXXZ")

extern bool g_aiTargetDispatchSuppressed;
extern void j_00006dcf();
extern void j_000359bd();
extern void j_0002308d();
extern void j_00019e2a();

class BFMEActionObject
{
public:
	Bool testStatus(Int status) const;
};

struct RvaC4390Interface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual Bool slot0c(Object *object) = 0;
};

class RvaC4390First
{
public:
	RvaC4390Interface *getInterface();
};

class NestedCommandInterface
{
public:
	virtual void accept(const AICommandParms *parms) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
public:
	virtual void base00() = 0;
	virtual void base04() = 0;
	virtual void base08() = 0;
	virtual void base0c() = 0;
	virtual void base10() = 0;
	virtual void base14() = 0;
	virtual void base18() = 0;
	virtual void base1c() = 0;
	virtual void base20() = 0;
	virtual void base24() = 0;
	virtual void base28() = 0;

protected:
	char m_beforeObject[4];
	Object *m_object;                       // +0x08
	char m_afterObject[0x20 - 0x0c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandInterface
{
public:
	virtual void aiDoCommand(const AICommandParms *parms) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public UpdateModule, public AICommandInterface
{
protected:
	virtual void dispatch_2c(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_30(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_34(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_38(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_3c(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_40(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_44(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_48(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_4c(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_50(CommandSourceType source) = 0;
	virtual void dispatch_54(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_58(const Waypoint *waypoint, CommandSourceType source) = 0;
	virtual void dispatch_5c(const Waypoint *waypoint, CommandSourceType source) = 0;
	virtual void dispatch_60(const Waypoint *waypoint, CommandSourceType source) = 0;
	virtual void dispatch_64(const Waypoint *waypoint, CommandSourceType source) = 0;
	virtual void dispatch_68(const void *coords, Object *object, CommandSourceType source, Bool exitProduction) = 0;
	virtual void dispatch_6c(const void *coords, Object *object, float value, CommandSourceType source) = 0;
	virtual void dispatch_70(const void *coords, Object *object, float value, CommandSourceType source) = 0;
	virtual void dispatch_74(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_78(Object *object, Int value, CommandSourceType source) = 0;
	virtual void dispatch_7c(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_80(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_84(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_88(Object *object, Int value, CommandSourceType source) = 0;
	virtual void dispatch_8c(const Team *team, Int value, CommandSourceType source) = 0;
	virtual void dispatch_90(const Coord3D *pos, Int value, CommandSourceType source) = 0;
	virtual void dispatch_94(const Coord3D *pos, Int value, CommandSourceType source) = 0;
	virtual void dispatch_98(const Waypoint *waypoint, Int value, Bool asTeam, CommandSourceType source) = 0;
	virtual void dispatch_9c(CommandSourceType source) = 0;
	virtual void dispatch_a0(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_a4(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_a8(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_ac(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_b0(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_b4(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_b8(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_bc(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_c0(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_c4(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_c8(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_cc(Int value, CommandSourceType source) = 0;
	virtual void dispatch_d0(const void *damage, CommandSourceType source) = 0;
	virtual void dispatch_d4(Int value, CommandSourceType source) = 0;
	virtual void dispatch_d8(const Coord3D *pos, Int value, CommandSourceType source) = 0;
	virtual void dispatch_dc(Object *object, Int value, CommandSourceType source) = 0;
	virtual void dispatch_e0(const Team *team, Int value, CommandSourceType source) = 0;
	virtual void dispatch_e4(Object *object, const Coord3D *pos, Int value, CommandSourceType source) = 0;
	virtual void dispatch_e8(const PolygonTrigger *polygon, Int value, CommandSourceType source, const Coord3D *pos) = 0;
	virtual void dispatch_ec(const PolygonTrigger *polygon, CommandSourceType source) = 0;
	virtual void dispatch_f0(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_f4(const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_f8() = 0;
	virtual void dispatch_fc(const CommandButton *button, CommandSourceType source) = 0;
	virtual void dispatch_100(const CommandButton *button, const Coord3D *pos, CommandSourceType source) = 0;
	virtual void dispatch_104(const CommandButton *button, Object *object, CommandSourceType source) = 0;
	virtual void dispatch_108(const Waypoint *waypoint, CommandSourceType source) = 0;
	virtual void dispatch_10c(CommandSourceType source) = 0;
	virtual void dispatch_110(const Waypoint *waypoint, CommandSourceType source) = 0;
	virtual void dispatch_114(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_118(Int value, CommandSourceType source) = 0;
	virtual void dispatch_11c(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_120(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_124(Object *object, CommandSourceType source) = 0;
	virtual void dispatch_128(CommandSourceType source) = 0;
	virtual void dispatch_12c(Object *object, CommandSourceType source) = 0;

	#if 0
	virtual void pad76() = 0;
	virtual void pad77() = 0;
	virtual void pad78() = 0;
	virtual void pad79() = 0;
	virtual void pad7a() = 0;
	virtual void pad7b() = 0;
	virtual void pad7c() = 0;
	virtual void pad7d() = 0;
	virtual void pad7e() = 0;
	virtual void pad7f() = 0;
	virtual void pad80() = 0;
	virtual void pad81() = 0;
	virtual void pad82() = 0;
	virtual void pad83() = 0;
	virtual void pad84() = 0;
	virtual void pad85() = 0;
	virtual void pad86() = 0;
	virtual void pad87() = 0;
	virtual void pad88() = 0;
	virtual void pad89() = 0;
	virtual void pad8a() = 0;
	virtual void pad8b() = 0;
	virtual void pad8c() = 0;
	virtual void pad8d() = 0;
	virtual void pad8e() = 0;
	virtual void pad8f() = 0;
	virtual void pad90() = 0;
	virtual void pad91() = 0;
	virtual void pad92() = 0;
	virtual void pad93() = 0;
	virtual void pad94() = 0;
	virtual void pad95() = 0;
	virtual void pad96() = 0;
	virtual void pad97() = 0;
	virtual void pad98() = 0;
	virtual void pad99() = 0;
	virtual void pad9a() = 0;
	virtual void pad9b() = 0;
	virtual void pad9c() = 0;
	virtual void pad9d() = 0;
	virtual void pad9e() = 0;
	virtual void pad9f() = 0;
	virtual void pada0() = 0;
	virtual void pada1() = 0;
	virtual void pada2() = 0;
	virtual void pada3() = 0;
	virtual void pada4() = 0;
	virtual void pada5() = 0;
	virtual void pada6() = 0;
	virtual void pada7() = 0;
	virtual void pada8() = 0;
	virtual void pada9() = 0;
	virtual void padaa() = 0;
	virtual void padab() = 0;
	virtual void padac() = 0;
	virtual void padad() = 0;
	virtual void padae() = 0;
	virtual void padaf() = 0;
	virtual void padb0() = 0;
	virtual void padb1() = 0;
	virtual void padb2() = 0;
	virtual void padb3() = 0;
	virtual void padb4() = 0;
	virtual void padb5() = 0;
	virtual void padb6() = 0;
	virtual void padb7() = 0;
	virtual void padb8() = 0;
	virtual void padb9() = 0;
	virtual void padba() = 0;
	virtual void padbb() = 0;
	virtual void padbc() = 0;
	virtual void padbd() = 0;
	virtual void padbe() = 0;
	virtual void padbf() = 0;
	virtual void padc0() = 0;
	virtual void padc1() = 0;
	virtual void padc2() = 0;
	virtual void padc3() = 0;
	virtual void padc4() = 0;
	virtual void padc5() = 0;
	virtual void padc6() = 0;
	virtual void padc7() = 0;
	virtual void padc8() = 0;
	virtual void padc9() = 0;
	virtual void padca() = 0;
	virtual void padcb() = 0;
	virtual void padcc() = 0;
	virtual void padcd() = 0;
	virtual void padce() = 0;
	virtual void padcf() = 0;
	virtual void padd0() = 0;
	virtual void padd1() = 0;
	virtual void padd2() = 0;
	virtual void padd3() = 0;
	virtual void padd4() = 0;
	virtual void padd5() = 0;
	virtual void padd6() = 0;
	virtual void padd7() = 0;
	virtual void padd8() = 0;
	virtual void padd9() = 0;
	virtual void padda() = 0;
	virtual void paddb() = 0;
	virtual void paddc() = 0;
	virtual void paddd() = 0;
	virtual void padde() = 0;
	virtual void paddf() = 0;
	virtual void pade0() = 0;
	virtual void pade1() = 0;
	virtual void pade2() = 0;
	virtual void pade3() = 0;
	virtual void pade4() = 0;
	virtual void pade5() = 0;
	virtual void pade6() = 0;
	virtual void pade7() = 0;
	virtual void pade8() = 0;
	virtual void pade9() = 0;
	virtual void padea() = 0;
	virtual void padeb() = 0;
	virtual void padec() = 0;
	virtual void paded() = 0;
	virtual void padee() = 0;
	virtual void padef() = 0;
	virtual void padf0() = 0;
	virtual void padf1() = 0;
	virtual void padf2() = 0;
	virtual void padf3() = 0;
	virtual void padf4() = 0;
	virtual void padf5() = 0;
	virtual void padf6() = 0;
	virtual void padf7() = 0;
	virtual void padf8() = 0;
	virtual void padf9() = 0;
	virtual void padfa() = 0;
	virtual void padfb() = 0;
	virtual void padfc() = 0;
	virtual void padfd() = 0;
	virtual void padfe() = 0;
	virtual void padff() = 0;
	virtual void pade0x() = 0;
	virtual void pade1x() = 0;
	virtual void pade2x() = 0;
	virtual void pade3x() = 0;
	virtual void pade4x() = 0;
	virtual void pade5x() = 0;
	virtual void pade6x() = 0;
	virtual void pade7x() = 0;
	virtual void pade8x() = 0;
	virtual void pade9x() = 0;
	virtual void padeax() = 0;
	virtual void padebx() = 0;
	virtual void padecx() = 0;
	virtual void padedx() = 0;
	virtual void padex() = 0;
	virtual void padefx() = 0;
	virtual void padf0x() = 0;
	virtual void padf1x() = 0;
	virtual void padf2x() = 0;
	virtual void padf3x() = 0;
	virtual void padf4x() = 0;
	virtual void padf5x() = 0;
	virtual void padf6x() = 0;
	virtual void padf7x() = 0;
	virtual void padf8x() = 0;
	virtual void padf9x() = 0;
	virtual void padfax() = 0;
	virtual void padfbx() = 0;
	virtual void padfcx() = 0;
	virtual void padfdx() = 0;
	virtual void padfex() = 0;
	virtual void padffx() = 0;
	virtual void padffx() = 0;
	#endif
	virtual void activePad76() = 0;
	virtual void activePad77() = 0;
	virtual void activePad78() = 0;
	virtual void activePad79() = 0;
	virtual void activePad7a() = 0;
	virtual void activePad7b() = 0;
	virtual void activePad7c() = 0;
	virtual void activePad7d() = 0;
	virtual void activePad7e() = 0;
	virtual void activePad7f() = 0;
	virtual void activePad80() = 0;
	virtual void activePad81() = 0;
	virtual void activePad82() = 0;
	virtual void activePad83() = 0;
	virtual void activePad84() = 0;
	virtual void activePad85() = 0;
	virtual void activePad86() = 0;
	virtual void activePad87() = 0;
	virtual void activePad88() = 0;
	virtual void activePad89() = 0;
	virtual void activePad8a() = 0;
	virtual void activePad8b() = 0;
	virtual void activePad8c() = 0;
	virtual void activePad8d() = 0;
	virtual void activePad8e() = 0;
	virtual void activePad8f() = 0;
	virtual void activePad90() = 0;
	virtual void activePad91() = 0;
	virtual void activePad92() = 0;
	virtual void activePad93() = 0;
	virtual void activePad94() = 0;
	virtual void activePad95() = 0;
	virtual void activePad96() = 0;
	virtual void activePad97() = 0;
	virtual void activePad98() = 0;
	virtual void activePad99() = 0;
	virtual void activePad9a() = 0;
	virtual void activePad9b() = 0;
	virtual void activePad9c() = 0;
	virtual void activePad9d() = 0;
	virtual void activePad9e() = 0;
	virtual void activePad9f() = 0;
	virtual void activePada0() = 0;
	virtual void activePada1() = 0;
	virtual void activePada2() = 0;
	virtual void activePada3() = 0;
	virtual void activePada4() = 0;
	virtual void activePada5() = 0;
	virtual void activePada6() = 0;
	virtual void activePada7() = 0;
	virtual void activePada8() = 0;
	virtual void activePada9() = 0;
	virtual void activePadaa() = 0;
	virtual void activePadab() = 0;
	virtual void activePadac() = 0;
	virtual void activePadad() = 0;
	virtual Bool isAllowedToRespondToAiCommands(const AICommandParms *parms) const = 0;

	char m_to34[0x34 - 0x24];
	void *m_field34;
	char m_to140[0x140 - 0x38];
	void *m_field140;
	char m_to1a4[0x1a4 - 0x144];
	unsigned int m_field1a4;
	char m_to1d8[0x1d8 - 0x1a8];
	void *m_field1d8;
	char m_to27c[0x27c - 0x1dc];
	AICommandParmsStorage m_field27c;
	unsigned char m_field31c;
	char m_to335[0x335 - 0x31d];
	unsigned char m_field335;
	char m_to33a[0x33a - 0x336];
	unsigned char m_field33a;
	char m_to33c[0x33c - 0x33b];
	unsigned int m_field33c;

public:
	virtual void aiDoCommand(const AICommandParms *parms);
};

typedef Bool (__fastcall *BFMEStatusCall)(void *object);
typedef void (__fastcall *BFMEOneArgCall)(void *object);

void AIUpdateInterface::aiDoCommand(const AICommandParms *parms)
{
	m_field1a4 = 0;
	if (g_aiTargetDispatchSuppressed)
		return;

	if (!isAllowedToRespondToAiCommands(parms))
		return;

	Bool rejected = false;
	if (m_field140 != 0 && m_field1d8 != 0 &&
			reinterpret_cast<BFMEStatusCall>(j_00006dcf)(m_field140))
		rejected = true;

	Object *object = m_object;
	if (((*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(object) + 0x1a4) & 0x100) == 0) &&
		!rejected &&
		(((*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(object) + 0x98) & 0x200) == 0) ||
		 parms->m_cmdSource == CMD_FROM_AI))
	{

	if (m_field34 != 0 && parms->m_cmdSource != CMD_FROM_AI)
		reinterpret_cast<BFMEOneArgCall>(j_000359bd)(reinterpret_cast<char *>(this));

	if (reinterpret_cast<BFMEActionObject *>(object)->testStatus(0x25))
	{
		void *outer = *reinterpret_cast<void **>(reinterpret_cast<char *>(object) + 0x214);
		NestedCommandInterface *inner = reinterpret_cast<NestedCommandInterface *>(
			*reinterpret_cast<void **>(reinterpret_cast<char *>(outer) + 0x204));
		if (outer != 0 && inner != 0 && parms->m_cmdSource != CMD_FROM_AI)
		{
			switch (parms->m_cmd)
			{
				case 0x1c:
				case 0x3b:
				case 0x43:
				{
					reinterpret_cast<NestedCommandInterface *>(
						reinterpret_cast<char *>(
							*reinterpret_cast<void **>(
								reinterpret_cast<char *>(
									*reinterpret_cast<void **>(reinterpret_cast<char *>(m_object) + 0x214)) + 0x204)) + 0x20)->accept(parms);
					return;
				}
				default:
					break;
			}
		}
	}

	if (reinterpret_cast<BFMEActionObject *>(object)->testStatus(0x40))
	{
		RvaC4390Interface *interfacePointer =
			reinterpret_cast<RvaC4390First *>(object)->getInterface();
		if (interfacePointer != 0)
		{
			if (parms->m_cmd == 0x0c || parms->m_cmd == 0x36)
			{
				if (parms->m_obj != 0 && !interfacePointer->slot0c(parms->m_obj))
					interfacePointer->slot04();
			}
			else
				interfacePointer->slot04();
		}
	}

	m_field335 = 0;
	m_field33c = 0;
	if (parms->m_cmd != 5 && parms->m_cmdSource == CMD_FROM_PLAYER && m_field33a)
		m_field33a = 0;

	switch (parms->m_cmd)
	{
		case 0x00:
		case 0x36:
			dispatch_2c(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x47:
			dispatch_34(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x01:
			dispatch_30(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x48:
			dispatch_38(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x02:
			dispatch_54(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x03:
			dispatch_3c(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x04:
			dispatch_40(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x38:
			dispatch_44(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x41:
			dispatch_48(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x42:
			dispatch_4c(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x05:
			dispatch_50(parms->m_cmdSource);
			break;
		case 0x06:
			dispatch_58(parms->m_waypoint, parms->m_cmdSource);
			break;
		case 0x07:
			dispatch_5c(parms->m_waypoint, parms->m_cmdSource);
			break;
		case 0x32:
			dispatch_60(parms->m_waypoint, parms->m_cmdSource);
			break;
		case 0x33:
			dispatch_64(parms->m_waypoint, parms->m_cmdSource);
			break;
		case 0x09:
			dispatch_68(parms->m_coords, parms->m_obj, parms->m_cmdSource, false);
			break;
		case 0x24:
			dispatch_6c(parms->m_coords, parms->m_obj, parms->m_pos.x, parms->m_cmdSource);
			break;
		case 0x25:
			dispatch_70(parms->m_coords, parms->m_obj, parms->m_pos.x, parms->m_cmdSource);
			break;
		case 0x35:
			dispatch_74(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x0a:
			dispatch_68(parms->m_coords, parms->m_obj, parms->m_cmdSource, true);
			break;
		case 0x0b:
			dispatch_78(parms->m_obj, parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x0c:
			dispatch_88(parms->m_obj, parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x39:
			dispatch_7c(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x3f:
			dispatch_80(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x40:
			dispatch_84(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x0d:
			dispatch_8c(parms->m_team, parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x0e:
			dispatch_90(&parms->m_pos, parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x0f:
			dispatch_94(&parms->m_pos, parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x10:
			dispatch_98(parms->m_waypoint, parms->m_intValue, false, parms->m_cmdSource);
			break;
		case 0x11:
			dispatch_98(parms->m_waypoint, parms->m_intValue, true, parms->m_cmdSource);
			break;
		case 0x12:
			dispatch_9c(parms->m_cmdSource);
			break;
		case 0x23:
			dispatch_ec(parms->m_polygon, parms->m_cmdSource);
			break;
		case 0x13:
			dispatch_a0(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x14:
			dispatch_a4(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x15:
			dispatch_a8(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x16:
			dispatch_ac(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x45:
			dispatch_b8(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x17:
			dispatch_b0(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x3d:
			dispatch_b4(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x18:
			dispatch_bc(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x19:
			dispatch_c0(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x1a:
			dispatch_c4(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x3e:
			dispatch_c8(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x1b:
			dispatch_cc(parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x1d:
			dispatch_d0(&parms->m_damage, parms->m_cmdSource);
			break;
		case 0x1e:
			dispatch_d8(&parms->m_pos, parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x1f:
			dispatch_dc(parms->m_obj, parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x20:
			dispatch_e0(parms->m_team, parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x37:
			dispatch_d4(parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x21:
			dispatch_e8(parms->m_polygon, parms->m_intValue, parms->m_cmdSource, 0);
			break;
		case 0x44:
			dispatch_e8(parms->m_polygon, parms->m_intValue, parms->m_cmdSource, &parms->m_pos);
			break;
		case 0x46:
			dispatch_e4(parms->m_obj, &parms->m_pos, parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x26:
			dispatch_f0(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x27:
			dispatch_f4(&parms->m_pos, parms->m_cmdSource);
			break;
		case 0x2a:
			dispatch_fc(parms->m_commandButton, parms->m_cmdSource);
			break;
		case 0x29:
			dispatch_104(parms->m_commandButton, parms->m_obj, parms->m_cmdSource);
			break;
		case 0x28:
			dispatch_100(parms->m_commandButton, &parms->m_pos, parms->m_cmdSource);
			break;
		case 0x2b:
			dispatch_108(parms->m_waypoint, parms->m_cmdSource);
			break;
		case 0x2c:
			dispatch_10c(parms->m_cmdSource);
			break;
		case 0x2d:
			dispatch_110(parms->m_waypoint, parms->m_cmdSource);
			break;
		case 0x2e:
			dispatch_114(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x2f:
			dispatch_124(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x31:
			dispatch_118(parms->m_intValue, parms->m_cmdSource);
			break;
		case 0x34:
			dispatch_11c(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x3a:
			dispatch_128(parms->m_cmdSource);
			break;
		case 0x43:
			dispatch_12c(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x3c:
			dispatch_120(parms->m_obj, parms->m_cmdSource);
			break;
		case 0x08:
		case 0x1c:
		case 0x22:
		case 0x30:
		case 0x3b:
		default:
			break;
	}

	if (!reinterpret_cast<BFMEActionObject *>(object)->testStatus(0x45))
		return;
	if (parms->m_cmdSource == CMD_FROM_AI)
		return;
	reinterpret_cast<BFMEOneArgCall>(j_0002308d)(object);
	}
	else
	{
		new (&m_field27c) AICommandParmsStorage(*parms);
		m_field31c = 1;
	}
}
