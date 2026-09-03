// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x0022F130. Virtual at owner+0x1FC, Object::onRemovedFrom,
// then isInContainer/bfmeApply on the controlling player's +0x22C tracker.

class BfmeVirt48;

class Object
{
public:
	void onRemovedFrom(Object *other);
	class Player *getControllingPlayer() const;

	char m_pad[0x1FC];
	BfmeVirt48 *m_virt;
};

class BfmeVirt48
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void notify(Object *obj);
};

class BfmePointed2F130
{
public:
	char m_pad[0x1FC];
	BfmeVirt48 *m_virt;
};

class TunnelTracker
{
public:
	bool isInContainer(Object *obj);
	void bfmeApply(Object *obj, void *extra);
};

class Player
{
public:
	char m_pad[0x22C];
	TunnelTracker *m_tunnels;
};

class Gen_0022F130
{
public:
	void bfmeRemove(Object *obj, void *extra);
};

// ?bfmeRemove@Gen_0022F130@@QAEXPAVObject@@PAX@Z
void Gen_0022F130::bfmeRemove(Object *obj, void *extra)
{
	if (obj == 0)
		return;
	BfmeVirt48 *v = (*(Object **)((char *)this - 0x18))->m_virt;
	if (v != 0)
		v->notify(obj);
	obj->onRemovedFrom(*(Object **)((char *)this - 0x18));
	Player *player = (*(Object **)((char *)this - 0x18))->getControllingPlayer();
	if (player == 0)
		return;
	if (!player->m_tunnels->isInContainer(obj))
		return;
	player->m_tunnels->bfmeApply(obj, extra);
}
