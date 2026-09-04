// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
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
