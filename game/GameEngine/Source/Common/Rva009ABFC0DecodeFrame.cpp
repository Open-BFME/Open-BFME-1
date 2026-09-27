// Retail 009ABFC0: initialize per-frame tables and visit interior blocks.
struct Rva009AAFE0Context;
struct Rva009AB760Context;
struct Rva009AB7F0Context;
void Rva009B6A30LoadTables(unsigned char*);
void Rva009B65F0Update(unsigned char*,unsigned char);
void Rva009AAFE0BuildTable(Rva009AAFE0Context*,const unsigned char*);
void Rva009AB530BuildProbabilityTables(unsigned char*,bool);
struct Rva009AB320Tables;
void Rva009AB320BuildTables(Rva009AB320Tables*);
int bfmeGoUSC(void*,int);
void Rva009AB7F0Reset(Rva009AB7F0Context*);
void Rva009AB760Initialize(Rva009AB760Context*);
void Rva009B5DB0Vp6DecodeBlock(unsigned char*,int,unsigned);
extern "C" void* memcpy(void*,const void*,unsigned);
extern "C" void* memset(void*,int,unsigned);
extern unsigned char g_Rva01143758[80],g_Rva0114338C[2],g_Rva0114336C[14],g_Rva01143390[2],g_Rva0114337C[16];
extern unsigned char g_Rva01142B60[64],g_Rva01142B20[64];
#define U(o) (*(unsigned*)(s+(o)))
void Rva009ABFC0DecodeFrame(unsigned char* s)
{
    unsigned rows=U(0x22c),columns=U(0x230);
    if(s[0x1ac]) {
        Rva009B6A30LoadTables(s);
        Rva009B65F0Update(s,s[0x1ac]);
        U(0x39c)=0;
    } else {
        memcpy(s+0x72c,g_Rva01143758,80);
        memcpy(s+0x706,g_Rva0114338C,2);
        memcpy(s+0x708,g_Rva0114336C,14);
        memcpy(s+0x704,g_Rva01143390,2);
        memcpy(s+0x71c,g_Rva0114337C,16);
        memset(s+0x67c,128,11);
        memset(s+0x687,128,11);
        memset((void*)U(0x6f0),1,U(0x228));
        if(U(0x1dc)==1) memcpy(s+0x63c,g_Rva01142B60,64); else memcpy(s+0x63c,g_Rva01142B20,64);
        Rva009AAFE0BuildTable((Rva009AAFE0Context*)s,s+0x63c);
    }
    Rva009AB530BuildProbabilityTables(s,*(bool*)(s+0x1ac));
    unsigned char* p=s+0x57c;
    int n=16;
    do {
        p[0]=*(unsigned char*)(*(unsigned*)(U(0x13c)+0x13c)+p[0x40]*4);
        p[1]=*(unsigned char*)(*(unsigned*)(U(0x13c)+0x13c)+p[0x41]*4);
        p[2]=*(unsigned char*)(*(unsigned*)(U(0x13c)+0x13c)+p[0x42]*4);
        p[3]=*(unsigned char*)(*(unsigned*)(U(0x13c)+0x13c)+p[0x43]*4);
        p+=4;
    }while(--n);
    if(U(0x4520)) Rva009AB320BuildTables((Rva009AB320Tables*)s);
    if(U(0x1dc)==1) U(0x6e8)=(unsigned char)bfmeGoUSC(s+0x150,8);
    Rva009AB7F0Reset((Rva009AB7F0Context*)s);
    memset((void*)U(4),0,768);
    U(0x4524)=0;U(0x4528)=0;U(0x452c)=0;U(0x4530)=0;
    for(unsigned row=3;row<rows-3;++row) {
        Rva009AB760Initialize((Rva009AB760Context*)s);
        for(unsigned col=3;col<columns-3;++col) Rva009B5DB0Vp6DecodeBlock(s,row,col);
    }
}
