// ?bfmeTwoCGD@BfmeThingCGD@@QAEXXZ
// partial score=0.264264 date=2026-09-28
// BfmeThingCGD::bfmeTwoCGD; identity witnessed by BfmeConv597.cpp.
struct Rva009A30B0Vector { float x,y,z; Rva009A30B0Vector(const Rva009A30B0Vector &v) : x(v.x), y(v.y), z(v.z) {} };
struct Rva009A30B0Interface {
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void *slot0c(Rva009A30B0Vector *, Rva009A30B0Vector *);
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
    virtual bool slot20(void *);
    virtual void slot24(void *);
};
struct Rva009A30B0Object { void *field00; Rva009A30B0Interface *field04; };
struct Rva009A30B0Record {
    Rva009A30B0Object *first, *second;
    unsigned key0,key1,state;
    Rva009A30B0Vector field14,field20;
    void *field2c;
    Rva009A30B0Record *next;
};
class BfmeThingCGD {
public:
    void bfmeTwoCGD();
    char pad00[0xae10];
    Rva009A30B0Record *buckets[0x493];
    char padc05c[4];
    unsigned fieldc060;
    Rva009A30B0Record *fieldc064;
    __forceinline Rva009A30B0Record *next() {
        while (!fieldc064) {
            if (fieldc060 + 1 == 0x493) return 0;
            ++fieldc060;
            fieldc064 = buckets[fieldc060];
        }
        Rva009A30B0Record *p = fieldc064;
        fieldc064 = p->next;
        return p;
    }
};
void BfmeThingCGD::bfmeTwoCGD() {
    fieldc060 = 0;
    fieldc064 = buckets[0];
    Rva009A30B0Record *p;
    while ((p = next()) != 0) {
        if (p->first->field04 && p->second->field04) {
            if (!p->state)
                p->state = p->first->field04->slot20(p->second->field04->slot0c(&p->field14,&p->field20)) ? 1 : 2;
            if (p->state != 2) {
                p->first->field04->slot24(p->second->field04->slot0c(&p->field14,&p->field20));
                if (p->first->field04 && p->second->field04) {
                    Rva009A30B0Vector v = p->field20;
                    v.x = -v.x; v.y = -v.y; v.z = -v.z;
                    p->second->field04->slot24(p->first->field04->slot0c(&p->field14,&v));
                }
            }
        }
    }
}
