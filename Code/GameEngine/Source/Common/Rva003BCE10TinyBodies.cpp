// These carved leaves are reached only through anonymous thunks. Each type
// keeps its RVA so the source does not claim an unproved semantic owner.
class Rva003BCE10Self { public: void *getSelf(); };
void *Rva003BCE10Self::getSelf() { return this; }

void Rva003BCE20Noop() {}

class Rva003BCE70Self { public: void *getSelf(); };
void *Rva003BCE70Self::getSelf() { return this; }

void Rva003BCE80Noop() {}

class Rva003BCED0Self { public: void *getSelf(); };
void *Rva003BCED0Self::getSelf() { return this; }

void Rva003BCEE0Noop() {}

class Rva003BCF40Self { public: void *getSelf(); };
void *Rva003BCF40Self::getSelf() { return this; }

class Rva003BCFB0PointerGetter
{
public:
	void *get() const;
private:
	void *m_first;
	void *m_value;
};
void *Rva003BCFB0PointerGetter::get() const { return m_value; }

class Rva003BCFC0PointerGetter
{
public:
	void *get() const;
private:
	void *m_value;
};
void *Rva003BCFC0PointerGetter::get() const { return m_value; }

class Rva003BCFD0Self { public: void *getSelf(); };
void *Rva003BCFD0Self::getSelf() { return this; }

void Rva003BCFE0Noop() {}
