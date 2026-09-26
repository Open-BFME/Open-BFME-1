// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: 24 factories of 98 bytes, one shape:
//
//     operator new(760) / test the result / on success run a one-argument
//     constructor on it and return it / on failure return null
//
// The 760-byte allocation and the constructor are both read straight out of
// the retail bytes.  Every constructor is one of the twenty-five-byte
// base-then-vptr constructors already converted in BaseCtorThenVptrCtors.cpp,
// so the class each factory builds is the class that constructor belongs to
// and needs no guessing; only its width is new here, and the allocation states
// it.
//
// The SEH prologue is the throwing new-expression's: the state variable is set
// to zero once the block exists so an unwind frees it, which is why these carry
// an __ehfuncinfo at all.
//
// IDENTITY IS NOT RECOVERED for the factory itself.  It takes one dword and
// cleans it off the stack, so it is spelled __stdcall and named for its
// address; a member function that never touches its `this` would compile to
// the same bytes and the bytes cannot separate the two.  Nothing calls any of
// them -- each is reached only through a link thunk that nothing reaches -- so
// there is no call site to settle it either.
//
// Two more bodies of this exact shape at 0x0078D390 and 0x0078F520 are left
// alone: they share one constructor at 0x0078D310 that carries no name yet, so
// there is nothing to tell the two classes apart.

class Rva00796A60VptrCtor
{
public:
	Rva00796A60VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078E8F0
Rva00796A60VptrCtor *__stdcall Rva0078E8F0New( void *argument )
{
	return new Rva00796A60VptrCtor( argument );
}

class Rva00796AF0VptrCtor
{
public:
	Rva00796AF0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078E970
Rva00796AF0VptrCtor *__stdcall Rva0078E970New( void *argument )
{
	return new Rva00796AF0VptrCtor( argument );
}

class Rva00793D30VptrCtor
{
public:
	Rva00793D30VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078E9F0
Rva00793D30VptrCtor *__stdcall Rva0078E9F0New( void *argument )
{
	return new Rva00793D30VptrCtor( argument );
}

class Rva00793E00VptrCtor
{
public:
	Rva00793E00VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078EA70
Rva00793E00VptrCtor *__stdcall Rva0078EA70New( void *argument )
{
	return new Rva00793E00VptrCtor( argument );
}

class Rva007961D0VptrCtor
{
public:
	Rva007961D0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078EB00
Rva007961D0VptrCtor *__stdcall Rva0078EB00New( void *argument )
{
	return new Rva007961D0VptrCtor( argument );
}

class Rva00796260VptrCtor
{
public:
	Rva00796260VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078EB80
Rva00796260VptrCtor *__stdcall Rva0078EB80New( void *argument )
{
	return new Rva00796260VptrCtor( argument );
}

class Rva0078FCA0VptrCtor
{
public:
	Rva0078FCA0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078EC00
Rva0078FCA0VptrCtor *__stdcall Rva0078EC00New( void *argument )
{
	return new Rva0078FCA0VptrCtor( argument );
}

class Rva0078FD30VptrCtor
{
public:
	Rva0078FD30VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078EC80
Rva0078FD30VptrCtor *__stdcall Rva0078EC80New( void *argument )
{
	return new Rva0078FD30VptrCtor( argument );
}

class Rva007974C0VptrCtor
{
public:
	Rva007974C0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078ED00
Rva007974C0VptrCtor *__stdcall Rva0078ED00New( void *argument )
{
	return new Rva007974C0VptrCtor( argument );
}

class Rva00797550VptrCtor
{
public:
	Rva00797550VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078ED80
Rva00797550VptrCtor *__stdcall Rva0078ED80New( void *argument )
{
	return new Rva00797550VptrCtor( argument );
}

class Rva00798510VptrCtor
{
public:
	Rva00798510VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078EE00
Rva00798510VptrCtor *__stdcall Rva0078EE00New( void *argument )
{
	return new Rva00798510VptrCtor( argument );
}

class Rva007985A0VptrCtor
{
public:
	Rva007985A0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078EE80
Rva007985A0VptrCtor *__stdcall Rva0078EE80New( void *argument )
{
	return new Rva007985A0VptrCtor( argument );
}

class Rva00791F40VptrCtor
{
public:
	Rva00791F40VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078EF00
Rva00791F40VptrCtor *__stdcall Rva0078EF00New( void *argument )
{
	return new Rva00791F40VptrCtor( argument );
}

class Rva00791FF0VptrCtor
{
public:
	Rva00791FF0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078EF80
Rva00791FF0VptrCtor *__stdcall Rva0078EF80New( void *argument )
{
	return new Rva00791FF0VptrCtor( argument );
}

class Rva00792040VptrCtor
{
public:
	Rva00792040VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F000
Rva00792040VptrCtor *__stdcall Rva0078F000New( void *argument )
{
	return new Rva00792040VptrCtor( argument );
}

class Rva00792070VptrCtor
{
public:
	Rva00792070VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F080
Rva00792070VptrCtor *__stdcall Rva0078F080New( void *argument )
{
	return new Rva00792070VptrCtor( argument );
}

class Rva007903F0VptrCtor
{
public:
	Rva007903F0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F100
Rva007903F0VptrCtor *__stdcall Rva0078F100New( void *argument )
{
	return new Rva007903F0VptrCtor( argument );
}

class Rva00790480VptrCtor
{
public:
	Rva00790480VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F180
Rva00790480VptrCtor *__stdcall Rva0078F180New( void *argument )
{
	return new Rva00790480VptrCtor( argument );
}

class Rva00793150VptrCtor
{
public:
	Rva00793150VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F200
Rva00793150VptrCtor *__stdcall Rva0078F200New( void *argument )
{
	return new Rva00793150VptrCtor( argument );
}

class Rva007931B0VptrCtor
{
public:
	Rva007931B0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F280
Rva007931B0VptrCtor *__stdcall Rva0078F280New( void *argument )
{
	return new Rva007931B0VptrCtor( argument );
}

class Rva007996A0VptrCtor
{
public:
	Rva007996A0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F300
Rva007996A0VptrCtor *__stdcall Rva0078F300New( void *argument )
{
	return new Rva007996A0VptrCtor( argument );
}

class Rva00799730VptrCtor
{
public:
	Rva00799730VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F380
Rva00799730VptrCtor *__stdcall Rva0078F380New( void *argument )
{
	return new Rva00799730VptrCtor( argument );
}

class Rva00790C40VptrCtor
{
public:
	Rva00790C40VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F400
Rva00790C40VptrCtor *__stdcall Rva0078F400New( void *argument )
{
	return new Rva00790C40VptrCtor( argument );
}

class Rva00790CD0VptrCtor
{
public:
	Rva00790CD0VptrCtor( void *argument );

private:
	char m_body[ 760 ];					// the width operator new asks for
};

// retail 0x0078F480
Rva00790CD0VptrCtor *__stdcall Rva0078F480New( void *argument )
{
	return new Rva00790CD0VptrCtor( argument );
}

