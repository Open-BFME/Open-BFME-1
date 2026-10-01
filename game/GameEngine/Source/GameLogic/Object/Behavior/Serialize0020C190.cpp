// Retail RVA 0x0020C190; address-derived owner. Versioned field transfer.
// Xfer slots are witnessed at +0x28/+0x68/+0x74/+0x78/+0x8c.
// The local version constructor preserves retail stack-slot allocation.
// ThrowInfo VA 0x011DFE5C is the RTTI-proven eight-byte XferException.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "string_base.h"
template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length==0; }
#include "ascii_string.h"
#include "xfer.h"
class XferException { public: XferException(int,const char*,...); XferException(const XferException&); ~XferException(); char* text; int tag; };
struct TransferVersion0020C190 : Xfer::Version { TransferVersion0020C190(unsigned char a,unsigned char b) { data[0]=a;data[1]=b; } };
class Serialize0020C190;
class BfmeSeedTarget;
class Gen_001F61B0 { friend class Serialize0020C190; void bfmeAccept(BfmeSeedTarget*); };
class Gen_001ED0C0 { friend class Serialize0020C190; void bfmeAccept(BfmeSeedTarget*); };
class BfmeSubAccept_00029DAC { public: void bfmeAccept(BfmeSeedTarget*); };
class BfmeFind975D { public: void* bfmeFind975D(int); };
class ThingFactory;
extern ThingFactory* TheThingFactory;
extern const AsciiString Rva01336E50EmptyString;
Xfer* xferListInt(Xfer*,_STL::list<int>*);
void bfmeHandOver_0000FFE2(BfmeSeedTarget*,void*);
struct Template0020C190 { char pad00[0x20]; AsciiString name20; };
class Serialize0020C190 { public:
 char pad00[0x34]; Template0020C190* field34; int field38,field3C,field40;
 _STL::list<int> list44; int field48; bool flag4C,flag4D,flag4E; char pad4F; int field50; unsigned field54,field58;
 void xfer(Xfer*);
};
void Serialize0020C190::xfer(Xfer* xfer) {
 ((Gen_001F61B0*)this)->bfmeAccept((BfmeSeedTarget*)xfer);
 TransferVersion0020C190 version(1,3);
 *xfer==version;
 if(version.data[1]>=3) ((Gen_001ED0C0*)this)->bfmeAccept((BfmeSeedTarget*)xfer);
 if(!xfer->IsLightCRC()) {
 *xfer==flag4E;
 if(version.data[1]>=2) {
  ((BfmeSubAccept_00029DAC*)((char*)this+0x2c))->bfmeAccept((BfmeSeedTarget*)xfer);
  *xfer==field58;
 }
 AsciiString name;
 name=field34 ? field34->name20 : Rva01336E50EmptyString;
 *xfer==name;
 if(xfer->IsLoading()) {
  field34=0;
  if(!name.isEmpty()) {
   field34=(Template0020C190*)((BfmeFind975D*)TheThingFactory)->bfmeFind975D((int)&name);
   if(!field34) throw XferException(5,0);
  }
 }
 *xfer==field38; *xfer==field3C; *xfer==field40;
 if(xfer->IsLoading()) list44.clear();
 xferListInt(xfer,&list44);
 bfmeHandOver_0000FFE2((BfmeSeedTarget*)xfer,&field48);
 *xfer==flag4C; *xfer==flag4D; *xfer==field50; *xfer==field54;
}
}





