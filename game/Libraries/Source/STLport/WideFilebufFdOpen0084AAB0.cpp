// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 wide basic_filebuf::open(int fd, openmode) at 0x0084AAB0
// (31 B: `ret 8` after the `pop esi`, then one int3). The 40-byte dump
// extent is a mis-carve: the 9 bytes at 0x0084AACF are the tail of the
// neighbouring 8-byte _M_write forwarder at 0x0084AAC8 (the same
// `add ecx,0x24 / jmp _M_write` pair already landed at 0x0084AAA0 for the
// same wide filebuf), not part of this open.
//
// The wide specialization is witnessed by probe.py: the narrow open emits
// `lea ecx,[esi+0x54]` (one byte off), the wide open emits retail's
// `lea ecx,[esi+0x24]` with zero non-reloc diffs over the 31 bytes.

#include <fstream>

template _STL::basic_filebuf<unsigned short, _STL::char_traits<unsigned short> >::_Self *
_STL::basic_filebuf<unsigned short, _STL::char_traits<unsigned short> >::open(
    int, _STL::ios_base::openmode);
