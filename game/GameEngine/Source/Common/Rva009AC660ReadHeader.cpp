// Retail RVA 009AC660, 1279 bytes. Offset-derived view: no class identity claimed.
// ESI input is witnessed by the sole caller at 009ACB60.
// The external harness exists only to let MSVC select the private static ABI.
struct Rva009AC5D0State;
struct BfmeBits1186;
struct BfmeS1040;
struct CodecState;
class Rva009A5E90Owner;
class Rva009A5EA0Owner;
unsigned Rva009AC5D0ReadBits(Rva009AC5D0State*, unsigned);
void bfmeLoadTable(unsigned char*);
void bfmeInit1186(BfmeBits1186*, unsigned char*);
void Rva009A5E90(Rva009A5E90Owner*,int);
void Rva009A5EA0(Rva009A5EA0Owner*,int);
int bfmeGoUSC(void*,int);
int bfmeCheckJX(CodecState*);
int Rva009B4600DecodeBool(void*,int);
void bfmeGo1040B(BfmeS1040*,int);
extern "C" void* __cdecl memset(void*,int,unsigned);
#pragma intrinsic(memset)
#define U(o) (*(unsigned*)(s+(o)))
#define B(o) (*(unsigned char*)(s+(o)))
#define P(o) (*(unsigned char**)(s+(o)))

static int Rva009AC660ReadHeader(unsigned char* s)
{
    Rva009AC5D0State* bits=(Rva009AC5D0State*)(s+0x450c);
    B(0x1ac)=(unsigned char)Rva009AC5D0ReadBits(bits,1);
    unsigned char index=(unsigned char)Rva009AC5D0ReadBits(bits,6);
    U(0x944)=(unsigned char)Rva009AC5D0ReadBits(bits,1);
    BfmeBits1186* decoder;
    if (!B(0x1ac)) {
        B(0x19c)=(unsigned char)Rva009AC5D0ReadBits(bits,5);
        B(0x19d)=(unsigned char)Rva009AC5D0ReadBits(bits,2);
        if (B(0x19c)>7) return 0;
        // Retail passes a second unused slot to the existing one-argument callee.
        ((void (__cdecl *)(unsigned char*,unsigned char))bfmeLoadTable)(P(0x13c),B(0x19c));
        U(0x1dc)=(unsigned char)Rva009AC5D0ReadBits(bits,1);
        if (!U(0x944) && B(0x19d)) {
            decoder=(BfmeBits1186*)(s+0x150);
            bfmeInit1186(decoder,P(0x450c)+2);
        } else {
            decoder=(BfmeBits1186*)(s+0x150);
            bfmeInit1186(decoder,P(0x450c)+4);
            U(0x451c)=Rva009AC5D0ReadBits(bits,16);
        }
        Rva009A5E90((Rva009A5E90Owner*)P(0x298),U(0x1dc));
        if (U(0x1dc)) Rva009A5EA0((Rva009A5EA0Owner*)P(0x298),U(0x4944));
        unsigned a=(unsigned char)bfmeGoUSC(decoder,8)*2u;
        unsigned b=(unsigned char)bfmeGoUSC(decoder,8)*2u;
        unsigned c=(unsigned char)bfmeGoUSC(decoder,8)*2u;
        unsigned d=(unsigned char)bfmeGoUSC(decoder,8)*2u;
        if (!U(0x1cc)) U(0x1cc)=1;
        if (!U(0x1d4)) U(0x1d4)=1;
        unsigned oldB=U(0x1f8)*U(0x1c8)*8/U(0x1cc);
        unsigned oldA=U(0x1d0)*U(0x1f4)*8/U(0x1d4);
        U(0x1e0)=d*8;
        U(0x1e4)=c*8;
        if (a>=c) { U(0x1d0)=1; U(0x1d4)=1; }
        else if (a*5>=c*4) { U(0x1d0)=5; U(0x1d4)=4; }
        else if (a*5>=c*3) { U(0x1d0)=5; U(0x1d4)=3; }
        else { U(0x1d0)=2; U(0x1d4)=1; }
        if (b>=d) { U(0x1c8)=1; U(0x1cc)=1; }
        else if (b*5>=d*4) { U(0x1c8)=5; U(0x1cc)=4; }
        else if (b*5>=d*3) { U(0x1c8)=5; U(0x1cc)=3; }
        else { U(0x1c8)=2; U(0x1cc)=1; }
        unsigned newB=U(0x1c8)*b*8/U(0x1cc);
        unsigned newA=U(0x1d0)*a*8/U(0x1d4);
        U(0x234)=newB;
        U(0x238)=newA;
        U(0x1d8)=bfmeGoUSC(decoder,2);
        if (a!=U(0x1f4) || b!=U(0x1f8)) {
            U(0x1b0)=b*8;
            U(0x1b4)=a*8;
            bfmeCheckJX((CodecState*)s);
        }
        if (P(0x264) && (oldB!=newB || oldA!=newA)) {
            memset(P(0x264),0,(U(0x240)+32)*(U(0x23c)+32));
            unsigned n=(U(0x240)+32)*(U(0x23c)+32);
            memset(P(0x264)+n,128,n/2);
        }
        if (B(0x19d)) {
            if (Rva009B4600DecodeBool(decoder,128)) {
                B(0x692)=2;
                U(0x694)=bfmeGoUSC(decoder,5)<<5;
                B(0x693)=(unsigned char)bfmeGoUSC(decoder,3);
            } else B(0x692)=Rva009B4600DecodeBool(decoder,128)!=0;
        }
    } else {
        if (!U(0x944) && B(0x19d)) {
            decoder=(BfmeBits1186*)(s+0x150);
            bfmeInit1186(decoder,P(0x450c)+1);
        } else {
            decoder=(BfmeBits1186*)(s+0x150);
            bfmeInit1186(decoder,P(0x450c)+3);
            U(0x451c)=Rva009AC5D0ReadBits(bits,16);
        }
        U(0x698)=Rva009B4600DecodeBool(decoder,128);
        if (B(0x19d)) {
            B(0x4534)=(unsigned char)Rva009B4600DecodeBool(decoder,128);
            if (B(0x4534)) B(0x4534)=(unsigned char)Rva009B4600DecodeBool(decoder,128) | (B(0x4534)<<1);
        }
    }
    U(0x4520)=Rva009B4600DecodeBool(decoder,128);
    *(unsigned*)P(0x13c)=index;
    unsigned char* table=P(0x13c);
    *(unsigned*)(table+4)=((unsigned*)(table+0x3c))[index];
    // Retail zero-extends this byte into the outgoing four-byte stack slot.
    // Preserve the existing callee identity while expressing the narrow call-site ABI.
    ((void (__cdecl *)(BfmeS1040*,unsigned char))bfmeGo1040B)((BfmeS1040*)P(0x13c),B(0x19c));
    return 1;
}

// The sole retail caller passes the codec state and consumes an int boolean.
int d_009acb60(unsigned char* s)
{
    int result = 1;
    if (!Rva009AC660ReadHeader(s))
        result = 0;
    return result;
}

#undef U
#undef B
#undef P

