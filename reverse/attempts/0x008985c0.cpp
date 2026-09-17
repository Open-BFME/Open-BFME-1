// ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z
// partial score=0.48 date=2026-09-17
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?getName@Rva8CD130Value@@QAEXPAVRva8CD130String@@@Z
//
// Apt value-to-name formatting at retail RVA 0x008985C0.  The class name is
// address-derived and is retained by the already matched callers at
// 0x008CD130 and 0x008D0D80.  The value layout is witnessed by those callers
// and by the adjacent Apt value predicates.

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPool3AF0
{
	void *m_unused;
	void (__cdecl *free)(void *storage);
};

extern BfmeStringData3AF0 g_bfmeDefaultString1284;
extern BfmeStringPool3AF0 *g_bfmeStringPool1284;
extern const float BfmeZeroRange;
extern double g_bfmeSubB3;

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *destination, const char *format, ...);
extern "C" long __cdecl __ftol2(double value);
extern "C" double __cdecl fmod(double value, double divisor);
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class BfmeStrVKI
{
public:
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}

	void __declspec(nothrow) bfmeSetVKI(const char *text);

	~BfmeStrVKI()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	BfmeStringData3AF0 *m_data;
};

class Rva8CD130String
{
public:
	Rva8CD130String()
	{
		m_data = &g_bfmeDefaultString1284;
		++m_data->m_refCount;
	}

	~Rva8CD130String()
	{
		BfmeStringData3AF0 *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}

	void assign(BfmeStringData3AF0 *data)
	{
		++data->m_refCount;
		BfmeStringData3AF0 *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);
		m_data = data;
	}

	void assign(const BfmeStrVKI &text)
	{
		assign(text.m_data);
	}

	BfmeStringData3AF0 *m_data;
};

class BfmeString1284
{
public:
	BfmeStringData3AF0 *m_data;
};

class BfmeStringWriter1284
{
public:
	void bfmeBuildString1284(BfmeString1284 *result, int value);
};

class Rva8CD130Value
{
public:
	virtual void addRef();
	virtual void release();
	void getName(Rva8CD130String *name);

	unsigned m_flags;
	union
	{
		bool m_boolean;
		int m_integer;
		float m_float;
		BfmeStringData3AF0 *m_string;
	};
	unsigned char m_gap0c[0x14];
	void *m_indirect;
	void *m_elements;
	unsigned m_unused24;
	int m_count;

	bool isUndefined() const
	{
		return ((m_flags >> 15) & 1) == 0;
	}
};

struct Rva008985C0Locals
{
	BfmeStringData3AF0 *strings[15];
};

extern void bfmeResetEVF(void *context, BfmeStrVKI *text);
extern void d_008b6880();

#define APT_ASSIGN_LITERAL(SLOT, LITERAL) \
	{ \
		BfmeStrVKI text((const char *)(LITERAL)); \
		locals.strings[SLOT] = text.m_data; \
		name->assign(locals.strings[SLOT]); \
	}

void Rva8CD130Value::getName(Rva8CD130String *name)
{
	Rva8CD130Value *self = this;
	Rva008985C0Locals locals;
	char buffer[0x80];
	_ReadWriteBarrier();
	if (self->isUndefined())
	{
		unsigned type = self->m_flags & 0x3f;
		switch (type)
		{
		case 1:
		case 42:
		{
			Rva8CD130Value *value = self;
			if (type != 1)
				value = reinterpret_cast<Rva8CD130Value *>(self->m_indirect);
			name->assign(value->m_string);
			break;
		}
		case 5:
			if (self->m_boolean)
				name->assign(*reinterpret_cast<BfmeStringData3AF0 **>(0x01338720));
			else
				name->assign(*reinterpret_cast<BfmeStringData3AF0 **>(0x01338550));
			break;
		case 6:
		{
			float number = self->m_float;
			if (fmod((double)number, g_bfmeSubB3) == (double)BfmeZeroRange)
			{
					sprintf(buffer, (const char *)0x0107C7B4,
					(long)__ftol2((double)number));
				BfmeStrVKI text(buffer);
				locals.strings[0] = text.m_data;
				name->assign(locals.strings[0]);
			}
			else
			{
				sprintf(buffer, (const char *)0x01082F4C, (double)number);
				BfmeStrVKI text(buffer);
				locals.strings[1] = text.m_data;
				name->assign(locals.strings[1]);
			}
			break;
		}
		case 7:
		{
			sprintf(buffer, (const char *)0x0107C7B4, self->m_integer);
			BfmeStrVKI text(buffer);
			locals.strings[2] = text.m_data;
			name->assign(locals.strings[2]);
			break;
		}
		case 8:
			APT_ASSIGN_LITERAL(3, 0x01135FA8);
			break;
		case 9:
		{
			sprintf(buffer, (const char *)0x0113600C, self->m_indirect);
			BfmeStrVKI text(buffer);
			locals.strings[4] = text.m_data;
			name->assign(locals.strings[4]);
			break;
		}
		case 10:
			APT_ASSIGN_LITERAL(5, 0x01136000);
			break;
		case 11:
			APT_ASSIGN_LITERAL(6, 0x01135F9C);
			break;
		case 20:
			APT_ASSIGN_LITERAL(7, 0x01135F8C);
			break;
		case 21:
			APT_ASSIGN_LITERAL(8, 0x01136028);
			break;
		case 22:
			reinterpret_cast<BfmeStringWriter1284 *>(self)->bfmeBuildString1284(
				reinterpret_cast<BfmeString1284 *>(name), 0x01076FE8);
			break;
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
		case 31:
		case 35:
		case 36:
		case 39:
			APT_ASSIGN_LITERAL(9, 0x01135FF0);
			break;
		case 28:
			APT_ASSIGN_LITERAL(10, 0x01135FCC);
			break;
		case 29:
			// The current callee contract exposes this target under its
			// address-derived cdecl name; its output ABI remains unresolved.
			d_008b6880();
			break;
		case 30:
			APT_ASSIGN_LITERAL(11, 0x01135FC0);
			break;
		case 32:
		case 33:
		case 34:
			APT_ASSIGN_LITERAL(12, 0x01135FE4);
			break;
		case 37:
			APT_ASSIGN_LITERAL(13, 0x01135F80);
			break;
		case 38:
			APT_ASSIGN_LITERAL(14, 0x01135F6C);
			break;
		case 41:
			name->assign(reinterpret_cast<BfmeStringData3AF0 *>(self->m_indirect));
			break;
		default:
			bfmeResetEVF(self, reinterpret_cast<BfmeStrVKI *>(name));
			break;
		}
	}
	else
	{
		bfmeResetEVF(self, reinterpret_cast<BfmeStrVKI *>(name));
	}
}

#undef APT_ASSIGN_LITERAL
