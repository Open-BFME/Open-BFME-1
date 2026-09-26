// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// The retail body returns its this pointer. No caller proves a semantic owner.

class Rva000689F0ReturnThis
{
public:
    void *returnThis();
};

void *Rva000689F0ReturnThis::returnThis()
{
    return this;
}
