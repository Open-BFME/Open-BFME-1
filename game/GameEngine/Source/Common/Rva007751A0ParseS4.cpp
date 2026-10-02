// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Clean reconstruction of the four-argument INI callback at retail RVA
// 0x007751A0.  The callback builds the 44-byte S4 record used by the
// neighboring 0x00754590/0x00755610/0x00753E80 family: three STLport strings
// followed by two Ints.  Only the first two strings and the second Int are
// populated here; the S4 constructor supplies the empty/zero defaults.

#include <string>

typedef int Int;

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

class BfmeSubESD
{
public:
	void bfmeAssignESD(void *a, void *b, void **spare);

	BfmeSubESD &operator=(const BfmeSubESD &other)
	{
		if (&other != this)
		{
			void *spare;

			bfmeAssignESD(other.m_bfmeAESD, other.m_bfmeBESD, &spare);
		}

		return *this;
	}

	void *m_bfmeAESD;
	void *m_bfmeBESD;
	void *m_bfmeCESD;
};

class BfmeRecESD
{
public:
	BfmeRecESD &operator=(const BfmeRecESD &other);

	BfmeSubESD m_bfmeXESD;
	BfmeSubESD m_bfmeYESD;
	BfmeSubESD m_bfmeZESD;
	int m_bfme24ESD;
	int m_bfme28ESD;
};

// The constructor and destructor use the matched S4 rows. Retail assignment
// ILT 0x00046CC2 resolves to the matched BfmeRecESD::operator= body at
// 0x00755610, so keep that owner's type on the call below.
class S4Elem007746E0
{
public:
	S4Elem007746E0();
	~S4Elem007746E0();
	S4Elem007746E0 &operator=(const S4Elem007746E0 &other);

	_STL::string m_first;
	_STL::string m_second;
	_STL::string m_unused;
	Int m_unusedValue;
	Int m_value;
};


// Only the INI methods and the separator field reached by this body.
class INI
{
public:
	const char *getNextTokenOrNull(const char *separators);
	static Int scanInt(const char *token);

	const char *getSepsColon() const { return m_sepsColon; }

private:
	char m_beforeSeps[0x41c];
	const char *m_sepsColon;
};



// This is the ordinary four-argument INI callback ABI: retail reads the INI
// from argument one and the destination owner from argument two.
class Rva007751A0Owner
{
public:
	char m_pad[0x84];
	S4Elem007746E0 m_value;
};

// ?Rva007751A0ParseS4@@YAXPAVINI@@PAVRva007751A0Owner@@PAXPBX@Z
void __cdecl Rva007751A0ParseS4(INI *ini, Rva007751A0Owner *owner,
	void *, const void *)
{
	if (owner == 0)
		return;

	S4Elem007746E0 value;

	const char *first = ini->getNextTokenOrNull(0);
	if (first != 0)
		value.m_first.assign(first, first + strlen(first));
	else
		value.m_first.assign("",
			"");

	const char *number = ini->getNextTokenOrNull(0);
	if (number != 0)
		value.m_value = INI::scanInt(number);
	else
		value.m_value = 0;

	const char *second = ini->getNextTokenOrNull(0);
	if (second != 0)
		value.m_second.assign(second, second + strlen(second));
	else
		value.m_second.assign("",
			"");

	*((BfmeRecESD *)&owner->m_value) = *((const BfmeRecESD *)&value);
}
