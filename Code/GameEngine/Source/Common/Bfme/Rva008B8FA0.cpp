// ?rva008B8FA0@@YG_NPAVBfmeN1242@@PAPBDPAVBfmeE1242@@@Z
// Address-derived identity for retail 0x008B8FA0; the argument layout and
// helper calls are proven by the exact retail body and matched callees.
// cl: /O2 /DNDEBUG /MD

extern "C" int __cdecl atoi(const char *text);
extern void *g_bfmeFallbackDB;

class BfmeE1242;

class BfmeN1242
{
public:
	void bfmeReserve1242(int n);
	void bfmePut1242(int i, BfmeE1242 *e);

	char m_bfmePad00[0x28];
	int m_bfme28;
};

bool __stdcall rva008B8FA0(BfmeN1242 *list, const char **input, BfmeE1242 *fallback)
{
	const char *text = *input + 8;
	if (atoi(text) != 0)
		goto valid_text;
	if (text[0] == '0')
		goto valid_text;
	goto invalid_text;

valid_text:
	{
		int index = atoi(*input + 8);
		if (fallback == 0)
			fallback = reinterpret_cast<BfmeE1242 *>(g_bfmeFallbackDB);

		if (index >= 0)
		{
			list->bfmeReserve1242(index + 1);
			list->bfmePut1242(index, fallback);

			int count = list->m_bfme28;
			if (index + 1 > count)
				count = index + 1;
			list->m_bfme28 = count;
		}
	}

	return true;

invalid_text:
	return false;
}
