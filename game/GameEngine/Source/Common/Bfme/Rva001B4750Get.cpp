// cl: /DNDEBUG /MD /EHsc

void *Rva001B4750Get(void *object)
{
	void *nested = *reinterpret_cast<void **>(static_cast<unsigned char *>(object) + 0x204);
	if (nested != 0)
		return *reinterpret_cast<void **>(static_cast<unsigned char *>(nested) + 0x140);
	return 0;
}
