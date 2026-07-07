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

class BFMENetworkQueueItem1
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
	char *volatile m_end;
	char m_pad14[0x04];
	char *m_storageEnd;
	char m_pad1c[0x0c];
};

class BFMENetworkQueue1
{
public:
	Bool empty() const { return m_end == m_begin; }
	void popFront();

	void *volatile m_begin;
	char m_pad04[0x0c];
	char *volatile m_end;
	char m_pad14[0x04];
	char *m_storageEnd;
	char m_pad1c[0x0c];
};

class BFMENetwork
{
public:
	Bool backendHasLiveHandle();
	void destroyBackend();
	void pushQueue0(BFMENetworkQueueItem *item);
	Bool popQueue0(BFMENetworkQueueItem *item);
	void pushQueue1(BFMENetworkQueueItem1 *item);
	Bool popQueue1(BFMENetworkQueueItem1 *item);

private:
	void *m_vtable;
	BFMENetworkLock m_lock0;
	BFMENetworkLock m_lock1;
	BFMENetworkQueue m_queue0;
	BFMENetworkQueue1 m_queue1;
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

__declspec(naked) void BFMENetwork::pushQueue0(BFMENetworkQueueItem *item)
{
	__asm {
		push 0ffffffffh
		push 01043a39h
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		sub esp, 10h
		push esi
		mov esi, ecx
		push 0ffffffffh
		lea eax, [esi+4]
		push eax
		lea ecx, [esp+14h]
		__emit 0xe8
		__emit 0x36
		__emit 0xd3
		__emit 0x37
		__emit 0x00
		mov al, [esp+10h]
		test al, al
		mov dword ptr [esp+1ch], 0
		jne done
		mov ecx, [esi+2ch]
		mov eax, [esi+24h]
		add esi, 14h
		sub ecx, 210h
		cmp eax, ecx
		je slow
		mov [esp+4], eax
		mov [esp+8], eax
		test eax, eax
		mov byte ptr [esp+1ch], 1
		je fastDone
		mov edx, [esp+24h]
		push edx
		mov ecx, eax
		__emit 0xe8
		__emit 0x70
		__emit 0xae
		__emit 0x9b
		__emit 0xff
fastDone:
		add dword ptr [esi+10h], 210h
		jmp done
slow:
		mov eax, [esp+24h]
		push eax
		mov ecx, esi
		__emit 0xe8
		__emit 0xe0
		__emit 0xcb
		__emit 0x9e
		__emit 0xff
done:
		lea ecx, [esp+0ch]
		mov dword ptr [esp+1ch], 0ffffffffh
		__emit 0xe8
		__emit 0x20
		__emit 0xd3
		__emit 0x37
		__emit 0x00
		mov ecx, [esp+14h]
		pop esi
		mov fs:[0], ecx
		add esp, 1ch
		ret 4
	}
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

__declspec(naked) void BFMENetwork::pushQueue1(BFMENetworkQueueItem1 *item)
{
	__asm {
		push 0ffffffffh
		push 01043a69h
		mov eax, fs:[0]
		push eax
		mov fs:[0], esp
		sub esp, 10h
		push esi
		mov esi, ecx
		push 0ffffffffh
		lea eax, [esi+0ch]
		push eax
		lea ecx, [esp+14h]
		__emit 0xe8
		__emit 0x66
		__emit 0xd2
		__emit 0x37
		__emit 0x00
		mov al, [esp+10h]
		test al, al
		mov dword ptr [esp+1ch], 0
		jne done1
		mov ecx, [esi+54h]
		mov eax, [esi+4ch]
		add esi, 3ch
		sub ecx, 1f0h
		cmp eax, ecx
		je slow1
		mov [esp+4], eax
		mov [esp+8], eax
		test eax, eax
		mov byte ptr [esp+1ch], 1
		je fastDone1
		mov edx, [esp+24h]
		push edx
		mov ecx, eax
		__emit 0xe8
		__emit 0x5a
		__emit 0x25
		__emit 0x9c
		__emit 0xff
fastDone1:
		add dword ptr [esi+10h], 1f0h
		jmp done1
slow1:
		mov eax, [esp+24h]
		push eax
		mov ecx, esi
		__emit 0xe8
		__emit 0x79
		__emit 0xce
		__emit 0x9b
		__emit 0xff
done1:
		lea ecx, [esp+0ch]
		mov dword ptr [esp+1ch], 0ffffffffh
		__emit 0xe8
		__emit 0x50
		__emit 0xd2
		__emit 0x37
		__emit 0x00
		mov ecx, [esp+14h]
		pop esi
		mov fs:[0], ecx
		add esp, 1ch
		ret 4
	}
}

Bool BFMENetwork::popQueue1(BFMENetworkQueueItem1 *item)
{
	BFMEAutoLockRef lock(&m_lock1, 0);

	if (lock.failed()) {
		return false;
	}

	BFMENetworkQueue1 *queue = &m_queue1;
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
