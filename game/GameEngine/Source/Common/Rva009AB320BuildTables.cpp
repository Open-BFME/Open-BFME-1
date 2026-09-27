// Retail 009AB320: construct groups of prefix lookup tables.
// All offsets are witnessed in this body; no semantic context identity is asserted.
struct Rva009B6320Node;
void Rva009AB0B0ExpandWeights(const unsigned char*, unsigned*);
void Rva009AB200BuildWeights(unsigned char*, int*);
void Rva009B60E0BuildTree(unsigned*, unsigned*, int);
void Rva009B62A0ExpandTable(const unsigned*, unsigned short*);
void Rva009B6320DecodeTree(Rva009B6320Node*, int, int*, unsigned char*, int, int);
// Array extents inferred from this body's strides, not an asserted codec class.
struct Rva009AB320Tables {
    unsigned char pad0000[0x3a0];
    unsigned char at03a0[2][11];
    unsigned char at03b6[2][3][6][11];
    unsigned char pad0542[0x1e];
    unsigned char at0560[2][14];
    unsigned char pad057c[0x3cc];
    int at0948[2][12];
    unsigned char at09a8[2][12];
    unsigned at09c0[2][12];
    unsigned at0a20[2][36];
    int at0b40[3][2][6][12];
    unsigned char at1200[3][2][6][12];
    unsigned at13b0[3][2][6][12];
    unsigned at1a70[3][2][6][36];
    int at2eb0[2][14];
    unsigned char at2f20[2][14];
    int at2f3c[2][14];
    unsigned at2fac[2][42];
    unsigned short at30fc[2][64];
    unsigned short at31fc[3][2][6][64];
    unsigned short at43fc[2][64];
};
void Rva009AB320BuildTables(Rva009AB320Tables* s)
{
    int plane,group,band;
    for(plane=0;plane<2;++plane) {
        Rva009AB0B0ExpandWeights(s->at03a0[plane],s->at09c0[plane]);
        Rva009B60E0BuildTree(s->at0a20[plane],s->at09c0[plane],12);
        Rva009B62A0ExpandTable(s->at0a20[plane],s->at30fc[plane]);
        Rva009B6320DecodeTree((Rva009B6320Node*)s->at0a20[plane],0,s->at0948[plane],s->at09a8[plane],0,0);
    }
    for(plane=0;plane<2;++plane) {
        Rva009AB200BuildWeights(s->at0560[plane],s->at2f3c[plane]);
        Rva009B60E0BuildTree(s->at2fac[plane],(unsigned*)s->at2f3c[plane],9);
        Rva009B62A0ExpandTable(s->at2fac[plane],s->at43fc[plane]);
        Rva009B6320DecodeTree((Rva009B6320Node*)s->at2fac[plane],0,s->at2eb0[plane],s->at2f20[plane],0,0);
    }
    for(group=0;group<3;++group) {
        for(plane=0;plane<2;++plane) {
            for(band=0;band<6;++band) {
                Rva009AB0B0ExpandWeights(s->at03b6[plane][group][band],s->at13b0[group][plane][band]);
                Rva009B60E0BuildTree(s->at1a70[group][plane][band],s->at13b0[group][plane][band],12);
                Rva009B62A0ExpandTable(s->at1a70[group][plane][band],s->at31fc[group][plane][band]);
                Rva009B6320DecodeTree((Rva009B6320Node*)s->at1a70[group][plane][band],0,s->at0b40[group][plane][band],s->at1200[group][plane][band],0,0);
            }
        }
    }
}
