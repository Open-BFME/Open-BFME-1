// cl: /EHsc
// stlport
// Retail RVA 0x0019E880: append a three-pointer inner vector to an int-keyed
// map of outer vectors at this+0x1C. Semantic owner is unproved.
// The 0x0019F1E0 caller supplies a key and vector by reference; the body
// witnesses the 16-byte tree node header and 12-byte inner-vector stride.
// Callee bodies independently establish: int tree find 0x195120;
// inner copy 0x1953B0; outer growth 0x19E030; pair construction 0x19E1A0;
// outer copy 0x197480; insertion 0x19E470; outer destruction 0x19D850.
// Keep make_pair visible but out of line: its non-escaping key reference
// lets MSVC reuse the incoming key slot for placement construction.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>
struct VectorPoint0019E880 { int words[3]; };
typedef _STL::vector<VectorPoint0019E880> Inner0019E880;
typedef _STL::vector<Inner0019E880> Outer0019E880;
typedef _STL::pair<int, Outer0019E880> Pair0019E880;
typedef _STL::map<int, Outer0019E880> Map0019E880;
namespace _STL {
template<> vector<VectorPoint0019E880>::vector(const vector<VectorPoint0019E880>&);
template<> vector<Inner0019E880>::vector(const vector<Inner0019E880>&);
template<> vector<Inner0019E880>::~vector();
template<> void vector<Inner0019E880>::_M_insert_overflow(Inner0019E880*, const Inner0019E880&, const __false_type&, size_t, bool);
template<> __forceinline void vector<Inner0019E880>::push_back(const Inner0019E880& x) {
 if (_M_finish != _M_end_of_storage._M_data) {
   _Construct(_M_finish, x);
   ++_M_finish;
 } else { __false_type tag; _M_insert_overflow(_M_finish, x, tag, 1, true); }
}
template<> __declspec(noinline) Pair0019E880 make_pair(const int& key, const Outer0019E880& value) { return Pair0019E880(key, value); }
}
class MapVectorAppend0019E880 {
    unsigned char field_00[0x1c];
    Map0019E880 field_1c;
public:
    void append(int key, const Inner0019E880& value);
};
void MapVectorAppend0019E880::append(int key, const Inner0019E880& value) {
    Map0019E880::iterator it = field_1c.find(key);
    if (it != field_1c.end()) {
        it->second.push_back(value);
    } else {
        Outer0019E880 values;
        values.push_back(value);
        field_1c.insert(_STL::make_pair(key, values));
    }
}

typedef char InnerWidth0019E880[(sizeof(Inner0019E880)==12)?1:-1];
typedef char OuterWidth0019E880[(sizeof(Outer0019E880)==12)?1:-1];
