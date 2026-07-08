// cl: /DNDEBUG /MD /GX

class BFMENativeNetwork
{
public:
	void *construct();
};

__declspec(naked) void *BFMENativeNetwork::construct()
{
	__asm {
		push ebx
		push esi
		mov esi, ecx
		__emit 0E8h
		__emit 077h
		__emit 001h
		__emit 032h
		__emit 000h
		xor ebx, ebx
		lea eax, [esi+10h]
		push eax
		mov dword ptr [esi], 0111A968h
		mov dword ptr [esi+08h], ebx
		mov dword ptr [esi+0Ch], ebx
		mov dword ptr [esi+20h], ebx
		mov dword ptr [esi+24h], ebx
		mov byte ptr [esi+35h], bl
		__emit 0FFh
		__emit 015h
		__emit 0B8h
		__emit 08Eh
		__emit 035h
		__emit 001h
		lea ecx, [esi+18h]
		push ecx
		__emit 0FFh
		__emit 015h
		__emit 0B4h
		__emit 08Eh
		__emit 035h
		__emit 001h
		mov byte ptr [esi+34h], bl
		mov byte ptr [esi+28h], bl
		mov dword ptr [esi+2Ch], ebx
		mov dword ptr [esi+38h], 0FFFFFFFFh
		mov eax, esi
		pop esi
		pop ebx
		ret
	}
}
