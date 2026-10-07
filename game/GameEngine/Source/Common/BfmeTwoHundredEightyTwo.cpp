// cl: /Od
// A block asked for and, when one comes back, emptied to a bare text. What was
// kept of it is never read again. Built without optimisation; the callee is
// pinned by address.

// Retail calls ILT 0x30940 -> 0x607E0, the matched OpenBFME5_ReturnSecondPointer.
void *OpenBFME5_ReturnSecondPointer(void *, void *value);

void bfmeMakePV(unsigned int bytes)
{
	void *out;

	char *got = (char *)OpenBFME5_ReturnSecondPointer((void *)1, (void *)bytes);

	if (got != 0)
	{
		*got = 0;

		out = got;
	}
	else
	{
		out = 0;
	}
}
