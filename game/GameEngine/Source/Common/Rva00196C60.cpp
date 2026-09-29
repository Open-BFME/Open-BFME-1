// The matched caller in Gen00375590PlayerObjectCreate.cpp invokes this body
// through ILT 0x0000BF2D with three arguments. The caller does not prove the
// function's owner, so this source keeps Rva00196C60::method address-derived.
// cl: /O2 /EHsc
// stlport
#include <map>
#include <vector>
struct BfmeVector3BG { int x,y,z; };
struct VectorPoint0019E880 { int x,y,z; };
class Gen_0018F210 {
public:
    void bfmeAppendVector3(const BfmeVector3BG *);
};
typedef _STL::vector<VectorPoint0019E880> Points;
typedef _STL::vector<Points> Groups;
typedef _STL::pair<const int,Groups> LookupPair;
typedef _STL::_Rb_tree<int,LookupPair,_STL::_Select1st<LookupPair>,_STL::less<int>,_STL::allocator<LookupPair> > LookupTree;
template<> template<> __declspec(noinline) LookupTree::iterator LookupTree::find<int>(const int &key)
{
    return LookupTree::iterator(_M_find(key));
}
typedef _STL::pair<const int,Groups> ActualPair;
class Rva00196C60 {
public:
    bool method(int key,int index,Gen_0018F210 *out);
private:
    char m_prefix[0x1c];
    LookupTree m_lookup;
};
bool Rva00196C60::method(int key,int index,Gen_0018F210 *out)
{
    if(!out) return false;
    LookupTree::iterator found=m_lookup.find(key);
    if(found==m_lookup.end()) return false;
    if(index >= (int)found->second.size()) return false;
    Points &points=found->second[index];
    if(points.size()==0) return false;
    for(Points::iterator i=points.begin();i!=points.end();++i)
        out->bfmeAppendVector3(reinterpret_cast<const BfmeVector3BG *>(i));
    return true;
}
