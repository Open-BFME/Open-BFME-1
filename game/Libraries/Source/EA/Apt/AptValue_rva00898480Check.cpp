// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00898480 is the Apt-value truth predicate reached by the named
// bfmeSwapTop/bfmeGo1218/bfmeGo1219 callers.  The neutral method name keeps
// the recovered public identity honest while retaining the complete 251-byte
// body; the jump table after the final RET is compiler data, not code.

extern unsigned int AptGetSwfVersion();
extern const float BfmeZeroRange;

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned int m_capacity;
	char m_text[1];
};

class AptValue
{
public:
	bool rva00898480Check();

private:
	void *m_vtable;
	unsigned int m_flags;
	union
	{
		bool m_boolean;
		int m_integer;
		float m_float;
		BfmeStringData3AF0 *m_string;
	};
	unsigned char m_gap0c[0x14];
	AptValue *m_indirect;
};

extern const BfmeStringData3AF0 g_bfmeDefaultString1284;
extern AptValue *g_bfmeFallbackDB;
extern "C" long __cdecl strtol(const char *, char **, int);
extern "C" double __cdecl Rva008921B0Atof(const char *);

bool AptValue::rva00898480Check()
{
	switch (m_flags & 0x3f)
	{
	case 1:
	case 42:
		if (AptGetSwfVersion() == 7)
		{
			AptValue *value = this;
			if ((m_flags & 0x3f) != 1)
				value = m_indirect;
			BfmeStringData3AF0 *const &string = value->m_string;
			return (string != const_cast<BfmeStringData3AF0 *>(&g_bfmeDefaultString1284)) ? 1 : 0;
		}
		{
			AptValue *value = this;
			if ((m_flags & 0x3f) != 1)
				value = m_indirect;
			BfmeStringData3AF0 *string = value->m_string;
			if (string->m_length > 2 && string->m_text[0] == '0' && string->m_text[1] == 'x')
			{
				return (strtol(string->m_text, 0, 16) != 0) ? 1 : 0;
			}
			value = this;
			if ((m_flags & 0x3f) != 1)
				value = m_indirect;
			BfmeStringData3AF0 *const &secondString = value->m_string;
			return (Rva008921B0Atof(secondString->m_text) != BfmeZeroRange) ? 1 : 0;
		}
	case 5:
		return m_boolean;
	case 7:
		return (m_integer != 0) ? 1 : 0;
	case 6:
		return (m_float != BfmeZeroRange) ? 1 : 0;
	default:
		return (this != g_bfmeFallbackDB) ? 1 : 0;
	}
}
