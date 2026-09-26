// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-

class Rva00696530FirstPointer
{
public:
    void *get();
};

void *Rva00696530FirstPointer::get()
{
    return *reinterpret_cast<void *const *>(this);
}

void Rva00696560NoOp()
{
}

class Rva00696590Self
{
public:
    void *returnThis();
};

void *Rva00696590Self::returnThis()
{
    return this;
}

void Rva006965A0NoOp()
{
}

class Rva006965B0Self
{
public:
    void *returnThis();
};

void *Rva006965B0Self::returnThis()
{
    return this;
}

class Rva006965D0PointerPlus8
{
public:
    void *get();
};

void *Rva006965D0PointerPlus8::get()
{
    return static_cast<unsigned char *>(*reinterpret_cast<void *const *>(this)) + 8;
}
