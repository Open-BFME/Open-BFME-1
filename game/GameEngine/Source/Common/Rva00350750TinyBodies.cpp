// Anonymous thunk callers do not prove semantic ownership for these carved
// leaves, so every type or function keeps its retail address.
class Rva00350750PointerGetter
{
public:
	void *get() const;
private:
	void *m_first;
	void *m_value;
};
void *Rva00350750PointerGetter::get() const { return m_value; }

class Rva00350760Self { public: void *getSelf(); };
void *Rva00350760Self::getSelf() { return this; }

void Rva00350770Noop() {}

class Rva003507B0Self { public: void *getSelf(); };
void *Rva003507B0Self::getSelf() { return this; }

void Rva003507C0Noop() {}

class Rva00350840PointerGetter
{
public:
	void *get() const;
private:
	void *m_value;
};
void *Rva00350840PointerGetter::get() const { return m_value; }

class Rva00350850PointerGetter
{
public:
	void *get() const;
private:
	void *m_value;
};
void *Rva00350850PointerGetter::get() const { return m_value; }

void Rva00350860Noop() {}
void Rva00350890Noop() {}
