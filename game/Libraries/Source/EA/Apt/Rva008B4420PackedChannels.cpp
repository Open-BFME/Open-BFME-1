// cl: /DNDEBUG /MD /EHsc
// RVA 0x008B4420: pack three integer-converted channels from a float getter.
class AptValue;
class AptInteger
{
public:
    static AptValue *Create(int value);
};

class Rva008AC9E0
{
public:
    float get(int channel);
};

struct Rva008B4420Owner
{
    char m_padding[0x20];
    Rva008AC9E0 *m_getter;
};

extern AptValue *g_bfmeFallbackDB;

AptValue *aptPackedChannels008B4420(Rva008B4420Owner *self, int argc)
{
    Rva008AC9E0 *getter = self->m_getter;
    AptValue *result;
    if (getter)
    {
        int packed = (int)getter->get(8);
        packed <<= 16;
        packed |= (int)getter->get(9) << 8;
        packed |= (int)getter->get(10);
        result = AptInteger::Create(packed);
    }
    else
        result = g_bfmeFallbackDB;
    return result;
}
