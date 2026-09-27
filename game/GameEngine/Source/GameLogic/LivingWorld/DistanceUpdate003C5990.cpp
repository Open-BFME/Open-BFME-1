// cl: /DNDEBUG /MD /EHsc
class Gen003C4CB0Point;
class Gen003C4CB0Owner { public: float planarDistance(const Gen003C4CB0Point *) const; };
struct DistanceNode003C5990 {
    void *m_00;
    DistanceNode003C5990 **m_begin04, **m_end08, **m_capacity0C;
    float m_10, m_14;
    char m_18;
    float m_1C, m_20, m_24;
    DistanceNode003C5990 *m_28;
};
struct PointerVector003C5990 {
    DistanceNode003C5990 **begin, **end, **capacity;
    unsigned size() const { return end-begin; }
    bool contains(DistanceNode003C5990 *p) const {
        for(unsigned i=0; i<size(); ++i) if(begin[i]==p) return true;
        return false;
    }
};
class DistanceUpdate003C5990 {
public:
    void update(DistanceNode003C5990 *, bool);
    void remove003C4FF0(PointerVector003C5990 *, DistanceNode003C5990 *);
    void insert003C58E0(PointerVector003C5990 *, DistanceNode003C5990 *);
    char m_00[0x10];
    DistanceNode003C5990 *m_10;
    PointerVector003C5990 m_14, m_20;
};
void DistanceUpdate003C5990::update(DistanceNode003C5990 *node, bool flag) {
    for(unsigned i=0; i<unsigned(node->m_end08-node->m_begin04); ++i) {
        DistanceNode003C5990 *p=node->m_begin04[i];
        if(p->m_18 || flag) {
            float distance=((Gen003C4CB0Owner*)node)->planarDistance((Gen003C4CB0Point*)p)+node->m_1C;
            if(m_14.contains(p) && p->m_1C<=distance) continue;
            if(m_20.contains(p) && p->m_1C<=distance) continue;
            remove003C4FF0(&m_14,p);
            remove003C4FF0(&m_20,p);
            p->m_28=node;
            p->m_1C=distance;
            p->m_20=((Gen003C4CB0Owner*)p)->planarDistance((Gen003C4CB0Point*)m_10);
            p->m_24=p->m_20+distance;
            insert003C58E0(&m_14,p);
        }
    }
}
