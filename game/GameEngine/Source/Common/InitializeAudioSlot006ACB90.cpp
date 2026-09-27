// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
#include <set>
#include <map>
#include "ascii_string.h"
class Rva00699180Owner { public: void refreshPair(int,int) throw(); };
class InitializeAudioSlot006ACB90 {
public:
    InitializeAudioSlot006ACB90();
    int dword_0;
    float floats_4[6][2]; float floats_34[6];
    _STL::vector<_STL::pair<float,int> > vectors_4c[6];
    float float_94,float_98,float_9c;
    _STL::set<AsciiString> tree_a0;
    float float_ac,float_b0;
    int dword_b4,dword_b8,dword_bc,dword_c0;
    bool byte_c4;
    float floats_c8[6][2][4];
    unsigned char bytes_188[6][2][4];
    _STL::map<int,float> tree_1b8;
};
InitializeAudioSlot006ACB90::InitializeAudioSlot006ACB90()
: dword_0(3),float_94(1.0f),float_98(1.0f),float_9c(1.0f),
  float_ac(1.0f),float_b0(1.0f),dword_b4(0),dword_b8(0),dword_bc(0),dword_c0(0),byte_c4(false)
{
    for(int i=0;i<6;++i) {
        floats_34[i]=1.0f;
        for(int j=0;j<2;++j) {
            floats_4[i][j]=1.0f;
            for(int k=0;k<4;++k) {
                floats_c8[i][j][k]=1.0f;
                bytes_188[i][j][k]=0;
            }
        }
    }
    for(int a=0;a<6;++a) for(int b=0;b<2;++b) ((Rva00699180Owner*)this)->refreshPair(a,b);
}

