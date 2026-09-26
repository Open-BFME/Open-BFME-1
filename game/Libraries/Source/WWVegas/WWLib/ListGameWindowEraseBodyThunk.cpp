// cl: /DNDEBUG /MD /GX- /O2 /Ob2

__declspec(naked) void ListGameWindowEraseBodyThunk()
{
	__asm {
		_emit 056h
		_emit 08Bh
		_emit 074h
		_emit 024h
		_emit 00Ch
		_emit 057h
		_emit 08Bh
		_emit 07Ch
		_emit 024h
		_emit 014h
		_emit 03Bh
		_emit 0F7h
		_emit 074h
		_emit 01Fh
		_emit 08Bh
		_emit 0FFh
		_emit 08Bh
		_emit 0C6h
		_emit 08Bh
		_emit 008h
		_emit 08Bh
		_emit 050h
		_emit 004h
		_emit 08Bh
		_emit 036h
		_emit 06Ah
		_emit 00Ch
		_emit 089h
		_emit 00Ah
		_emit 050h
		_emit 089h
		_emit 051h
		_emit 004h
		_emit 0E8h
		_emit 0BAh
		_emit 0B2h
		_emit 03Ah
		_emit 000h
		_emit 083h
		_emit 0C4h
		_emit 008h
		_emit 03Bh
		_emit 0F7h
		_emit 075h
		_emit 0E3h
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 00Ch
		_emit 089h
		_emit 038h
		_emit 05Fh
		_emit 05Eh
		_emit 0C2h
		_emit 00Ch
		_emit 000h
	}
}
