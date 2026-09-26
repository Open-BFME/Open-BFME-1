// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6D50: package the adjusted integer field at offset 0x38.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptAdjustedIntField38At008B6D50(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x38) - 0x76c);
}
