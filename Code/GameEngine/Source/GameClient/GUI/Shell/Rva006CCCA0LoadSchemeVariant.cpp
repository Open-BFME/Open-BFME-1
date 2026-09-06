// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

// Address-derived: unidentified manager pointer read at *(this + 0x30A4).
// Instruction stream is a 0.872 difflib match to the landed
// ?loadScheme@Shell@@QAEXVAsciiString@@@Z (Code/GameEngine/Source/GameClient/
// GUI/Shell/Shell.cpp), same null-guard/copy-ctor/release skeleton, but the
// retail bytes prove a different owning class (field offset 0x30A4, not
// 0x60), a two-argument __thiscall setter (ret 8, not ret 4) whose first
// argument is the AsciiString's raw internal handle read back from its own
// argument slot and whose second argument is a by-value copy of the same
// string, and an outer signature with a second, entirely unused stack
// parameter. Real class and method names not recovered; the setter body at
// 0x006F9840 is still unconverted and is reached here only through its ILT
// thunk 0x00016793.
class Rva006CCCA0Mgr
{
public:
	void setRva006CCCA0( void *rawHandle, AsciiString name );
};

class Rva006CCCA0Owner
{
public:
	// ?loadSchemeVariant@Rva006CCCA0Owner@@QAEXPAXVAsciiString@@@Z
	void loadSchemeVariant( void *rawHandle, AsciiString name );

private:
	char m_unmodelled[ 0x30A8 ];
};

void Rva006CCCA0Owner::loadSchemeVariant( void *rawHandle, AsciiString name )
{
	if ( !*(Rva006CCCA0Mgr **)( m_unmodelled + 0x30A4 ) )
		return;

	( *(Rva006CCCA0Mgr **)( m_unmodelled + 0x30A4 ) )->setRva006CCCA0( rawHandle, name );
}
