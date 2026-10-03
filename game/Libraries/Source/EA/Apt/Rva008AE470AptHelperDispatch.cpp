// cl: /DNDEBUG /MD /EHsc
// RVA 0x008AE470: invoke the three-argument Apt helper with its flag set.
class AptValue;
void d_008ae3a0();

AptValue *aptHelperSetFlag008AE470(void *entry, int count)
{
    return reinterpret_cast<AptValue *(__cdecl *)(void *, int, int)>(
        d_008ae3a0)(entry, count, 1);
}
