// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6B80: package the integer field at offset 0x28 as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField28At008B6B80(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x28));
}
