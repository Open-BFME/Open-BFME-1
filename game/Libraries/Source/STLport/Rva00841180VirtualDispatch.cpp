// cl: /MD /EHsc
// Retail 0x00841180, 0x008411A0, and 0x008411C0 each contain 19 bytes.
// Each INT3-delimited body reads a vbtable at argument+0, adjusts by its
// second dword, and calls adjusted-this vtable slot zero with stack argument 0.
// Native inherited virtual-destructor syntax reproduces that ABI and load
// order without an explicit virtual-base cast (which adds a null guard).
// The native narrow istream and ostream spellings both match these bytes,
// so byte equality does not identify a stream specialization or original name.
// Keep an independent address-derived layout view and entry for each body.

class Rva00841180Base
{
public:
    virtual ~Rva00841180Base();
};

class Rva00841180Owner : public virtual Rva00841180Base
{
};

void rva00841180Dispatch(Rva00841180Owner *object)
{
    object->~Rva00841180Owner();
}

class Rva008411A0Base
{
public:
    virtual ~Rva008411A0Base();
};

class Rva008411A0Owner : public virtual Rva008411A0Base
{
};

void rva008411A0Dispatch(Rva008411A0Owner *object)
{
    object->~Rva008411A0Owner();
}

class Rva008411C0Base
{
public:
    virtual ~Rva008411C0Base();
};

class Rva008411C0Owner : public virtual Rva008411C0Base
{
};

void rva008411C0Dispatch(Rva008411C0Owner *object)
{
    object->~Rva008411C0Owner();
}

