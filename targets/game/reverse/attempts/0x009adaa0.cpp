// ?Rva009ADAA0@@YAXPAURva009AF200Context@@PAE1IIHPBI@Z
// partial score=0.2821917808219178 date=2026-09-27
// Retail 009ADAA0 edge filter. Actual boundary is RET at 009ADD79 (730 bytes).
struct Rva009AF200Context;
extern unsigned char g_Rva01356FE0[];
#define DIFF(a,b) ((int)((a)-(b))>0 ? (a)-(b) : (b)-(a))
void Rva009ADAA0(Rva009AF200Context* context,unsigned char* source,unsigned char* destination,unsigned stride,unsigned width,int index,const unsigned* table)
{
    int limit=table[*(int*)((char*)context+12)];
    unsigned end=width-1+index;
    if((unsigned)index<end) {
        int threshold=limit*limit*3>>5;
        int distance=source-destination;
        unsigned char* dest=destination+5;
        unsigned count=end-index;
        do {
            source+=8;
            unsigned char* in=source;
            unsigned char* out=dest;
            int rows=8;
            do {
                int pixels[10];
                pixels[2]=in[-3];
                pixels[1]=in[-4];
                pixels[0]=in[-5];
                pixels[3]=in[-2];
                pixels[5]=in[0];
                pixels[6]=in[1];
                pixels[7]=in[2];
                pixels[8]=in[3];
                pixels[9]=in[4];
                pixels[4]=in[-1];
                int left=DIFF(pixels[1],pixels[0]);
                left+=DIFF(pixels[2],pixels[1]);
                left+=DIFF(pixels[3],pixels[2]);
                left+=DIFF(pixels[4],pixels[3]);
                int right=DIFF(pixels[5],pixels[6]);
                right+=DIFF(pixels[6],pixels[7]);
                right+=DIFF(pixels[7],pixels[8]);
                right+=DIFF(pixels[8],pixels[9]);
                if(left<threshold && right<threshold && (int)(pixels[5]-pixels[4])<limit && (int)(pixels[4]-pixels[5])<limit) {
                    int sum=pixels[4]+pixels[0]*3+pixels[3]+pixels[2]+4+pixels[1];
                    out[-1]=(unsigned char)((int)(pixels[1]+sum)>>3);
                    sum+=pixels[5]-pixels[0]; out[0]=(unsigned char)((int)(pixels[2]+sum)>>3);
                    sum+=pixels[6]-pixels[0]; out[1]=(unsigned char)((int)(pixels[3]+sum)>>3);
                    sum+=pixels[7]-pixels[0]; out[2]=(unsigned char)((int)(sum+pixels[4])>>3);
                    sum+=pixels[8]-pixels[1]; out[3]=(unsigned char)((int)(sum+pixels[5])>>3);
                    sum+=pixels[9]-pixels[2]; out[4]=(unsigned char)((int)(sum+pixels[6])>>3);
                    sum+=pixels[9]-pixels[3]; out[5]=(unsigned char)((int)(sum+pixels[7])>>3);
                    out[6]=(unsigned char)((int)((pixels[9]-pixels[4])+sum+pixels[8])>>3);
                } else {
                    int adjust=(*(int**)((char*)context+0x38))[(int)((pixels[5]-pixels[4])*3-pixels[6]+4+pixels[3])>>3];
                    out[2]=g_Rva01356FE0[pixels[4]+adjust];
                    out[3]=g_Rva01356FE0[pixels[5]-adjust];
                }
                in+=stride;out+=stride;
            }while(--rows);
            dest+=8;
        }while(--count);
    }
}
