// cl: /DNDEBUG /MD /EHsc
// Open-BFME6: 0x00219C70. Guarded find through g_bfmeJ1101, two methods on the
// result, then a virtual at owner+0x1FC vtable+0x48 and Object::onRemovedFrom.

class Object
{
public:
	void onRemovedFrom(Object *other);
};

class TunnelTracker
{
public:
	bool isInContainer(Object *obj);
	void bfmeApply(Object *obj, void *extra);
};

class BfmeK1101;

class BfmeJ1101
{
public:
	class BfmeK1101 *bfmeFind1101(int key);
};

extern BfmeJ1101 *g_bfmeJ1101;

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

class BfmePointed19C70
{
public:
	char m_pad[0x1FC];
	BfmeVirt48 *m_virt;
};

class Gen_00219C70
{
public:
	void bfmeRemove(Object *obj, void *extra);

private:
	char m_pad[0xBC];
	int m_key;
};

// ?bfmeRemove@Gen_00219C70@@QAEXPAVObject@@PAX@Z
void Gen_00219C70::bfmeRemove(Object *obj, void *extra)
{
	if (obj == 0)
		return;
	TunnelTracker *k = (TunnelTracker *)g_bfmeJ1101->bfmeFind1101(m_key);
	if (!k->isInContainer(obj))
		return;
	k->bfmeApply(obj, extra);
	BfmeVirt48 *v = (*(BfmePointed19C70 **)((char *)this - 0x18))->m_virt;
	if (v != 0)
		v->notify(obj);
	obj->onRemovedFrom(*(Object **)((char *)this - 0x18));
}
