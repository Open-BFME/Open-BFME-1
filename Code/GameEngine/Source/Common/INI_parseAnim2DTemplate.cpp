// cl: /DNDEBUG /MD /EHsc
// Open-BFME: INI::parseAnim2DTemplate, retail 0x000BAB30, 150 bytes. The body
// carried no ledger row; its name sat on a 5-byte thunk.
//
// The reference's body unchanged. What it costs in bytes is the temporary:
// the token becomes an AsciiString through StringBase<char>'s const char *
// constructor at 0x00888BC0, is handed to findTemplate, and is released on the
// way out under the /EHsc frame that pairing needs.
//
// The else arm is BFME's own: where the reference throws the INI_UNKNOWN_ERROR
// enumerator, this build constructs an INIException with the code and the
// message and throws that -- the same idiom, and the same
// __TI1?AVINIException@@ descriptor, the rest of the INI parsers use.

typedef int Int;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *str);				// retail 0x00888BC0
	void releaseBuffer();					// retail 0x00887940

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *text) : m_string(text) {}
	~AsciiString() { m_string.releaseBuffer(); }

	StringBase<char> m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException(Int, const char *, ...);
	INIException(const INIException &);

private:
	Int m_code;
	const char *m_message;
};

class Anim2DTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Anim2D.h
class Anim2DCollection
{
public:
	Anim2DTemplate *findTemplate(const AsciiString &name);	// ILT 0x0000C0EA
};

extern Anim2DCollection *TheAnim2DCollection;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken(const char *seps = 0);		// retail 0x00850970

	static void parseAnim2DTemplate(INI *ini, void *instance, void *store, const void *userData);
};

void INI::parseAnim2DTemplate(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token = ini->getNextToken();

	if (TheAnim2DCollection)
	{
		Anim2DTemplate **anim2DTemplate = (Anim2DTemplate **)store;
		*anim2DTemplate = TheAnim2DCollection->findTemplate(AsciiString(token));
	}
	else
	{
		throw INIException(9, "iniParseAnim2DTemplate - TheAnim2DCollection is NULL");
	}
}
