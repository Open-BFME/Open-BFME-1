// cl: /DNDEBUG /MD /EHsc
// Retail 0x002D4D80 returns false, but no caller or vtable slot proves a
// semantic method name, so this source keeps the address in its identity.

bool Rva002D4D80False()
{
	return false;
}
