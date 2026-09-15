// The callers at 0x0071DAF0 and 0x007348A0 use the returned output handle.
// Retail reads the cached resource from this+0x18.
// Retail reads the dirty byte from this+0x1c.
// The resource stores its reference count at offset 0x4.

void d_0094d450(void);

#pragma optimize("y", on)

struct Rva0094D9F0Thing
{
	int head;
	unsigned short refs;
};

class Rva0094D9F0Handle
{
public:
	Rva0094D9F0Thing * volatile value;
};

static void copy_ref(Rva0094D9F0Thing *source, Rva0094D9F0Handle *destination)
{
	destination->value = source;
	if (source != 0)
		++source->refs;
}

class Rva0094D9F0
{
public:
	Rva0094D9F0Handle *assign(Rva0094D9F0Handle *destination);

private:
	unsigned char m_prefix[0x18];
	Rva0094D9F0Handle m_handle;
	unsigned char m_refresh;
};

Rva0094D9F0Handle *Rva0094D9F0::assign(Rva0094D9F0Handle *destination)
{
	volatile unsigned state = 0;
	if (m_refresh != 0)
		d_0094d450();
	copy_ref(m_handle.value, destination);
	return destination;
}
