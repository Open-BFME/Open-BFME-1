// ?d_006f9a30@@YAXXZ
// partial score=0.84 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Retail 0x006F9A30. TheGameClient (0x012F1464) virtual slot +0x2C, then a
// by-value AsciiString argument the callee destroys, then a byte at +0x95.

template <typename T> struct Rva006F9A30StringData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class Rva006F9A30StringBase
{
	friend class Rva006F9A30String;

private:
	Rva006F9A30StringBase();
	Rva006F9A30StringBase(const Rva006F9A30StringBase<T> &other);
	~Rva006F9A30StringBase();

	Rva006F9A30StringData<T> *m_data;
};

class Rva006F9A30String : private Rva006F9A30StringBase<char>
{
public:
	Rva006F9A30String(const Rva006F9A30String &other) : Rva006F9A30StringBase<char>(other) {}
	~Rva006F9A30String() {}
};

class Rva006F9A30Client
{
public:
	virtual void pad00();
	virtual void pad04();
	virtual void pad08();
	virtual void pad0C();
	virtual void pad10();
	virtual void pad14();
	virtual void pad18();
	virtual void pad1C();
	virtual void pad20();
	virtual void pad24();
	virtual void pad28();
	virtual void *findById(unsigned int id);
};

extern Rva006F9A30Client *TheRva006F9A30Client;		// 0x012F1464

class Rva006F9A30Result
{
public:
	unsigned char m_pad[0x95];
	unsigned char m_flag;
};

class Rva006F9A30Host
{
public:
	void apply(unsigned int id, const Rva006F9A30String &name);
	Rva006F9A30Result *make(unsigned int id, Rva006F9A30String name);

private:
	unsigned char m_pad[0x28];
	unsigned char m_enabled;
};

// ?apply@Rva006F9A30Host@@QAEXIABVRva006F9A30String@@@Z
void Rva006F9A30Host::apply(unsigned int id, const Rva006F9A30String &name)
{
	register unsigned int localId;
	register Rva006F9A30Host *self = this;
	Rva006F9A30Client *client = TheRva006F9A30Client;
	if (client)
	{
		localId = id;
		if (client->findById(localId) && self->m_enabled)
		{
			Rva006F9A30Result *result = self->make(localId, name);
			if (result)
				result->m_flag = 1;
		}
	}
}
