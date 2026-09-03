// ?bfmeOnDie@Gen_0022F300@@QAEXPAVDamageInfo@@@Z
// partial score=0.78 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022F300. DieMux check on (this-0x24)+8, then
// getControllingPlayer on *(this-0x20) and TunnelTracker::onTunnelDestroyed.

class Object;
class DamageInfo;

class DieMuxData
{
public:
	bool isDieApplicable(Object const *obj, DamageInfo const *info) const;
};

struct BfmeDieHolder
{
	char m_pad[8];
	DieMuxData m_mux;
};

class Player
{
public:
	char m_pad[0x22C];
	class TunnelTracker *m_tunnels;
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class TunnelTracker
{
public:
	void onTunnelDestroyed(Object const *obj);
};

class Gen_0022F300
{
public:
	void bfmeOnDie(DamageInfo *info);

private:
	char m_pad[0xAD];
	unsigned char m_flag;
};

// ?bfmeOnDie@Gen_0022F300@@QAEXPAVDamageInfo@@@Z
void Gen_0022F300::bfmeOnDie(DamageInfo *info)
{
	Object *obj = *(Object **)((char *)this - 0x20);
	BfmeDieHolder *holder = *(BfmeDieHolder **)((char *)this - 0x24);
	if (!holder->m_mux.isDieApplicable(obj, info))
		return;
	if (m_flag == 0)
		return;
	Player *player = (*(Object **)((char *)this - 0x20))->getControllingPlayer();
	if (player == 0)
		return;
	TunnelTracker *t = player->m_tunnels;
	if (t == 0)
		return;
	Object *again = *(Object **)((char *)this - 0x20);
	t->onTunnelDestroyed(again);
	m_flag = 0;
}
