// cl: /O2
// 0x007F99B0: copy the argument into a new chain node at +0x6AC, with the
// string at +0x10 inlined after a 0x34-byte header.

extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" char *__cdecl strncpy(char *dest, const char *src, unsigned int n);
#pragma intrinsic(strlen)

class Rva00800550Chain
{
public:
	void *append(int size);
};

class Rva007FA2C0
{
public:
	int onBusy(void *arg);

private:
	char m_pad[0x6AC];
	Rva00800550Chain m_chain;
};

int Rva007FA2C0::onBusy(void *arg)
{
	unsigned char *src = (unsigned char *)arg;
	unsigned len = strlen(*(char **)(src + 0x10)) + 1;
	unsigned char *node = (unsigned char *)m_chain.append((int)(len + 0x34));
	*(int *)(node + 4) = *(int *)(src + 4);
	*(int *)(node + 8) = *(int *)(src + 8);
	*(int *)(node + 0xC) = *(int *)(src + 0xC);
	*(int *)(node + 0x10) = *(int *)(src + 0x10);
	*(int *)(node + 0x14) = *(int *)(src + 0x14);
	*(int *)(node + 0x18) = *(int *)(src + 0x18);
	*(int *)(node + 0x1C) = *(int *)(src + 0x1C);
	*(int *)(node + 0x20) = *(int *)(src + 0x20);
	*(int *)(node + 0x24) = *(int *)(src + 0x24);
	*(int *)(node + 0x28) = *(int *)(src + 0x28);
	*(int *)(node + 0x2C) = *(int *)(src + 0x2C);
	node[0x30] = src[0x30];
	char *dest = (char *)(node + 0x34);
	*(char **)(node + 0x10) = dest;
	strncpy(dest, *(char **)(src + 0x10), len);
	return 0;
}
