// cl: /DNDEBUG /MD /GX /Od /GZ /GS

#define _DLL
#include <string.h>

// EA's DirtySock CommUDP transport, which BFME uses for its GameSpy/online
// traffic. It has no counterpart in the vendored Zero Hour reference, and no
// __FILE__ string for it survives in the executable, so the directory name here
// is inferred from the module prefixes retail logs -- commudp, commtcp,
// protoadvt, NetGameUtil -- and from the sibling EA middleware that already
// lives under Code/Libraries/Source (Compression/EAC). Move it if better
// evidence turns up; only the `source` column of these rows has to follow.
//
// The surviving log strings establish the named entry points; the address-
// derived Rva helpers are retained by their retail RVAs and call graph. They
// are declared extern "C" because DirtySock is a C library.
//
// The lockstep path does not run through here -- that is SAGE's own udp.cpp.

extern "C" {
	int CommUDPWrite(void *ref, void *packet);
	int CommUDPConnect(void *ref, const char *addr, int bind, int peer);
	int CommUDPResolve(void *ref, const char *addr, char *buffer, int length, char divider);
	int Rva007FD920(void *socket, const void *data, int length, int flags, void *address, int addressLength);
	unsigned int Rva007FEA00();
	int Rva007FFDD0(unsigned int *address, int *port, int *extra, const char *text);
	void *Rva007FD2D0(int family, int type, int protocol);
	int Rva007FD510(void *socket, const void *address, int addressLength);
	void Rva007FD3F0(void *socket);
	void Rva00818FF0(void *ref, const char *text);
	int Rva00819590(void *ref, void *socket, const void *peerAddress);
	void Rva007FEBD0(void *lock);
	void Rva007FECB0(void *lock);
	void Rva00817640(void *ref);
	int Rva00817B30(unsigned int tick);
}

extern char g_Rva0130AF38Lock[4];
extern int g_Rva0130AD08Count;

int Rva007FE780Printf(const char *format, ...);

// Always fails: it logs "CommUDPResolve: Resolve functionality not supported by
// CommUDP" and returns the error.
int CommUDPResolve(void *ref, const char *addr, char *buffer, int length, char divider)
{
	Rva007FE780Printf("CommUDPResolve: Resolve functionality not supported by CommUDP\n");
	return -1;
}

// Hands a datagram to the socket layer, logging "CommUDPWrite: SocketSendto
// returned %d" on the way out.
int CommUDPWrite(void *ref, void *packet)
{
	int result;
	int packetLength = *(int *)packet + 8;
	result = Rva007FD920(*(void **)((char *)ref + 0x7C),
	                     (char *)packet + 8, packetLength, 0,
	                     (char *)ref + 0x80, 0x10);
	if (result == packetLength) {
		*(unsigned int *)((char *)ref + 0xD8) = Rva007FEA00();
		*(int *)((char *)ref + 0x5C) += packetLength;
		++*(int *)((char *)ref + 0x64);
		if (*(int *)((char *)packet + 8) != 6) {
			*(int *)((char *)ref + 0xB4) = 0;
		}
	} else {
		Rva007FE780Printf("CommUDPWrite: SocketSendto returned %d\n", result);
		*(int *)((char *)ref + 0xD4) = result;
		result = -1;
	}
	return result;
}

// Opens the port. Logs "CommUdpConnect: addr=%08x, bind=%d, peer=%d
// connident=0x%08x" on entry and "CommUDPConnect: bind to %d failed with %d"
// when the bind is refused, then retries with port 0.
int CommUDPConnect(void *ref, const char *addr, int bind, int peer)
{
	int result;
	int peerPort;
	int bindPort;
	unsigned int address;
	void *socket;
	unsigned char bindAddress[0x10];
	unsigned char peerAddress[0x10];
	unsigned int temp;

	*(unsigned short *)&peerAddress[0] = 2;
	*(unsigned short *)&peerAddress[2] = 0;
	*(unsigned int *)&peerAddress[4] = 0;
	*(unsigned int *)&peerAddress[8] = 0;
	*(unsigned int *)&peerAddress[12] = 0;
	*(unsigned short *)&bindAddress[0] = 2;
	*(unsigned short *)&bindAddress[2] = 0;
	*(unsigned int *)&bindAddress[4] = 0;
	*(unsigned int *)&bindAddress[8] = 0;
	*(unsigned int *)&bindAddress[12] = 0;
	result = Rva007FFDD0(&address, &bindPort, &peerPort, addr);
	if ((result & 3) != 3) {
		return -3;
	}
	if (peerPort == 0) {
		peerPort = bindPort;
		++bindPort;
	}
	Rva00818FF0(ref, addr);
	Rva007FE780Printf("CommUdpConnect: addr=%08x, bind=%d, peer=%d connident=0x%08x\n",
	                   address, bindPort, peerPort, *(int *)((char *)ref + 0x94));
	socket = Rva007FD2D0(2, 2, 0);
	if (socket == 0) {
		return -4;
	}
	bindAddress[2] = (unsigned char)(bindPort >> 8);
	bindAddress[3] = (unsigned char)bindPort;
	result = Rva007FD510(socket, bindAddress, 0x10);
	if (result < 0) {
		Rva007FE780Printf("CommUDPConnect: bind to %d failed with %d\n", bindPort, result);
		bindAddress[2] = 0;
		bindAddress[3] = 0;
		result = Rva007FD510(socket, bindAddress, 0x10);
		Rva007FE780Printf("CommUDPConnect: bind to 0 with result %d\n", result);
	}
	if (result < 0) {
		Rva007FD3F0(socket);
		return -5;
	}
	temp = address;
	peerAddress[7] = (unsigned char)temp; temp >>= 8;
	peerAddress[6] = (unsigned char)temp; temp >>= 8;
	peerAddress[5] = (unsigned char)temp; temp >>= 8;
	peerAddress[4] = (unsigned char)temp;
	peerAddress[2] = (unsigned char)(peerPort >> 8);
	peerAddress[3] = (unsigned char)peerPort;
	*(int *)((char *)ref + 0xD4) = 0;
	return Rva00819590(ref, socket, peerAddress);
}

extern "C" {
	int CommUdpProcess();
	void CommUdpSetup(void *ref, void *packet, void *from);
	int CommUdpPoke(void *ref);
	int CommUdpListen(void *ref, const char *text);
	int CommUDPSend(void *ref, const void *buffer, int length, int flags);
	void Rva00818500(void *ref, void *from);
	int Rva00819090(void *ref, void *socket, const void *address);
}

// The CommUDP tick. Logs "CommUdpProcess: got RAW_PACKET_INIT", closes the
// connection on timeout, and handles poke packets -- including retargeting the
// peer when one arrives from an address other than the expected one.
__declspec(naked) int CommUdpProcess()
{
	__asm {
		push ebp
		mov ebp, esp
		sub esp, 44h
		push esi
		push edi
		lea edi,  [ebp-44h]
		mov ecx, 11h
		mov eax, 0CCCCCCCCh
		rep stosd
		__emit 0A1h
		__emit 0B0h
		__emit 0BDh
		__emit 02Dh
		__emit 001h   // mov eax, dword ptr [0x12dbdb0]
		mov dword ptr [ebp-4h], eax
		mov dword ptr [ebp-14h], 0h
		mov dword ptr [ebp-1Ch], 0h
		push 10h
		push 0h
		lea eax,  [ebp-30h]
		push eax
		__emit 0E8h
		__emit 05Ah
		__emit 0FAh
		__emit 01Dh
		__emit 000h   // call 0x9F75C4
		add esp, 0Ch
		__emit 0C7h
		__emit 005h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 0FFh
		__emit 0FFh
		__emit 0FFh
		__emit 0FFh   // mov dword ptr [0x130ad10], 0xffffffff
		mov dword ptr [ebp-38h], 0h
		__emit 08Bh
		__emit 00Dh
		__emit 088h
		__emit 0B1h
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130b188]
		mov dword ptr [ebp-18h], ecx
		jmp L00_817B92
L05_817B89:
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+78h]
		mov dword ptr [ebp-18h], eax
L00_817B92:
		cmp dword ptr [ebp-18h], 0h
		je L01_817C5D
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+7Ch], 0h
		je L02_817C58
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+7Ch]
		cmp eax, dword ptr [ebp-38h]
		je L02_817C58
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+7Ch]
		mov dword ptr [ebp-38h], edx
		mov dword ptr [ebp-0Ch], 10h
		lea eax,  [ebp-0Ch]
		push eax
		lea ecx,  [ebp-30h]
		push ecx
		push 0h
		push 220h
		push 130AD18h
		mov edx, dword ptr [ebp-38h]
		push edx
		__emit 0E8h
		__emit 06Bh
		__emit 05Eh
		__emit 0FEh
		__emit 0FFh   // call 0x7FDA50
		add esp, 18h
		mov dword ptr [ebp-0Ch], eax
		cmp dword ptr [ebp-0Ch], 0h
		jle L02_817C58
		mov eax, dword ptr [ebp-0Ch]
		sub eax, 8h
		__emit 0A3h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130ad10], eax
		movzx ecx, byte ptr [ebp-28h]
		shl ecx, 8h
		movzx edx, byte ptr [ebp-27h]
		or ecx, edx
		shl ecx, 8h
		movzx eax, byte ptr [ebp-26h]
		or ecx, eax
		shl ecx, 8h
		movzx edx, byte ptr [ebp-25h]
		or ecx, edx
		__emit 089h
		__emit 00Dh
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130ad14], ecx
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 001h   // cmp dword ptr [0x130ad18], 1
		jne L03_817C37
		push 12C4E3Ch
		__emit 0E8h
		__emit 04Ch
		__emit 06Bh
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
L03_817C37:
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 002h   // cmp dword ptr [0x130ad18], 2
		jne L04_817C4D
		push 12C4E64h
		__emit 0E8h
		__emit 036h
		__emit 06Bh
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
L04_817C4D:
		mov eax, dword ptr [ebp-14h]
		add eax, 1h
		mov dword ptr [ebp-14h], eax
		jmp L01_817C5D
L02_817C58:
		jmp L05_817B89
L01_817C5D:
		__emit 08Bh
		__emit 00Dh
		__emit 088h
		__emit 0B1h
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130b188]
		mov dword ptr [ebp-18h], ecx
		jmp L06_817C71
L34_817C68:
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+78h]
		mov dword ptr [ebp-18h], eax
L06_817C71:
		cmp dword ptr [ebp-18h], 0h
		je L07_818199
		__emit 0E8h
		__emit 080h
		__emit 06Dh
		__emit 0FEh
		__emit 0FFh   // call 0x7FEA00
		mov dword ptr [ebp+8h], eax
		cmp dword ptr [ebp-1Ch], 0h
		jne L08_817CC9
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ebp-38h]
		cmp edx, dword ptr [ecx+7Ch]
		jne L08_817CC9
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+90h], 3h
		jne L08_817CC9
		__emit 083h
		__emit 03Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h   // cmp dword ptr [0x130ad10], 0
		jne L08_817CC9
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 001h   // cmp dword ptr [0x130ad18], 1
		jne L08_817CC9
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+94h]
		__emit 03Bh
		__emit 015h
		__emit 01Ch
		__emit 0ADh
		__emit 030h
		__emit 001h   // cmp edx, dword ptr [0x130ad1c]
		jne L08_817CC9
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [ebp-1Ch], eax
L08_817CC9:
		__emit 083h
		__emit 03Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h   // cmp dword ptr [0x130ad10], 0
		jl L09_817F32
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+90h], 3h
		je L09_817F32
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+90h], 5h
		je L09_817F32
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp-38h]
		cmp ecx, dword ptr [eax+7Ch]
		jne L09_817F32
		lea edx,  [ebp-30h]
		push edx
		mov eax, dword ptr [ebp-18h]
		add eax, 80h
		push eax
		__emit 0E8h
		__emit 009h
		__emit 07Ah
		__emit 0FEh
		__emit 0FFh   // call 0x7FF720
		add esp, 8h
		test eax, eax
		jne L09_817F32
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+60h]
		__emit 003h
		__emit 015h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // add edx, dword ptr [0x130ad10]
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+60h], edx
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+68h]
		add edx, 1h
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+68h], edx
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 001h   // cmp dword ptr [0x130ad18], 1
		je L10_817D5E
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 002h   // cmp dword ptr [0x130ad18], 2
		je L10_817D5E
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 003h   // cmp dword ptr [0x130ad18], 3
		jne L11_817D78
L10_817D5E:
		lea ecx,  [ebp-30h]
		push ecx
		push 130AD10h
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 090h
		__emit 006h
		__emit 000h
		__emit 000h   // call 0x818400
		add esp, 0Ch
		jmp L12_817F28
L11_817D78:
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+90h], 4h
		je L13_817D89
		jmp L12_817F28
L13_817D89:
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 004h   // cmp dword ptr [0x130ad18], 4
		jne L14_817DB7
		mov ecx, dword ptr [ebp-18h]
		__emit 08Bh
		__emit 015h
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad14]
		mov dword ptr [ecx+0DCh], edx
		push 130AD10h
		mov eax, dword ptr [ebp-18h]
		push eax
		__emit 0E8h
		__emit 011h
		__emit 009h
		__emit 000h
		__emit 000h   // call 0x8186C0
		add esp, 8h
		jmp L12_817F28
L14_817DB7:
		__emit 081h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h
		__emit 000h
		__emit 000h
		__emit 010h   // cmp dword ptr [0x130ad18], 0x10000000
		jbe L15_817EF7
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+0ACh]
		mov dword ptr [ebp-3Ch], edx
		__emit 0A1h
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov eax, dword ptr [0x130ad18]
		shr eax, 1Ch
		mov dword ptr [ebp-40h], eax
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad14]
		__emit 089h
		__emit 00Dh
		__emit 064h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af64], ecx
		__emit 08Bh
		__emit 015h
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad18]
		and edx, 0FFFFFFFh
		sub edx, dword ptr [ebp-40h]
		__emit 089h
		__emit 015h
		__emit 068h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af68], edx
		__emit 0A1h
		__emit 01Ch
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov eax, dword ptr [0x130ad1c]
		__emit 0A3h
		__emit 06Ch
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af6c], eax
		mov ecx, dword ptr [ebp-18h]
		__emit 08Bh
		__emit 015h
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad14]
		mov dword ptr [ecx+0DCh], edx
		jmp L16_817E23
L22_817E1A:
		mov eax, dword ptr [ebp-40h]
		sub eax, 1h
		mov dword ptr [ebp-40h], eax
L16_817E23:
		cmp dword ptr [ebp-40h], 0h
		jl L17_817EF5
		cmp dword ptr [ebp-40h], 0h
		jle L18_817E56
		__emit 08Bh
		__emit 00Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad10]
		sub ecx, 1h
		__emit 089h
		__emit 00Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130ad10], ecx
		__emit 08Bh
		__emit 015h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad10]
		movzx eax, byte ptr [edx+130AD20h]
		__emit 0A3h
		__emit 060h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af60], eax
		jmp L19_817E62
L18_817E56:
		__emit 08Bh
		__emit 00Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad10]
		__emit 089h
		__emit 00Dh
		__emit 060h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af60], ecx
L19_817E62:
		__emit 08Bh
		__emit 015h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130ad10]
		__emit 02Bh
		__emit 015h
		__emit 060h
		__emit 0AFh
		__emit 030h
		__emit 001h   // sub edx, dword ptr [0x130af60]
		__emit 089h
		__emit 015h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130ad10], edx
		__emit 0A1h
		__emit 060h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov eax, dword ptr [0x130af60]
		push eax
		__emit 08Bh
		__emit 00Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad10]
		add ecx, 130AD20h
		push ecx
		push 130AF70h
		__emit 0E8h
		__emit 027h
		__emit 0F7h
		__emit 01Dh
		__emit 000h   // call 0x9F75B8
		add esp, 0Ch
		push 130AF60h
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 01Eh
		__emit 008h
		__emit 000h
		__emit 000h   // call 0x8186C0
		add esp, 8h
		push 130AF60h
		mov eax, dword ptr [ebp-18h]
		push eax
		__emit 0E8h
		__emit 02Dh
		__emit 009h
		__emit 000h
		__emit 000h   // call 0x8187E0
		add esp, 8h
		test eax, eax
		jge L20_817EC1
		mov dword ptr [ebp-40h], 0h
L20_817EC1:
		cmp dword ptr [ebp-40h], 0h
		jle L21_817EE1
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ebp-3Ch]
		cmp edx, dword ptr [ecx+0ACh]
		je L21_817EE1
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [eax+0ACh]
		mov dword ptr [ebp-3Ch], ecx
L21_817EE1:
		__emit 08Bh
		__emit 015h
		__emit 068h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130af68]
		add edx, 1h
		__emit 089h
		__emit 015h
		__emit 068h
		__emit 0AFh
		__emit 030h
		__emit 001h   // mov dword ptr [0x130af68], edx
		jmp L22_817E1A
L17_817EF5:
		jmp L12_817F28
L15_817EF7:
		mov eax, dword ptr [ebp-18h]
		__emit 08Bh
		__emit 00Dh
		__emit 014h
		__emit 0ADh
		__emit 030h
		__emit 001h   // mov ecx, dword ptr [0x130ad14]
		mov dword ptr [eax+0DCh], ecx
		push 130AD10h
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 0ACh
		__emit 007h
		__emit 000h
		__emit 000h   // call 0x8186C0
		add esp, 8h
		push 130AD10h
		mov eax, dword ptr [ebp-18h]
		push eax
		__emit 0E8h
		__emit 0BBh
		__emit 008h
		__emit 000h
		__emit 000h   // call 0x8187E0
		add esp, 8h
L12_817F28:
		__emit 0C7h
		__emit 005h
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 0FFh
		__emit 0FFh
		__emit 0FFh
		__emit 0FFh   // mov dword ptr [0x130ad10], 0xffffffff
L09_817F32:
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+90h], 2h
		jne L23_817F5D
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp+8h]
		sub eax, dword ptr [edx+0D8h]
		cmp eax, 3E8h
		jbe L23_817F5D
		mov ecx, dword ptr [ebp-18h]
		push ecx
		__emit 0E8h
		__emit 0C6h
		__emit 006h
		__emit 000h
		__emit 000h   // call 0x818620
		add esp, 4h
L23_817F5D:
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+90h], 4h
		jne L24_817F89
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [eax+0C8h]
		cmp edx, dword ptr [ecx+0C0h]
		je L24_817F89
		mov eax, dword ptr [ebp-18h]
		push eax
		__emit 0E8h
		__emit 0BAh
		__emit 0F6h
		__emit 0FFh
		__emit 0FFh   // call 0x817640
		add esp, 4h
L24_817F89:
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+90h], 4h
		jne L25_817FFA
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp+8h]
		sub eax, dword ptr [edx+0DCh]
		cmp eax, 1D4C0h
		jbe L25_817FFA
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ebp+8h]
		sub edx, dword ptr [ecx+0D8h]
		cmp edx, 7D0h
		jae L25_817FFA
		push 12C4E8Ch
		__emit 0E8h
		__emit 0BAh
		__emit 067h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 4h
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [eax+0D8h]
		push ecx
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+0DCh]
		push eax
		mov ecx, dword ptr [ebp+8h]
		push ecx
		push 12C4EB8h
		__emit 0E8h
		__emit 095h
		__emit 067h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 10h
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 069h
		__emit 0EFh
		__emit 0FFh
		__emit 0FFh   // call 0x816F60
		add esp, 4h
L25_817FFA:
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+90h], 3h
		jne L26_818035
		mov ecx, dword ptr [ebp-18h]
		movzx edx, word ptr [ecx+80h]
		cmp edx, 2h
		jne L26_818035
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [eax+0D8h]
		add ecx, 3E8h
		cmp dword ptr [ebp+8h], ecx
		jbe L26_818035
		mov edx, dword ptr [ebp-18h]
		push edx
		__emit 0E8h
		__emit 0EEh
		__emit 009h
		__emit 000h
		__emit 000h   // call 0x818A20
		add esp, 4h
L26_818035:
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+21Ch], 0h
		jne L27_818076
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+0E0h]
		add edx, 0FAh
		cmp dword ptr [ebp+8h], edx
		jbe L27_818076
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp+8h]
		mov dword ptr [eax+0E0h], ecx
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+21Ch]
		or eax, 4h
		mov ecx, dword ptr [ebp-18h]
		mov dword ptr [ecx+21Ch], eax
L27_818076:
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+218h], 0h
		jne L28_8180FC
		mov eax, dword ptr [ebp-18h]
		cmp dword ptr [eax+21Ch], 0h
		je L28_8180FC
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+218h]
		add edx, 1h
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+218h], edx
		mov ecx, dword ptr [ebp-18h]
		cmp dword ptr [ecx+220h], 0h
		je L29_8180D2
		mov esi, esp
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+21Ch]
		push eax
		mov ecx, dword ptr [ebp-18h]
		push ecx
		mov edx, dword ptr [ebp-18h]
		call dword ptr [edx+220h]
		add esp, 8h
		cmp esi, esp
		__emit 0E8h
		__emit 030h
		__emit 0F4h
		__emit 01Dh
		__emit 000h   // call 0x9F7502
L29_8180D2:
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+218h]
		sub edx, 1h
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+218h], edx
		mov ecx, dword ptr [ebp-18h]
		mov dword ptr [ecx+21Ch], 0h
		__emit 0E8h
		__emit 007h
		__emit 069h
		__emit 0FEh
		__emit 0FFh   // call 0x7FEA00
		mov dword ptr [ebp+8h], eax
L28_8180FC:
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+90h], 4h
		jne L30_818194
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [eax+0C8h]
		cmp edx, dword ptr [ecx+0C0h]
		jne L30_818194
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [ebp+8h]
		sub ecx, dword ptr [eax+0D8h]
		mov dword ptr [ebp-44h], ecx
		cmp dword ptr [ebp-44h], 64h
		jbe L31_818149
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [edx+0B0h]
		cmp ecx, dword ptr [eax+0ACh]
		jne L32_81817B
L31_818149:
		cmp dword ptr [ebp-44h], 64h
		jbe L33_818163
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [edx+0C0h]
		cmp ecx, dword ptr [eax+0C4h]
		jne L32_81817B
L33_818163:
		cmp dword ptr [ebp-44h], 9C4h
		ja L32_81817B
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+0B4h], 800h
		jl L30_818194
L32_81817B:
		mov eax, dword ptr [ebp-18h]
		mov dword ptr [eax+0B4h], 0h
		mov ecx, dword ptr [ebp-18h]
		push ecx
		__emit 0E8h
		__emit 03Fh
		__emit 009h
		__emit 000h
		__emit 000h   // call 0x818AD0
		add esp, 4h
L30_818194:
		jmp L34_817C68
L07_818199:
		__emit 083h
		__emit 03Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h   // cmp dword ptr [0x130ad10], 0
		jl L35_818343
		__emit 083h
		__emit 03Dh
		__emit 018h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 005h   // cmp dword ptr [0x130ad18], 5
		jne L35_818343
		movzx edx, word ptr [ebp-30h]
		cmp edx, 2h
		jne L35_818343
		movzx eax, byte ptr [ebp-2Ch]
		shl eax, 8h
		movzx ecx, byte ptr [ebp-2Bh]
		or eax, ecx
		shl eax, 8h
		movzx edx, byte ptr [ebp-2Ah]
		or eax, edx
		shl eax, 8h
		movzx ecx, byte ptr [ebp-29h]
		or eax, ecx
		push eax
		push 12C4EE0h
		__emit 0E8h
		__emit 096h
		__emit 065h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		__emit 08Bh
		__emit 015h
		__emit 088h
		__emit 0B1h
		__emit 030h
		__emit 001h   // mov edx, dword ptr [0x130b188]
		mov dword ptr [ebp-18h], edx
		jmp L36_818201
L38_8181F8:
		mov eax, dword ptr [ebp-18h]
		mov ecx, dword ptr [eax+78h]
		mov dword ptr [ebp-18h], ecx
L36_818201:
		cmp dword ptr [ebp-18h], 0h
		je L35_818343
		mov edx, dword ptr [ebp-18h]
		cmp dword ptr [edx+90h], 2h
		jne L37_81833E
		mov eax, dword ptr [ebp-18h]
		movzx ecx, word ptr [eax+80h]
		cmp ecx, 2h
		jne L37_81833E
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [edx+94h]
		__emit 03Bh
		__emit 005h
		__emit 01Ch
		__emit 0ADh
		__emit 030h
		__emit 001h   // cmp eax, dword ptr [0x130ad1c]
		jne L37_81833E
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+84h]
		shl edx, 8h
		mov eax, dword ptr [ebp-18h]
		movzx ecx, byte ptr [eax+85h]
		or edx, ecx
		shl edx, 8h
		mov eax, dword ptr [ebp-18h]
		movzx ecx, byte ptr [eax+86h]
		or edx, ecx
		shl edx, 8h
		mov eax, dword ptr [ebp-18h]
		movzx ecx, byte ptr [eax+87h]
		or edx, ecx
		push edx
		push 12C4F0Ch
		__emit 0E8h
		__emit 0FBh
		__emit 064h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 8h
		mov edx, dword ptr [ebp-18h]
		mov eax, dword ptr [ebp-38h]
		cmp eax, dword ptr [edx+7Ch]
		jne L37_81833E
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+82h]
		shl edx, 8h
		mov eax, dword ptr [ebp-18h]
		movzx ecx, byte ptr [eax+83h]
		or edx, ecx
		push edx
		mov edx, dword ptr [ebp-18h]
		movzx eax, byte ptr [edx+84h]
		shl eax, 8h
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+85h]
		or eax, edx
		shl eax, 8h
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+86h]
		or eax, edx
		shl eax, 8h
		mov ecx, dword ptr [ebp-18h]
		movzx edx, byte ptr [ecx+87h]
		or eax, edx
		push eax
		movzx eax, byte ptr [ebp-2Eh]
		shl eax, 8h
		movzx ecx, byte ptr [ebp-2Dh]
		or eax, ecx
		push eax
		movzx edx, byte ptr [ebp-2Ch]
		shl edx, 8h
		movzx eax, byte ptr [ebp-2Bh]
		or edx, eax
		shl edx, 8h
		movzx ecx, byte ptr [ebp-2Ah]
		or edx, ecx
		shl edx, 8h
		movzx eax, byte ptr [ebp-29h]
		or edx, eax
		push edx
		push 12C4F40h
		__emit 0E8h
		__emit 05Fh
		__emit 064h
		__emit 0FEh
		__emit 0FFh   // call 0x7FE780
		add esp, 14h
		push 10h
		lea ecx,  [ebp-30h]
		push ecx
		mov edx, dword ptr [ebp-18h]
		add edx, 80h
		push edx
		__emit 0E8h
		__emit 07Fh
		__emit 0F2h
		__emit 01Dh
		__emit 000h   // call 0x9F75B8
		add esp, 0Ch
		jmp L35_818343
L37_81833E:
		jmp L38_8181F8
L35_818343:
		cmp dword ptr [ebp-1Ch], 0h
		je L39_8183A3
		__emit 083h
		__emit 03Dh
		__emit 010h
		__emit 0ADh
		__emit 030h
		__emit 001h
		__emit 000h   // cmp dword ptr [0x130ad10], 0
		jne L39_8183A3
		mov eax, dword ptr [ebp-1Ch]
		mov dword ptr [ebp-18h], eax
		mov ecx, dword ptr [ebp-18h]
		mov edx, dword ptr [ecx+94h]
		__emit 03Bh
		__emit 015h
		__emit 01Ch
		__emit 0ADh
		__emit 030h
		__emit 001h   // cmp edx, dword ptr [0x130ad1c]
		jne L39_8183A3
		push 10h
		lea eax,  [ebp-30h]
		push eax
		mov ecx, dword ptr [ebp-18h]
		add ecx, 80h
		push ecx
		__emit 0E8h
		__emit 03Ah
		__emit 0F2h
		__emit 01Dh
		__emit 000h   // call 0x9F75B8
		add esp, 0Ch
		mov edx, dword ptr [ebp-18h]
		mov dword ptr [edx+90h], 4h
		lea eax,  [ebp-30h]
		push eax
		push 130AD10h
		mov ecx, dword ptr [ebp-18h]
		push ecx
		__emit 0E8h
		__emit 060h
		__emit 000h
		__emit 000h
		__emit 000h   // call 0x818400
		add esp, 0Ch
L39_8183A3:
		mov eax, dword ptr [ebp-14h]
		push edx
		mov ecx, ebp
		push eax
		__emit 08Dh
		__emit 015h
		__emit 0CFh
		__emit 083h
		__emit 0C1h
		__emit 000h   // lea edx, [0xc183cf]
		__emit 0E8h
		__emit 070h
		__emit 0F1h
		__emit 01Dh
		__emit 000h   // call 0x9F7525
		pop eax
		pop edx
		mov ecx, dword ptr [ebp-4h]
		__emit 0E8h
		__emit 035h
		__emit 0F1h
		__emit 01Dh
		__emit 000h   // call 0x9F74F4
		pop edi
		pop esi
		add esp, 44h
		cmp ebp, esp
		__emit 0E8h
		__emit 037h
		__emit 0F1h
		__emit 01Dh
		__emit 000h   // call 0x9F7502
		mov esp, ebp
		pop ebp
		ret
	}
}

// Answers an INIT with a CONN, and warns "commudp: warning - connident
// mismatch" when the connection identifier does not line up.
void CommUdpSetup(void *ref, void *packet, void *from)
{
	if (*(int *)packet != 0) {
		return;
	}

		if (*(int *)((char *)packet + 0x0C) != *(int *)((char *)ref + 0x94)) {
			Rva007FE780Printf("commudp: warning - connident mismatch\n");
			if (*(int *)((char *)packet + 8) == 1) {
				*(int *)((char *)ref + 0x90) = 5;
			}
		} else {
			*(unsigned int *)((char *)ref + 0xDC) = Rva007FEA00() - 1000;
			if (*(int *)((char *)packet + 8) == 1) {
				Rva00818500(ref, from);
				Rva007FE780Printf("CommUdpSetup: sending CONN in response to INIT\n");
				*(int *)((char *)packet + 8) = 2;
				((int (__cdecl *)(void *, void *))CommUDPWrite)(ref, packet);
			} else if (*(int *)((char *)packet + 8) == 2) {
				if (*(int *)((char *)ref + 0x90) == 2) {
					Rva00818500(ref, from);
					*(int *)((char *)ref + 0x90) = 4;
				}
			} else if (*(int *)((char *)packet + 8) == 3 &&
			           *(int *)((char *)ref + 0x90) == 4) {
				*(int *)((char *)ref + 0x90) = 5;
			}
		}
}

// Sends a poke packet to prod a peer whose address may have moved.
int CommUdpPoke(void *ref)
{
	char packet[0x228];
	Rva007FE780Printf("CommUdpPoke: sending poke packet\n");
	*(int *)&packet[0] = 0;
	*(int *)&packet[8] = 5;
	*(int *)&packet[12] = *(int *)((char *)ref + 0x94);
	return ((int (__cdecl *)(void *, void *))CommUDPWrite)(ref, &packet);
}

// Puts the socket into listening mode for an incoming CommUDP connection.
int CommUdpListen(void *ref, const char *text)
{
	int result;
	int port;
	int extra;
	unsigned int address;
	void *socket;
	unsigned char socketAddress[0x10];
	unsigned int temp;

	*(unsigned short *)&socketAddress[0] = 2;
	*(unsigned short *)&socketAddress[2] = 0;
	*(unsigned int *)&socketAddress[4] = 0;
	*(unsigned int *)&socketAddress[8] = 0;
	*(unsigned int *)&socketAddress[12] = 0;
	if ((Rva007FFDD0(&address, &port, &extra, text) & 2) == 0) {
		return -3;
	}
	socketAddress[2] = (unsigned char)(port >> 8);
	socketAddress[3] = (unsigned char)port;
	socket = Rva007FD2D0(2, 2, 0);
	if (socket == 0) {
		return -4;
	}
	result = Rva00819090(ref, socket, socketAddress);
	Rva00818FF0(ref, text);
	Rva007FE780Printf("CommUdpListen: err=%d, bind=%d, connident=0x%08x\n",
	                   result, port, *(int *)((char *)ref + 0x94));
	if (result == 0 && address != 0) {
		if (extra == 0) {
			extra = port + 1;
		}
		Rva007FE780Printf("CommUdpListen: poke=%08x:%d\n", address, extra);
		*(unsigned short *)((char *)ref + 0x80) = 2;
		*(unsigned short *)((char *)ref + 0x82) = 0;
		*(unsigned int *)((char *)ref + 0x84) = 0;
		*(unsigned int *)((char *)ref + 0x88) = 0;
		*(unsigned int *)((char *)ref + 0x8C) = 0;
		temp = address;
		*((unsigned char *)ref + 0x87) = (unsigned char)temp; temp >>= 8;
		*((unsigned char *)ref + 0x86) = (unsigned char)temp; temp >>= 8;
		*((unsigned char *)ref + 0x85) = (unsigned char)temp; temp >>= 8;
		*((unsigned char *)ref + 0x84) = (unsigned char)temp;
		*((unsigned char *)ref + 0x82) = (unsigned char)(extra >> 8);
		*((unsigned char *)ref + 0x83) = (unsigned char)extra;
	}
	*(int *)((char *)ref + 0xD4) = 0;
	return result;
}

// Queues an outbound packet, rejecting anything past the limit with
// "CommUDP: Oversized packet send (%d bytes)".
int CommUDPSend(void *ref, const void *buffer, int length, int flags)
{
	int queued;
	char *packet;
	unsigned int tick;

	if (*(int *)((char *)ref + 0x90) != 4) {
		return -2;
	}
	if ((*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xB8)) %
	        *(int *)((char *)ref + 0xBC) == *(int *)((char *)ref + 0xC4)) {
		return 0;
	}
	if (length > *(int *)((char *)ref + 0xB8) - 0x10) {
		Rva007FE780Printf("CommUDP: Oversized packet send (%d bytes)\n", length);
		return -6;
	}
	if (length == 0) {
		queued = ((*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xBC) -
		           *(int *)((char *)ref + 0xC4)) % *(int *)((char *)ref + 0xBC)) /
		         *(int *)((char *)ref + 0xB8);
		return queued + 1;
	}
	packet = *(char **)((char *)ref + 0xCC) + *(int *)((char *)ref + 0xC0);
	*(int *)packet = length;
	memcpy(packet + 0x10, buffer, length);
	*(unsigned int *)(packet + 4) = Rva007FEA00();
	if ((flags & 1) != 0) {
		Rva007FEBD0(g_Rva0130AF38Lock);
		*(int *)(packet + 8) = 6;
		*(int *)(packet + 0x0C) = *(int *)((char *)ref + 0xAC) - 1;
		CommUDPWrite(ref, packet);
		Rva007FECB0(g_Rva0130AF38Lock);
		return 1;
	}
	*(int *)(packet + 8) = *(int *)((char *)ref + 0xD0);
	++*(int *)((char *)ref + 0xD0);
	*(int *)(packet + 0x0C) = *(int *)((char *)ref + 0xAC) - 1;
	*(int *)((char *)ref + 0xC0) =
		(*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xB8)) %
		*(int *)((char *)ref + 0xBC);
	queued = ((*(int *)((char *)ref + 0xC0) + *(int *)((char *)ref + 0xBC) -
	           *(int *)((char *)ref + 0xC4)) % *(int *)((char *)ref + 0xBC)) /
	         *(int *)((char *)ref + 0xB8);
	if (queued < 0x10) {
		Rva007FEBD0(g_Rva0130AF38Lock);
		Rva00817640(ref);
		if (g_Rva0130AD08Count != 0) {
			tick = Rva007FEA00();
			while (Rva00817B30(tick) > 0) {
			}
			g_Rva0130AD08Count = 0;
		}
		Rva007FECB0(g_Rva0130AF38Lock);
	}
    return queued > 0 ? queued : 1;
}
