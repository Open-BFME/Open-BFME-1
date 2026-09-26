// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6C00: package the integer field at offset 0x20 as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField20At008B6C00(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x20));
}
