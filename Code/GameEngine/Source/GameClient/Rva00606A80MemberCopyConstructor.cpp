// Rva00606A80Member copy constructor, retail 0x00606A80 (178 bytes).
// The caller at 0x006089C0 reaches this body through ILT 0x0001FF64.

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &);
	~AudioEventRTS();
	char m_body[0x70];
};

#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABV0@@Z=?j_00047b27@@YAXXZ")

struct Rva00606A80Item
{
	virtual void Slot();
	AudioEventRTS m_audio;
};

struct Rva00606A80Member
{
	Rva00606A80Item *m_items[0x6D];

	Rva00606A80Member(const Rva00606A80Member &);
};

Rva00606A80Member::Rva00606A80Member(const Rva00606A80Member &other)
{
	for (int i = 0; i < 0x6D; ++i)
	{
		if (other.m_items[i])
			m_items[i] = new Rva00606A80Item(*other.m_items[i]);
		else
			m_items[i] = 0;
	}
}
