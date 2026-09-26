// cl: /DNDEBUG /MD /EHsc
//
// Neutral address-derived owner for retail 0x003CC780.  The direct caller is
// the Elem60 STLport copy helper at 0x003CD920 (also reached by the parking
// vector family), but the generated pair spelling does not prove a semantic
// record name.  Retail copies a 0x3c-byte record and deep-copies its optional
// +0x0c subobject, a 0x74-byte object whose +0x04 member is AudioEventRTS.

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &other);

private:
	unsigned char m_data[0x70];
};

#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABV0@@Z=?j_00047b27@@YAXXZ")

// This is the already-pinned retail table installed by the neighboring
// BTB/TD constructor family.  Keeping it as data avoids emitting a synthetic
// vtable while retaining the exact DIR32 relocation in the copy constructor.
extern "C" unsigned char bfmeVftBTB[];

struct Rva003CC780OwnedAudio
{
	void *m_vft;
	AudioEventRTS m_audio;

	Rva003CC780OwnedAudio(const Rva003CC780OwnedAudio &other)
		: m_vft(bfmeVftBTB), m_audio(other.m_audio)
	{
	}
};

struct Rva003CC780Record
{
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	Rva003CC780OwnedAudio *m_ownedAudio;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2c;
	unsigned int m_30;
	unsigned int m_34;
	unsigned char m_38;
	unsigned char m_39;

	Rva003CC780Record(const Rva003CC780Record &other);
};

// ??0Rva003CC780Record@@QAE@ABU0@@Z
Rva003CC780Record::Rva003CC780Record(const Rva003CC780Record &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_30 = other.m_30;
	m_34 = other.m_34;
	m_38 = other.m_38;
	m_39 = other.m_39;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1c = other.m_1c;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2c = other.m_2c;
	if (other.m_ownedAudio == 0)
		m_ownedAudio = 0;
	else
		m_ownedAudio = new Rva003CC780OwnedAudio(*other.m_ownedAudio);
}
