// ?d_0094d9f0@@YAXXZ
// partial score=0.9 date=2026-09-04
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Structural recovery for the handle-output body at retail 0x0094D9F0.

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
	void assign(Rva0094D9F0Handle *destination);

private:
	unsigned char m_prefix[0x18];
	Rva0094D9F0Handle m_handle;
	unsigned char m_refresh;
};

void Rva0094D9F0::assign(Rva0094D9F0Handle *destination)
{
	volatile unsigned state = 0;
	if (m_refresh != 0)
		d_0094d450();
	copy_ref(m_handle.value, destination);
}
