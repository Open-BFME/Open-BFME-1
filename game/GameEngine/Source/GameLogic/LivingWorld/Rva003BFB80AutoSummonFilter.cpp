// Retail 0x003BFB80 (117 bytes).
//
// The named LivingWorld field table identifies the literal's role as the
// AutoSummon marker.  Retail calls this neutral helper through ILT 0x000012F3
// from the LivingWorld record loop at 0x003C2166 (body 0x003C2100), which is
// reached by the surrounding LivingWorld manager body at 0x003C3850.  The
// exact semantic owner is not named by those generated siblings, so this
// source keeps the operation's identity address-derived.

extern char *(__cdecl *g_bfmeStrStrVMZ)(const char *text, const char *find);

struct Rva003BFB80StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &source);
	void removeLastChar();
	const T *find(T value) const
	{
		const T *start = m_data != 0
			? (const T *)&m_data->data[0]
			: (const T *)"";
		const T *end = start + (m_data != 0 ? m_data->length : 0);
		for (const T *p = start; p != end; ++p)
		{
			if (*p == value)
				return p;
		}
		return 0;
	}

private:
	Rva003BFB80StringHeader *m_data;
};

struct Rva003BFB80String
{
	Rva003BFB80StringHeader *m_data;
};

static const char *rva003BFB80Text(const Rva003BFB80String *value)
{
	return value->m_data != 0
		? value->m_data->data
		: "";
}

class Rva003BFB80Owner
{
public:
	bool rva003BFB80(Rva003BFB80String *source,
		Rva003BFB80String *output);
};

// ?rva003BFB80@Rva003BFB80Owner@@QAE_NPAURva003BFB80String@@0@Z
bool Rva003BFB80Owner::rva003BFB80(
	Rva003BFB80String *source, Rva003BFB80String *output)
{
	if (g_bfmeStrStrVMZ(rva003BFB80Text(source),
		":AutoSummon") != 0)
	{
		((StringBase<char> *)output)->set(
			*(const StringBase<char> *)source);

		while (((StringBase<char> *)output)->find(':') != 0)
		{
			((StringBase<char> *)output)->removeLastChar();
		}
		return true;
	}
	return false;
}
