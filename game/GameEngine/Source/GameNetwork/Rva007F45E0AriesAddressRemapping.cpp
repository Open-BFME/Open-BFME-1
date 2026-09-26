// cl: /O2 /GS
// EA FESL (jabba) ariesudp address-remapping table.
//
// The gamebrowser callback at 0x007F4530 passes the addressRemapping field of
// its decoded endpoint record to this member.  The receiver clears eight
// three-word entries at +0x10, then consumes the comma-separated network map.
// The original public class spelling is not present in the retail image, so
// this source keeps the owner neutral while preserving the observed ABI.

extern "C" int __cdecl sscanf(const char *, const char *, ...);
extern "C" unsigned int __cdecl strlen(const char *);
extern "C" void * __cdecl memset(void *, int, unsigned int);

int Rva007EB410NetConnStatus(int selector, void *buffer, int bufferSize);
extern "C" int Rva007EE930(const char *text, char *dest, int destSize,
	const char *defaultText, int index, int separator);
extern "C" unsigned int Rva007FFC10(const char *text);

struct Rva007F45E0Entry
{
	unsigned network;
	unsigned mask;
	unsigned host;
};

class Rva007F45E0Aries
{
public:
	void setAddressRemapping(const char *source);

private:
	char m_pad[0x10];
	Rva007F45E0Entry m_entries[8];
};

void Rva007F45E0Aries::setAddressRemapping(const char *source)
{
	char network[0x40];
	char mask[0x40];
	char value[0x40];
	char ignored[0x40];
	int index;
	int count;

	if (Rva007EB410NetConnStatus(0x73656375, 0, 0) == 0)
		return;

	if (source == 0)
	{
		source = "10.40.0.0 255.255.0.0 45410000,159.153.224.0 255.255.240.0 45410000";
	}
	else
	{
		if (strlen(source) == 0)
			source = "10.40.0.0 255.255.0.0 45410000,159.153.224.0 255.255.240.0 45410000";
	}

	memset(m_entries, 0, sizeof(m_entries));
	index = 0;
	count = 0;

	while (count < 8)
	{
		int extracted = Rva007EE930(source, value, 0x40,
			"", index, 0x2c);
		if (extracted <= 0)
			break;

		if (sscanf(value, "%s %s %s,",
			network, mask, ignored) == 3)
		{
			m_entries[count].network = Rva007FFC10(network);
			m_entries[count].mask = Rva007FFC10(mask);
			m_entries[count].host = Rva007EB410NetConnStatus(0x686f7374, 0, 0);
			++count;
		}

		++index;
	}
}
