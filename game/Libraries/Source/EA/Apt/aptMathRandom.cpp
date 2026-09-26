// ?aptMathRandom@@YAPAVAptValue@@PAXH@Z
// cl: /DNDEBUG /MD /EHsc
// Math callback uses the engine random generator and scales its unsigned result.
class AptValue;
extern float g_bfmeRandomScale011366D8;
unsigned int __cdecl bfmeNext1221();
AptValue* __cdecl Rva008A4EA0MakeFloat(float value);

AptValue* __cdecl aptMathRandom(void* self, int argc)
{
    unsigned int next = bfmeNext1221();
    return Rva008A4EA0MakeFloat((float)next * g_bfmeRandomScale011366D8);
}
