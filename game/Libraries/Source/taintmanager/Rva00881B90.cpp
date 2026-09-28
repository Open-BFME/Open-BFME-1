// cl: /O2 /MD /EHs-c-

class Rva00881B90Class;

struct SomeStruct
{
	Rva00881B90Class* pThis;
	int arg4;
	bool arg5;
};

extern void d_00881770( int arg1, int arg2, int arg3, SomeStruct s );

class Rva00881B90Class
{
public:
	void update( int arg1, int arg2, int arg3, int arg4, bool arg5 );
};

void Rva00881B90Class::update( int arg1, int arg2, int arg3, int arg4, bool arg5 )
{
	if ( arg3 >= 0 && (arg4 != 0 || arg5) )
	{
		SomeStruct s;
		s.pThis = this;
		s.arg4 = arg4;
		s.arg5 = arg5;
		d_00881770( arg1, arg2, arg3, s );
	}
}
