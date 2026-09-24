// ?rva000D4660@Player@@QBEPAVObject@@_NPAPAV2@@Z
// partial score=0.6 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /MD
class Object
{
public:
	char m_pad[0xA0];
	int m_id;
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};
extern GameLogic *TheBfmeGameLogic;

class Player;
// Retail passes the callback at RVA 0x000D4500 (VA 0x004D4500).
// Its original method name is unresolved, so this source keeps the address.
typedef void (*Rva000D4500Visitor)(Object *, void *);
struct Rva000D4660VisitContext
{
	const Player *player;
	bool flag;
	Object *chosen;
	Object *special;
};

class Player
{
public:
	void iterateObjects(Rva000D4500Visitor visitor, void *data) const;
	Object *rva000D4660(bool flag, Object **out) const;
};

Object *Player::rva000D4660(bool flag, Object **out) const
{
	Rva000D4660VisitContext info;
	info.player = this;
	info.flag = flag;
	info.chosen = 0;
	info.special = 0;
	iterateObjects(reinterpret_cast<Rva000D4500Visitor>(0x004D4500), &info);
	Object *chosen = info.chosen;
	if (out)
		*out = chosen;
	if (info.special) {
		Object *special = TheBfmeGameLogic->findObjectByID(info.special->m_id);
		if (special)
			return special;
	}
	return chosen;
}
