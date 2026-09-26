// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6BA0: package the integer field at offset 0x3C as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField3CAt008B6BA0(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x3C));
}
