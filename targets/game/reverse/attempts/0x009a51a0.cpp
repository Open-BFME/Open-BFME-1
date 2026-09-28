// ?Rva009A51A0DecodeFrame@@YAXPAXPAI@Z
// partial score=0.7384481255448997 date=2026-09-28
// Retail 009A51A0-009A561A inclusive; cdecl(context, ten-dword plane descriptor).
// All offset accessors describe observed storage; no product type is asserted.
struct BfmeVp6Context;
extern "C" int __cdecl bfmeVp6ThresholdSelect(BfmeVp6Context *);
void __cdecl d_009a8410();
void __cdecl d_009a6130();
typedef void (__cdecl *Rva009A8410ReadTicks)(unsigned *);
typedef void (__cdecl *Rva009A6130Call)(void *, int, int, unsigned, unsigned, unsigned, unsigned, unsigned, int, int);
// The dump names are retained, with call-site ABI independently read from bytes.
#define readTicks ((Rva009A8410ReadTicks)d_009a8410)
#define decodePlane ((Rva009A6130Call)d_009a6130)
class Bucket {
public:
    enum BucketMagicEnum { Bucket_GLUE_NOT_IMPLEMENTED=0 };
    static void *__cdecl operator new(unsigned, BucketMagicEnum);
};
struct Rva009A5C40Context;
int Rva009A5C40Initialize(Rva009A5C40Context *);
struct Rva009AAC80Context;
void Rva009AAC80CodecGrid(Rva009AAC80Context *);
struct Rva009AABB0Context;
void Rva009AABB0CodecDispatch(Rva009AABB0Context *);
struct Rva009AA8F0Context;
struct Rva009AA8F0Block;
void Rva009AA8F0Dispatch(Rva009AA8F0Context *, int, Rva009AA8F0Block *);
extern void (__cdecl *Rva01356EAC)(void *,unsigned,unsigned,unsigned,unsigned);
extern void (__cdecl *Rva01356B48)();
#define U(off) (*(unsigned *)((char *)context+(off)))
#define B(off) (*(unsigned char *)((char *)context+(off)))
void Rva009A51A0DecodeFrame(void *context, unsigned *out)
{
    unsigned endTicks, startTicks;
    readTicks(&startTicks);
    U(0x1a0)=bfmeVp6ThresholdSelect((BfmeVp6Context *)context);
    if(U(0x1a0) || (U(0x1dc) && U(0x4944))) {
        if(!U(0x25c)) {
            void *allocation=Bucket::operator new(U(0x208)+U(0x20c)*2+32+U(0x1b8),Bucket::Bucket_GLUE_NOT_IMPLEMENTED);
            U(0x260)=(unsigned)allocation;
            U(0x25c)=((unsigned)allocation+31)&~31u;
            Rva009A5C40Initialize((Rva009A5C40Context *)U(0x298));
        }
        if(U(0x1a0)>200) {
            decodePlane((void *)U(0x298),B(0x19c),B(0x1ac),U(0x1a0)-200,U(0x6a0),U(0x254),U(0x25c),U(0x148),4,1);
            readTicks(&endTicks);
            Rva009AAC80CodecGrid((Rva009AAC80Context *)context);
        } else if(U(0x1a0)>100) {
            decodePlane((void *)U(0x298),B(0x19c),B(0x1ac),U(0x1a0)-100,U(0x6a0),U(0x254),U(0x25c),U(0x148),4,1);
            readTicks(&endTicks);
            Rva009AABB0CodecDispatch((Rva009AABB0Context *)context);
        } else {
            decodePlane((void *)U(0x298),B(0x19c),B(0x1ac),U(0x1a0),U(0x6a0),U(0x254),U(0x25c),U(0x148),4,1);
            readTicks(&endTicks);
        }
        if(U(0x493c)) Rva01356EAC((void *)U(0x298),U(0x493c),U(0x4940),U(0x25c),U(0x25c));
    }
    if(U(0x1b0)>=U(0x23c) && U(0x1b4)>=U(0x240)) {
        out[0]=U(0x1b0); out[1]=U(0x1b4); out[2]=U(0x1b8);
        out[3]=U(0x1b0)>>1; out[4]=U(0x1b4)>>1; out[5]=U(0x1bc);
        if(!U(0x1a0) && (!U(0x1dc) || !U(0x4944))) {
            out[6]=(U(0x1b8)+1)*48+U(0x21c)+U(0x254);
            out[7]=U(0x220)+(U(0x1bc)+1)*24+U(0x254);
            out[8]=U(0x224)+(U(0x1bc)+1)*24+U(0x254);
            out[9]=U(0x21c)+U(0x254);
        } else {
            out[6]=(U(0x1b8)+1)*48+U(0x21c)+U(0x25c);
            out[7]=U(0x220)+(U(0x1bc)+1)*24+U(0x25c);
            out[8]=U(0x224)+(U(0x1bc)+1)*24+U(0x25c);
            out[9]=U(0x21c)+U(0x25c);
        }
    } else {
        out[0]=U(0x23c)+32;
        out[1]=U(0x240)+32;
        out[3]=(int)out[0]/2; out[2]=out[0]; out[4]=(int)out[1]/2; out[5]=out[3];
        out[6]=U(0x264);
        out[7]=U(0x264)+out[1]*out[0];
        out[8]=out[4]*out[3]+out[1]*out[0]+U(0x264);
        out[9]=U(0x264);
        if(U(0x1a0)) Rva009AA8F0Dispatch((Rva009AA8F0Context *)U(0x298),U(0x25c),(Rva009AA8F0Block *)out);
        else Rva009AA8F0Dispatch((Rva009AA8F0Context *)U(0x298),U(0x254),(Rva009AA8F0Block *)out);
        out[6]+=((out[1]-U(0x240))>>1)*out[2]+((out[0]-U(0x23c))>>1);
        out[0]=U(0x23c); out[1]=U(0x240);
        out[7]+=((out[4]-(U(0x240)>>1))>>1)*out[5]+((out[3]-(U(0x23c)>>1))>>1);
        out[8]+=((out[4]-(U(0x240)>>1))>>1)*out[5]+((out[3]-(U(0x23c)>>1))>>1);
        out[3]=U(0x23c)>>1; out[4]=U(0x240)>>1;
    }
    Rva01356B48();
    unsigned elapsed=(endTicks-startTicks)/U(0x1a4);
    volatile unsigned *sample=(unsigned *)((char *)context+0x918)+(U(0x1a0)%10);
    if(!*sample) *sample=elapsed;
    else *sample=(*sample*7+elapsed)>>3;
}
