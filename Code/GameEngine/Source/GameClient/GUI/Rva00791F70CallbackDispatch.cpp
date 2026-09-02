// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

class Rva00791F70CallbackHost;

typedef void (__cdecl *Rva00791F70Callback)(
	Rva00791F70CallbackHost *, int, int, int );

void rva00791F70DefaultDispatch(
	Rva00791F70CallbackHost *, int, int, int );

class Rva00791F70CallbackHost
{
public:
	void dispatch( int first, int second, int third );

private:
	char m_unreconstructed[ 0x1E0 ];
	Rva00791F70Callback m_callback;
};

void Rva00791F70CallbackHost::dispatch(
	int first, int second, int third )
{
	if( m_callback )
		m_callback( this, first, second, third );
	else
		rva00791F70DefaultDispatch( this, first, second, third );
}
