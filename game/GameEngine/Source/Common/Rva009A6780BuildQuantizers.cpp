// Retail 009A6780: derive fixed-point reciprocal and scaled quantizer tables.
extern short g_Rva01141D08[],g_Rva01141D88[];
extern unsigned g_Rva01141708[],g_Rva01141808[];
extern int g_Rva01142008[],g_Rva01141E08[],g_Rva01141B08[],g_Rva01141908[];
extern int g_Rva01142108[],g_Rva01141F08[],g_Rva01141C08[],g_Rva01141A08[];
extern int g_Rva01142208[64];
extern double g_Rva01142610;
struct Rva009A6780State {
    int index,at0004;
    short at0008[8],at0018[8],at0028[8];
    unsigned char pad0038[0x158];
    int at0190[2][64],at0390[2][64],at0590[2][64],at0790[2][64];
};
void Rva009A6780BuildQuantizers(Rva009A6780State* s)
{
    int index=s->index;
    double reciprocal=1.0/(g_Rva01141D08[index]*4);
    reciprocal*=g_Rva01142610;
    s->at0190[0][0]=(int)(reciprocal+0.5);
    s->at0390[0][0]=g_Rva01142008[index];
    s->at0590[0][0]=g_Rva01141E08[index];
    int i;
    for(i=1;i<64;++i) {
        reciprocal=1.0/(g_Rva01141708[s->index]*4);
        reciprocal*=g_Rva01142610;
        s->at0190[0][i]=(int)(reciprocal+0.5);
        s->at0390[0][i]=g_Rva01141B08[s->index];
        s->at0590[0][i]=g_Rva01141908[s->index];
    }
    index=s->index;
    reciprocal=1.0/(g_Rva01141D88[index]*4);
    reciprocal*=g_Rva01142610;
    s->at0190[1][0]=(int)(reciprocal+0.5);
    s->at0390[1][0]=g_Rva01142108[index];
    s->at0590[1][0]=g_Rva01141F08[index];
    for(i=1;i<64;++i) {
        reciprocal=1.0/(g_Rva01141808[s->index]*4);
        reciprocal*=g_Rva01142610;
        s->at0190[1][i]=(int)(reciprocal+0.5);
        s->at0390[1][i]=g_Rva01141C08[s->index];
        s->at0590[1][i]=g_Rva01141A08[s->index];
    }
    for(i=0;i<8;++i) {
        s->at0008[i]=(short)s->at0390[0][1];
        s->at0018[i]=(short)s->at0190[0][1];
        s->at0028[i]=(short)s->at0590[0][1]-1;
    }
    for(i=0;i<64;++i) {
        s->at0790[0][i]=(int)(g_Rva01141708[s->index]*g_Rva01142208[i]*4)/100;
        s->at0790[1][i]=(int)(g_Rva01141808[s->index]*g_Rva01142208[i]*4)/100;
    }
}
