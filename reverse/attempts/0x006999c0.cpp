// ?setVolumes@Rva006999C0Owner@@QAEXME@Z
// partial score=0.88 date=2026-09-04
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Bitmask volume fan-out; stdcall refreshPair. Wall: MSVC saves this (esi) across calls; retail keeps ecx.
void __stdcall refreshPair(int a, int b);
class Rva006999C0Owner {
public:
	void setVolumes(float volume, unsigned char flags);
	char m_pad0[4];
	float m_f04, m_f08, m_f0c, m_f10, m_f14, m_f18, m_f1c, m_f20, m_f24, m_f28;
};
void Rva006999C0Owner::setVolumes(float volume, unsigned char flags)
{
	if (flags & 1) {
		m_f14 = volume; m_f18 = volume;
		for (int i = 0; i < 2; ++i) refreshPair(2, i);
	}
	if (flags & 2) { m_f04 = volume; refreshPair(0, 0); }
	if (flags & 4) { m_f08 = volume; refreshPair(0, 1); }
	if (flags & 8) {
		m_f0c = volume; m_f24 = volume; m_f10 = volume; m_f28 = volume;
		for (int i = 0; i < 2; ++i) refreshPair(1, i);
		for (int i = 0; i < 2; ++i) refreshPair(4, i);
	}
	if (flags & 0x10) {
		m_f1c = volume; m_f20 = volume;
		for (int i = 0; i < 2; ++i) refreshPair(3, i);
	}
}
