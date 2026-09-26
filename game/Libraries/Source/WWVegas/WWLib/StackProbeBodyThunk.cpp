// cl: /DNDEBUG /MD /GX- /O2 /Ob2

__declspec(naked) void StackProbeBodyThunk()
{
	__asm {
		_emit 03Dh
		_emit 000h
		_emit 010h
		_emit 000h
		_emit 000h
		_emit 073h
		_emit 00Eh
		_emit 0F7h
		_emit 0D8h
		_emit 003h
		_emit 0C4h
		_emit 083h
		_emit 0C0h
		_emit 004h
		_emit 085h
		_emit 000h
		_emit 094h
		_emit 08Bh
		_emit 000h
		_emit 050h
		_emit 0C3h
		_emit 051h
		_emit 08Dh
		_emit 04Ch
		_emit 024h
		_emit 008h
		_emit 081h
		_emit 0E9h
		_emit 000h
		_emit 010h
		_emit 000h
		_emit 000h
		_emit 02Dh
		_emit 000h
		_emit 010h
		_emit 000h
		_emit 000h
		_emit 085h
		_emit 001h
		_emit 03Dh
		_emit 000h
		_emit 010h
		_emit 000h
		_emit 000h
		_emit 073h
		_emit 0ECh
		_emit 02Bh
		_emit 0C8h
		_emit 08Bh
		_emit 0C4h
		_emit 085h
		_emit 001h
		_emit 08Bh
		_emit 0E1h
		_emit 08Bh
		_emit 008h
		_emit 08Bh
		_emit 040h
		_emit 004h
		_emit 050h
		_emit 0C3h
	}
}
