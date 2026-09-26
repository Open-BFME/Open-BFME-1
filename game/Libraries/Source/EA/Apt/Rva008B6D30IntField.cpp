// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6D30: package the integer field at offset 0x40 as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField40At008B6D30(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x40));
}
