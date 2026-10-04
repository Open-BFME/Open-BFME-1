// Rva00606A80Member copy constructor, retail 0x00606A80 (178 bytes).
// The caller at 0x006089C0 reaches this body through ILT 0x0001FF64.

class AudioEventRTS
{
public:
	char m_body[0x70];
};

// The audio event copy constructor is reached through retail ILT 0x00047B27.
extern void j_00047b27(void);

// Each item is a DynamicAudioEventRTS; the TUs that define that class emit its vftable.
extern "C" int __identifier("??_7DynamicAudioEventRTS@@6B@");

struct Rva00606A80Item
{
	void *m_vft;
	AudioEventRTS m_audio;

	Rva00606A80Item(const Rva00606A80Item &other)
		: m_vft(&__identifier("??_7DynamicAudioEventRTS@@6B@"))
	{
		typedef void (AudioEventRTS::*Copy)(const AudioEventRTS &);
		union { void *address; Copy member; } call;
		call.address = (void *)j_00047b27;
		(this->m_audio.*call.member)(other.m_audio);
	}
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
