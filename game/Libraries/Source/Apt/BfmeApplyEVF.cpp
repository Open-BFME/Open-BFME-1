// Open-BFME7: recursive Apt hierarchy path builder behind bfmeResetEVF and
// bfmeNormalizeEVF; unnamed nodes get an "instance%ld" name registered in the
// parent owner's table.
extern const char g_Rva0107531CBackslash[];
extern const char g_Rva01081D4CPeriod[];
extern const char g_Rva011370DCInstanceFormat[];
extern char bfmeFmtDYG[];

extern "C" int __cdecl sprintf(char *buffer, const char *format, ...);

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

struct BfmeStringData3AF0
{
	unsigned short m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	unsigned short m_flags;
};

extern BfmeStringPoolVKI *g_bfmeStringPool1284;
extern BfmeStringData3AF0 g_bfmeDefaultString1284;

class BfmeStrVKI
{
public:
	BfmeStrVKI()
	{
		g_bfmeDefaultString1284.m_refCount++;
		m_data = (BfmeHdrVKI *)&g_bfmeDefaultString1284;
	}
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

class BfmeStrVKJ
{
public:
	BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &other);
	BfmeHdrVKI *m_data;
};

class Rva8CD130String
{
public:
	Rva8CD130String &rva0089EA60Append(const char *text);
	BfmeHdrVKI *m_data;
};

// 0x0089EB30 returns prefix followed by text through hidden return storage.
BfmeStrVKI rva0089EB30(const char *prefix, const BfmeStrVKI &text);
// 0x0089EDF0 formats its variadic arguments into out.
void rva0089EDF0(BfmeStrVKI *out, const char *format, ...);

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

	Rva8D0D80Table *table() const
	{
		return m_table;
	}
};

void bfmeApplyEVF(void *raw_node, BfmeStrVKI *text, int mode)
{
	const char *separator = g_Rva0107531CBackslash;
	if (mode)
		separator = g_Rva01081D4CPeriod;
	Rva008C4FA0Node *node = (Rva008C4FA0Node *)raw_node;
	Rva008C4FA0Node *parent = node->m_parent;

	if (parent == 0)
	{
		if ((mode == 0 && node->m_level != 0) || mode == 1)
		{
			char buffer[16];
			sprintf(buffer, bfmeFmtDYG, node->m_level);
			*text = BfmeStrVKI(buffer);
		}
		return;
	}

	bfmeApplyEVF(parent, text, mode);
	if (node->m_text.m_data != (BfmeHdrVKI *)&g_bfmeDefaultString1284)
	{
		((BfmeStrVKJ *)text)->bfmeAssignVKJ(
			(const BfmeStrVKJ &)rva0089EB30(separator, node->m_text));
	}
	else
	{
		int level = node->m_level;
		BfmeStrVKI value;
		((Rva8CD130String *)text)->rva0089EA60Append(separator);
		rva0089EDF0(&value, g_Rva011370DCInstanceFormat, level);
		((BfmeStrVKJ *)text)->bfmeAssignVKJ((const BfmeStrVKJ &)value);
		node->m_text = value;
		Rva008C4FA0Owner *owner = (Rva008C4FA0Owner *)parent->m_owner;
		owner->table()->add((Rva8D0D80String *)&value,
			(Rva8D0D80Value *)node);
	}
}
