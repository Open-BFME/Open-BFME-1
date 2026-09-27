// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <utility>
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Retail 0x006AB9F0: reset two trees, remove owner-tagged pairs, refresh 6x2 outputs.
// Owner is an embedded Miles audio slot; identity remains address-derived.
extern void j_0004412a();
extern void j_0002900f();
class Rva00699430Owner { public: void productClamp(int); };
class Rva00699180Owner { public: void refreshPair(int,int); };
struct Node006AB9F0 { int color; Node006AB9F0 *parent,*left,*right; };
struct Tree006AB9F0 {
    Node006AB9F0 *header; unsigned count;
    void clear(void (__cdecl *fn)()) {
        if(count) {
            typedef void (Tree006AB9F0::*Erase)(Node006AB9F0*);
            union { void (__cdecl *raw)(); Erase member; } call;
            call.raw=fn; (this->*call.member)(header->parent);
            header->left=header; header->parent=0; header->right=header; count=0;
        }
    }
};
typedef _STL::pair<float,int> Pair006AB9F0;
typedef _STL::vector<Pair006AB9F0> Vector006AB9F0;
class ResetAudioSlot006AB9F0 {
public:
    void reset();
    int dword_0; float floats_4[6][2]; float floats_34[6];
    Vector006AB9F0 vectors_4c[6];
    float float_94,float_98,float_9c;
    Tree006AB9F0 tree_a0;
    char pad_a8[0xc4-0xa8]; bool byte_c4;
    char pad_c5[0x1b8-0xc5]; Tree006AB9F0 tree_1b8;
};
void ResetAudioSlot006AB9F0::reset() {
    tree_1b8.clear(j_0004412a);
    for(int i=0;i<6;++i) for(int j=0;j<2;++j) floats_4[i][j]=1.0f;
    float_94=1.0f; float_9c=1.0f; byte_c4=false;
    tree_a0.clear(j_0002900f);
    for(int k=0;k<6;++k) {
        Vector006AB9F0 &v=vectors_4c[k];
        bool changed=false;
        for(Pair006AB9F0 *p=v.begin();p!=v.end();) {
            if(p->second==dword_0) { p=v.erase(p); changed=true; }
            else ++p;
        }
        if(changed) ((Rva00699430Owner*)this)->productClamp(k);
    }
    for(int a=0;a<6;++a) for(int b=0;b<2;++b) ((Rva00699180Owner*)this)->refreshPair(a,b);
}


