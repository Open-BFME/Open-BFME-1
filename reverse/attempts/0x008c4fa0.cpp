// ?d_008c4fa0@@YAXXZ
// partial score=0.82 date=2026-09-09
extern const char g_Rva0107301CEmptyString[];

struct BfmeHdrVKI
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

struct BfmeStringPoolVKI
{
	void *m_unused;
	void (__cdecl *free)(void *);
};

extern BfmeStringPoolVKI *g_bfmeStringPool1284;

class BfmeStrVKI
{
public:
	BfmeStrVKI() {}
	BfmeStrVKI(const char *text)
	{
		bfmeSetVKI(text);
	}
	BfmeStrVKI(const BfmeStrVKI &other)
	{
		m_data = other.m_data;
		++m_data->m_refCount;
	}
	void __declspec(nothrow) bfmeSetVKI(const char *text);
	~BfmeStrVKI()
	{
		BfmeHdrVKI *data = m_data;
		if (--data->m_refCount == 0)
			g_bfmeStringPool1284->free(data);
	}
	BfmeStrVKI &operator=(const BfmeStrVKI &other)
	{
		other.m_data->m_refCount++;

		BfmeHdrVKI *old = m_data;
		if (--old->m_refCount == 0)
			g_bfmeStringPool1284->free(old);

		m_data = other.m_data;
		return *this;
	}

	BfmeHdrVKI *m_data;
};

void bfmeApplyEVF(void *ctx, BfmeStrVKI *text, int flag);

void bfmeResetEVF(void *ctx, BfmeStrVKI *text)
{
	*text = g_Rva0107301CEmptyString;

	bfmeApplyEVF(ctx, text, 1);
}

extern "C" int __cdecl sprintf(char *buffer, const char *format, ...);
extern const char g_Rva0107531CBackslash[];
extern const char g_Rva01081D4CPeriod[];
extern const char g_Rva011370DCInstanceFormat[];
extern char bfmeFmtDYG[];

class BfmeStrVKJ
{
public:
	BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &other);
	BfmeStrVKJ *rva0089EA60(const char *text);
	BfmeHdrVKI *m_data;
};

BfmeStrVKI *rva0089EB30(BfmeStrVKI *out, const char *prefix,
	BfmeStrVKI *text);
void rva0089EDF0(BfmeStrVKI *out, const char *format, int value);

struct Rva008C4FA0Node
{
	char m_pad00[8];
	int m_level;
	BfmeStrVKI m_text;
	char m_pad10[0x3c];
	Rva008C4FA0Node *m_parent;
	void *m_owner;
};

class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Table
{
public:
	void add(Rva8D0D80String *key, Rva8D0D80Value *value);
};

struct Rva008C4FA0Owner
{
	char m_pad00[0x10];
	Rva8D0D80Table *m_table;
};

void rva008C4FA0(void *raw_node, BfmeStrVKI *text, int mode)
{
	const char *separator = mode ? g_Rva01081D4CPeriod
		: g_Rva0107531CBackslash;
	Rva008C4FA0Node *node = (Rva008C4FA0Node *)raw_node;
	Rva008C4FA0Node *parent = node->m_parent;

	if (parent == 0)
	{
		if (mode == 0)
		{
			if (node->m_level == 0)
				return;
		}
		else if (mode != 1)
		{
			return;
		}

		char buffer[16];
		sprintf(buffer, bfmeFmtDYG, node->m_level);
		BfmeStrVKI value;
		value.bfmeSetVKI(buffer);
		*text = value;
		return;
	}

	rva008C4FA0(parent, text, mode);
	if (node->m_text.m_data != (BfmeHdrVKI *)0x012D5298)
	{
		BfmeStrVKI value;
		rva0089EB30(&value, separator, &node->m_text);
		((BfmeStrVKJ *)text)->bfmeAssignVKJ(
			(const BfmeStrVKJ &)value);
		return;
	}

	BfmeStrVKI value = node->m_text;
	((BfmeStrVKJ *)text)->rva0089EA60(separator);
	rva0089EDF0(&value, g_Rva011370DCInstanceFormat, node->m_level);
	((BfmeStrVKJ *)text)->bfmeAssignVKJ(
		(const BfmeStrVKJ &)value);
	node->m_text = value;
	Rva008C4FA0Owner *owner = (Rva008C4FA0Owner *)node->m_owner;
	owner->m_table->add((Rva8D0D80String *)&value,
		(Rva8D0D80Value *)node);
}
