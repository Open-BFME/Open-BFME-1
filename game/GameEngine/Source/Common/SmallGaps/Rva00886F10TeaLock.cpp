// ?enter@BfmeLockTEA@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: three tiny TEA lock helpers at 0x00886F10/0x00886F20/0x00886F30:
// conditional enter/leave through the imported stdcall pair and a guard
// object constructor that enters when the lock is armed.
struct BfmeLockTEA {
	char m_pad[0x18];
	bool m_armed;
	void enter();
	void leave();
};
extern "C" __declspec(dllimport) void __stdcall bfmeEnterTEA(BfmeLockTEA* lock);
extern "C" __declspec(dllimport) void __stdcall bfmeLeaveTEA(BfmeLockTEA* lock);
void BfmeLockTEA::enter()
{
	if (m_armed)
		bfmeEnterTEA(this);
}
// ?leave@BfmeLockTEA@@QAEXXZ
void BfmeLockTEA::leave()
{
	if (m_armed)
		bfmeLeaveTEA(this);
}
// ??0Rva00886F60Class@@QAE@PAUBfmeLockTEA@@@Z
class Rva00886F60Class {
public:
	virtual ~Rva00886F60Class();
	BfmeLockTEA* m_lock;
	Rva00886F60Class(BfmeLockTEA* lock);
};
Rva00886F60Class::Rva00886F60Class(BfmeLockTEA* lock)
{
	m_lock = lock;
	if (lock && lock->m_armed)
		bfmeEnterTEA(lock);
}
