// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Clamp float into [0,1], store at +0x98, refresh 6x2 pairs via stdcall helper.

void __stdcall refreshPair(int a, int b);

class Rva00699850Owner
{
public:
	void setVolume(float volume);

	char m_pad[0x98];
	float m_vol;
};

void Rva00699850Owner::setVolume(float volume)
{
	float v;
	if (volume < 0.0f)
		v = 0.0f;
	else if (volume > 1.0f)
		v = 1.0f;
	else
		v = volume;
	m_vol = v;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 2; ++j)
			refreshPair(i, j);
	}
}
