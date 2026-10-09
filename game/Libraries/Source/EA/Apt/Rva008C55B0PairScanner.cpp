// cl: /O2 /DNDEBUG /MD /EHsc

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

class Rva8CD130String;
namespace Rva008C54A0 { void method(Rva8CD130String *); }

// Open BFME 2: Code/Libraries/Source/Apt/AptActionInterpreterConstantHandlers.cpp.
char *Rva008CF3C0State::parse(char *cursor, Rva008CF3C0String *name, Rva008CF3C0String *value)
{
    char *p = cursor, *eq = 0;
    {
        Rva008CF3C0Block *nameBlock = name->m_block;
        if (--nameBlock->m_ref == 0) g_pool01337A30->free(nameBlock);
        name->m_block = &g_default012D5298;
        ++g_default012D5298.m_ref;
    }
    {
        Rva008CF3C0Block *valueBlock = value->m_block;
        if (--valueBlock->m_ref == 0) g_pool01337A30->free(valueBlock);
        value->m_block = &g_default012D5298;
        ++g_default012D5298.m_ref;
    }
    for (; p && *p && *p != '&'; ++p)
        if (*p == '=') eq = p;
    if (eq)
    {
        ((BfmeBufVKG *)name)->bfmeAppendVKG(cursor, (unsigned)(eq - cursor));
        Rva008C54A0::method((Rva8CD130String *)name);
        ++eq;
        ((BfmeBufVKG *)value)->bfmeAppendVKG(eq, (unsigned)(p - eq));
        Rva008C54A0::method((Rva8CD130String *)value);
        if (*p == '&') ++p;
    }
    else p = 0;
    return p;
}
