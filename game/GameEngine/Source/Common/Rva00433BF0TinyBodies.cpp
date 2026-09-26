// These independently carved leaves are reached only by anonymous thunks.
// Their names retain the retail addresses instead of guessing an owner.
class Rva00433BF0Self
{
public:
	void *getSelf();
};

void *Rva00433BF0Self::getSelf()
{
	return this;
}

void Rva00433C00Noop() {}

class Rva00433C10PointerGetter
{
public:
	void *get() const;

private:
	void *m_first;
	void *m_value;
};

void *Rva00433C10PointerGetter::get() const
{
	return m_value;
}

void Rva00433C20Noop() {}
void Rva00433C30Noop() {}
void Rva00433CB0Noop() {}
