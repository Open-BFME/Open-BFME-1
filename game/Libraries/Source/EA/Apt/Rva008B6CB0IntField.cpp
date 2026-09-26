// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6CB0: package the integer field at offset 0x48 as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField48At008B6CB0(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x48));
}
