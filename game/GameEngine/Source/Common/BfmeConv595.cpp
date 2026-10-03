typedef bool Bool;

class BFMENetworkLock;

class BFMEAutoLockRef
{
public:
	BFMEAutoLockRef(BFMENetworkLock *lock, unsigned int timeout);
	__declspec(noinline) ~BFMEAutoLockRef();
	Bool failed() const { return m_failed; }

private:
	BFMENetworkLock *m_lock;
	Bool m_failed;
};

class BfmeRefCHA;

class BfmeThingCHA
{
public:
	void bfmeGoCHA(BfmeRefCHA *what);
	BfmeRefCHA *m_bfmeRef;
};

void __cdecl operator delete(void *what);

void BfmeThingCHA::bfmeGoCHA(BfmeRefCHA *what)
{
	BfmeRefCHA *cur = m_bfmeRef;
	if (what != cur)
	{
		if (cur != 0)
		{
			reinterpret_cast<BFMEAutoLockRef *>(cur)->~BFMEAutoLockRef();
			::operator delete(cur);
		}
		m_bfmeRef = what;
	}
}
