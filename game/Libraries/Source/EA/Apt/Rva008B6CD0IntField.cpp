// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6CD0: package the integer field at offset 0x5C as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField5CAt008B6CD0(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x5C));
}
