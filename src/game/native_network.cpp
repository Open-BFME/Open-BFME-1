// cl: /DNDEBUG /MD /GX

typedef bool Bool;

class BFMENetworkBackend
{
public:
	virtual ~BFMENetworkBackend();
	__declspec(noinline) Bool hasLiveHandle();
	__declspec(noinline) void closeLiveHandle();

private:
	char m_pad[0x40];
	void *m_auxHandle;
	void *m_liveHandle;
};

class BFMENetworkLock
{
public:
	void *m_handle;
	int m_refCount;
};

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

class BFMENetworkQueueItem
{
public:
	void copyFromQueueNode(void *node);
};

class BFMENetworkQueue
{
public:
	Bool empty() const { return m_end == m_begin; }
	void popFront();

	void *volatile m_begin;
	char m_pad04[0x0c];
	void *volatile m_end;
	char m_pad14[0x14];
};

class BFMENetwork
{
public:
	Bool backendHasLiveHandle();
	void destroyBackend();
	Bool popQueue0(BFMENetworkQueueItem *item);

private:
	void *m_vtable;
	BFMENetworkLock m_lock0;
	BFMENetworkLock m_lock1;
	BFMENetworkQueue m_queue0;
	BFMENetworkQueue m_queue1;
	BFMENetworkBackend *m_backend;
	char m_pad2[0x3c];
	BFMEAutoLockRef *m_backendLockRef;
};

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

__declspec(noinline) Bool BFMENetworkBackend::hasLiveHandle()
{
	void *liveHandle = m_liveHandle;
	return liveHandle != 0;
}

__declspec(noinline) void BFMENetworkBackend::closeLiveHandle()
{
	if (m_liveHandle) {
		WaitForSingleObject(m_liveHandle, 0xffffffff);
		m_liveHandle = 0;
		m_auxHandle = 0;
	}
}

Bool BFMENetwork::backendHasLiveHandle()
{
	if (m_backend) {
		return m_backend->hasLiveHandle();
	}
	return false;
}

void BFMENetwork::destroyBackend()
{
	if (m_backend) {
		if (m_backendLockRef) {
			delete m_backendLockRef;
		}
		BFMENetworkBackend *volatile *backendSlot = &m_backend;
		m_backendLockRef = 0;
		(*backendSlot)->closeLiveHandle();
		if (m_backend) {
			delete m_backend;
		}
	}
	m_backend = 0;
}

Bool BFMENetwork::popQueue0(BFMENetworkQueueItem *item)
{
	BFMEAutoLockRef lock(&m_lock0, 2);

	if (lock.failed()) {
		return false;
	}

	BFMENetworkQueue *queue = &m_queue0;
	if (queue->empty()) {
		return false;
	}

	void *node = queue->m_begin;
	item->copyFromQueueNode(node);
	queue->popFront();
	return true;
}

__declspec(noinline) BFMEAutoLockRef::~BFMEAutoLockRef()
{
	if (!m_failed) {
		BFMENetworkLock *lock = m_lock;
		--lock->m_refCount;
		ReleaseMutex(lock->m_handle);
	}
}
