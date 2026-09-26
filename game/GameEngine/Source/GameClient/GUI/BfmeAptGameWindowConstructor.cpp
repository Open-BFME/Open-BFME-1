// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x00465310: the shared APT game-window base constructor.
// The vtable pair 0x010F711C/0x010F7118 and the five APT screen callers identify
// this body as _bfme_AptGameWindow.  The base constructor supplies the first
// 0x218 bytes, and the stores below initialize S4Owner and filename state.

class BfmeAptScreenBase
{
public:
	void initialize( void *context );
};

#pragma comment(linker, "/alternatename:?initialize@BfmeAptScreenBase@@QAEXPAX@Z=??0BfmeAptScreenBase@@QAE@PAX@Z")
extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( void *context );
};

// ??0_bfme_AptGameWindow@@QAE@PAX@Z
_bfme_AptGameWindow::_bfme_AptGameWindow( void *context )
{
	( (BfmeAptScreenBase *)this )->initialize( context );

	*(volatile unsigned int *)( (char *)this + 0x218 ) = 0x010F7114;
	_ReadWriteBarrier();
	unsigned int zero = 0;
	*(unsigned int *)( (char *)this + 0x21C ) = zero;
	*(unsigned int *)( (char *)this + 0x220 ) = zero;
	*(unsigned int *)( (char *)this + 0x224 ) = zero;
	*(unsigned int *)( (char *)this + 0x228 ) = zero;
	*(unsigned int *)( (char *)this + 0x22C ) = zero;
	*(unsigned int *)( (char *)this + 0x230 ) = zero;
	*(unsigned int *)( (char *)this + 0x234 ) = zero;
	*(unsigned int *)( (char *)this + 0x238 ) = zero;
	*(unsigned int *)( (char *)this + 0x23C ) = zero;
	*(unsigned int *)( (char *)this + 0x240 ) = zero;
	*(unsigned int *)( (char *)this + 0x244 ) = zero;
	*(unsigned int *)( (char *)this + 0x248 ) = zero;

	_ReadWriteBarrier();
	*(volatile unsigned int *)( (char *)this + 0x000 ) = 0x010F711C;
	*(volatile unsigned int *)( (char *)this + 0x218 ) = 0x010F7118;
	_ReadWriteBarrier();
	*(unsigned int *)( (char *)this + 0x24C ) = zero;
	*(unsigned char *)( (char *)this + 0x254 ) = 0;
	*(unsigned int *)( (char *)this + 0x250 ) = 0xFFFFFFFF;
}
