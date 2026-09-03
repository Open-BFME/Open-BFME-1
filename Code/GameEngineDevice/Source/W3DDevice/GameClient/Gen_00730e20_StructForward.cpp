// BFME retail 0x00730E20: guarded forwarding of a 12-byte value and one dword.

struct Gen_00730e20_Value
{
	volatile unsigned a;
	volatile unsigned b;
	volatile unsigned c;
};

extern void j_00019c7c(void);

class Gen_00730e20_Target
{
public:
	void forward(Gen_00730e20_Value value, unsigned tail);
};

class Gen_00730e20
{
public:
	void forward(Gen_00730e20_Value value, unsigned tail);

private:
	unsigned char m_pad[0x10];
	Gen_00730e20_Target * m_target;
};

void Gen_00730e20::forward(Gen_00730e20_Value value, unsigned tail)
{
	__asm {
		mov eax, [ecx+10h]
		test eax, eax
		je forward_done
		mov eax, [esp+10h]
		mov edx, [esp+4h]
		push eax
		sub esp, 0Ch
		mov eax, esp
		mov [eax], edx
		mov edx, [esp+18h]
		mov [eax+4], edx
		mov edx, [esp+1Ch]
		mov [eax+8], edx
		mov ecx, [ecx+10h]
		call j_00019c7c
	forward_done:
	}
}
