// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Open-BFME: address-derived reconstruction of the retail callback at
// 0x001FD120.  The owner name is intentionally not invented: only the
// offsets and the existing retail callee identities are proven here.

class Object;

class Overridable
{
public:
    const Overridable *getFinalOverride() const;
    void *m_vtable;
    Overridable *m_field04;
};

class BFMEObjectLayerQuery
{
public:
	int getLayer() const;
};

class StateMachine
{
public:
    Object *getGoalObject();
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class Rva001FD120Template : public Overridable {};

class Object
{
public:
	void *m_vtable;
	Rva001FD120Template *m_template;
	unsigned char m_pad08[0x204 - 0x08];
	AIUpdateInterface *m_ai;
};

class Rva001FD120Dispatch
{
public:
	void dispatch(Object *candidate, unsigned int value);
};

class Rva001FD120Owner
{
public:
	void run(Object *candidate, void *unused0, void *unused2);

private:
	unsigned char m_pad00[0x0C];
	Object * volatile m_field0C;
	unsigned char m_pad10[0x2C - 0x10];
	int m_field2C;
};

void Rva001FD120Owner::run(Object *candidate, void *, void *)
{
	if (m_field2C != 1)
		return;
	if (candidate == 0)
		return;

	const Rva001FD120Template *template_ = candidate->m_template;
	if (template_ != 0)
	{
		if (template_->m_field04 != 0)
			template_ = static_cast<const Rva001FD120Template *>(
                template_->m_field04->getFinalOverride());
	}
	if (*(const unsigned char *)((const char *)template_ + 0xC8) & 4)
		return;

	if (((BFMEObjectLayerQuery *)candidate)->getLayer() != 1)
		return;
	AIUpdateInterface *ai = candidate->m_ai;
	if (ai != 0)
	{
		StateMachine *holder =
			*(StateMachine **)((char *)ai + 0x30);
		Object *owner = m_field0C;
		if (holder->getGoalObject() == owner)
			return;
		owner = m_field0C;
		if (ai->getCurrentVictim() == owner)
			return;
	}

	((Rva001FD120Dispatch *)this)->dispatch(candidate, 0x41855C29);
}
