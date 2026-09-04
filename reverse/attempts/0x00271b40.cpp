// ?bfmeSyncEGF@BfmeThingEGF@@QAEXXZ
// partial score=0.95 date=2026-09-04
// ?bfmeSyncEGF@BfmeThingEGF@@QAEXXZ
// partial score=0.95 date=2026-09-03
// Open-BFME6: convert 0x00271B40 list-tag shadow sync, sibling of bfmeGoEGFc.
// 249B body exact except 3 else-path thiscall sites: retail mov ecx,edi then
// push imm; ours push imm then mov ecx,edi. Same 12 bytes, no lever flipped it
// (local/ref/fastcall/inlined-thiscall/TU-dummy /Os).

class Drawable
{
public:
	void setShadowsEnabled(bool enable);

	unsigned char m_pad[0x3ac];
	unsigned char m_flag3ac;
};

class Object
{
public:
	virtual void spare00();
	virtual void spare01();
	virtual void spare02();
	virtual void spare03();
	virtual void spare04();
	virtual void spare05();
	virtual void spare06();
	virtual void spare07();
	virtual void spare08();
	virtual void spare09();
	virtual Drawable *getDrawable();

	bool isLocallyControlled() const;

	unsigned char m_pad[0x214 - 4];
	Object *m_other;
};

class BfmeInit962
{
public:
	void bfmeInit962(int a);
};

class BfmeA1057
{
public:
	void bfmeGo1057A(int a);
};

class Rva004141C0
{
public:
	void broadcast();
};

class Rva004141A0GuardedVCall
{
public:
	void forward(int a0, int a1);
};

class ObjectAttemptDamageFlagHook
{
public:
	int value();
};

class BfmeTimerF2C
{
public:
	int m_pad00[2];
	BfmeTimerF2C *m_alt;
	int m_pad0C[5];
	int m_deadline;
};

class BfmeSubF2C
{
public:
	bool fastActive() const
	{
		if (!m_owner)
			return false;
		if (!m_timer)
			return false;
		BfmeTimerF2C *node = m_timer->m_alt;
		if (!node)
			node = m_timer;
		return node->m_deadline != 0x7FFFFFFF;
	}

	int m_head;
	int *m_owner;
	int m_gap[2];
	BfmeTimerF2C *m_timer;
};

class BfmeThingEGF
{
public:
	void bfmeSyncEGF();

private:
	unsigned char m_headA[8];
	Object *m_object;
	unsigned char m_headB[0x140 - 0x0c];
	BfmeSubF2C *m_p;
	unsigned char m_headC[0x339 - 0x144];
	bool m_flag339;
};

// ?bfmeSyncEGF@BfmeThingEGF@@QAEXXZ
void BfmeThingEGF::bfmeSyncEGF()
{
	bool extra = false;
	Drawable *draw = m_object->getDrawable();
	if (!draw)
		return;

	Object *o = m_object;
	Object *other = o->m_other;
	if (other)
	{
		Drawable *draw2 = other->getDrawable();
		if (draw2)
			extra = draw2->m_flag3ac != 0;
	}
	else
		extra = draw->m_flag3ac != 0;

	BfmeSubF2C *p = m_p;
	if (p && p->fastActive())
	{
		if (m_flag339)
			return;
		((BfmeInit962 *)draw)->bfmeInit962(5);
		draw->setShadowsEnabled(false);
		m_flag339 = true;
		if (!extra)
			return;
		if (!m_object->isLocallyControlled())
			return;
		((Rva004141C0 *)draw)->broadcast();
	}
	else
	{
		if (!m_flag339)
			return;
		((BfmeA1057 *)draw)->bfmeGo1057A(5);
		draw->setShadowsEnabled(true);
		m_flag339 = false;
		if (!extra)
			return;
		if (!m_object->isLocallyControlled())
			return;
		((Rva004141A0GuardedVCall *)draw)->forward(1, ((ObjectAttemptDamageFlagHook *)m_object)->value());
	}
}
