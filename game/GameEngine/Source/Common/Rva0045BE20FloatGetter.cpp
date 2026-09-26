// ?get@Rva0045BE20FloatField@@QBEMXZ
// The carved boundary proves a const thiscall getter for the float at +0x6C.
// No caller identifies the owning class or field semantically.
// cl: /O2 /Ob2 /G6 /DNDEBUG /MD /EHs-c-

class Rva0045BE20FloatField
{
public:
	float get() const;
};

float Rva0045BE20FloatField::get() const
{
	return *reinterpret_cast<const float *>(
		reinterpret_cast<const char *>(this) + 0x6c);
}

class Rva0045BD30FloatGetter
{
public:
    float get() const;
};

class Rva0045BD80FloatGetter
{
public:
    float get() const;
};

class Rva0045BDB0FloatGetter
{
public:
    float get() const;
};

class Rva0045BDF0FloatGetter
{
public:
    float get() const;
};

class Rva0045BE30DwordGetter
{
public:
    int get() const;
};

class Rva0045BEA0FloatGetter
{
public:
    float get() const;
};

class Rva0045BEB0DwordGetter
{
public:
    int get() const;
};

class Rva0045BEF0ByteGetter
{
public:
    bool get() const;
};

float Rva0045BD30FloatGetter::get() const
{
    return *reinterpret_cast<const float *>(
        reinterpret_cast<const char *>(this) + 0x30);
}

float Rva0045BD80FloatGetter::get() const
{
    return *reinterpret_cast<const float *>(
        reinterpret_cast<const char *>(this) + 0x40);
}

float Rva0045BDB0FloatGetter::get() const
{
    return *reinterpret_cast<const float *>(
        reinterpret_cast<const char *>(this) + 0x34);
}

float Rva0045BDF0FloatGetter::get() const
{
    return *reinterpret_cast<const float *>(
        reinterpret_cast<const char *>(this) + 0x50);
}

int Rva0045BE30DwordGetter::get() const
{
    return *reinterpret_cast<const int *>(
        reinterpret_cast<const char *>(this) + 0x58);
}

float Rva0045BEA0FloatGetter::get() const
{
    return *reinterpret_cast<const float *>(
        reinterpret_cast<const char *>(this) + 0x68);
}

int Rva0045BEB0DwordGetter::get() const
{
    return *reinterpret_cast<const int *>(
        reinterpret_cast<const char *>(this) + 0x5c);
}

bool Rva0045BEF0ByteGetter::get() const
{
    return *reinterpret_cast<const bool *>(
        reinterpret_cast<const char *>(this) + 0x74);
}
