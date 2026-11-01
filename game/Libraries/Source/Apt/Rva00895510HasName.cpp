// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00895510 (308 bytes, ret 4): does the receiver's name table
// (this+0x10: count at +0x28, 16-byte entries at +0x2C with the name first)
// hold the string of the candidate handle's object? Each table name is copied
// into a pooled string, compared by length, identity and bytes, and released;
// the by-value handle is destroyed on both returns. The only caller is
// Rva008956C0List::contains008956C0, which passes its own handle; no owner or
// vtable names the class, so it keeps the retail address.

extern void (*TheBfmeFree)(void *p, unsigned int bytes);	// retail 0x01337830

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
	char m_data[1];
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

class BfmeStrVKI
{
public:
	void bfmeSetVKI(const char *s);
	int getLength() const { return m_data->m_length; }
	void release()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_rva01337A30AllocPair->free(data);
	}
	bool operator==(const BfmeStrVKI &other) const
	{
		BfmeStringData3AF0 *a = m_data;
		int length = a->m_length;
		BfmeStringData3AF0 *b = other.m_data;
		if (length != b->m_length)
			return false;
		if (a == b)
			return true;
		return memcmp(a->m_data, b->m_data, length) == 0;
	}
	BfmeStringData3AF0 *m_data;
};

class BfmeDropObjectA
{
public:
	~BfmeDropObjectA(void);					// retail 0x00895260

	void operator delete(void *p, unsigned int bytes)
	{
		TheBfmeFree(p, bytes);
	}

	int m_refCount;						// +0x00
	BfmeStrVKI m_string;					// +0x04
	char m_rest[0x10];
};

class RefHandle008956C0
{
public:
	RefHandle008956C0(const RefHandle008956C0 &other)
	{
		BfmeDropObjectA *o = other.m_object;

		m_object = o;

		if (o != 0)
			++o->m_refCount;
	}

	~RefHandle008956C0(void)
	{
		BfmeDropObjectA *o = m_object;

		if (o != 0 && --o->m_refCount == 0)
			delete o;
	}

	BfmeDropObjectA *m_object;				// +0x00
};

struct Rva00895510Entry
{
	const char *m_name;					// +0x00
	int m_rest[3];
};

struct Rva00895510Table
{
	char m_gap00[0x28];
	int m_count;						// +0x28
	Rva00895510Entry *m_entries;				// +0x2C
};

class Rva00895510Receiver
{
public:
	int method(RefHandle008956C0 candidate);

private:
	char m_gap00[0x10];
	Rva00895510Table *m_table;				// +0x10
};

// ?method@Rva00895510Receiver@@QAEHVRefHandle008956C0@@@Z
int Rva00895510Receiver::method(RefHandle008956C0 candidate)
{
	for (int i = 0; i < m_table->m_count; ++i)
	{
		const char *text = m_table->m_entries[i].m_name;
		BfmeStrVKI name;
		name.bfmeSetVKI(text);
		bool same = name == candidate.m_object->m_string;
		name.release();
		if (same)
			return 1;
	}
	return 0;
}


