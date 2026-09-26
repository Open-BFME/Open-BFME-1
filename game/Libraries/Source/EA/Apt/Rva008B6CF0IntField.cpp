// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6CF0: package the integer field at offset 0x44 as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField44At008B6CF0(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x44));
}
