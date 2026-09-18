// ?Rva008C4A30Check@@YA_NPAVRva008C4A30Value@@@Z
// partial score=0.28 date=2026-09-18
// Retail 0x008C4A30, 873 bytes.
// Address-qualified AptValue numeric-string predicate.  The caller identity is
// not retained, so the RVA remains in the name.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

#include <ctype.h>
#include <stdlib.h>

struct Rva008C4A30StringBlock
{
	unsigned short refs;
	unsigned short length;
	unsigned int capacity;
	char text[1];
};

struct Rva008C4A30StringPool
{
	void *slot0;
	void (__cdecl *release)(Rva008C4A30StringBlock *);
};

extern Rva008C4A30StringBlock g_bfmeDefaultString1284;
extern Rva008C4A30StringPool *g_bfmeStringPool1284;
extern int Rva00892370Get();

struct Rva008C4A30String
{
	Rva008C4A30StringBlock *block;

	Rva008C4A30String()
		: block(&g_bfmeDefaultString1284)
	{
		++block->refs;
	}

	~Rva008C4A30String()
	{
		if (--block->refs == 0)
			g_bfmeStringPool1284->release(block);
	}
};

class Rva008C4A30Value
{
public:
    void fillString(Rva008C4A30String *result);
    unsigned int type() const { return flags & 0x3f; }
    bool isUndefined() const { return ((flags >> 15) & 1) == 0; }

    void *vtable;
    unsigned int flags;
};

#pragma comment(linker, "/alternatename:?fillString@Rva008C4A30Value@@QAEXPAURva008C4A30String@@@Z=?d_008985c0@@YAXXZ")
#pragma comment(linker, "/alternatename:?g_bfmeDefaultString1284@@3URva008C4A30StringBlock@@A=?g_bfmeDefaultString1284@@3UBfmeStringData3AF0@@A")
#pragma comment(linker, "/alternatename:?g_bfmeStringPool1284@@3PAURva008C4A30StringPool@@A=?g_bfmeStringPool1284@@3PAUBfmeStringPool3AF0@@A")

bool Rva008C4A30Check(Rva008C4A30Value *value)
{
    unsigned int type = value->type();
    if (type == 7)
    {
        if (!value->isUndefined())
            goto numeric;
    }
    if (type == 6)
    {
        if (!value->isUndefined())
            goto numeric;
    }

    if (type == 1 || (type == 42 && !value->isUndefined()))
	{
		Rva008C4A30String string;
		value->fillString(&string);
		Rva008C4A30StringBlock *block = string.block;

		if (block->length == 0)
			return true;

		char *text = block->text;
		if (block->length > 2 && text[0] == '0' && text[1] == 'x')
		{
			char *end = 0;
			strtol(text, &end, 16);
			if (*end == 0)
				return false;
		}

		char last = text[block->length - 1];
		if (last != '-' && last != '+' && last != 'e' && last != '.' && !isdigit(last))
			return true;

		char first = text[0];
		if (first != '.' && first != '-' && first != '+' && !isdigit(first))
			return true;

		bool sawDot = false;
		for (int index = 1; index < block->length; ++index)
		{
			char current = text[index];
			if (current == '.' && !sawDot)
			{
				sawDot = true;
				continue;
			}

            if (current == 'e' && index != 1)
            {
                if (index == 2 && (text[0] == '+' || text[0] == '-'))
                    return true;

                int next = index + 1;
                if (next < block->length)
                {
                    current = text[next];
                    if (current == '-' || current == '+')
                    {
                        ++index;
                        continue;
                    }
                    if (!isdigit(current))
                        return true;
                }
                    continue;
            }

			if (!isdigit(current))
				return true;
		}

		return false;
	}

    if (!value->isUndefined() && type != 3)
        goto numeric;
    return Rva00892370Get() == 7;

numeric:
    return false;
}
