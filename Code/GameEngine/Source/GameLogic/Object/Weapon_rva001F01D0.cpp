// cl: /DNDEBUG /MD /EHs-c-
//
// thiscall that fires a temp weapon through the five-argument
// WeaponStore::createAndFireTempWeapon then appends the target's object id
// onto a circular 12-byte list whose sentinel lives at this+0x7c.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	char m_pad[0x38];
	Coord3D m_position;
	char m_pad44[0x74 - 0x44];
	int m_id;
};

class WeaponTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Coord3D *sourcePos,
		const Object *source, const Coord3D *pos, int extra);
};

extern WeaponStore *TheWeaponStore;

void *__cdecl operator new(unsigned int);
inline void *__cdecl operator new(unsigned int, void *p) { return p; }

struct Rva001F01D0Payload
{
	int value;
	Rva001F01D0Payload(int v) { value = v; }
};

struct Rva001F01D0Node
{
	Rva001F01D0Node *next;
	Rva001F01D0Node *prev;
	Rva001F01D0Payload payload;
};

class Rva001F01D0
{
public:
	void fireAndRecord(Object *target);

	char m_pad00[0x08];
	Object *m_source; // +0x08
	char m_pad0C[0x2c - 0x0C];
	Coord3D m_sourcePos; // +0x2c
	char m_pad38[0x40 - 0x38];
	WeaponTemplate *m_template; // +0x40
	char m_pad44[0x74 - 0x44];
	int m_extra; // +0x74
	char m_pad78[0x7c - 0x78];
	Rva001F01D0Node *m_sentinel; // +0x7c
};

void Rva001F01D0::fireAndRecord(Object *target)
{
	TheWeaponStore->createAndFireTempWeapon(m_template, &m_sourcePos, m_source, &target->m_position, m_extra);
	int id = target->m_id;
	Rva001F01D0Node *sent = m_sentinel;
	Rva001F01D0Node *node = (Rva001F01D0Node *)::operator new(sizeof(Rva001F01D0Node));
	new (&node->payload) Rva001F01D0Payload(id);
	Rva001F01D0Node *prev = sent->prev;
	node->next = sent;
	node->prev = prev;
	prev->next = node;
	sent->prev = node;
}
