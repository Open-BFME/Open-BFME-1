// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// Retail 0x000DA250, 395 bytes. Player serializer 0x000DCF9F passes
// Xfer and its AsciiString-keyed table at +0x200. Incoming ECX is unused.
// Native helper spelling is unknown; retain the address identity.
// RET 8 at +0x188, followed by INT3 at +0x18B.
// Xfer slots 2/29/26/30 and the matched hash index body at 0x000D9870
// establish the table transfer ABI. Separate iterator initialization
// preserves the retail load before the empty-table branch.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include "string_base.h"
#include "xfer.h"
#include "ascii_string.h"
namespace rts { template<class T> struct hash { unsigned int operator()(T value) const; }; }
enum Rva000D6C60Mapped { Rva000D6C60MappedZero=0 };
typedef _STL::hash_map<AsciiString,Rva000D6C60Mapped,rts::hash<AsciiString> > HashB;
template<> Rva000D6C60Mapped &HashB::operator[](const AsciiString &);
typedef HashB::value_type HashBValue;
typedef _STL::hashtable<HashBValue,AsciiString,rts::hash<AsciiString>,
 _STL::_Select1st<HashBValue>,_STL::equal_to<AsciiString>,
 _STL::allocator<HashBValue> > HashBTable;
class Rva000D0A30 {
public:
 HashB::iterator method() {
 for(unsigned int i=0;i<m_rva000D0A30_buckets.size();++i)
  if(m_rva000D0A30_buckets[i])
   return HashB::iterator(m_rva000D0A30_buckets[i],reinterpret_cast<HashBTable *>(this));
 return HashB::iterator(0,reinterpret_cast<HashBTable *>(this));
}
private:
 unsigned char m_rva000D0A30_prefix[4];
 _STL::vector<_STL::_Hashtable_node<HashBValue> *> m_rva000D0A30_buckets;
};

inline HashB::iterator rva000da250_begin(HashB *table) {
 return reinterpret_cast<Rva000D0A30 *>(table)->method();
}
void __stdcall rva000da250(Xfer *xfer,HashB *table) {
 if(xfer->IsStoring()) {
   unsigned int count=table->size();
   *xfer == count;
   HashB::iterator it;
   it=rva000da250_begin(table);
   for(;it!=table->end();++it) {
     AsciiString key=it->first;
     int value=it->second;
     *xfer == key;
     *xfer == value;
   }
 } else {
   unsigned int count=0;
   *xfer == count;
   AsciiString key;
   for(unsigned int i=0;i<count;++i) {
     int value;
     *xfer == key;
     *xfer == value;
     (*table)[key]=(Rva000D6C60Mapped)value;
   }
 }
}
