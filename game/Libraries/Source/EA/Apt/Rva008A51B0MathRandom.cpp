// Apt Math.random callback at 0x008A51B0.
// Retail converts the RNG word as unsigned and scales it to a float.
class AptValue;
extern const float Rva008A51B0RandomScale;
unsigned int __cdecl bfmeNext1221();
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);
AptValue* aptMathRandom(void* self, int argc)
{
    unsigned int randomBits = bfmeNext1221();
    return Rva008A4EA0MakeFloat((float)randomBits * Rva008A51B0RandomScale);
}
