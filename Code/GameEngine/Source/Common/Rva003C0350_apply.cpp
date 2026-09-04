// cl: /DNDEBUG /MD /EHsc
//
// Rva003C0350::run, retail 0x003C0350, 80 bytes.
//
// thiscall with two args on d_003b8450: lookup(key) then probe(m_at28,&m_at30);
// on success fill(hit, src, &local) and apply(found, &local).

class Gen003C0350Owner
{
public:
	void *probe( void * key );
};

class Gen003C0350Found
{
public:
	bool fill( void * src, void * out );
};

class Gen003C0350Lookup
{
public:
	void apply( void * local );
};

Gen003C0350Lookup * __stdcall Gen003C0350Find( void * key );

class Rva003C0350
{
public:
	void run( void * key, void * src );

private:
	char m_pad00[ 0x28 ];
	Gen003C0350Owner *m_at28;
	char m_pad2C[ 0x4 ];
	char m_at30;
};

// ?run@Rva003C0350@@QAEXPAX0@Z
void Rva003C0350::run( void * key, void * src )
{
	Gen003C0350Lookup *found = Gen003C0350Find( key );
	if( !found )
		return;
	Gen003C0350Found *hit = (Gen003C0350Found *)m_at28->probe( &m_at30 );
	if( !hit )
		return;
	char local[ 8 ];
	if( !hit->fill( src, local ) )
		return;
	found->apply( local );
}
