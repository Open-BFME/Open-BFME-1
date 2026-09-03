// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022F300. Guarded list dispatch over the same neighborhood
// as the 0x0022F260 forwarder: the check object sits 8 past the pointer at
// this-0x24, the Object at this-0x20, and a flag at this+0xAD gates the
// whole dispatch. The check runs first; then the flag, the controlling
// player, and its list at player+0x22C are validated in turn; finally the
// list method runs with the Object and the flag is cleared. Object/Player
// reuse the real names so the getControllingPlayer call resolves to its
// matched body; the check and list callees are pinned at their thunks.

class BfmeCheck300
{
};

bool __fastcall bfmeCheck300(BfmeCheck300 *check, int b, void *o, void *a);

struct BfmeList300
{
	void bfmeDo(void *o);
};

class Player
{
public:
	char m_pad[0x22C];
	BfmeList300 *m_list;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class BfmeThing300
{
public:
	void bfmeGo(void *a);

private:
	char m_pad[0xAD];
	bool m_flag;
};

// ?bfmeGo@BfmeThing300@@QAEXPAX@Z
void BfmeThing300::bfmeGo(void *a)
{
	if (!bfmeCheck300((BfmeCheck300 *)((char *)*(void **)((char *)this - 0x24) + 8), (int)a, *(void **)((char *)this - 0x20), a))
		return;
	if (!m_flag)
		return;
	Object *objA = *(Object **)((char *)this - 0x20);
	Player *player = objA->getControllingPlayer();
	if (!player)
		return;
	BfmeList300 *list = player->m_list;
	if (!list)
		return;
	list->bfmeDo(*(void **)((char *)this - 0x20));
	m_flag = false;
}
