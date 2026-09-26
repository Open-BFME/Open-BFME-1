// cl: /O2 /GS /MD /GR- /EHsc-
typedef unsigned __int64 uint64;

// Retail's 64-bit exponent update keeps the fraction and sign bits unchanged.
void setExponent00847460(uint64 &value, unsigned int exponent)
{
    unsigned int oldHigh = reinterpret_cast<unsigned int *>(&value)[1];
    unsigned int newHigh = exponent << 20;
    uint64 changed = static_cast<uint64>((oldHigh ^ newHigh) & 0x7FF00000u) << 32;
    value ^= changed;
}
