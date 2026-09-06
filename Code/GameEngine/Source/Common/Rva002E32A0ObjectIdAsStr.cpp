// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x002E32A0, 143 bytes. Sibling of SkirmishBattleHonors::intAsStr
// (0x000A9010, in SkirmishBattleHonorsLoyalGames.cpp): same "%d" format-into-
// AsciiString shape (fuzzy twin, tools/fuzzy_twin_scan.py), but the literal read
// out of retail .rdata at 0x010CF4F0 is "ObjID#%08x" and the value is the id at
// +0x74 of the incoming object. Identity unproven; landed under an
// address-derived name. Reading the id into a local AFTER the result string is
// declared is what keeps the value in eax (retail); before it, or through the
// expression, the allocator mirrors ecx/edx.

typedef int Int;

template <class Type>
class StringBase
{
private:
	StringBase(const char *s);
	StringBase(const StringBase &that);
	friend class Rva002E32A0AsciiString;
};

class Rva002E32A0AsciiString
{
public:

	Rva002E32A0AsciiString() { m_text = 0; }

	Rva002E32A0AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	Rva002E32A0AsciiString(const Rva002E32A0AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}

	~Rva002E32A0AsciiString();

	const char *str() const
	{
		return m_text ? (const char *)m_text + 8 : "";
	}

	void __cdecl format(Rva002E32A0AsciiString fmt, ...);

private:

	void *m_text;

};

struct Rva002E32A0IdOwner
{
	unsigned char pad00[ 0x74 ];
	Int m_id;			// +0x74, the object id the "ObjID#%08x" literal names
};

static Rva002E32A0AsciiString Rva002E32A0ObjectIdAsStr(const Rva002E32A0IdOwner *p)
{
	Rva002E32A0AsciiString result;
	Int id = p->m_id;
	result.format("ObjID#%08x", id);
	return result;
}

// The body is STATIC in retail (internal linkage is what orders the return-slot
// load before the local's zero store; the same function with external linkage
// compiles 53 bytes apart), so this TU-local caller keeps it emitted.
// ?Rva002E32A0Caller@@YAXPBURva002E32A0IdOwner@@PAVRva002E32A0AsciiString@@@Z absent-from-retail
void Rva002E32A0Caller(const Rva002E32A0IdOwner *p, Rva002E32A0AsciiString *out)
{
	*out = Rva002E32A0ObjectIdAsStr(p);
}
