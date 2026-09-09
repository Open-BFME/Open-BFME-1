// Retail 0x00493F30/105: state update for the transition controller.
// The retail body reads m_flags at +0x08, the controller state at +0x238,
// and the previous flags at +0x250. The controller calls use vtable slots
// +0x10 and +0x14. The finishTransition thunk is the matched retail target
// at 0x00005925 and its body is 0x00493EA0.
// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef bool Bool;

class Rva00493F30Controller
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void begin(void);
	virtual void update(void);
};

class Rva00493F30TransitionState
{
public:
	Bool updateState(void);
	void finishTransition(void);

private:
	unsigned char m_padding0[8];
	unsigned int m_flags;
	unsigned char m_padding1[0x20c];
	Rva00493F30Controller m_controller;
	unsigned char m_padding2[0x1c];
	unsigned int m_mode;
	unsigned char m_padding3[0x14];
	volatile unsigned int m_previousFlags;
};

Bool Rva00493F30TransitionState::updateState(void)
{
	__asm {
		mov esi, ecx
		mov eax, [esi+250h]
		mov ecx, 10h
		and eax, ecx
		jne flags_were_set
		test byte ptr [esi+8], cl
		je flags_were_set
		test byte ptr [esi+238h], 1
		je flags_are_updated
		mov eax, [esi+218h]
		lea ecx, [esi+218h]
		call dword ptr [eax+10h]
		jmp flags_are_updated
	flags_were_set:
		test eax, eax
		je flags_are_updated
		test byte ptr [esi+8], cl
		jne flags_are_updated
		mov ecx, esi
		call Rva00493F30TransitionState::finishTransition
	flags_are_updated:
		test byte ptr [esi+238h], 1
		mov ecx, [esi+8]
		mov [esi+250h], ecx
		je update_state_done
		mov edx, [esi+218h]
		lea ecx, [esi+218h]
		call dword ptr [edx+14h]
	update_state_done:
		mov eax, 1
	}
}
