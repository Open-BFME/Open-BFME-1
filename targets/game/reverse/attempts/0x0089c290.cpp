// ?bfmeTest1220@BfmeNode1220@@QAEHPAHH@Z
// partial score=0.81 date=2026-09-28
// ?bfmeTest1220@BfmeNode1220@@QAEHPAHH@Z
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern "C" int __cdecl atoi(const char *);

struct R4Word
{
	const char *name;
	int value;
};
const R4Word *Rva00897FD0(const char *str, unsigned int len);

class BfmeNestedBE;
BfmeNestedBE *Rva008930C0AptLookup(int level);

class BfmeTab1024
{
public:
	int bfmeFind1024(int key);
};

class Gen_008C41D0
{
public:
	int bfmeValue() const;
};

struct Rva00899C20Registry
{
	char m_pad00[8];
	BfmeTab1024 m_table;
};
struct BfmeMap1024
{
	char m_pad00[8];
	BfmeTab1024 m_table;
};
extern Rva00899C20Registry *g_Va013387D8;
extern BfmeMap1024 *g_bfmeMap1024;

struct AptStringHeader
{
	unsigned short refs;
	unsigned short len;
	unsigned short capacity;
	unsigned short flags;
	char text[1];
};

class BfmeNode1220;

class AptScope1220 : public BfmeTab1024
{
public:
	void *m_vtable;
	unsigned int m_word04;
	unsigned int m_link;
	BfmeNode1220 *next() const { return (BfmeNode1220 *)(m_link & ~1u); }
};

class BfmeNode1220
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual AptScope1220 *scope();

	int bfmeTest1220(int *name, int context);
	int rva00899C20();

	__forceinline bool isDescendantOf(BfmeNode1220 *ancestor)
	{
		AptScope1220 *s = scope();
		while (s)
		{
			BfmeNode1220 *n = s->next();
			if (!n)
				break;
			if (n == ancestor)
				return true;
			s = n->scope();
		}
		return false;
	}
	int type() const { return m_flags04 & 0x3f; }
	bool inactive() const { return !m_bits.m_visible; }
	__forceinline bool notSprite() const { return type() < 12 || type() > 19 || inactive(); }

	union
	{
		unsigned int m_flags04;
		struct
		{
			unsigned int m_kind : 6;
			unsigned int m_bits06 : 9;
			unsigned int m_visible : 1;
		} m_bits;
	};
	unsigned char m_pad08[0x14];
	unsigned int m_flags1c;
	unsigned char m_pad20[0x2c];
	BfmeNode1220 *m_parent4c;
};

extern BfmeNode1220 **g_aptTargetStack01338780;
extern int g_aptTargetCount01338778;
extern BfmeNode1220 **g_aptScopeStack01338768;
extern int g_aptScopeCount01338760;
extern int g_aptGlobal013379FC;
extern int g_aptGlobal013379B4;
extern int g_aptGlobal013379AC;
extern int g_aptGlobal013379F0;
extern int g_aptGlobal01337A00;
extern int g_aptGlobal01337A20;
extern int g_aptGlobal013379BC;

int BfmeNode1220::bfmeTest1220(int *name, int context)
{
	BfmeNode1220 *target = (BfmeNode1220 *)context;
	BfmeNode1220 *other;
	if (!target)
		target = this;
	AptStringHeader *header = *(AptStringHeader **)name;
	const R4Word *word = Rva00897FD0(header->text, header->len);
	if (word)
	{
		switch (word->value)
		{
		case 2:
		{
			target = g_aptTargetStack01338780[g_aptTargetCount01338778 - 1];
			if (target == this)
				return (int)this;
			if (g_aptScopeCount01338760 > 0)
			{
				other = g_aptScopeStack01338768[g_aptScopeCount01338760 - 1];
				if (!other->inactive())
				{
					if (target == other)
						return (int)target;
					if (other->isDescendantOf(target))
						return (int)other;
				}
			}
			if (isDescendantOf(target))
				return (int)this;
			return (int)g_aptTargetStack01338780[g_aptTargetCount01338778 - 1];
		}
		case 3:
		{
			if (target->notSprite())
				return 0;
			BfmeNode1220 *root = target;
			while (root->m_parent4c)
				root = root->m_parent4c;
			return (int)root;
		}
		case 19: return (int)g_Va013387D8;
		case 4: return g_aptGlobal013379FC;
		case 20: return g_aptGlobal013379AC;
		case 5: return g_aptGlobal013379B4;
		case 36: return g_aptGlobal013379F0;
		case 37: return g_aptGlobal01337A00;
		case 17: return g_aptGlobal01337A20;
		case 18:
		{
			target = g_aptTargetStack01338780[g_aptTargetCount01338778 - 1];
			AptScope1220 *s = target->scope();
			if (s)
			{
				other = s->next();
				if (other)
				{
					if (target != this && target->rva00899C20() && target->notSprite())
					{
						if (target->type() != 0x1b || target->inactive() || !(target->m_flags1c & 0x200))
							return (int)other;
						AptScope1220 *ps = other->scope();
						if (!ps)
							return (int)other;
						return (int)ps->next();
					}
					if ((unsigned char)target->type() == 0x1c && !target->inactive())
						return (int)other;
					AptScope1220 *ps = other->scope();
					if (ps)
					{
						BfmeNode1220 *grand = ps->next();
						if (grand)
							return (int)grand;
					}
				}
			}
			return g_aptGlobal013379BC;
		}
		case 16:
			if (target->notSprite())
				return 0;
			return (int)target->m_parent4c;
		case 1:
			return 0;
		default:
			return 0;
		case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13: case 14: case 15:
		case 21: case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30:
		case 31: case 32: case 33: case 34: case 35:
			return (int)Rva008930C0AptLookup(atoi(header->text + 6));
		}
	}

	if (target->inactive())
		return 0;
	AptScope1220 *s = target->scope();
	if (!s)
	{
		if (target->notSprite() || target->type() != 0xe)
			goto global;
		s = (AptScope1220 *)((Gen_008C41D0 *)target->m_parent4c)->bfmeValue();
		if (!s)
			goto global;
	}
	do
	{
		int found = s->bfmeFind1024((int)name);
		if (found)
			return found;
		BfmeNode1220 *next = s->next();
		if (!next)
			break;
		s = next->scope();
	} while (s);
global:
	int found = g_bfmeMap1024->m_table.bfmeFind1024((int)name);
	if (found)
		return found;
	return g_Va013387D8->m_table.bfmeFind1024((int)name);
}
