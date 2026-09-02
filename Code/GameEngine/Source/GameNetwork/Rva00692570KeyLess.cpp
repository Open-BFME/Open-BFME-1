// Binary less over a 12-byte key: unsigned primary at +0, AsciiString at +4.
// thiscall functor, two by-ref arguments, ret 8. Unsigned trichotomy then
// AsciiString::compare via the ILT at 0x000220C5.

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

class AsciiString
{
public:
	int compare(const AsciiString &str) const;

private:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

struct Rva00692570Key
{
	unsigned primary;
	AsciiString secondary;
	unsigned trailing;
};

class Rva00692570Less
{
public:
	bool operator()(const Rva00692570Key &left, const Rva00692570Key &right) const;
};

// ??RRva00692570Less@@QBE_NABURva00692570Key@@0@Z
bool Rva00692570Less::operator()(const Rva00692570Key &left, const Rva00692570Key &right) const
{
	if (left.primary < right.primary)
		return true;
	if (left.primary > right.primary)
		return false;
	return left.secondary.compare(right.secondary) < 0;
}
