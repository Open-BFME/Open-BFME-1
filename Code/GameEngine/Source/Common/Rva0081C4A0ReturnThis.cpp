// cl: /DNDEBUG /MD /EHsc
// RVA 0x0081C4A0: independent member body after two int3 bytes.
class Rva0081C4A0Owner
{
public:
    void *returnThis();
};

void *Rva0081C4A0Owner::returnThis()
{
    return this;
}
