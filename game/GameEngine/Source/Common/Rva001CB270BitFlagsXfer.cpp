// ?xfer@Rva001CB270BitFlags@@QAEXPAVXfer@@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame
// Retail 0x001CB270, 497-byte extent: 496 bytes of body ending on the
// _CxxThrowException call plus the throw-site INT3, the same convention the
// byte-matched sibling 0x001CB730 uses for its 481-byte extent.
// Address-derived identity. The 304-bit cardinality is proven by the object
// size (0x28) and the 0x130 loop bound; the bit-name table is VA 0x012A6918
// (pin _bfmeGlobalTable12A6918), whose string anchor FRONTCRUSHED and Zero
// Hour's Common/BitFlags.cpp show the algorithm is a named-bit transfer, but
// the owner of the table is not proven here, so no upstream class is claimed.
// Spelling follows the byte-matched sibling 0x001CB730 (NamedBits1CB730.cpp):
// same Xfer virtual slot usage (0x08 save, 0x10 light CRC, 0x28 version,
// 0x68 AsciiString, 0x78 Int), same 4-byte aligned two-byte version record,
// same combined bit-test-and-lookup save condition, and the same AsciiString
// lifetime. The 40-byte table-summed loop is the STLport bitset count().
// stlport
#include <bitset>
#include "Libraries/Source/WWVegas/WWLib/ascii_string.h"

struct XferException { char *text; int tag; };
extern "C" XferException *__cdecl bfmeFormatText(XferException *,int,const char *,...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *,void *);
extern int g_guardTargetTypeThrowInfo;
extern int __cdecl bfmeLookup_001c62b0(void *);

struct __declspec(align(4)) Version1CB270 { unsigned char version,current; };

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
 virtual void version(Version1CB270 *);
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

extern const char *names1CB270[];

class Rva001CB270BitFlags { _STL::bitset<304> bits; public: void xfer(Xfer *xfer); };

void Rva001CB270BitFlags::xfer(Xfer *xfer)
{
 Version1CB270 v; v.version=1; v.current=1;
 xfer->version(&v);
 if (xfer->crc()) { ((BitFlags<304> *)this)->xfer(xfer); return; }
 if (xfer->save()) {
  int count=bits.count();
  xfer->integer(&count);
  for (int i=0;i<304;++i) {
   if (bits._Unchecked_test(i) && names1CB270[i]) {
    AsciiString name(names1CB270[i]);
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
   int bit=bfmeLookup_001c62b0(const_cast<char *>(name.str()));
   if (bit<0) {
    XferException error;
    bfmeFormatText(&error,0,0);
    _CxxThrowException(&error,&g_guardTargetTypeThrowInfo);
   }
   bits._Unchecked_set(bit);
  }
 }
}
