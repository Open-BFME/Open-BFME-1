// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B6D10: package the integer field at offset 0x54 as an Apt value.
class AptInteger
{
public:
    static AptInteger *Create(int value);
};

AptInteger *aptIntField54At008B6D10(void *self, int argc)
{
    return AptInteger::Create(*(int *)((char *)self + 0x54));
}
