// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame
// Retail 0x001CB730, complete 481-byte extent including the throw-site INT3.
// ZH BitFlagsIO.h supplies the save/load algorithm; BFME adds the CRC route,
// a two-byte version record aligned to four bytes, and XferException handling.
// The table at VA 0x012A8D40 is shared with the established getSingleBitFromName
// callee at RVA 0x001C0A30. This body independently witnesses 116 flag bits
// and 16 bytes of storage.
// stlport
#include <bitset>
#include "Libraries/Source/WWVegas/WWLib/ascii_string.h"
struct XferException { char *text; int tag; };
extern "C" XferException *__cdecl bfmeFormatText(XferException *,int,const char *,...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *,void *);
extern int g_guardTargetTypeThrowInfo;
struct __declspec(align(4)) Version1CB730 { unsigned char version,current; };
class Xfer { public:
 virtual void pad00();
 virtual void pad04();
 virtual bool save();
 virtual void pad0C();
 virtual bool crc();
 virtual void pad14();
 virtual void pad18();
 virtual void pad1C();
 virtual void pad20();
 virtual void pad24();
 virtual void version(Version1CB730 *);
 virtual void pad2C();
 virtual void pad30();
 virtual void pad34();
 virtual void pad38();
 virtual void pad3C();
 virtual void pad40();
 virtual void pad44();
 virtual void pad48();
 virtual void pad4C();
 virtual void pad50();
 virtual void pad54();
 virtual void pad58();
 virtual void pad5C();
 virtual void pad60();
 virtual void pad64();
 virtual void text(AsciiString *);
 virtual void pad6C();
 virtual void pad70();
 virtual void pad74();
 virtual void integer(int *);
};
template<int N> class BitFlags { public:
 _STL::bitset<N> bits;
 void xfer(Xfer *);
 static int getSingleBitFromName(const char *);
};
extern const char *names1CB730[];
class NamedBits1CB730 { _STL::bitset<116> bits; public: void transfer(Xfer *xfer); };
void NamedBits1CB730::transfer(Xfer *xfer)
{
 Version1CB730 v; v.version=1; v.current=1;
 xfer->version(&v);
 if (xfer->crc()) { ((BitFlags<116> *)this)->xfer(xfer); return; }
 if (xfer->save()) {
  int count=bits.count();
  xfer->integer(&count);
  for (int i=0;i<116;++i) {
   if (bits._Unchecked_test(i) && names1CB730[i]) {
    AsciiString name(names1CB730[i]);
    xfer->text(&name);
    --count;
   }
  }
 } else {
  bits.reset();
  int count;
  xfer->integer(&count);
  AsciiString name;
  for (int i=0;i<count;++i) {
   xfer->text(&name);
   int bit=BitFlags<116>::getSingleBitFromName(name.str());
   if (bit<0) {
    XferException error;
    bfmeFormatText(&error,0,0);
    _CxxThrowException(&error,&g_guardTargetTypeThrowInfo);
   }
   bits._Unchecked_set(bit);
  }
 }
}
