// cl: /DNDEBUG /MD /EHsc
// RVA 0x008AE450: invoke the three-argument Apt helper with its flag clear.
class AptValue;
// The worker is the matched aptHelper008AE3A0 (AptHelper008AE3A0.cpp).
AptValue *aptHelper008AE3A0(void *entry, int count, int flag);

AptValue *aptHelperClearFlag008AE450(void *entry, int count)
{
    return aptHelper008AE3A0(entry, count, 0);
}
