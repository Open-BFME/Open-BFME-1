// cl: /DNDEBUG /MD /O2
// Address-derived tiny bodies from the carved 0x0027F1xx-0x0027F4xx family.

// ?Rva0027F1D0False@@YA_NXZ
bool Rva0027F1D0False()
{
	return false;
}

class Rva0027F1E0Owner
{
public:
	void *get();
};

// ?get@Rva0027F1E0Owner@@QAEPAXXZ
void *Rva0027F1E0Owner::get()
{
	return reinterpret_cast<void *>(reinterpret_cast<char *>(this) - 0x0c);
}

// ?Rva0027F220False@@YA_NXZ
bool Rva0027F220False()
{
	return false;
}

// ?Rva0027F230False@@YA_NXZ
bool Rva0027F230False()
{
	return false;
}

// ?Rva0027F240False@@YA_NXZ
bool Rva0027F240False()
{
	return false;
}

// ?Rva0027F260Zero@@YAHXZ
int Rva0027F260Zero()
{
	return 0;
}

// ?Rva0027F270Zero@@YAHXZ
int Rva0027F270Zero()
{
	return 0;
}

// ?Rva0027F2B0Zero@@YAHXZ
int Rva0027F2B0Zero()
{
	return 0;
}

// ?Rva0027F2D0Zero@@YAHXZ
int Rva0027F2D0Zero()
{
	return 0;
}

// ?Rva0027F2F0Zero@@YAHXZ
int Rva0027F2F0Zero()
{
	return 0;
}

// ?Rva0027F300Zero@@YAHXZ
int Rva0027F300Zero()
{
	return 0;
}

// ?Rva0027F380Zero@@YAHXZ
int Rva0027F380Zero()
{
	return 0;
}

class Rva0027F3B0Owner
{
public:
	int get();

private:
	char m_leading[ 0x68 ];
	int m_value;
};

// ?get@Rva0027F3B0Owner@@QAEHXZ
int Rva0027F3B0Owner::get()
{
	return m_value;
}

class Rva0027F3E0Owner
{
public:
	int get();

private:
	char m_leading[ 0x54 ];
	int m_value;
};

// ?get@Rva0027F3E0Owner@@QAEHXZ
int Rva0027F3E0Owner::get()
{
	return m_value;
}

class Rva0027F410Owner
{
public:
	int get();

private:
	char m_leading[ 0x4c ];
	int m_value;
};

// ?get@Rva0027F410Owner@@QAEHXZ
int Rva0027F410Owner::get()
{
	return m_value;
}

// ?Rva0027F490Zero@@YAHXZ
int Rva0027F490Zero()
{
	return 0;
}
