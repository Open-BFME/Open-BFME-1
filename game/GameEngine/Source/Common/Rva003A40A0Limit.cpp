// cl: /O2
// Retail 0x003A40A0 (117 bytes, ret): returns the smaller of the cap at +0x20
// and the 2D distance between (+0x0C,+0x10) and (+0x14,+0x18); the cap is
// scaled by the 0x01075C74 weight while Shift is held (Keyboard::isShift via
// ILT 0x000156B3) and the GlobalData byte at +0x90 is set. Its only caller is
// the unmatched 0x003A50F0 through ILT 0x000239D9, so the owner keeps an
// address name. The volatile reads keep retail's dx spill and the cap's
// memory copy; the double root is what pops the dead dy after fsqrt.
extern "C" double sqrt(double x);
#pragma intrinsic(sqrt)

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva003A40A0GlobalFlags
{
	unsigned char m_pad[0x90];
	char m_flag90;
};

class Keyboard
{
public:
	bool isShift();
};
extern Keyboard *TheKeyboard;

extern const float g_bfmeDirectionWeight1285;

template<class T> inline const T &rva003A40A0Min(const T &a, const T &b)
{
	return a < b ? a : b;
}

class Rva003A40A0Host
{
public:
	float limit();

private:
	unsigned char m_pad00[0xc];
	float m_x0;
	float m_y0;
	float m_x1;
	float m_y1;
	unsigned char m_pad1c[4];
	float m_cap;
};

// ?limit@Rva003A40A0Host@@QAEMXZ
float Rva003A40A0Host::limit()
{
	float dy = *(volatile float *)&m_y1;
	float cap = m_cap;
	volatile float dx = m_x1 - m_x0;
	dy -= m_y0;
	float len[2];
	double root = sqrt(dx * dx + dy * dy);
	len[0] = (float)root;
	if (TheKeyboard->isShift()
		&& reinterpret_cast<Rva003A40A0GlobalFlags *>(TheWritableGlobalData)->m_flag90)
		*(volatile float *)&cap = *(volatile float *)&cap * g_bfmeDirectionWeight1285;
	return rva003A40A0Min(cap, len[0]);
}
