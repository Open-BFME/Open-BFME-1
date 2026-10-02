// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0021A080. DieMux on *(this-0x24)+8, skip if object status
// bit 2, then find+unregisterCave through TheCaveSystem and onTunnelDestroyed.

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

#include "../GameLogic/Object/object.h"

class TunnelTracker
{
public:
	void onTunnelDestroyed(Object const *obj);
};

class CaveSystem
{
public:
	void unregisterCave(int id);
};

class BfmeK1101;

class BfmeJ1101
{
public:
	BfmeK1101 *bfmeFind1101(int key);
};

// The DIR32 at 0x012F086C is retail's `CaveSystem *TheCaveSystem`
// (?TheCaveSystem@@3PAVCaveSystem@@A); ZH spells the same declaration
// `extern CaveSystem *TheCaveSystem;` in GameLogic/CaveSystem.h. This TU's
// own view of the class, BfmeJ1101, is reached through a cast.
extern CaveSystem *TheCaveSystem;

class Gen_0021A080
{
public:
	void bfmeOnDie(DamageInfo *info);

private:
	char m_pad[0xB4];
	int m_id;
};

// ?bfmeOnDie@Gen_0021A080@@QAEXPAVDamageInfo@@@Z
void Gen_0021A080::bfmeOnDie(DamageInfo *info)
{
	Object *obj = *(Object **)((char *)this - 0x20);
	BfmeDieHolder *holder = *(BfmeDieHolder **)((char *)this - 0x24);
	if (!holder->m_mux.isDieApplicable(obj, info))
		return;
	obj = *(Object **)((char *)this - 0x20);
	if ((reinterpret_cast<const unsigned char *>(obj->m_status)[0] & 4) != 0)
		return;
	TunnelTracker *t = (TunnelTracker *)((BfmeJ1101 *)TheCaveSystem)->bfmeFind1101(m_id);
	TheCaveSystem->unregisterCave(m_id);
	t->onTunnelDestroyed(*(Object **)((char *)this - 0x20));
}
