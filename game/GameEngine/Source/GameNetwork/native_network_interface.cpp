// cl: /DNDEBUG /MD /GX

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(__int64 *frequency);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

class BFMENativeNetwork
{
public:
	void *construct();
	int getFramePacingStatus();
	int getFrameAdvanceCount();
	void baseConstruct();

private:
	void *m_vtable;
	unsigned int m_unknown04;
	void *m_connectionManager;
	int m_state;
	__int64 m_performanceFrequency;
	__int64 m_lastPerformanceCounter;
	__int64 m_accumulator;
	bool m_stallTimerRunning;
	char m_unknown29[3];
	unsigned int m_stallCount;
	unsigned int m_unknown30;
	bool m_flag34;
	bool m_flag35;
	char m_unknown36[2];
	int m_lastValue;
};

void *BFMENativeNetwork::construct()
{
	baseConstruct();
	m_vtable = (void *)0x0111A968;
	m_connectionManager = 0;
	m_state = 0;
	m_accumulator = 0;
	m_flag35 = false;
	QueryPerformanceFrequency(&m_performanceFrequency);
	QueryPerformanceCounter(&m_lastPerformanceCounter);
	m_flag34 = false;
	m_stallTimerRunning = false;
	m_stallCount = 0;
	m_lastValue = -1;
	return this;
}

// Vtable slot +0x3C. Returns how many logic frames the sim may advance now:
// 1 outside a network game, (frameCeiling - currentFrame + 1) when that is
// positive and the connection manager reports the frame's commands complete,
// 0 when they are not, and the non-positive allowance when starved. As packet
// router it instead consumes a fixed QueryPerformanceFrequency/5 (200ms)
// quantum, which is what pins BFME's off-host command delay.
__declspec(naked) int BFMENativeNetwork::getFrameAdvanceCount()
{
	__asm {
		sub esp, 8h
		push esi
		mov esi, ecx
		cmp dword ptr [esi+0Ch], 1h
		je active
		mov eax, 1h
		pop esi
		add esp, 8h
		ret
active:
		mov eax, dword ptr [esi]
		push edi
		mov ecx, esi
		call dword ptr [eax+8Ch]
		test al, al
		jne routerTiming
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov eax, dword ptr [ecx+3Ch]
		test eax, eax
		jne haveFrame
		pop edi
		mov eax, 1h
		pop esi
		add esp, 8h
		ret
haveFrame:
		mov al, byte ptr [esi+28h]
		test al, al
		jne stallTimerRunning
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		__emit 0A3h
		__emit 018h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov dword ptr [0x12f7718], eax
		mov byte ptr [esi+28h], 1h
stallTimerRunning:
		mov ecx, dword ptr [esi+8h]
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov edx, dword ptr [0x12f0898]
		mov eax, dword ptr [edx+3Ch]
		mov edi, dword ptr [ecx+1205Ch]
		sub edi, eax
		inc edi
		test edi, edi
		jle starved
		push 0h
		push eax
		__emit 0E8h
		__emit 015h
		__emit 003h
		__emit 09Ch
		__emit 0FFh   // call 0x422FD
		test al, al
		jne allowAdvance
		mov eax, dword ptr [esi]
		push 0h
		mov ecx, esi
		call dword ptr [eax+24h]
		pop edi
		xor eax, eax
		pop esi
		add esp, 8h
		ret
allowAdvance:
		mov eax, edi
		pop edi
		mov byte ptr [esi+28h], 0h
		pop esi
		add esp, 8h
		ret
starved:
		__emit 03Bh
		__emit 005h
		__emit 028h
		__emit 077h
		__emit 02Fh
		__emit 001h   // cmp eax, dword ptr [0x12f7728]
		je sameStallFrame
		inc dword ptr [esi+2Ch]
		__emit 08Bh
		__emit 00Dh
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h   // mov ecx, dword ptr [0x12f0898]
		mov edx, dword ptr [ecx+3Ch]
		__emit 089h
		__emit 015h
		__emit 028h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov dword ptr [0x12f7728], edx
sameStallFrame:
		mov eax, edi
		pop edi
		pop esi
		add esp, 8h
		ret
routerTiming:
		mov ecx, dword ptr [esi+8h]
		__emit 0E8h
		__emit 064h
		__emit 082h
		__emit 09Bh
		__emit 0FFh   // call 0x3A297
		test al, al
		je consumeQuantum
		xor eax, eax
		pop edi
		mov dword ptr [esi+20h], eax
		mov dword ptr [esi+24h], eax
		pop esi
		add esp, 8h
		ret
consumeQuantum:
		push ebx
		push ebp
		lea eax, dword ptr [esp+10h]
		push eax
		__emit 0FFh
		__emit 015h
		__emit 0B4h
		__emit 08Eh
		__emit 035h
		__emit 001h   // call dword ptr [0x1358eb4]
		mov eax, dword ptr [esp+10h]
		mov ebp, dword ptr [esi+18h]
		mov ecx, dword ptr [esp+14h]
		mov ebx, dword ptr [esi+1Ch]
		mov edx, eax
		sub edx, ebp
		mov ebp, dword ptr [esi+20h]
		mov edi, ecx
		sbb edi, ebx
		mov ebx, dword ptr [esi+24h]
		add ebp, edx
		adc ebx, edi
		push 0h
		push 5h
		mov dword ptr [esi+24h], ebx
		mov ebx, dword ptr [esi+14h]
		mov dword ptr [esi+20h], ebp
		mov ebp, dword ptr [esi+10h]
		push ebx
		push ebp
		mov dword ptr [esi+18h], eax
		mov dword ptr [esi+1Ch], ecx
		__emit 0E8h
		__emit 051h
		__emit 050h
		__emit 037h
		__emit 000h   // call 0x9F70E0
		mov ecx, dword ptr [esi+24h]
		cmp ecx, edx
		mov edi, dword ptr [esi+20h]
		jg quantumElapsed
		jl quantumPending
		cmp edi, eax
		jae quantumElapsed
quantumPending:
		pop ebp
		pop ebx
		pop edi
		xor eax, eax
		pop esi
		add esp, 8h
		ret
quantumElapsed:
		sub edi, eax
		sbb ecx, edx
		mov dword ptr [esi+20h], edi
		xor edi, edi
		push edi
		push 2h
		push ebx
		push ebp
		mov dword ptr [esi+24h], ecx
		__emit 0E8h
		__emit 051h
		__emit 051h
		__emit 037h
		__emit 000h   // call 0x9F7210
		mov ecx, dword ptr [esi+24h]
		cmp ecx, edx
		jl noBacklog
		jg clampBacklog
		mov edx, dword ptr [esi+20h]
		cmp edx, eax
		jbe noBacklog
clampBacklog:
		__emit 0FFh
		__emit 005h
		__emit 024h
		__emit 077h
		__emit 02Fh
		__emit 001h   // inc dword ptr [0x12f7724]
		mov dword ptr [esi+20h], edi
		mov dword ptr [esi+24h], edi
		jmp stampTime
noBacklog:
		__emit 089h
		__emit 03Dh
		__emit 024h
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov dword ptr [0x12f7724], edi
stampTime:
		__emit 0FFh
		__emit 015h
		__emit 044h
		__emit 095h
		__emit 035h
		__emit 001h   // call dword ptr [0x1359544]
		pop ebp
		pop ebx
		pop edi
		__emit 0A3h
		__emit 01Ch
		__emit 077h
		__emit 02Fh
		__emit 001h   // mov dword ptr [0x12f771c], eax
		mov eax, 1h
		pop esi
		add esp, 8h
		ret
	}
}

__declspec(naked) int BFMENativeNetwork::getFramePacingStatus()
{
	__asm {
		sub esp, 10h
		push esi
		mov esi, ecx
		cmp dword ptr [esi+0Ch], 1
		je active
		mov eax, 1
		pop esi
		add esp, 10h
		ret
active:
		mov eax, dword ptr [esi]
		mov ecx, esi
		call dword ptr [eax+8Ch]
		test al, al
		jne timerPath
		mov ecx, dword ptr [esi+08h]
		__emit 08Bh
		__emit 015h
		__emit 098h
		__emit 008h
		__emit 02Fh
		__emit 001h
		mov esi, dword ptr [edx+3Ch]
		mov eax, dword ptr [ecx+1205Ch]
		sub eax, esi
		inc eax
		pop esi
		add esp, 10h
		ret
timerPath:
		push ebx
		push edi
		lea eax, [esp+0Ch]
		push eax
		__emit 0FFh
		__emit 015h
		__emit 0B4h
		__emit 08Eh
		__emit 035h
		__emit 001h
		mov eax, dword ptr [esp+0Ch]
		mov ecx, dword ptr [esi+18h]
		mov ebx, dword ptr [esi+1Ch]
		mov edx, eax
		sub edx, ecx
		mov ecx, dword ptr [esp+10h]
		mov edi, ecx
		sbb edi, ebx
		mov ebx, dword ptr [esi+20h]
		push 0
		add ebx, edx
		mov edx, dword ptr [esi+24h]
		mov dword ptr [esi+18h], eax
		mov eax, dword ptr [esi+14h]
		push 5
		mov dword ptr [esi+1Ch], ecx
		mov ecx, dword ptr [esi+10h]
		push eax
		adc edx, edi
		push ecx
		mov dword ptr [esi+20h], ebx
		mov dword ptr [esi+24h], edx
		__emit 0E8h
		__emit 0F8h
		__emit 04Eh
		__emit 037h
		__emit 000h
		mov esi, dword ptr [esi+24h]
		cmp esi, edx
		mov ecx, ebx
		pop edi
		mov dword ptr [esp+10h], eax
		mov dword ptr [esp+14h], edx
		mov dword ptr [esp+08h], ecx
		mov dword ptr [esp+0Ch], esi
		pop ebx
		jg readyEnough
		jl notReady
		cmp ecx, eax
		jae readyEnough
notReady:
		xor eax, eax
		pop esi
		add esp, 10h
		ret
readyEnough:
		fild qword ptr [esp+04h]
		fild qword ptr [esp+0Ch]
		__emit 0D8h
		__emit 00Dh
		__emit 06Ch
		__emit 0B4h
		__emit 009h
		__emit 001h
		fcompp
		fnstsw ax
		test ah, 41h
		mov eax, 1
		je done
		mov eax, 2
done:
		pop esi
		add esp, 10h
		ret
	}
}
