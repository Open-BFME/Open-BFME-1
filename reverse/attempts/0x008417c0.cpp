// ?seekoff@?$basic_filebuf@DV?$char_traits@D@_STL@@@_STL@@MAE?AV?$fpos@H@2@JHH@Z
// partial score=0.72 date=2026-09-03
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 basic_filebuf<char>::seekoff.
// Probe: ours=805 retail=911; first divergence sub esp 0x10 vs 0x14;
 // register color ebp/ebx; member offsets (+0x60 is_open) match.
 // Same upstream _fstream.c seekoff; BFME body ~106B longer (var-width /
 // Tmp_Buf / equal path expansion). Helpers _M_seek_init@0x841C20 and
 // _M_seek@0x84A310 already matched; _M_seek_return pin@0x841B90.

#include <fstream>

_STLP_BEGIN_NAMESPACE

template basic_filebuf<char, char_traits<char> >::pos_type
basic_filebuf<char, char_traits<char> >::seekoff(
	off_type, ios_base::seekdir, ios_base::openmode);

_STLP_END_NAMESPACE
