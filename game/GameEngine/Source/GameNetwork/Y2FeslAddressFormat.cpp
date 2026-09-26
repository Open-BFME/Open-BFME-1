// cl: /O2
// 0x007E8760 / 0x007E86D0: FESL address.cpp dotted-quad format and parse.
// Format asserts if the destination is shorter than 17 bytes (line 49).
// Parse packs %d.%d.%d.%d into this+8 and stores the second argument at +0xC.

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();
extern "C" int __cdecl sprintf(char *buf, const char *fmt, ...);
extern "C" int __cdecl sscanf(const char *buf, const char *fmt, ...);

class Rva007E8760Addr
{
public:
	void format(char *destination, unsigned destinationSize);
	void parse(const char *addressText, int extra);

private:
	char m_pad[8];
	unsigned m_addr;
	int m_extra;
};

void Rva007E8760Addr::format(char *destination, unsigned destinationSize)
{
	if (destinationSize < 17)
		Rva007EB810Get()->fail(
			"false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\address.cpp",
			49);
	unsigned packedAddress = m_addr;
	sprintf(destination, "%hu.%hu.%hu.%hu",
		(unsigned char)(packedAddress >> 24),
		(unsigned char)(packedAddress >> 16),
		(unsigned char)(packedAddress >> 8),
		(unsigned char)packedAddress);
}

void Rva007E8760Addr::parse(const char *addressText, int extra)
{
	int firstOctet, secondOctet, thirdOctet, fourthOctet;
	sscanf(addressText, "%d.%d.%d.%d", &firstOctet, &secondOctet, &thirdOctet, &fourthOctet);
	unsigned packedAddress = (unsigned)firstOctet;
	packedAddress = (packedAddress << 8) + (unsigned)secondOctet;
	packedAddress = (packedAddress << 8) + (unsigned)thirdOctet;
	packedAddress = (packedAddress << 8) + (unsigned)fourthOctet;
	m_addr = packedAddress;
	m_extra = extra;
}
