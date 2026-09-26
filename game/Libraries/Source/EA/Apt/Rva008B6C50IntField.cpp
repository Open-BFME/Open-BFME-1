// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6C50: package the integer field at offset 0x50 as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField50At008B6C50(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x50));
}
