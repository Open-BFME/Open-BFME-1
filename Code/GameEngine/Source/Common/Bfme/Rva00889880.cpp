// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern "C" char* (__cdecl *BfmeItoaImport)( int, char*, int );

class Rva00889880Class
{
public:
	virtual void func0();
	virtual void func4();
	virtual void func8();
	virtual void funcC();
	virtual void func10();
	virtual void func14();
	virtual void func18();
	virtual void func1C();
	virtual void func20();
	virtual void func24();
	virtual void func28();
	virtual void func2C();
	virtual void func30();
	virtual void func34();
	virtual Rva00889880Class* print( const char* );

	Rva00889880Class* d_00889880( int val );
};

Rva00889880Class* Rva00889880Class::d_00889880( int val )
{
	print( (const char*)0x0113310C );
	if ( val )
	{
		char buf[12];
		print( (const char*)0x01132DD4 )->print( BfmeItoaImport( val, buf, 16 ) );
	}
	else
	{
		print( (const char*)0x01080374 );
	}
	return this;
}
