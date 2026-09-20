// cl: /O2 /Ob2 /DNDEBUG /MD

// The carved body at retail RVA 0x004891E0 stores its argument at offset 0,
// calls the imported enter function, and returns this.
struct Rva004891E0CriticalSection;
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(
	Rva004891E0CriticalSection *section);

class Rva004891E0Lock
{
public:
	Rva004891E0Lock(Rva004891E0CriticalSection *section);

private:
	Rva004891E0CriticalSection *m_section;
};

Rva004891E0Lock::Rva004891E0Lock(
	Rva004891E0CriticalSection *section)
	: m_section(section)
{
	EnterCriticalSection(section);
}
