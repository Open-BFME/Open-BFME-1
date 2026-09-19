// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern "C" __declspec(dllimport) int __cdecl _snprintf( char*, int, const char*, ... );

class Rva008897E0Class
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
	virtual void print( const char* ); // offset 0x38

	void d_008897e0( float val );
	void d_00889830( double val );
};

void Rva008897E0Class::d_008897e0( float val )
{
	char buf[200]; // 0xC8 = 200
	_snprintf( buf, 200, (const char*)0x01082F4C, val );
	print( buf );
}

void Rva008897E0Class::d_00889830( double val )
{
	char buf[200];
	_snprintf( buf, 200, (const char*)0x01082F4C, val );
	print( buf );
}
