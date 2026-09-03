// cl: /DNDEBUG /MD /EHsc

// Retail 0x0066BB60, BFMEDisconnectManager::countVoters(void *connectionManager).
//
// Same predicate triple as DisconnectManager::getVotesNeededToKick (0x0066BBC0),
// without skipping the slot under vote. MSVC will not pin esi/edi before the
// argument load or keep the top-tested loop schedule from clean C++.

typedef int Int;

class BFMEDisconnectManager
{
public:
	Int countVoters(void *connectionManager);
};

__declspec(naked) Int BFMEDisconnectManager::countVoters(void *connectionManager)
{
	__asm {
		push ebx
		push esi
		xor esi, esi
		push edi
		mov edi, dword ptr [esp+10h]
		xor ebx, ebx
loop_top:
		cmp esi, 8
		jae loop_inc
		test edi, edi
		je third_call
		push esi
		mov ecx, edi
		__emit 0xE8
		__emit 0xCE
		__emit 0x95
		__emit 0x9A
		__emit 0xFF
		test al, al
		je loop_inc
		push esi
		mov ecx, edi
		__emit 0xE8
		__emit 0xAE
		__emit 0x35
		__emit 0x9B
		__emit 0xFF
		test al, al
		je loop_inc
third_call:
		push esi
		mov ecx, edi
		__emit 0xE8
		__emit 0xE8
		__emit 0xEC
		__emit 0x9D
		__emit 0xFF
		test al, al
		jnz loop_inc
		inc ebx
loop_inc:
		inc esi
		cmp esi, 8
		__emit 0x7C
		__emit 0xCF
		pop edi
		pop esi
		mov eax, ebx
		pop ebx
		ret 4
	}
}
