// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Combined TU: thiscall refreshPair (0x00699180) + setVolumes (0x006999C0).
// Helper body is the real member; no stand-in.

class Rva00699180Owner
{
public:
	void refreshPair(int a, int b);
	void setVolumes(float volume, unsigned char flags);

	char m_pad0[4];
	float m_base[12];
	float m_product[6];
	char m_pad4c[0x94 - 0x4c];
	float m_atten;
	float m_vol;
	float m_scale;
	char m_padA0[0xC8 - 0xA0];
	float m_slot[12][4];
	unsigned char m_dirty[48];
};

void Rva00699180Owner::refreshPair(int a, int b)
{
	int idx = b + a * 2;
	float *slot = (float *)((char *)this + 0xC8 + (idx << 4));
	float old[4];
	old[0] = slot[0];
	old[1] = slot[1];
	old[2] = slot[2];
	old[3] = slot[3];

	if (a == 5)
	{
		slot[0] = 1.0f;
		slot[1] = 1.0f;
		slot[2] = 1.0f;
		slot[3] = 1.0f;
	}
	else if (*(unsigned char *)0x012BA144)
	{
		slot[0] = *((float *)((char *)this + 4 + idx * 4)) * ((float *)0x012BA12C)[a] * m_vol;
		if (b == 1)
			slot[0] = slot[0] * m_atten;
		slot[1] = slot[0] * m_scale;
		slot[2] = m_product[a] * slot[0];
		slot[3] = slot[2] * m_scale;

		float x0 = slot[0];
		if (x0 < *(const float *)0x01075350)
			x0 = *(const float *)0x01075350;
		else if (x0 > *(const float *)0x01075334)
			x0 = *(const float *)0x01075334;
		slot[0] = x0;

		float x1 = slot[1];
		if (x1 < *(const float *)0x01075350)
			x1 = *(const float *)0x01075350;
		else if (x1 > *(const float *)0x01075334)
			x1 = *(const float *)0x01075334;
		slot[1] = x1;

		float x2 = slot[2];
		if (x2 < *(const float *)0x01075350)
			x2 = *(const float *)0x01075350;
		else if (x2 > *(const float *)0x01075334)
			x2 = *(const float *)0x01075334;
		slot[2] = x2;

		float x3 = slot[3];
		if (x3 < *(const float *)0x01075350)
			x3 = *(const float *)0x01075350;
		else if (x3 > *(const float *)0x01075334)
			x3 = *(const float *)0x01075334;
		slot[3] = x3;
	}
	else
	{
		slot[0] = 0.0f;
		slot[1] = 0.0f;
		slot[2] = 0.0f;
		slot[3] = 0.0f;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (slot[i] != old[i])
			*((unsigned char *)this + 0x188 + (b + a * 2) * 4 + i) = 2;
	}
}
