// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include <vector>
#include "ascii_string.h"
struct DistanceNode003C5990 { char m_00[0x1c]; float m_1C,m_20,m_24; DistanceNode003C5990 *m_parent; };
class DistanceUpdate003C5990 { public: void update(DistanceNode003C5990 *, int); };
class BfmeObjHC {
public:
    bool bfmeDoHC(void *,void *,void *,int);
    DistanceNode003C5990 *find003C5360(void *,void *);
    void trace003C5C10(DistanceNode003C5990 *,void *);
    char m_00[0xc];
    DistanceNode003C5990 *m_startNode,*m_goalNode;
    std::vector<DistanceNode003C5990 *> m_openList,m_20;
};
bool BfmeObjHC::bfmeDoHC(void *a,void *b,void *out,int flag) {
    m_openList.clear();
    m_20.clear();
    if(out) ((std::vector<AsciiString>*)out)->clear();
    DistanceNode003C5990 *start=find003C5360(this,a);
    m_startNode=start;
    m_goalNode=find003C5360(this,b);
    if(start && m_goalNode) {
        start->m_1C=0;
        start->m_20=0;
        start->m_24=0;
        m_startNode->m_parent=0;
        m_openList.push_back(m_startNode);
        while(m_openList.size()) {
            DistanceNode003C5990 *current=m_openList[0];
            m_openList.erase(m_openList.begin());
            if(current==m_goalNode) {
                if(out) trace003C5C10(current,out);
                return true;
            }
            ((DistanceUpdate003C5990*)this)->update(current,flag);
            m_20.push_back(current);
        }
    }
    return false;
}
