// cl: /DNDEBUG /MD /EHsc

class Rva003AC210Owner
{
public:
	void *getField04();
};

void *Rva003AC210Owner::getField04()
{
	return reinterpret_cast<char *>(this) + 4;
}

class Rva003AC220Owner
{
public:
	unsigned char getByte1C() const;
};

unsigned char Rva003AC220Owner::getByte1C() const
{
	return *(reinterpret_cast<const unsigned char *>(this) + 0x1C);
}

class Rva003AC230Owner
{
public:
	unsigned char getByte1D() const;
};

unsigned char Rva003AC230Owner::getByte1D() const
{
	return *(reinterpret_cast<const unsigned char *>(this) + 0x1D);
}

class Rva003AC240Owner
{
public:
	void *getField20();
};

void *Rva003AC240Owner::getField20()
{
	return reinterpret_cast<char *>(this) + 0x20;
}

class Rva003AC250Owner
{
public:
	unsigned char getByte18() const;
};

unsigned char Rva003AC250Owner::getByte18() const
{
	return *(reinterpret_cast<const unsigned char *>(this) + 0x18);
}

class Rva003AC260Owner
{
public:
	unsigned char getByte19() const;
};

unsigned char Rva003AC260Owner::getByte19() const
{
	return *(reinterpret_cast<const unsigned char *>(this) + 0x19);
}

class Rva003AC270Owner
{
public:
	unsigned char getByte2C() const;
};

unsigned char Rva003AC270Owner::getByte2C() const
{
	return *(reinterpret_cast<const unsigned char *>(this) + 0x2C);
}

class Rva003AC280Owner
{
public:
	unsigned char getByte10() const;
};

unsigned char Rva003AC280Owner::getByte10() const
{
	return *(reinterpret_cast<const unsigned char *>(this) + 0x10);
}

class Rva003AC290Owner
{
public:
	float getFloat1C() const;
};

float Rva003AC290Owner::getFloat1C() const
{
	return *(reinterpret_cast<const float *>(this) + 7);
}

class Rva003AC2A0Owner
{
public:
	unsigned char getByte08() const;
};

unsigned char Rva003AC2A0Owner::getByte08() const
{
	return *(reinterpret_cast<const unsigned char *>(this) + 8);
}
