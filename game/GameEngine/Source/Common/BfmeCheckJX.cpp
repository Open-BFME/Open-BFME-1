// Retail 009A89C0. Existing bfmeInitCodecJX caller establishes this name.
// Fields are offset-derived; sizes and helper ABIs were checked against retail.
struct CodecState;
struct Rva009A8910Context;
class Bucket { public: enum BucketMagicEnum { Zero = 0 }; static void* operator new(unsigned, BucketMagicEnum); };
void Rva009A4E50Configure(void*,unsigned,int);
void bfmeInitD70(void*,void*);
int Rva009A86F0Allocate(void*);
int Rva009A8910Initialize(Rva009A8910Context*,int);
void bfmeStepJW(void*);
extern int g_Rva01142620[24];
struct CodecState {
    unsigned char pad0000[0x1a8];
    unsigned at01a8;
    unsigned char pad01ac[0x4];
    unsigned at01b0;
    unsigned at01b4;
    unsigned at01b8;
    unsigned at01bc;
    unsigned at01c0;
    unsigned at01c4;
    unsigned char pad01c8[0x24];
    unsigned at01ec;
    unsigned at01f0;
    unsigned at01f4;
    unsigned at01f8;
    unsigned at01fc;
    unsigned at0200;
    unsigned at0204;
    unsigned at0208;
    unsigned at020c;
    unsigned at0210;
    unsigned at0214;
    unsigned at0218;
    unsigned at021c;
    unsigned at0220;
    unsigned at0224;
    unsigned at0228;
    unsigned at022c;
    unsigned at0230;
    unsigned char pad0234[0x8];
    unsigned at023c;
    unsigned at0240;
    unsigned char pad0244[0x20];
    unsigned at0264;
    unsigned at0268;
    unsigned char pad026c[0x2c];
    unsigned at0298;
};
int bfmeCheckJX(CodecState* s)
{
    if(s->at01a8>0) Rva009A4E50Configure(s,1,(int)s->at01a8);
    s->at01ec=s->at01b0*s->at01b4;
    s->at01f0=s->at01ec/4;
    s->at01f8=s->at01b0/s->at01c0;
    s->at01f4=s->at01b4/s->at01c4;
    s->at0200=s->at01f8*s->at01f4;
    s->at01fc=s->at0200*3/2;
    s->at0204=s->at0200/4;
    s->at01b8=s->at01b0+96;
    s->at01bc=(int)s->at01b8/2;
    s->at0208=(s->at01b4+96)*s->at01b8;
    s->at020c=s->at0208/4;
    unsigned allocation=s->at0208+s->at020c*2;
    s->at0210=0;
    s->at0214=s->at01ec;
    s->at0218=s->at01ec+s->at01f0;
    s->at021c=0;
    s->at0220=s->at0208;
    s->at0224=s->at0208+s->at020c;
    s->at022c=(s->at01b4>>4)+((s->at01b4&15)!=0)+6;
    s->at0230=(s->at01b0>>4)+((s->at01b0&15)!=0)+6;
    s->at0228=s->at0230*s->at022c;
    int* out=(int*)((unsigned char*)s+0x6ac);
    unsigned offset=0;
    do {
        out[-1]=*(int*)((char*)g_Rva01142620+offset)*(int)s->at0230+*(int*)((char*)g_Rva01142620+offset+4);
        out[0]=*(int*)((char*)g_Rva01142620+offset+8)*(int)s->at0230+*(int*)((char*)g_Rva01142620+offset+12);
        out[1]=*(int*)((char*)g_Rva01142620+offset+16)*(int)s->at0230+*(int*)((char*)g_Rva01142620+offset+20);
        out[2]=*(int*)((char*)g_Rva01142620+offset+24)*(int)s->at0230+*(int*)((char*)g_Rva01142620+offset+28);
        out[3]=*(int*)((char*)g_Rva01142620+offset+32)*(int)s->at0230+*(int*)((char*)g_Rva01142620+offset+36);
        out[4]=*(int*)((char*)g_Rva01142620+offset+40)*(int)s->at0230+*(int*)((char*)g_Rva01142620+offset+44);
        offset+=48; out+=6;
    }while(offset<96);
    void* cfg=(unsigned char*)s+0x1b0;
    bfmeInitD70((void*)s->at0298,cfg);
    if(!Rva009A86F0Allocate(s)) return 0;
    if(!Rva009A8910Initialize((Rva009A8910Context*)s,allocation)) {bfmeStepJW(s); return 0;}
    if(s->at0264==0 && (int)s->at023c!=0 && (*(int*)cfg!=(int)s->at023c || (int)s->at01b4!=(int)s->at0240)) {
        void* p=Bucket::operator new(((unsigned)(((int)s->at0240+32)*((int)s->at023c+32)*3)>>1)+32,Bucket::Zero);
        s->at0268=(unsigned)p;s->at0264=((unsigned)p+31)&~31;
    }
    return 1;
}
