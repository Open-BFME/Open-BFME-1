// ?d_008abfe0@@YAXXZ
// partial score=0.8554 date=2026-09-26
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct Rva008AC020StringData
{
	unsigned short m_refs;
	unsigned short m_length;
	unsigned int m_flags;
	char m_text[1];
};

class Rva008AC020String
{
public:
	bool rva008AC020(const Rva008AC020String *other) const;

private:
	Rva008AC020StringData *m_data;
	__forceinline bool equals(const Rva008AC020String *other) const
	{
		Rva008AC020StringData *left = m_data;
		Rva008AC020StringData *right = other->m_data;
		unsigned int length = left->m_length;
		unsigned int otherLength = right->m_length;
		if (length != otherLength)
			return false;
		if (left == right)
			return true;
		return memcmp(left->m_text, right->m_text, length) == 0;
	}
};

bool Rva008AC020String::rva008AC020(const Rva008AC020String *other) const
{
	return !equals(other);
}
