// cl: /DNDEBUG /MD /EHsc
// Retail 0x00174510 returns false. The surrounding vtable does not prove a
// semantic method name, so this source keeps the address in its identity.

bool Rva00174510False()
{
	return false;
}
