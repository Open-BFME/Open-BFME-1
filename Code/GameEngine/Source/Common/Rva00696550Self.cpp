// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Retail loads this into EAX and returns it. The body proves only return-this behavior.

class Rva00696550Self
{
public:
    void *returnThis();
};

void *Rva00696550Self::returnThis()
{
    return this;
}
