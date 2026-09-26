// Character-classification members driven by three 256-entry tables: a byte
// upper table, a byte lower table, and a dword mask table.  The tables are
// DIR32 operands the patcher fills, but each one is referenced from several of
// these rows, which is what makes the three-table split checkable rather than
// assumed.
typedef unsigned short T2WChar;

extern const char t2_upper_table[256];
extern const char t2_lower_table[256];
extern const unsigned int t2_mask_table[256];

// The block copy is an indirect call through an import slot, so it is declared
// as an imported function rather than the intrinsic the compiler would inline.
extern "C" __declspec(dllimport) void *__cdecl t2_block_copy(void *dst, const void *src, unsigned int n);

struct T2NarrowCtype
{
	char toUpper(char c) const;
	const char *toLowerRange(char *low, char *high) const;
	const char *widenRange(const char *low, const char *high, char *to) const;
	const char *narrowRange(const char *low, const char *high, char dflt, char *to) const;
};

char T2NarrowCtype::toUpper(char c) const
{
	return t2_upper_table[(unsigned char)c];
}

const char *T2NarrowCtype::toLowerRange(char *low, char *high) const
{
	while (low < high)
	{
		*low = t2_lower_table[(unsigned char)*low];
		++low;
	}
	return high;
}

const char *T2NarrowCtype::widenRange(const char *low, const char *high, char *to) const
{
	if (high != low)
		t2_block_copy(to, low, (unsigned int)(high - low));
	return high;
}

const char *T2NarrowCtype::narrowRange(const char *low, const char *high, char, char *to) const
{
	if (high != low)
		t2_block_copy(to, low, (unsigned int)(high - low));
	return high;
}

struct T2WideCtype
{
	const T2WChar *isRange(const T2WChar *low, const T2WChar *high, unsigned int *vec) const;
	T2WChar toUpper(unsigned int c) const;
	const T2WChar *toUpperRange(T2WChar *low, T2WChar *high) const;
	T2WChar toLower(unsigned int c) const;
	const T2WChar *toLowerRange(T2WChar *low, T2WChar *high) const;
	T2WChar widen(char c) const;
	const char *widenRange(const char *low, const char *high, T2WChar *to) const;
	int narrow(T2WChar c, char dflt) const;
	const T2WChar *narrowRange(const T2WChar *low, const T2WChar *high, char dflt, char *to) const;
};

const T2WChar *T2WideCtype::isRange(const T2WChar *low, const T2WChar *high,
                                    unsigned int *vec) const
{
	while (low < high)
	{
		*vec = (*low < 0x100) ? t2_mask_table[*low] : 0;
		++low;
		++vec;
	}
	return high;
}

T2WChar T2WideCtype::toUpper(unsigned int c) const
{
	if ((T2WChar)c < 0x100)
		return (T2WChar)(unsigned char)t2_upper_table[(T2WChar)c];
	return (T2WChar)c;
}

const T2WChar *T2WideCtype::toUpperRange(T2WChar *low, T2WChar *high) const
{
	while (low < high)
	{
		T2WChar c = *low;
		*low = (c < 0x100) ? (T2WChar)(unsigned char)t2_upper_table[c] : c;
		++low;
	}
	return high;
}

T2WChar T2WideCtype::toLower(unsigned int c) const
{
	if ((T2WChar)c < 0x100)
		return (T2WChar)(unsigned char)t2_lower_table[(T2WChar)c];
	return (T2WChar)c;
}

const T2WChar *T2WideCtype::toLowerRange(T2WChar *low, T2WChar *high) const
{
	while (low < high)
	{
		T2WChar c = *low;
		*low = (c < 0x100) ? (T2WChar)(unsigned char)t2_lower_table[c] : c;
		++low;
	}
	return high;
}

T2WChar T2WideCtype::widen(char c) const
{
	return (T2WChar)(signed char)c;
}

const char *T2WideCtype::widenRange(const char *low, const char *high, T2WChar *to) const
{
	while (low != high)
	{
		*to = (T2WChar)(signed char)*low;
		++to;
		++low;
	}
	return high;
}

int T2WideCtype::narrow(T2WChar c, char dflt) const
{
	if ((int)(char)c == (int)c)
		return c;
	return dflt;
}

const T2WChar *T2WideCtype::narrowRange(const T2WChar *low, const T2WChar *high,
                                        char dflt, char *to) const
{
	while (low != high)
	{
		T2WChar c = *low;
		++low;
		int v = ((int)(char)c == (int)c) ? (int)c : (int)dflt;
		*to = (char)v;
		++to;
	}
	return high;
}
