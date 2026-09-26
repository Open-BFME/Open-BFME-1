// cl: /DNDEBUG /MD /EHsc
// RVA 0x008A60D0: wrap the signed result of callback slot 0x013378BC as a float.
class AptValue;
extern int (__cdecl *Rva013378BC)(void *, int);
AptValue *Rva008A4EA0MakeFloat(float value);

AptValue *aptCallbackFloat008A60D0()
{
    float value = (float)Rva013378BC(0, 3);
    return Rva008A4EA0MakeFloat(value);
}
