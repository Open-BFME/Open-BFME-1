// Releases two audio handles then drops the referenced object at retail RVA 0x00087C30.
// cl: /DNDEBUG /MD

typedef unsigned int AudioHandle;
typedef long Long;

class AudioManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3c();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void removeAudioEvent(AudioHandle handle);
};

extern AudioManager *TheAudio;

extern "C" __declspec(dllimport) Long __stdcall InterlockedDecrement(Long volatile *addend);

class RefTarget
{
public:
	virtual ~RefTarget();
	Long m_refCount;
};

class Gen00087C30_00088480
{
public:
	void gen00087C30();
	void gen00088480();

private:
	char m_pad[0x54];
	AudioHandle m_handleA;
	AudioHandle m_handleB;
	RefTarget *m_ptr;
};

void Gen00087C30_00088480::gen00087C30()
{
	if (TheAudio)
	{
		if (m_handleA >= 5)
		{
			TheAudio->removeAudioEvent(m_handleA);
			m_handleA = 1;
		}
		if (m_handleB >= 5)
		{
			TheAudio->removeAudioEvent(m_handleB);
			m_handleB = 1;
		}
	}

	if (m_ptr)
	{
		RefTarget *p = m_ptr;
		if (InterlockedDecrement(&p->m_refCount) <= 0)
			delete p;
		m_ptr = 0;
	}
}
