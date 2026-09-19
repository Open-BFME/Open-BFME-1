// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of the SpecialAbilityUpdateModuleData
// destructor. The four AudioEventRTS members sit at +0x08, +0x78, +0xE8 and
// +0x158. The reference and four string members explain the remaining cleanup.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *lpAddend);

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

class RefCountedThing
{
public:
	virtual ~RefCountedThing();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0) {
			delete this;
		}
	}

	long m_refCount;
};

class ThingRef
{
public:
	~ThingRef()
	{
		if (m_ptr) {
			m_ptr->Release_Ref();
		}
	}

private:
	RefCountedThing *m_ptr;
};

class AudioEventRTS
{
public:
	~AudioEventRTS();

private:
	unsigned char m_data[0x70];
};

class SpecialAbilityUpdateModuleDataBase
{
public:
	virtual ~SpecialAbilityUpdateModuleDataBase() {}

private:
	unsigned int m_word04;
};

class SpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleDataBase
{
public:
	virtual ~SpecialAbilityUpdateModuleData();

private:
	AudioEventRTS m_packSound;
	AudioEventRTS m_unpackSound;
	AudioEventRTS m_prepSoundLoop;
	AudioEventRTS m_triggerSound;
	unsigned char m_gap0[0x0c];
	ThingRef m_ref;
	unsigned char m_gap1[0x08];
	BFMERetailAsciiString m_string0;
	BFMERetailAsciiString m_string1;
	BFMERetailAsciiString m_string2;
	unsigned char m_gap2[0x64];
	BFMERetailAsciiString m_string3;
};

// ??1SpecialAbilityUpdateModuleData@@UAE@XZ
SpecialAbilityUpdateModuleData::~SpecialAbilityUpdateModuleData()
{
}
