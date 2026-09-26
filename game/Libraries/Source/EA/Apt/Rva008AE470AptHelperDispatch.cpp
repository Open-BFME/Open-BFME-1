// cl: /DNDEBUG /MD /EHsc
// RVA 0x008AE470: invoke the three-argument Apt helper with its flag set.
class AptValue;
AptValue *aptHelper008AE3A0(void *entry, int count, int flag);

AptValue *aptHelperSetFlag008AE470(void *entry, int count)
{
    return aptHelper008AE3A0(entry, count, 1);
}
