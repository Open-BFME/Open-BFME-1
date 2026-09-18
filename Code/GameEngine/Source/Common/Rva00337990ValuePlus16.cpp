// cl: /DNDEBUG /MD /EHsc
// ?d_00337990@@YAXXZ
// Retail 0x00337990 loads the first object field and adds 16.

class Rva00337990Owner
{
public:
    int valuePlus16();
};

int Rva00337990Owner::valuePlus16()
{
    return *(int *)this + 16;
}
