// _Rva0080C6F0
// partial score=0.5 date=2026-09-09
// Open-BFME partial ASM-to-C++ reconstruction; retained for future shape work.
// Retail RVA 0x0080C6F0, body 546B; RTC names: MD5Data/uSeqn/MD5Context.
// First non-reloc divergence in the source draft is the cursor update at +0x56:
// retail add edx,2; add edx,[ebp-0x90]; this draft emits load/LEA.
// cl: /Od /GZ /GS /MD /DNDEBUG
void Rva0080F300(void *state, unsigned char *data, int length);
void Rva00810020(void *context);
void Rva00810060(void *context, const unsigned char *data, int length);
void Rva00810FF0(void *context, char *out, int outSize);
int memcmp(const void *first, const void *second, unsigned int count);

unsigned char *Rva0080C6F0(unsigned char *object)
{
	int length;
	unsigned char context[0x54];
	unsigned char header[4];
	unsigned char digest[0x10];
	unsigned char *state;
	unsigned char *base;

	state = *(unsigned char **)(object + 0x120);
	base = state + 0x4018;
	base = ((base[0] <= 0x7F) + 2) + base;
	length = *(int *)(state + 0x4010) + state + 0x4018 - base;
	if (*(int *)(state + 0x80A8) > 0)
	{
		Rva0080F300(state + 0x86BC, base, length);
		header[0] = (unsigned char)(*(unsigned int *)(state + 0x8018) >> 24);
		header[1] = (unsigned char)(*(unsigned int *)(state + 0x8018) >> 16);
		header[2] = (unsigned char)(*(unsigned int *)(state + 0x8018) >> 8);
		header[3] = (unsigned char)*(unsigned int *)(state + 0x8018);
		Rva00810020(context);
		Rva00810060(context, state + 0x80AC, *(int *)(state + 0x80A8));
		Rva00810060(context, base + 0x10, length - 0x10);
		Rva00810060(context, header, 4);
		Rva00810FF0(context, (char *)digest, 0x10);
		if (memcmp(digest, base, 0x10) != 0)
			base = 0;
		else
		{
			base += 0x10;
			*(int *)(state + 0x4010) = length - 0x10;
			*(int *)(state + 0x400C) = *(int *)(state + 0x4010);
		}
	}
	*(unsigned int *)(state + 0x8018) += 1;
	return base;
}
