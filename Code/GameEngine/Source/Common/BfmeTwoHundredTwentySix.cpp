// A twice-emitted writer, both copies converted here under their own names: a
// four-byte number turned around and then laid down only when it fits inside
// the window the caller gave.

extern "C" __declspec(dllimport) unsigned long __stdcall htonl(unsigned long hostlong);

unsigned char *bfmeWriteLA(unsigned char *at, unsigned long value, const unsigned char *end)
{
	unsigned long raw = htonl(value);

	if (end == 0 || (at <= end && at + 4 <= end))
	{
		*(unsigned long *)at = raw;

		at += 4;
	}

	return at;
}

unsigned char *bfmeWriteLC(unsigned char *at, unsigned long value, const unsigned char *end)
{
	unsigned long raw = htonl(value);

	if (end == 0 || (at <= end && at + 4 <= end))
	{
		*(unsigned long *)at = raw;

		at += 4;
	}

	return at;
}
