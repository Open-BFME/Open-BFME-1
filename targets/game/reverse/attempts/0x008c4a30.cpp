// ?Rva008C4A30Check@@YA_NPAVRva8CD130Value@@@Z
// partial score=0.64 date=2026-09-28
// ?Rva008C4A30Check@@YA_NPAVRva8CD130Value@@@Z
// Retail 0x008C4A30, 873 bytes: AptValue numeric-string predicate (false for defined numbers
// and numeric strings, true otherwise; undefined/type 3 answer SWF version == 7).
// Rewritten from retail: per-type inline predicates, forceinline string dtor,
// text/length re-read from m_data at every use, bool local for the SWF test.
// Remaining: loop allocates length in EDX and next in EDI where retail uses EDI/EBP.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" long __cdecl strtol(const char *, char **, int);
extern "C" int __cdecl isdigit(int);

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool3AF0
{
	void *slot0;
	void (__cdecl *free)(void *);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;

int Rva00892370Get();

class Rva8CD130String
{
public:
	Rva8CD130String() : m_data(&g_bfmeDefaultString1284)
	{
		++m_data->m_refCount;
	}
	__forceinline ~Rva8CD130String()
	{
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
	}
	int getLength() const { return m_data->m_length; }
	char *text() const { return (char *)(m_data + 1); }

	BfmeStringData3AF0 *m_data;
};

class Rva8CD130Value
{
public:
	void getName(Rva8CD130String *output);
	bool isUndefined() const { return !m_valid15; }
	bool isType7() const { return m_type == 7 && !isUndefined(); }
	bool isType6() const { return m_type == 6 && !isUndefined(); }
	bool isStringType() const { return (m_type == 1 || m_type == 42) && !isUndefined(); }

	void *m_unknown00;
	union
	{
		unsigned int m_flags;
		struct
		{
			unsigned int m_type : 6;
			unsigned int m_bits06 : 9;
			unsigned int m_valid15 : 1;
		};
	};
};

bool Rva008C4A30Check(Rva8CD130Value *value)
{
	if (value->isType7() || value->isType6())
		return false;

	if (value->isStringType())
	{
		Rva8CD130String string;
		value->getName(&string);

		if (string.getLength() == 0)
			return true;

		if (string.text()[0] == '0' && string.getLength() > 2 && string.text()[1] == 'x')
		{
			char *end;
			strtol(string.text(), &end, 16);
			if (*end == 0)
				return false;
		}

		bool sawDot = false;
		char last = string.text()[string.getLength() - 1];
		if (last != '-' && last != '+' && last != 'e' && last != '.' && !isdigit(last))
			return true;

		char first = string.text()[0];
		if (first != '.' && first != '-' && first != '+' && !isdigit(first))
			return true;

		for (int index = 1; index < string.getLength(); ++index)
		{
			char current = string.text()[index];
			if (current == '.' && !sawDot)
			{
				sawDot = true;
				continue;
			}
			if (current == 'e' && index != 1)
			{
				if (index == 2 && (string.text()[0] == '+' || string.text()[0] == '-'))
					return true;
				int next = index + 1;
				if (next < string.getLength())
				{
					char following = string.text()[index + 1];
					if (following != '-' && following != '+' && !isdigit(following))
						return true;
					index = next;
				}
				continue;
			}
			if (!isdigit(current))
				return true;
		}
		return false;
	}

	if (!value->isUndefined() && value->m_type != 3)
		return true;
	bool swf7 = Rva00892370Get() == 7;
	return swf7;
}
