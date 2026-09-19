// cl: /O2 /DNDEBUG /MD

class Rva00219270Owner
{
public:
	void *get();
};

void *Rva00219270Owner::get()
{
	return (char *)this + 8;
}

class Rva00219790Owner
{
public:
	void *get();
};

void *Rva00219790Owner::get()
{
	return (char *)this - 0x20;
}

class Rva00219AB0Owner
{
public:
	void *get();
};

void *Rva00219AB0Owner::get()
{
	return *(void **)((char *)this - 0x18);
}

bool Rva002193A0False()
{
	return false;
}

bool Rva00219400False()
{
	return false;
}

bool Rva00219410False()
{
	return false;
}

class Rva00219440Owner
{
public:
	void ret4(int);
};

void Rva00219440Owner::ret4(int)
{
}

class Rva00219450Owner
{
public:
	void ret12(int, int, int);
};

void Rva00219450Owner::ret12(int, int, int)
{
}

int Rva00219470Zero()
{
	return 0;
}

class Rva002194E0Owner
{
public:
	void ret4(int);
};

void Rva002194E0Owner::ret4(int)
{
}

class Rva00219510Owner
{
public:
	void ret4(int);
};

void Rva00219510Owner::ret4(int)
{
}

int Rva00219530Zero()
{
	return 0;
}

bool Rva00219550False()
{
	return false;
}

int Rva00219560Zero()
{
	return 0;
}

class Rva00219580Owner
{
public:
	void ret8(int, int);
};

void Rva00219580Owner::ret8(int, int)
{
}

class Rva00219590Owner
{
public:
	void ret4(int);
};

void Rva00219590Owner::ret4(int)
{
}

int Rva002195E0Zero()
{
	return 0;
}

class Rva00219630Owner
{
public:
	void ret8(int, int);
};

void Rva00219630Owner::ret8(int, int)
{
}

class Rva00219680Owner
{
public:
	bool test();
};

bool Rva00219680Owner::test()
{
	return true;
}

class Rva00219690Owner
{
public:
	bool test();
};

bool Rva00219690Owner::test()
{
	return false;
}

class Rva002196A0Owner
{
public:
	bool test();
};

bool Rva002196A0Owner::test()
{
	return false;
}

class Rva002196B0Owner
{
public:
	int value();
};

int Rva002196B0Owner::value()
{
	return 0;
}

bool Rva002197A0False()
{
	return false;
}

bool Rva002197B0False()
{
	return false;
}

bool Rva002197C0False()
{
	return false;
}
