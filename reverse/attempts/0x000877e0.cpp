// ?d_000877e0@@YAXXZ
// partial score=0.91 date=2026-08-30
// cl: /O2
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *addend);
class BfmeIface877E0 { public: virtual ~BfmeIface877E0(); };
class BfmeCounted877E0 : public BfmeIface877E0 { public: long m_references; };
class BfmeRef877E0 { public: void bfmeRelease877E0(); private: BfmeCounted877E0 *m_held; };
void BfmeRef877E0::bfmeRelease877E0()
{
	BfmeCounted877E0 *held = m_held;

	if (held != 0)
	{
		if (InterlockedDecrement(&held->m_references) <= 0)
			delete static_cast<BfmeIface877E0 *>(held);
		m_held = 0;
	}
}
