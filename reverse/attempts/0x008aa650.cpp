// ?d_008aa650@@YAXXZ
// partial score=0.15 date=2026-09-22
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// RVA 008AA650: opaque Apt string split callback.

struct BfmeStringData3AF0
{
	unsigned short m_refCount, m_length, m_capacity, m_unknown06;
};

struct BfmeStringPool3AF0
{
	void *m_unknown00;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern void *(__cdecl *Rva008C5D70Alloc)(unsigned int);

class Rva8CD130String
{
public:
	Rva8CD130String()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	Rva8CD130String(const Rva8CD130String &source)
	{
		m_data = source.m_data;
		++m_data->m_refCount;
	}

	~Rva8CD130String()
	{
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
	}

	BfmeStringData3AF0 *m_data;
};

class EAStringC
{
public:
	int Find(const char *text, int start);
};

class BfmeBufVKG
{
public:
	BfmeBufVKG *bfmeAppendVKG(const char *text, unsigned int limit);
};

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *output);

	void *m_unknown00;
	unsigned int m_flags;
	Rva8CD130String m_string;
	char m_unknown0C[0x14];
	Rva8CD130Value *m_indirect;
};

class AptValue
{
public:
	int toInteger() const;
};

extern Rva8CD130Value **g_bfmeArr1233;
extern int g_count01338748;

class BfmeItemDX
{
};

extern void __cdecl bfmePush(BfmeItemDX *item);

class BfmeC1030
{
public:
	BfmeC1030 *bfmeGo1030C();
	void set(int index, class Rva008A9B00 *value);
};

struct BfmeC1030Block
{
	int m_header[2];
	BfmeC1030 m_object;
};

extern void d_008b8e10();
#pragma comment(linker, "/alternatename:?set@BfmeC1030@@QAEXHPAVRva008A9B00@@@Z=?d_008b8e10@@YAXXZ")

class Rva008A9B00
{
public:
	__declspec(nothrow) Rva008A9B00();
	void *operator new(unsigned int bytes) { return Rva008C5D70Alloc(bytes); }

	void *m_unknown00;
	unsigned int m_flags;
	BfmeStringData3AF0 *m_data;
	Rva008A9B00 *m_next;
};

class Rva008B2EA0Node
{
public:
	void append(void *text);
};

struct Rva008AA650Registry
{
	int m_capacity;
	int m_count;
	void **m_entries;

	__forceinline void add(Rva008A9B00 *object)
	{
		int index = m_count;
		if (index >= m_capacity)
		{
			object->m_flags &= ~0x40000000u;
			return;
		}
		m_entries[index] = object;
		++m_count;
	}
};

extern Rva008AA650Registry *g_registry01337810;
extern Rva008A9B00 *g_free01338478;

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned int length);
};

class Rva008A0320String
{
public:
	Rva008A0320String()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	~Rva008A0320String()
	{
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
	}

	Rva008A0320String &rva008A0320(int value);
	BfmeStringData3AF0 *m_data;
};

#pragma comment(linker, "/alternatename:?rva008A0320@Rva008A0320String@@QAEAAV1@H@Z=?d_008a0320@@YAXXZ")

__forceinline Rva008A9B00 *acquire008AA650()
{
	Rva008A9B00 *object = g_free01338478;
	if (object)
	{
		g_free01338478 = object->m_next;
		g_registry01337810->add(object);
		if (object->m_data != &g_bfmeDefaultString1284)
			((BfmeStrVKK *)&object->m_data)->bfmeTruncVKK(0);
	}
	else
	{
		object = new Rva008A9B00;
	}
	return object;
}

BfmeC1030 *rva008AA650StringSplit(Rva8CD130Value *value, int count)
{
	BfmeC1030 *result = &((BfmeC1030Block *)Rva008C5D70Alloc(0x34))->m_object;
	bfmePush((BfmeItemDX *)result);
	if (result)
		result = result->bfmeGo1030C();

	int index = 0;
	if (count == 0)
	{
		result->set(0, (Rva008A9B00 *)value);
		return result;
	}

	Rva8CD130String separator;
	int limit = 0xF423F;
	if (count >= 1)
	{
		Rva8CD130Value *top = g_bfmeArr1233[g_count01338748 - 1];
		top->getName(&separator);
	}
	if (count >= 2)
		limit = ((AptValue *)g_bfmeArr1233[g_count01338748 - 2])->toInteger();

	Rva8CD130String input(*(Rva8CD130String *)
		(((value->m_flags & 0x3f) == 1)
			? (char *)value + 8
			: (char *)value->m_indirect + 8));
	int separatorLength = separator.m_data->m_length;

	if (separatorLength == 0)
	{
		const unsigned char *scan = (const unsigned char *)input.m_data + 8;
		while (index < limit)
		{
			unsigned int first = *scan;
			int codePoint;
			if (first <= 0x7f)
			{
				codePoint = first;
				++scan;
			}
			else if ((first & 0xe0) == 0xc0)
			{
				codePoint = (first & 0x1f) << 6;
				codePoint |= scan[1] & 0x3f;
				scan += 2;
			}
			else if ((first & 0xf0) == 0xe0)
			{
				codePoint = (first & 0x0f) << 6;
				codePoint |= scan[1] & 0x3f;
				codePoint = (codePoint << 6) | (scan[2] & 0x3f);
				scan += 3;
			}
			else
			{
				codePoint = (first & 7) << 6;
				codePoint |= scan[1] & 0x3f;
				codePoint = (codePoint << 6) | (scan[2] & 0x3f);
				codePoint = (codePoint << 6) | (scan[3] & 0x3f);
				scan += 4;
			}
			if (codePoint == 0)
				break;
			{
				Rva008A0320String text;
				text.rva008A0320(codePoint);
				Rva008A9B00 *object = acquire008AA650();
				((Rva008B2EA0Node *)object)->append((char *)text.m_data + 8);
				result->set(index, object);
			}
			++index;
		}
	}
	else
	{
		const char *text = (const char *)input.m_data + 8;
		int start = 0;
		while (index < limit)
		{
			int found = ((EAStringC *)&input)->Find(
				(const char *)separator.m_data + 8, start);
			if (found == -1)
				break;
			Rva008A9B00 *object = acquire008AA650();
			Rva8CD130String part;
			((BfmeBufVKG *)&part)->bfmeAppendVKG(text + start,
				found - start);
			++part.m_data->m_refCount;
			BfmeStringData3AF0 *old = object->m_data;
			if (--old->m_refCount == 0)
				g_bfmeStringPool1284->free(old);
			object->m_data = part.m_data;
			result->set(index, object);
			start = found + separatorLength;
			++index;
		}

		Rva008A9B00 *object = acquire008AA650();
		Rva8CD130String part;
		if (start != -1)
			((BfmeBufVKG *)&part)->bfmeAppendVKG(text + start, -1 - start);
		++part.m_data->m_refCount;
		BfmeStringData3AF0 *old = object->m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		object->m_data = part.m_data;
		result->set(index, object);
	}
	return result;
}
