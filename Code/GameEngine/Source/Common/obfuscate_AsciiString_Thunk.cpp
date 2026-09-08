// cl: /DNDEBUG /MD /EHsc
// Canonical GameSpy login preference obfuscator, retail 0x0007FBF0.

typedef int Int;

extern "C" char *__cdecl strcpy(char *, const char *);
void *__cdecl operator new[](unsigned int);
void __cdecl operator delete[](void *);

template <typename T> class StringBase
{
	friend class AsciiString;
private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase &other);
	~StringBase();
	struct Data { Int refs; unsigned short length, capacity; T text[1]; };
	Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	Int getLength() const { return m_data ? m_data->length : 0; }
	const char *str() const { return m_data ? m_data->text : ""; }
};

AsciiString obfuscate(AsciiString in)
{
	char *buf = (char *)operator new[](in.getLength() + 1);
	strcpy(buf, in.str());
	static const char *xorKey = "1337Munkee";
	char *c = buf;
	const char *c2 = xorKey;
	while (*c)
	{
		if (!*c2)
			c2 = xorKey;
		if (*c != *c2)
			*c = *c++ ^ *c2++;
		else
			c++, c2++;
	}
	AsciiString out = buf;
	operator delete[](buf);
	return out;
}
