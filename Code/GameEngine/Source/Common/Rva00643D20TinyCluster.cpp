// cl: /O2 /Ob0 /DNDEBUG /MD /EHs-c-

class Rva00643D20FirstPointer
{
public:
    void *get();
};

void *Rva00643D20FirstPointer::get()
{
    return *reinterpret_cast<void *const *>(this);
}

void Rva00643D40NoOp()
{
}

void Rva00643D50NoOp()
{
}

void Rva00643E30NoOp()
{
}

void Rva00643E40NoOp()
{
}
