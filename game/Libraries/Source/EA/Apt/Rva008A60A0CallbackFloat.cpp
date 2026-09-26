// cl: /DNDEBUG /MD /EHsc
// RVA 0x008A60A0: wrap the signed result of callback slot 0x013378B8 as a float.
class AptValue;
extern int (__cdecl *Rva013378B8)(const char *, int);
AptValue *Rva008A4EA0MakeFloat(float value);

AptValue *aptCallbackFloat008A60A0()
{
    float value = (float)Rva013378B8(0, 3);
    return Rva008A4EA0MakeFloat(value);
}
