extern "C" void *bfmeVftTF[];

class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int wait);
		~LockClass();

		unsigned char m_bfmeBodyTF[8];
	};

	unsigned char m_bfmeBodyTF[8];
};

class ThreadClass
{
public:
	ThreadClass(const char *name);

	void *volatile m_bfmeVftTF;
	unsigned char m_bfmeBodyTF[0x4c];
};

class BfmeThreadTF : public ThreadClass
{
public:
	__forceinline BfmeThreadTF(MutexClass *mutex) : ThreadClass(0)
	{
		m_bfmeVftTF = bfmeVftTF;

		m_bfmeMutexTF = mutex;
	}

	MutexClass *m_bfmeMutexTF;
};

typedef void (__fastcall *BfmeRunTF)(BfmeThreadTF *self);

class BfmeHostTF
{
public:
	virtual void bfmeSlot00TF();
	virtual void bfmeSlot01TF();
	virtual void bfmeSlot02TF();
	virtual void bfmeSlot03TF();
	virtual void bfmeSlot04TF();
	virtual void bfmeSlot05TF();
	virtual void bfmeSlot06TF();
	virtual void bfmeSlot07TF();
	virtual void bfmeSlot08TF();
	virtual void bfmeSlot09TF();
	virtual void bfmePrepareTF();

	void bfmeStartTF();

	unsigned char m_bfmeHeadTF[0x6c];
	BfmeThreadTF *m_bfmeThreadTF;
	MutexClass m_bfmeMutexTF;
	MutexClass::LockClass *m_bfmeLockTF;
};

void BfmeHostTF::bfmeStartTF()
{
	bfmePrepareTF();

	MutexClass::LockClass *lock = new MutexClass::LockClass(m_bfmeMutexTF, -1);

	if (lock != m_bfmeLockTF)
	{
		delete m_bfmeLockTF;

		m_bfmeLockTF = lock;
	}

	m_bfmeThreadTF = new BfmeThreadTF(&m_bfmeMutexTF);

	((BfmeRunTF *)m_bfmeThreadTF->m_bfmeVftTF)[1](m_bfmeThreadTF);
}
