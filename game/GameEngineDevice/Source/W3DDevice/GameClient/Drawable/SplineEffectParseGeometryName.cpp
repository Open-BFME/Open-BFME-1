// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: SplineEffect::ParseGeometryName (retail 0x003BB680 135 B; a gap
// claimed through its own exception text -- despite the "::" the entry point
// takes no `this`, it is a plain (INI*, void*, void*, const void*) callback
// like its neighbours; ecx only ever holds the "ini" pointer loaded off the
// stack, exactly as in the sibling record-based Parse bodies).  With no INI
// or instance it throws INIException(3
// "SplineEffect::ParseGeometryName::Invalid data passed in."); otherwise it
// reads one token via INI::getNextAsciiString() and hands it straight to the
// instance's setter (thunk 0x00403EBD) by address, then releases the token's
// buffer.  No persistent record struct is built here at all -- the "record"
// in this family is just the temporary AsciiString.  Address-derived names.

typedef int Int;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const StringBase<T> &source );
	void releaseBuffer();
	void *m_data;
};

class AsciiString
{
public:
	AsciiString() : m_text( 0 ) {}
	~AsciiString() { ( (StringBase<char> *)this )->releaseBuffer(); }

private:
	void *m_text;
};

class INI
{
public:
	AsciiString getNextAsciiString();
};

class Rva003BB680Owner
{
public:
	void setGeometryName( AsciiString &name );
};

// ?SplineEffectParseGeometryName@@YAXPAVINI@@PAX1PBX@Z
void SplineEffectParseGeometryName( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		( (Rva003BB680Owner *)instance )->setGeometryName( ini->getNextAsciiString() );
	}
	else
		throw INIException( 3, "SplineEffect::ParseGeometryName::Invalid data passed in." );
}
