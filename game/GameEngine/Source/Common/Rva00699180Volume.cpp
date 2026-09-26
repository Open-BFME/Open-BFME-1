// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Product clamping and output-pair refresh share this receiver and translation unit.
// Keeping both helper bodies visible preserves retail's ECX call sequence at 0x006994C0.
class Rva00699430Owner {
public:
	void productClamp(int index);
	char m_bytes[0x60];
};
void Rva00699430Owner::productClamp(int index)
{
	char *slot = m_bytes + index * 12;
	float *begin = *(float **)(slot + 0x4c);
	float *end = *(float **)(slot + 0x50);
	float *out = (float *)(m_bytes + 0x34 + index * 4);
	*out = 1.0f;
	if (begin != end)
	{
		do
		{
			*out = *out * *begin;
			begin = (float *)((char *)begin + 8);
		} while (begin != end);
	}
	float v = *out;
	if (v < 0.0f)
	{
		static float s_zero = 0.0f;
		v = s_zero;
		*out = v;
		return;
	}
	if (v > 1.0f)
		v = 1.0f;
	*out = v;
}

class Rva00699180Owner
{
public:
	void refreshPair(int a, int b);
	void refreshAll();
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

void Rva00699180Owner::refreshAll()
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 2; ++j)
			refreshPair(i, j);
	}
}

void Rva00699180Owner::setVolumes(float volume, unsigned char flags)
{
	if (flags & 1)
	{
		m_base[4] = volume;
		m_base[5] = volume;
		for (int i = 0; i < 2; ++i)
			refreshPair(2, i);
	}
	if (flags & 2)
	{
		m_base[0] = volume;
		refreshPair(0, 0);
	}
	if (flags & 4)
	{
		m_base[1] = volume;
		refreshPair(0, 1);
	}
	if (flags & 8)
	{
		m_base[2] = volume;
		m_base[8] = volume;
		m_base[3] = volume;
		m_base[9] = volume;
		for (int i = 0; i < 2; ++i)
			refreshPair(1, i);
		for (int i = 0; i < 2; ++i)
			refreshPair(4, i);
	}
	if (flags & 0x10)
	{
		m_base[6] = volume;
		m_base[7] = volume;
		for (int i = 0; i < 2; ++i)
			refreshPair(3, i);
	}
}

// Retail 0x006994C0 updates one product channel, then its two output pairs.
// The receiver layout is shared by the matched productClamp and refreshPair bodies.
class Rva006994C0Owner {
public:
    void recomputeProductChannel(int index);
};

void Rva006994C0Owner::recomputeProductChannel(int index)
{
    ((Rva00699430Owner *)this)->productClamp(index);
    for (int i = 0; i < 2; ++i) {
        ((Rva00699180Owner *)this)->refreshPair(index, i);
    }
}
