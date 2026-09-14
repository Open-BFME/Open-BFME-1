// ?bfmeElseBBD@@YAXXZ
// partial score=0.93 date=2026-09-14
// stlport
// STLport 4.5.3 global stream teardown at retail 0x00842C00.

# include "stlport_prefix.h"

#include <istream>
#include <stl/_fstream.h>
#include <stdio_streambuf>
#include "aligned_buffer.h"

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void __cdecl _ReadWriteBarrier(void);

namespace _STL
{
void rva00832100Release(void);
}

typedef _STL::basic_ios<char, _STL::char_traits<char> > BfmeNarrowStream;
typedef _STL::basic_ios<wchar_t, _STL::char_traits<wchar_t> > BfmeWideStream;

#define BFME_STREAM_AT(Type, Address) \
	((Type *)((char *)(Address) + *(volatile int *)(*(int *)(Address) + 4)))


// ?bfmeElseBBD@@YAXXZ
void bfmeElseBBD()
{
	if (*(volatile int *)0x0130BD30 == 0)
		return;

	{
		BfmeNarrowStream *ptr_cin = BFME_STREAM_AT(BfmeNarrowStream, 0x0130BED8);
		_ReadWriteBarrier();
		ptr_cin->exceptions(0);
	}
	{
		BfmeNarrowStream *ptr_cout = BFME_STREAM_AT(BfmeNarrowStream, 0x0130BDA0);
		_ReadWriteBarrier();
		ptr_cout->exceptions(0);
	}
	{
		BfmeNarrowStream *ptr_cerr = BFME_STREAM_AT(BfmeNarrowStream, 0x0130BF40);
		_ReadWriteBarrier();
		ptr_cerr->exceptions(0);
	}
	{
		BfmeNarrowStream *ptr_clog = BFME_STREAM_AT(BfmeNarrowStream, 0x0130BE08);
		_ReadWriteBarrier();
		ptr_clog->exceptions(0);
	}

	{
		BfmeNarrowStream *ptr_cin = BFME_STREAM_AT(BfmeNarrowStream, 0x0130BED8);
		_ReadWriteBarrier();
		delete ptr_cin->rdbuf(0);
	}
	{
		BfmeNarrowStream *ptr_cout = BFME_STREAM_AT(BfmeNarrowStream, 0x0130BDA0);
		_ReadWriteBarrier();
		delete ptr_cout->rdbuf(0);
	}
	{
		BfmeNarrowStream *ptr_cerr = BFME_STREAM_AT(BfmeNarrowStream, 0x0130BF40);
		_ReadWriteBarrier();
		delete ptr_cerr->rdbuf(0);
	}
	{
		BfmeNarrowStream *ptr_clog = BFME_STREAM_AT(BfmeNarrowStream, 0x0130BE08);
		_ReadWriteBarrier();
		delete ptr_clog->rdbuf(0);
	}

	_STL::_Destroy(BFME_STREAM_AT(BfmeNarrowStream, 0x0130BED8));
	_STL::_Destroy(BFME_STREAM_AT(BfmeNarrowStream, 0x0130BDA0));
	_STL::_Destroy(BFME_STREAM_AT(BfmeNarrowStream, 0x0130BF40));
	_STL::_Destroy(BFME_STREAM_AT(BfmeNarrowStream, 0x0130BE08));

	{
		BfmeWideStream *ptr_wcin = BFME_STREAM_AT(BfmeWideStream, 0x0130BFA8);
		_ReadWriteBarrier();
		ptr_wcin->exceptions(0);
	}
	{
		BfmeWideStream *ptr_wcout = BFME_STREAM_AT(BfmeWideStream, 0x0130BE70);
		_ReadWriteBarrier();
		ptr_wcout->exceptions(0);
	}
	{
		BfmeWideStream *ptr_wcerr = BFME_STREAM_AT(BfmeWideStream, 0x0130C010);
		_ReadWriteBarrier();
		ptr_wcerr->exceptions(0);
	}
	{
		BfmeWideStream *ptr_wclog = BFME_STREAM_AT(BfmeWideStream, 0x0130BD38);
		_ReadWriteBarrier();
		ptr_wclog->exceptions(0);
	}

	{
		BfmeWideStream *ptr_wcin = BFME_STREAM_AT(BfmeWideStream, 0x0130BFA8);
		_ReadWriteBarrier();
		delete ptr_wcin->rdbuf(0);
	}
	{
		BfmeWideStream *ptr_wcout = BFME_STREAM_AT(BfmeWideStream, 0x0130BE70);
		_ReadWriteBarrier();
		delete ptr_wcout->rdbuf(0);
	}
	{
		BfmeWideStream *ptr_wcerr = BFME_STREAM_AT(BfmeWideStream, 0x0130C010);
		_ReadWriteBarrier();
		delete ptr_wcerr->rdbuf(0);
	}
	{
		BfmeWideStream *ptr_wclog = BFME_STREAM_AT(BfmeWideStream, 0x0130BD38);
		_ReadWriteBarrier();
		delete ptr_wclog->rdbuf(0);
	}

	_STL::_Destroy(BFME_STREAM_AT(BfmeWideStream, 0x0130BFA8));
	_STL::_Destroy(BFME_STREAM_AT(BfmeWideStream, 0x0130BE70));
	_STL::_Destroy(BFME_STREAM_AT(BfmeWideStream, 0x0130C010));
	_STL::_Destroy(BFME_STREAM_AT(BfmeWideStream, 0x0130BD38));

	if (*(volatile int *)0x0130BCA8 > 0)
		_STL::rva00832100Release();
	__asm {
		dec dword ptr ds:[0130BD30h]
	}
}
