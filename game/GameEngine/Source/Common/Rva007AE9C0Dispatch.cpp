// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;

class Rva007AE9C0Dispatcher
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual UnsignedInt dispatch( UnsignedInt first, void *mode,
		UnsignedInt second, UnsignedInt third );

	void forward( UnsignedInt first, UnsignedInt second, UnsignedInt third );
	UnsignedInt forwardIf( UnsignedInt first, void *second,
		UnsignedInt third, UnsignedInt fourth );
};

void Rva007AE9C0Dispatcher::forward( UnsignedInt first, UnsignedInt second,
	UnsignedInt third )
{
	dispatch( first, 0, second, third );
}

UnsignedInt Rva007AE9C0Dispatcher::forwardIf( UnsignedInt first,
	void *second, UnsignedInt third, UnsignedInt fourth )
{
	if ( second == 0 ) {
		return 0;
	}
	return dispatch( first, second, third, fourth );
}
