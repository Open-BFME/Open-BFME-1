// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6B20: package the integer field at offset 0x30 as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField30At008B6B20(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x30));
}
