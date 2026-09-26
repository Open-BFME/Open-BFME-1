// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0069A6B0, 48 bytes through its `ret 4` at +0x2D (the int3 run
// starts at +0x30).  Ghidra stopped at +0x28, so the shared `return 1` tail
// at 0x0069A6D8 was later claimed as a separate 8-byte alias; all three early
// exits branch to it.  Keeps an event whose info has the +0x38 bit 3 set or
// type 4 at +0x34, and otherwise drops it when the info's +0x18 level is
// below the +0x7C floor of the settings at +0x0C.  No caller names the owner,
// so the names keep the address.

struct Rva0069A6B0Settings
{
	char m_unmodelled00[ 0x7C ];
	float m_floor7C;
};

struct Rva0069A6B0EventInfo
{
	char m_unmodelled00[ 0x18 ];
	float m_level18;
	char m_unmodelled1C[ 0x34 - 0x1C ];
	int m_type34;
	unsigned int m_flags38;
};

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();

	char m_unmodelled04[ 4 ];
	const Rva0069A6B0EventInfo *m_eventInfo;
};

class Rva0069A6B0Owner
{
public:
	int passesLevel( const AudioEventRTS *event ) const;

private:
	char m_unmodelled00[ 0x0C ];
	const Rva0069A6B0Settings *m_settings;
};

int Rva0069A6B0Owner::passesLevel( const AudioEventRTS *event ) const
{
	const Rva0069A6B0EventInfo *info = event->m_eventInfo;
	return ( info->m_flags38 & 8 ) || info->m_type34 == 4 || info->m_level18 >= m_settings->m_floor7C;
}
