// cl: /DNDEBUG /MD /EHsc
// LANPreferences::LANPreferences, retail RVA 0x00086480 (92 bytes).
// The reference constructor supplies only the leaf preference filename; the
// superclass puts it in the per-user directory through UserPreferences::load.

typedef bool Bool;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const char *s);
	~StringBase();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	// The delegating constructor preserves the retail StringBase<char> call and
	// the outgoing-slot construction used by the sibling OptionPreferences ctor.
	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	~AsciiString();

private:
	char *m_text;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class UserPreferences
{
public:
	UserPreferences(void);                    // ILT 0x0004B19B

	virtual ~UserPreferences();
	virtual Bool load(AsciiString filename);  // ILT 0x00014308
	virtual Bool write(void);

private:
	char m_bfme_body[0x20];
};

class LANPreferences : public UserPreferences
{
public:
	LANPreferences(void);
};

// ??0LANPreferences@@
LANPreferences::LANPreferences(void)
{
	load("Network.ini");
}
