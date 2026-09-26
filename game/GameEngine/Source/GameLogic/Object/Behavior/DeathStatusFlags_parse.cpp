// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class AsciiString;

template <typename T>
class StringBase
{
	friend class AsciiString;
private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
	~StringBase() { releaseBuffer(); }

protected:
	void *m_data;

private:
	void releaseBuffer();
};

extern const char Rva006A16B0Empty[];

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	Bool nextToken(AsciiString *token, const char *seps = 0);

	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 : Rva006A16B0Empty;
	}
};

class Rva00204770BitFlagsParser
{
public:
	Bool parseToken(const char *token, Bool *foundNormal, Bool *foundAddOrSub);
};

class DeathStatusFlags
{
public:
	void parse(AsciiString description);

private:
	unsigned int m_words[3];
};

// ?parse@DeathStatusFlags@@QAEXVAsciiString@@@Z
void DeathStatusFlags::parse(AsciiString description)
{
	Bool foundNormal = false;
	Bool foundAddOrSub = false;
	AsciiString token;

	while (description.nextToken(&token))
	{
		if (!reinterpret_cast<Rva00204770BitFlagsParser *>(this)->parseToken(
			token.str(), &foundNormal, &foundAddOrSub))
			break;
	}
}
