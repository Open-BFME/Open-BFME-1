// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// The retail body returns its this pointer. No caller proves a semantic owner.

class Rva0075D0B0ReturnThis
{
public:
    void *returnThis();
};

void *Rva0075D0B0ReturnThis::returnThis()
{
    return this;
}
