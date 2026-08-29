// ?d_00716a50@@YAXXZ
// partial score=0.95 date=2026-08-28
// ---------------------------------------------------------------------------
// 0x00716A50 -- dispatch four arguments through a table entry, or fail.
//
//     mov eax,[esp+4] / mov ecx,[eax*4+TABLE] / test ecx,ecx / je none
//     mov edx,[esp+0x14] / mov eax,[ecx] / push edx (x4) / call [eax+0xc] / ret
//     none: mov [GLOBAL],0 / xor al,al / ret
//
// Each `push` re-reads [esp+0x14]: esp has moved by four, so the four reads
// walk arguments five, four, three and two BACKWARDS, which is exactly
// right-to-left argument order for a call that forwards them unchanged.  The
// dispatcher itself is __cdecl (bare `ret`) while the slot pops its own four,
// and the failure arm returns `xor al,al`, so the result is byte-wide and comes
// straight out of the slot.

class Open2716A50Handler
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual char slot0C( void *a, void *b, void *c, void *d );
};

extern Open2716A50Handler *g_open2716A50Table[];
extern int g_open2716A50Status;

// @?Rva00716A50@@YADHPAX000@Z 0x00716A50
char Rva00716A50( int which, void *a, void *b, void *c, void *d )
{
	Open2716A50Handler *handler = g_open2716A50Table[ which ];
	if( handler )
		return handler->slot0C( a, b, c, d );
	g_open2716A50Status = 0;
	return 0;
}

