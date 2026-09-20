class Rva005C0630Owner
{
public:
	void invoke( void *argument );
};

void Rva005C0630Owner::invoke( void * )
{
}

class Rva005C0660Owner
{
public:
	void invoke( void *argument );
};

void Rva005C0660Owner::invoke( void * )
{
}

class Rva005C0690Owner
{
public:
	void invoke( void *first, void *second );
};

void Rva005C0690Owner::invoke( void *, void * )
{
}

class Rva005C06B0Owner
{
public:
	void invoke( void *argument );
};

void Rva005C06B0Owner::invoke( void * )
{
}

class Rva005C06E0Owner
{
public:
	void invoke( void *argument );
};

void Rva005C06E0Owner::invoke( void * )
{
}

class Rva005C0710Owner
{
public:
	void invoke( void *first, void *second );
};

void Rva005C0710Owner::invoke( void *, void * )
{
}

class Rva005C0730Owner
{
public:
	void invoke( void *argument );
};

void Rva005C0730Owner::invoke( void * )
{
}

void rva005c0720()
{
}

bool Rva005C09E0()
{
	return true;
}

bool Rva005C0A70()
{
	return true;
}

bool Rva005C0A90()
{
	return true;
}

bool Rva005C0AA0()
{
	return true;
}

bool Rva005C0AB0()
{
	return true;
}

bool Rva005C0AC0()
{
	return true;
}

bool Rva005C0AD0()
{
	return true;
}

bool Rva005C0AE0()
{
	return true;
}

bool Rva005C0AF0()
{
	return true;
}

bool Rva005C0B00()
{
	return true;
}

bool Rva005C0B20()
{
	return true;
}

class Rva005C0BC0Owner
{
public:
	bool read();
};

bool Rva005C0BC0Owner::read()
{
	return *(bool *)((char *)this + 0x54);
}

class Rva005C0C00Owner
{
public:
	void *identity();
};

void *Rva005C0C00Owner::identity()
{
	return this;
}

class Rva005C0C30Owner
{
public:
	void *identity();
};

void *Rva005C0C30Owner::identity()
{
	return this;
}

class Rva005C0C40Owner
{
public:
	void *identity();
};

void *Rva005C0C40Owner::identity()
{
	return this;
}

class Rva005C0C60Owner
{
public:
	void *identity();
};

void *Rva005C0C60Owner::identity()
{
	return this;
}

class Rva005C0C70Owner
{
public:
	void *identity();
};

void *Rva005C0C70Owner::identity()
{
	return this;
}

class Rva005C0C90Owner
{
public:
	void *identity();
};

void *Rva005C0C90Owner::identity()
{
	return this;
}

// cl: /DNDEBUG /MD
