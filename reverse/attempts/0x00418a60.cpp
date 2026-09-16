// ?cleanup@Rva00418A60@@QAEX_N@Z
// partial score=0.71 date=2026-09-16
// Scratch-only native reconstruction for retail RVA 0x00418A60 (122 bytes).
// The owner and cleanup method retain address-derived names.  The audio and
// release layouts are copied from the matched 0x00411BE0 sibling; the final
// call is the known ILT 0x000294B5 -> retail 0x00417A70 family body.
// cl: /DNDEBUG /MD /EHsc

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

typedef unsigned int UnsignedInt;

class AudioManager
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void stopAudioEvent(UnsignedInt handle);
};

extern AudioManager *TheAudio;

class Rva00418A60AudioSlot
{
public:
	unsigned char m_rva00418A60Head[0x10];
	UnsignedInt m_rva00418A60Handle;
};

class Rva00418A60Owned
{
public:
	virtual ~Rva00418A60Owned();

	long m_rva00418A60RefCount;
};

class Rva00417A70
{
public:
	void rva00417A70(void *argument);
};

#pragma comment(linker, "/alternatename:?rva00417A70@Rva00417A70@@QAEXPAX@Z=?j_000294b5@@YAXXZ")

class Rva00418A60 : public Rva00417A70
{
public:
	void cleanup(bool incoming);

private:
	unsigned char m_rva00418A60Head[0x10c];
	Rva00418A60Owned *m_rva00418A60Owned;
	unsigned char m_rva00418A60Pad[0x34];
	Rva00418A60AudioSlot *m_rva00418A60First;
	Rva00418A60AudioSlot *m_rva00418A60Second;
};

void Rva00418A60::cleanup(bool incoming)
{
	if (m_rva00418A60First)
		TheAudio->stopAudioEvent(m_rva00418A60First->m_rva00418A60Handle);

	if (m_rva00418A60Second)
		TheAudio->stopAudioEvent(m_rva00418A60Second->m_rva00418A60Handle);

	Rva00418A60Owned *owned = m_rva00418A60Owned;
	if (owned)
	{
		if (InterlockedDecrement(&owned->m_rva00418A60RefCount) <= 0)
		{
			if (owned)
				delete owned;
		}
		m_rva00418A60Owned = 0;
	}

	if (incoming)
		rva00417A70(0);
}
