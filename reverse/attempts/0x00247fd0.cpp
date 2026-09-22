// ?rva00247fd0@Rva00247FD0HordeContain@@QAEXPAV?$vector@PAVRva00247FD0Object@@V?$allocator@PAVRva00247FD0Object@@@_STL@@@_STL@@@Z
// partial score=0.1 date=2026-09-22
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x00247FD0. The owner remains address-qualified because no caller names slot 115.
// The container and module-data offsets come from matched HordeContain layouts.

#define _STLP_USE_NEWALLOC 1
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int ObjectID;

template <typename T>
class LatchRestore
{
protected:
	T valueToRestore;
	T &whereToRestore;

public:
	LatchRestore(T &dest, const T &src) : whereToRestore(dest)
	{
		valueToRestore = dest;
		dest = src;
	}

	virtual ~LatchRestore()
	{
		whereToRestore = valueToRestore;
	}
};

struct Coord3D
{
	float x, y, z;
};

struct Matrix3D
{
	float m[16];
};

struct Rva00247FD0AsciiString
{
	void *m_data;
};

struct Rva00247FD0FormationEntry
{
	Rva00247FD0AsciiString m_name;
	Rva00247FD0AsciiString m_unit;
};

struct Rva00247FD0FormationData
{
	UnsignedInt m_values[12];
};

struct Gen_t_002468d0_p4cd
{
	void *m_node;
	Gen_t_002468d0_p4cd();
	Gen_t_002468d0_p4cd(const Gen_t_002468d0_p4cd &other);
	~Gen_t_002468d0_p4cd();
	Gen_t_002468d0_p4cd &operator=(const Gen_t_002468d0_p4cd &other);
};

struct Rva00247FD0ModuleData
{
	unsigned char m_pad[0x23c];
	_STL::vector<Rva00247FD0FormationEntry *> m_entries;
};

struct Rva00247FD0Vector16
{
	unsigned int m_value[4];
};

struct Rva00247FD0Map
{
	unsigned char m_pad[1];
};

class Rva00247FD0Player;
class Rva00247FD0ThingTemplate;
class Rva00247FD0Team;

class Rva00247FD0SubDSU
{
public:
	void **bfmeTwoDSU(void **what);
};

class Rva00247FD0HordeSlot
{
public:
	void *m_key;
	unsigned char m_pad04[12];
};

class Rva00247FD0HordeRosterView
{
public:
	Rva00247FD0SubDSU *indices() const
	{
		return (Rva00247FD0SubDSU *)((char *)this + 0x3c);
	}

	Rva00247FD0HordeSlot *slots() const
	{
		return *(Rva00247FD0HordeSlot **)((char *)this + 0x48);
	}
};

class Rva00247FD0Object
{
public:
	Rva00247FD0Player *getControllingPlayer() const;
	void transferReplacementState(Rva00247FD0Object *replacement);

	Rva00247FD0Object *m_pad00_object;
	unsigned char m_pad04[0x34];
	Coord3D m_position;
	unsigned char m_pad44[0x30];
	ObjectID m_id;
	unsigned char m_pad78[0x1c];
	UnsignedInt m_status;
	unsigned char m_pad98[0x16c];
	void *m_ai;
	unsigned char m_pad208[12];
	void *m_experience;
};

class Rva00247FD0Player
{
public:
	Rva00247FD0Team *m_pad00[0x230 / 4];
	Rva00247FD0Team *m_defaultTeam;
};

class Rva00247FD0Experience
{
public:
	void gainExpForLevel(Int levels, Bool canScale, Bool feedback);
	Int m_pad00[10];
};

class Rva00247FD0AICommands
{
public:
	void aiIdle(Int source);
};

class Rva00247FD0AI
{
public:
	Rva00247FD0AICommands *commands() const
	{
		return (Rva00247FD0AICommands *)((char *)this + 0x20);
	}
};

class Rva00247FD0Logic
{
public:
	Rva00247FD0Object *findObjectByID(Int id);
	void destroyObject(Rva00247FD0Object *object);
};

class Rva00247FD0ThingFactory
{
public:
	Rva00247FD0ThingTemplate *findTemplate(const Rva00247FD0AsciiString &name);
	Rva00247FD0Object *newObject(const Rva00247FD0ThingTemplate *tmpl,
		Rva00247FD0Team *team, const void *status, UnsignedInt extra);
};

class Rva00247FD0Thing
{
public:
	const Coord3D *getUnitDirectionVector2D() const;
	void setTransform(const Matrix3D *transform);
	void setPosition(const Coord3D *position);
};

class Rva00247FD0HordeInterface
{
public:
#define RVASLOT(N) virtual void rvaSlot##N();
	RVASLOT(00) RVASLOT(01) RVASLOT(02) RVASLOT(03) RVASLOT(04)
	RVASLOT(05) RVASLOT(06) RVASLOT(07) RVASLOT(08) RVASLOT(09)
	RVASLOT(10) RVASLOT(11) RVASLOT(12) RVASLOT(13) RVASLOT(14)
	RVASLOT(15) RVASLOT(16) RVASLOT(17) RVASLOT(18) RVASLOT(19)
	RVASLOT(20) RVASLOT(21) RVASLOT(22) RVASLOT(23) RVASLOT(24)
	RVASLOT(25) RVASLOT(26) RVASLOT(27) RVASLOT(28) RVASLOT(29)
	RVASLOT(30) RVASLOT(31) RVASLOT(32) RVASLOT(33) RVASLOT(34)
	RVASLOT(35) RVASLOT(36) RVASLOT(37) RVASLOT(38) RVASLOT(39)
	virtual void removeMember(Rva00247FD0Object *member);
	RVASLOT(41) RVASLOT(42) RVASLOT(43) RVASLOT(44) RVASLOT(45)
	RVASLOT(46) RVASLOT(47) RVASLOT(48) RVASLOT(49) RVASLOT(50)
	RVASLOT(51) RVASLOT(52) RVASLOT(53) RVASLOT(54) RVASLOT(55)
	RVASLOT(56) RVASLOT(57) RVASLOT(58) RVASLOT(59)
	virtual void getMembers(_STL::list<Rva00247FD0Object *> *members);
	RVASLOT(61) RVASLOT(62) RVASLOT(63) RVASLOT(64) RVASLOT(65)
	RVASLOT(66) RVASLOT(67) RVASLOT(68) RVASLOT(69) RVASLOT(70)
	RVASLOT(71) RVASLOT(72) RVASLOT(73) RVASLOT(74) RVASLOT(75)
	RVASLOT(76) RVASLOT(77) RVASLOT(78) RVASLOT(79) RVASLOT(80)
	RVASLOT(81) RVASLOT(82) RVASLOT(83) RVASLOT(84) RVASLOT(85)
	RVASLOT(86) RVASLOT(87) RVASLOT(88) RVASLOT(89) RVASLOT(90)
	RVASLOT(91) RVASLOT(92) RVASLOT(93) RVASLOT(94) RVASLOT(95)
	RVASLOT(96) RVASLOT(97) RVASLOT(98) RVASLOT(99) RVASLOT(100)
	RVASLOT(101) RVASLOT(102) RVASLOT(103) RVASLOT(104) RVASLOT(105)
	RVASLOT(106) RVASLOT(107) RVASLOT(108) RVASLOT(109) RVASLOT(110)
	RVASLOT(111)
	virtual Rva00247FD0FormationData *getFormationData();
	RVASLOT(113) RVASLOT(114)
	virtual void refreshMember(Rva00247FD0Object *member);
#undef RVASLOT
};

class Rva00247FD0Overridable
{
public:
	Rva00247FD0Overridable *getFinalOverride();
	Rva00247FD0Overridable *m_next;
};

extern Rva00247FD0Logic *TheBfmeGameLogic;
extern Rva00247FD0ThingFactory *Rva0020AA00TheRegistry;
extern float g_bfmeK1253;
extern Rva00247FD0AI *TheAI;
extern float BfmeShadowScale;

extern void j_000022bb();
extern void j_0000b81b();
extern void j_0001f253();
extern void j_0001f91f();
extern void j_00020824();
extern void j_000209fa();
extern void j_00024d70();
extern void j_00028560();
extern void j_00034185();
extern void j_000348ec();
extern void j_000361ce();
extern void j_000385f5();
extern void j_000392ca();
extern void j_0003a1a7();
extern void j_0003e80b();
extern void j_00040246();
extern void j_0004494a();
extern void j_0004966b();
extern void j_0004a12e();
extern void j_0001d0de();

typedef Rva00247FD0Object *(Rva00247FD0Logic::*RvaFindObject)(Int);
typedef void (Rva00247FD0Logic::*RvaDestroyObject)(Rva00247FD0Object *);
typedef Rva00247FD0Player *(Rva00247FD0Object::*RvaGetPlayer)() const;
typedef const Coord3D *(Rva00247FD0Thing::*RvaGetDirection)() const;
typedef void (Rva00247FD0Thing::*RvaSetTransform)(const Matrix3D *);
typedef void (Rva00247FD0Thing::*RvaSetPosition)(const Coord3D *);
typedef Rva00247FD0ThingTemplate *(Rva00247FD0ThingFactory::*RvaFindTemplate)(const Rva00247FD0AsciiString &);
typedef Rva00247FD0Object *(Rva00247FD0ThingFactory::*RvaNewObject)(const Rva00247FD0ThingTemplate *, Rva00247FD0Team *, const void *, UnsignedInt);
typedef void (Rva00247FD0Object::*RvaTransferState)(Rva00247FD0Object *);
typedef void (Rva00247FD0Experience::*RvaGainExperience)(Int, Bool, Bool);
typedef void (Rva00247FD0AICommands::*RvaIdle)(Int);
typedef Rva00247FD0Overridable *(Rva00247FD0Overridable::*RvaOverride)();
typedef Bool (Rva00247FD0Overridable::*RvaEquivalent)(Rva00247FD0Overridable *);
typedef void **(Rva00247FD0SubDSU::*RvaRosterIndex)(void **);

template <class T> T rvaCall(void (*raw)())
{
	union { void (*raw)(); T member; } cast;
	cast.raw = raw;
	return cast.member;
}

class Rva00247FD0HordeContain : public Rva00247FD0HordeInterface
{
public:
	void rva00247fd0(_STL::vector<Rva00247FD0Object *> *output);

private:
	char *container() const { return (char *)this - 0xe4; }
	Rva00247FD0Object *owner() const
	{
		return *(Rva00247FD0Object **)(container() + 8);
	}
	Rva00247FD0ModuleData *moduleData() const
	{
		return *(Rva00247FD0ModuleData **)(container() + 4);
	}
	Rva00247FD0HordeRosterView *roster() const
	{
		return (Rva00247FD0HordeRosterView *)this;
	}
};

void Rva00247FD0HordeContain::rva00247fd0(
	_STL::vector<Rva00247FD0Object *> *output)
{
	Rva00247FD0Object *me = owner();
	Rva00247FD0FormationData formation = *getFormationData();
	_STL::vector<Gen_t_002468d0_p4cd> pending;
	pending.clear();
	volatile unsigned char lookupState[12];
	lookupState[0] = 0;
	Rva00247FD0Object *old = (TheBfmeGameLogic->*rvaCall<RvaFindObject>(j_0001f253))(
		*(Int *)((char *)this + 0xd8));
	_STL::list<Rva00247FD0Object *> members;
	getMembers(&members);
	if (old != 0)
	{
		for (_STL::list<Rva00247FD0Object *>::iterator i = members.begin();
			i != members.end(); ++i)
		{
			if (*i == old)
			{
				members.erase(i);
				break;
			}
		}
		(TheBfmeGameLogic->*rvaCall<RvaDestroyObject>(j_0001d0de))(old);
	}

	const Coord3D *direction = (((const Rva00247FD0Thing *)me)->*rvaCall<RvaGetDirection>(j_00040246))();
	float scale = *(float *)((char *)*(void **)((char *)me + 0x210) + 0x28);
	Coord3D offset;
	offset.x = direction->x * scale * g_bfmeK1253;
	offset.y = direction->y * scale * g_bfmeK1253;
	offset.z = direction->z * scale * g_bfmeK1253;

	_STL::list<Rva00247FD0Object *> replacements;
	for (_STL::list<Rva00247FD0Object *>::iterator i = members.begin();
		i != members.end(); ++i)
	{
		Rva00247FD0Object *member = *i;
		Rva00247FD0AI *ai = *(Rva00247FD0AI **)((char *)member + 0x204);
		if (ai != 0)
			(ai->commands()->*rvaCall<RvaIdle>(j_00024d70))(0);

		Rva00247FD0Overridable *a = *(Rva00247FD0Overridable **)((char *)member + 4);
		Rva00247FD0Overridable *b = *(Rva00247FD0Overridable **)((char *)member + 4);
		if (a != 0 && a->m_next != 0)
			a = (a->*rvaCall<RvaOverride>(j_000022bb))();
		if (b != 0 && b->m_next != 0)
			b = (b->*rvaCall<RvaOverride>(j_000022bb))();
		if ((a->*rvaCall<RvaEquivalent>(j_0003e80b))(b))
		{
			void *key1 = (void *)(UnsignedInt)member->m_id;
			void **index1 = (roster()->indices()->*rvaCall<RvaRosterIndex>(j_0001f91f))(&key1);
			void *key2 = (void *)(UnsignedInt)member->m_id;
			void **index2 = (roster()->indices()->*rvaCall<RvaRosterIndex>(j_0001f91f))(&key2);
			Rva00247FD0HordeSlot *slots = roster()->slots();
			if (slots[(UnsignedInt)*index1].m_key == slots[(UnsignedInt)*index2].m_key)
				replacements.push_back(member);
		}
	}

	for (_STL::list<Rva00247FD0Object *>::iterator i = replacements.begin();
		i != replacements.end(); ++i)
	{
		Rva00247FD0Object *member = *i;
		refreshMember(member);
		Rva00247FD0FormationEntry **entry = moduleData()->m_entries.begin();
		Rva00247FD0FormationEntry **end = moduleData()->m_entries.end();
		if (entry == end)
			continue;
		Rva00247FD0ThingTemplate *tmpl = (Rva0020AA00TheRegistry->*rvaCall<RvaFindTemplate>(j_00028560))(
			(*entry)->m_name);
		if (tmpl == 0)
			continue;
		unsigned char status[12] = { 0 };
		Rva00247FD0Player *player = (me->*rvaCall<RvaGetPlayer>(j_00020824))();
		Rva00247FD0Object *replacement = (Rva0020AA00TheRegistry->*rvaCall<RvaNewObject>(j_0004494a))(
			tmpl, player->m_defaultTeam, status, 0);
		if (replacement == 0)
			continue;
		if (*(UnsignedInt *)((char *)me + 0x94) & 0x20000000)
			(me->*rvaCall<RvaTransferState>(j_0004966b))(replacement);
		*(Coord3D *)((char *)replacement + 0x38) = *(Coord3D *)((char *)me + 0x38);
		(((Rva00247FD0Thing *)replacement)->*rvaCall<RvaSetTransform>(j_000361ce))((const Matrix3D *)&formation);
		(((Rva00247FD0Thing *)replacement)->*rvaCall<RvaSetPosition>(j_0003a1a7))(&offset);
		(((Rva00247FD0Experience *)*(void **)((char *)replacement + 0x210))->*rvaCall<RvaGainExperience>(j_0004a12e))(
			*(Int *)((char *)me + 0x210) - *(Int *)((char *)replacement + 0x210),
			true, false);
		Bool latchValue = false;
		LatchRestore<Bool> latch(latchValue, true);
		((((Rva00247FD0AI *)*(void **)((char *)replacement + 0x204))->commands()->*rvaCall<RvaIdle>(j_00024d70))(2));
		if (output->end() != output->begin())
			output->push_back(replacement);
	}
}

#pragma comment(linker, "/alternatename:?getControllingPlayer@Rva00247FD0Object@@QBEPAVRva00247FD0Player@@XZ=?j_00020824@@YAXXZ")
#pragma comment(linker, "/alternatename:?transferReplacementState@Rva00247FD0Object@@QAEXPAV1@@Z=?j_0004966b@@YAXXZ")
#pragma comment(linker, "/alternatename:?gainExpForLevel@Rva00247FD0Experience@@QAEXH_N0@Z=?j_0004a12e@@YAXXZ")
#pragma comment(linker, "/alternatename:?aiIdle@Rva00247FD0AICommands@@QAEXH@Z=?j_00024d70@@YAXXZ")
#pragma comment(linker, "/alternatename:?getUnitDirectionVector2D@Rva00247FD0Thing@@QBEPBUCoord3D@@XZ=?j_00040246@@YAXXZ")
#pragma comment(linker, "/alternatename:?setTransform@Rva00247FD0Thing@@QAEXPBVMatrix3D@@@Z=?j_000361ce@@YAXXZ")
#pragma comment(linker, "/alternatename:?setPosition@Rva00247FD0Thing@@QAEXPBUCoord3D@@@Z=?j_0003a1a7@@YAXXZ")
#pragma comment(linker, "/alternatename:?findTemplate@Rva00247FD0ThingFactory@@QAEPAVRva00247FD0ThingTemplate@@ABVAsciiString@@@Z=?j_00028560@@YAXXZ")
#pragma comment(linker, "/alternatename:?newObject@Rva00247FD0ThingFactory@@QAEPAVRva00247FD0Object@@PBVRva00247FD0ThingTemplate@@PAVRva00247FD0Team@@PBXI@Z=?j_0004494a@@YAXXZ")
