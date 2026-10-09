// ?rva008AA650StringSplit@@YAPAVBfmeC1030@@PAVRva8CD130Value@@H@Z
// partial score=0.4118 date=2026-10-09
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
	__forceinline const Rva8CD130String &string008AA650() const {
		return *(const Rva8CD130String *)
			(((m_flags & 0x3f) == 1)
				? (const char *)this + 8
				: (const char *)m_indirect + 8);
	}


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

extern AptValue **g_bfmeArr1233;
struct Rva008AE770Stack { int field00; };
extern Rva008AE770Stack Rva008AE770TheStack;
#define g_count01338748 Rva008AE770TheStack.field00

class BfmeItemDX
{
};

extern void __cdecl bfmePush(BfmeItemDX *item);

class BfmeC1030
{
public:
	BfmeC1030 *bfmeGo1030C();
	__forceinline void set(int index, class Rva008A9B00 *value);
	void *m_bfmeVfptr;
	char m_bfmePad[0x1c];
	int m_bfme20, m_bfme24, m_bfme28;
};


class Rva008A9120HeaderedDelete {
public:
    static void operator delete(void *storage, unsigned int size);
};
class ArrayValue008B9C60 : public BfmeC1030, public Rva008A9120HeaderedDelete {
public:
    ArrayValue008B9C60();
    static void *operator new(unsigned int bytes) {
        unsigned int *raw = (unsigned int *)Rva008C5D70Alloc(bytes + 8);
        void *storage = raw + 2;
        bfmePush((BfmeItemDX *)storage);
        return storage;
    }
};

struct BfmeC1030Block
{
	int m_header[2];
	BfmeC1030 m_object;
};

class BfmeE1242;
class BfmeN1242 {
public:
    void rva008B8E10(int index, BfmeE1242 *value);
};

// ?set@BfmeC1030@@QAEXHPAVRva008A9B00@@@Z absent-from-retail
__forceinline void BfmeC1030::set(int index, Rva008A9B00 *value)
{
	((BfmeN1242 *)this)->rva008B8E10(index, (BfmeE1242 *)value);
}

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


struct Rva008A9A70Str { BfmeStringData3AF0 *m_block; };
class Rva008A9A70 { public: void set(const Rva008A9A70Str &src); };

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

struct Rva00899560Pool;
extern Rva00899560Pool *g_rva01337810GcRoots;
struct Rva008C3B60Node;
extern Rva008C3B60Node *g_rva01338478NodeHead;
__forceinline Rva008A9B00 *&freeHead008AA650() {
    return *(Rva008A9B00 **)&g_rva01338478NodeHead;
}

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


__forceinline Rva008A9B00 *acquire008AA650()
{
	Rva008A9B00 *object = freeHead008AA650();
	if (object)
	{
		freeHead008AA650() = object->m_next;
		((Rva008AA650Registry *)g_rva01337810GcRoots)->add(object);
		if (object->m_data != &g_bfmeDefaultString1284)
			((BfmeStrVKK *)&object->m_data)->bfmeTruncVKK(0);
	}
	else
	{
		object = new Rva008A9B00;
	}
	return object;
}

static __forceinline int decodeUtf8Rva008AA650(const unsigned char *&scan)
{
	unsigned char first = *scan;
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
	return codePoint;
}

BfmeC1030 *rva008AA650StringSplit(Rva8CD130Value *value, int count)
{
	BfmeC1030 *result = (BfmeC1030 *)new ArrayValue008B9C60;

	if (count == 0)
	{
		result->set(0, (Rva008A9B00 *)value);
		return result;
	}

	if (count >= 1)
	{
		Rva8CD130String separator;
		int limit = 0xF423F;
		{
			Rva8CD130Value *top = (Rva8CD130Value *)g_bfmeArr1233[g_count01338748 - 1];
			top->getName(&separator);
		}
		if (count >= 2)
			limit = g_bfmeArr1233[g_count01338748 - 2]->toInteger();

		Rva8CD130String input(value->string008AA650());
		int index = 0;

		if (separator.m_data->m_length == 0)
		{
			const unsigned char *scan = (const unsigned char *)input.m_data + 8;
			while (index < limit)
			{
				int codePoint = decodeUtf8Rva008AA650(scan);
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
			int separatorLength = separator.m_data->m_length;
			const char *text = (const char *)input.m_data + 8;
			int start = 0;
			while (index < limit)
			{
				int found = ((EAStringC *)&input)->Find(
					(const char *)separator.m_data + 8, start);
				if (found == -1)
				{
					Rva008A9B00 *object = acquire008AA650();
					Rva8CD130String part;
					if (start != -1)
						((BfmeBufVKG *)&part)->bfmeAppendVKG((const char *)input.m_data + 8 + start, -1 - start);
					((Rva008A9A70 *)object)->set(*(const Rva008A9A70Str *)&part);
					result->set(index, object);
					break;
				}
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

		}
	}
	return result;
}
