// ?parse@Rva008CF3C0State@@QAEPADPADPAVRva008CF3C0String@@1@Z
// partial score=0.27 date=2026-09-21
// cl: /O2 /DNDEBUG /MD /EHsc
// Open-BFME5: retail 0x008C55B0 (193B).
// ?parse@Rva008CF3C0State@@QAEPADPADPAVRva008CF3C0String@@1@Z
// Identity already pinned by the landed parseAndAppend caller
// (Rva008CF3C0ParseAppend.cpp, "pins:" alternatename to this exact RVA).
// Reuses that file's Rva008CF3C0String/Block/pool shapes. Scans
// "key=value&key2=value2..." from cursor: resets *name and *value to the
// shared default/empty string, finds the '=' and the following '&' or NUL,
// appends the key/value substrings via the landed BfmeBufVKG::bfmeAppendVKG
// (EAStringAppendBounded.cpp) -- name/value reinterpreted as BfmeBufVKG*,
// same ABI trick the caller already uses casting node->m_block -- then
// calls the still-carved per-string finisher at 0x008C54A0 (its own real
// signature/role not independently established) on each, and returns the
// cursor advanced past a trailing '&', or 0 when no '=' was found or the
// string was exhausted.

inline void *operator new(unsigned int, void *place) { return place; }

struct Rva008CF3C0Block
{
	unsigned short m_ref;
};

extern Rva008CF3C0Block g_default012D5298;

struct Rva008CF3C0Pool
{
	void *m_unused;
	void(__cdecl *free)(void *);
};

extern Rva008CF3C0Pool *g_pool01337A30;

class Rva008CF3C0String
{
public:
	Rva008CF3C0String()
	{
		m_block = &g_default012D5298;
		++g_default012D5298.m_ref;
	}

	~Rva008CF3C0String()
	{
		Rva008CF3C0Block *block = m_block;
		if (--block->m_ref == 0)
			g_pool01337A30->free(block);
	}

	Rva008CF3C0Block *m_block;
};

class BfmeBufVKG
{
public:
	BfmeBufVKG *bfmeAppendVKG(const char *source, unsigned int limit);
};

class Rva008CF3C0State
{
public:
	char *parse(char *cursor, Rva008CF3C0String *name, Rva008CF3C0String *value);
};

extern "C" void __cdecl bfmeFinish008C54A0(Rva008CF3C0String *s);
#pragma comment(linker, "/alternatename:_bfmeFinish008C54A0=?d_008c54a0@@YAXXZ")

char *Rva008CF3C0State::parse(char *cursor, Rva008CF3C0String *name, Rva008CF3C0String *value)
{
	char *p = cursor;
	char *eq = 0;

	{
		Rva008CF3C0Block *nameBlock = name->m_block;
		if (--nameBlock->m_ref == 0)
			g_pool01337A30->free(nameBlock);
		name->m_block = &g_default012D5298;
		++g_default012D5298.m_ref;
	}

	{
		Rva008CF3C0Block *valueBlock = value->m_block;
		if (--valueBlock->m_ref == 0)
			g_pool01337A30->free(valueBlock);
		value->m_block = &g_default012D5298;
		++g_default012D5298.m_ref;
	}

	if (cursor == 0)
		return 0;
	for (;;)
	{
		char c = *p;
		if (c == 0 || c == '&')
			break;
		if (c == '=')
		{
			eq = p;
			++p;
			continue;
		}
		++p;
	}

	if (eq == 0)
		return 0;

	((BfmeBufVKG *)name)->bfmeAppendVKG(cursor, (unsigned int)(eq - cursor));
	bfmeFinish008C54A0(name);

	char *valueStart = eq + 1;
	((BfmeBufVKG *)value)->bfmeAppendVKG(valueStart, (unsigned int)(p - valueStart));
	bfmeFinish008C54A0(value);

	if (*p == '&')
		++p;

	return p;
}
