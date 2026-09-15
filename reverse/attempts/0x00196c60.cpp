// ?appendPoints@Rva00196C60Owner@@QAE_NHHPAVGen_0018F210@@@Z
// partial score=0.5 date=2026-09-15
// cl: /O2 /EHsc
// stlport
#include <map>
#include <vector>
struct BfmeVector3BG { int x,y,z; };
class Gen_0018F210 {
public:
    void bfmeAppendVector3(const BfmeVector3BG *);
};
typedef _STL::vector<BfmeVector3BG> Points;
typedef _STL::vector<Points> Groups;
typedef _STL::pair<const int,Groups> LookupPair;
typedef _STL::_Rb_tree<int,LookupPair,_STL::_Select1st<LookupPair>,_STL::less<int>,_STL::allocator<LookupPair> > LookupTree;
template<> template<> __declspec(noinline) LookupTree::iterator LookupTree::find<int>(const int &key)
{
    return LookupTree::iterator(_M_find(key));
}
typedef _STL::pair<const int,Groups> ActualPair;
class Rva00196C60Owner {
public:
    bool appendPoints(int key,int index,Gen_0018F210 *out);
private:
    char m_prefix[0x1c];
    LookupTree m_lookup;
};
bool Rva00196C60Owner::appendPoints(int key,int index,Gen_0018F210 *out)
{
    if(!out) return false;
    LookupTree::iterator found=m_lookup.find(key);
    if(found==m_lookup.end()) return false;
    Groups &groups=found->second;
    if(index >= (int)groups.size()) return false;
    Points &points=groups[index];
    if(points.size()==0) return false;
    for(Points::iterator i=points.begin();i!=points.end();++i)
        out->bfmeAppendVector3(i);
    return true;
}
