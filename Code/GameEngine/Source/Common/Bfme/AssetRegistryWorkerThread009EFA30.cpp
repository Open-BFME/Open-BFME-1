// ?Worker_Thread_009EFA30@AssetRegistry@@QAEXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// The worker thread of the registry g_theAssetRegistry (0x0134FAAC) points
// at. The landed constructor ??0Gen_dtor_009eb9e0@@QAE@XZ starts it with
// _beginthread(0x009EFBE0, 0, this), and 0x009EFBE0 is the two-instruction
// proc that loads its argument into ECX and tail-jumps here. Layout from that
// size-checked constructor: thread handle +0x00, +0x04 (here the thread id),
// the bool at +0x08 the loop runs until, the lock at +0x60, the seven deques
// at +0x78 and the bool at +0x1EC.
//
// Each pass sets the flag 0x0134FAA8 that Q1Receiver0134FAAC::m009EC9A0
// clears and spins on, sleeps 100 ms while +0x1EC is clear, and otherwise
// services deques 1 and 5: under the lock it takes the front entry and marks
// its state byte 8, calls virtual slot +0x08 (deque 1) or +0x18 (deque 5)
// outside the lock, then under the lock restores the state, pops the entry,
// advances the state and appends the entry to the deque its new state
// selects. It sleeps 1 ms when neither deque had work.
//
// The entry's +4 word is written as a whole-word volatile read-modify-write
// (the state byte is bits 16-23; the landed AssetReference bumps the low
// sixteen bits), while retail reads the deque index back as the byte at +6,
// so the entry carries both views. The deque element is named for the
// push_back aux body it reaches, 0x009EF0D0. The address token stays in the
// method name: nothing names this body beyond what it does.

#define _STLP_USE_STATIC_LIB 1

#include <deque>
#include <windows.h>

class Rva009EF0D0Element
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();

	union
	{
		volatile unsigned int m_word;
		struct
		{
			volatile unsigned int m_refCount : 16;
			volatile unsigned int m_state : 8;
			volatile unsigned int m_bits : 8;
		};
		struct
		{
			unsigned short m_refCountBytes;
			unsigned char m_stateByte;
			unsigned char m_bitsByte;
		};
	};
};

typedef _STL::deque<Rva009EF0D0Element *> AssetQueue;

extern volatile bool g_q1Flag0134FAA8;
void setFPMode();

class AssetRegistry
{
public:
	void Worker_Thread_009EFA30();

private:
	unsigned int m_thread;
	unsigned int m_threadId;
	bool m_flag08;
	unsigned char m_unmodelled_009[0x57];
	CRITICAL_SECTION m_lock60;
	AssetQueue m_deques78[7];
	unsigned char m_unmodelled_190[0x5c];
	bool m_flag1ec;
};

typedef char AssetRegistryWorkerLayoutCheck[
	sizeof(AssetRegistry) == 0x1f0 ? 1 : -1];

void AssetRegistry::Worker_Thread_009EFA30()
{
	m_threadId = GetCurrentThreadId();
	while (!m_flag08)
	{
		bool enabled = m_flag1ec;
		g_q1Flag0134FAA8 = true;
		if (!enabled)
		{
			Sleep(100);
			continue;
		}

		bool worked = false;
		for (int state = 1; state <= 5; state += 4)
		{
			if (m_deques78[state].empty())
				continue;

			EnterCriticalSection(&m_lock60);
			if (m_deques78[state].empty())
			{
				LeaveCriticalSection(&m_lock60);
				continue;
			}
			Rva009EF0D0Element *asset = m_deques78[state].front();
			asset->m_state = 8;
			LeaveCriticalSection(&m_lock60);

			worked = true;
			setFPMode();
			switch (state)
			{
			case 1:
				asset->slot08();
				break;
			case 5:
				asset->slot18();
				break;
			}

			EnterCriticalSection(&m_lock60);
			asset->m_state = state;
			m_deques78[state].pop_front();
			++asset->m_state;
			m_deques78[asset->m_stateByte].push_back(asset);
			LeaveCriticalSection(&m_lock60);
		}

		if (!worked)
			Sleep(1);
	}
}
