// cl: /DNDEBUG /MD /EHsc
// RVA 0x008A60A0: wrap the signed result of callback slot 0x013378B8 as a float.
class AptValue;
// Retail .data VA 0x013378B8: the callback slot, zero in the image; both
// address-qualified users (this TU and Rva008AF330StringToFloatValue.cpp)
// call it as int __cdecl(const char *, int). Defined once here.
int (__cdecl *Rva013378B8)(const char *, int) = 0;
AptValue *Rva008A4EA0MakeFloat(float value);

AptValue *aptCallbackFloat008A60A0()
{
    float value = (float)Rva013378B8(0, 3);
    return Rva008A4EA0MakeFloat(value);
}
