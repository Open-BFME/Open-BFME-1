// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6BC0: package the integer field at offset 0x24 as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField24At008B6BC0(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x24));
}
