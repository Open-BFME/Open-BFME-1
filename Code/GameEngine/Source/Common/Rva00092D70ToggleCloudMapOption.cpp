// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the 154-byte routine at 0x00092D70.  It reloads
// Data\INI\OptionRegistry.ini through the loader at 0x00093F70 then opens the
// Render.UseCloudMap option entry (the 4-byte lookup handle whose constructor
// is 0x0007F560) reads its current Bool writes it straight back and finally
// writes the negation: the option ends up toggled.  The getter (0x0007F460)
// and setter (0x0007F440) forward through the handle.  Address-derived names.

typedef bool Bool;

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString();

private:
	void *m_data;
};

void rva00093f70( const AsciiString &path );

class Rva0007F560
{
public:
	Rva0007F560( const char *name );
	Bool get( void );
	Rva0007F560 *set( Bool value );

private:
	void *m_ptr;
};

// ?Rva00092D70ToggleCloudMapOption@@YAXXZ
void Rva00092D70ToggleCloudMapOption( void )
{
	{
		AsciiString path( "Data\\INI\\OptionRegistry.ini" );
		rva00093f70( path );
	}

	Rva0007F560 option( "Render.UseCloudMap" );
	Bool current = option.get();
	option.set( current );
	option.set( !option.get() );
}
