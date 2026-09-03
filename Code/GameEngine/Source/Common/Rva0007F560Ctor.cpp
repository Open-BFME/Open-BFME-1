// cl: /DNDEBUG /MD /EHsc
// Constructor: copy the name into a StringBase, look it up through the
// singleton at 0x012ED604, store the pointer at this+0.

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString();

private:
	void *m_data;
};

class Rva0007F560Factory
{
public:
	void *lookup( const AsciiString &name );
};

extern Rva0007F560Factory *g_rva0007F560Factory;

class Rva0007F560
{
public:
	Rva0007F560( const char *name );

private:
	void *m_ptr;
};

Rva0007F560::Rva0007F560( const char *name )
{
	AsciiString tmp( name );
	m_ptr = g_rva0007F560Factory->lookup( tmp );
}
