// ?d_00692690@@YAXXZ
// partial score=0.8 date=2026-08-31
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned count);
#pragma intrinsic(memcmp)

class Rva00692690String
{
public:
	int compare(const Rva00692690String &other) const
	{
		const int otherLength = other.m_data ? other.m_data->length : 0;
		const char *otherData = other.m_data ? other.m_data->text : "";
		const int length = m_data ? m_data->length : 0;
		const char *data = m_data ? m_data->text : "";
		int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
		if (result == 0)
			result = length - otherLength;
		return result;
	}

private:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		char text[1];
	};

	Header *m_data;
};

struct Rva00692690Key
{
	Rva00692690Key();
	Rva00692690Key(const Rva00692690Key &other);
	~Rva00692690Key();
	Rva00692690Key &operator=(const Rva00692690Key &other);

	unsigned primary;
	Rva00692690String secondary;
	unsigned trailing;
};

inline bool operator<(const Rva00692690Key &left, const Rva00692690Key &right)
{
	if (left.primary < right.primary)
		return true;
	if (right.primary < left.primary)
		return false;
	return left.secondary.compare(right.secondary) < 0;
}

struct Rva00692690Node
{
	int color;
	Rva00692690Node *parent;
	Rva00692690Node *left;
	Rva00692690Node *right;
	Rva00692690Key value;
};

class Rva00692690Tree
{
public:
	Rva00692690Node *lowerBound(const Rva00692690Key &key) const;

private:
	Rva00692690Node *m_header;
};

Rva00692690Node *Rva00692690Tree::lowerBound(const Rva00692690Key &key) const
{
	Rva00692690Node *candidate = m_header;
	Rva00692690Node *node = m_header->parent;
	while (node != 0)
	{
		if (!(node->value < key))
		{
			candidate = node;
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}
	return candidate;
}
