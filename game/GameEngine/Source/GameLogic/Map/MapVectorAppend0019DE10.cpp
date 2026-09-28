// cl: /EHsc
// stlport
// Retail RVA 0x0019DE10. Address-derived owner: append a 0x8C-byte
// polymorphic record to an int-keyed vector map at this+0x10.
// Layout and copy identity are independently established by 0x00193D50,
// 0x00195C40 and 0x00196F30; caller 0x0019F1E0 supplies two arguments.
// The sibling 0x0019E880 has identical lifetime/control flow but a 12-byte
// element. Visible non-inlined make_pair permits dead-key-slot reuse.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>
class Gen_00193D50 { public: virtual ~Gen_00193D50(); char field_04[0x88]; Gen_00193D50(const Gen_00193D50&); };
typedef Gen_00193D50 Inner0019DE10;
typedef _STL::vector<Inner0019DE10> Outer0019DE10;
typedef _STL::pair<int, Outer0019DE10> Pair0019DE10;
typedef _STL::map<int, Outer0019DE10> Map0019DE10;
namespace _STL {
template<> vector<Inner0019DE10>::vector(const vector<Inner0019DE10>&);
template<> vector<Inner0019DE10>::~vector();
template<> void vector<Inner0019DE10>::_M_insert_overflow(Inner0019DE10*, const Inner0019DE10&, const __false_type&, size_t, bool);
template<> __forceinline void vector<Inner0019DE10>::push_back(const Inner0019DE10& x) {
 if (_M_finish != _M_end_of_storage._M_data) {
   _Construct(_M_finish, x);
   ++_M_finish;
 } else { __false_type tag; _M_insert_overflow(_M_finish, x, tag, 1, true); }
}
template<> __declspec(noinline) Pair0019DE10 make_pair(const int& key, const Outer0019DE10& value) { return Pair0019DE10(key, value); }
}
class MapVectorAppend0019DE10 {
    unsigned char field_00[0x10];
    Map0019DE10 field_10;
public:
    void append(int key, const Inner0019DE10& value);
};
void MapVectorAppend0019DE10::append(int key, const Inner0019DE10& value) {
    Map0019DE10::iterator it = field_10.find(key);
    if (it != field_10.end()) {
        it->second.push_back(value);
    } else {
        Outer0019DE10 values;
        values.push_back(value);
        field_10.insert(_STL::make_pair(key, values));
    }
}

typedef char ElementWidth0019DE10[(sizeof(Gen_00193D50)==0x8c)?1:-1];
typedef char VectorWidth0019DE10[(sizeof(Outer0019DE10)==12)?1:-1];
