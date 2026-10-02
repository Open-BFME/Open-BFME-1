// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME GameSpyPeerMessageQueue::startThread at retail 0x0064D780.

#include "mutex.h"

class PeerThreadClass;

class BFMENetworkLock
{
public:
	void *m_handle;
	unsigned int m_refCount;
};

class BFMEPeerThreadView
{
public:
	BFMEPeerThreadView(BFMENetworkLock *lock);
	virtual ~BFMEPeerThreadView();
	virtual void Execute();
	virtual void Thread_Function();

private:
	char m_padding[0x3e8];
};

class GameSpyPeerMessageQueue
{
public:
	virtual void startThread();

private:
	char m_prefix[0x60];
	PeerThreadClass *m_thread;
	unsigned int m_serialAuth;
	BFMENetworkLock m_lock;
	MutexClass::LockClass *m_lockRef;
};

void GameSpyPeerMessageQueue::startThread()
{
	if (m_thread)
		return;

	MutexClass::LockClass *lock_ref = new MutexClass::LockClass(
		*reinterpret_cast<MutexClass *>(&m_lock), -1);
	if (lock_ref != m_lockRef)
	{
		if (m_lockRef)
			delete m_lockRef;
		m_lockRef = lock_ref;
	}

	BFMEPeerThreadView *thread = new BFMEPeerThreadView(&m_lock);
	m_thread = reinterpret_cast<PeerThreadClass *>(thread);
	thread->Execute();
}
