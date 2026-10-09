// Retail 009A6780: derive fixed-point reciprocal and scaled quantizer tables.
#include <string.h>
extern const unsigned short g_bfmeApplyTableC[64];
extern const short g_bfmeApplyTableD[];
extern const unsigned g_bfmeTableBZ[64];
// Retail has distinct 64-dword quantizer tables at each of these VAs.
// Keep the existing external ABI views and put their physical storage in
// retail's read-only section; every table has its own verified data row.
#pragma section(".rdata", read)
__declspec(allocate(".rdata")) unsigned g_Rva01141808[64] =
{
    94, 92, 90, 88, 86, 82, 78, 74,
    70, 66, 62, 58, 54, 53, 52, 51,
    50, 49, 48, 47, 46, 45, 44, 43,
    42, 40, 39, 37, 36, 35, 34, 33,
    32, 31, 30, 29, 28, 27, 26, 25,
    24, 23, 22, 21, 20, 19, 18, 17,
    16, 15, 14, 13, 12, 11, 10, 9,
    8, 7, 6, 5, 4, 3, 2, 1,
};

__declspec(allocate(".rdata")) int g_Rva01141908[64] =
{
    330, 314, 298, 284, 264, 246, 228, 213,
    201, 190, 178, 167, 156, 153, 149, 146,
    144, 141, 138, 135, 132, 130, 127, 124,
    121, 115, 110, 104, 99, 96, 94, 90,
    85, 82, 79, 76, 74, 71, 69, 66,
    63, 61, 58, 55, 53, 50, 47, 45,
    43, 40, 38, 36, 33, 31, 28, 24,
    21, 18, 16, 13, 10, 7, 4, 2,
};

__declspec(allocate(".rdata")) int g_Rva01141A08[64] =
{
    330, 314, 298, 284, 264, 246, 228, 213,
    201, 190, 178, 167, 156, 153, 149, 146,
    144, 141, 138, 135, 132, 130, 127, 124,
    121, 115, 110, 104, 99, 96, 94, 90,
    85, 82, 79, 76, 74, 71, 69, 66,
    63, 61, 58, 55, 53, 50, 47, 45,
    43, 40, 38, 36, 33, 31, 28, 24,
    21, 18, 16, 13, 10, 7, 4, 2,
};

__declspec(allocate(".rdata")) int g_Rva01141B08[64] =
{
    48, 56, 64, 70, 78, 82, 86, 88,
    91, 92, 94, 94, 99, 103, 102, 100,
    99, 97, 95, 93, 91, 89, 87, 85,
    83, 79, 77, 73, 71, 69, 67, 65,
    64, 62, 60, 58, 56, 54, 52, 50,
    48, 46, 44, 42, 40, 38, 36, 34,
    32, 30, 28, 26, 24, 22, 20, 18,
    16, 14, 12, 10, 8, 6, 4, 2,
};

__declspec(allocate(".rdata")) int g_Rva01141C08[64] =
{
    48, 56, 64, 70, 78, 82, 86, 88,
    91, 92, 94, 94, 99, 103, 102, 100,
    99, 97, 95, 93, 91, 89, 87, 85,
    83, 79, 77, 73, 71, 69, 67, 65,
    64, 62, 60, 58, 56, 54, 52, 50,
    48, 46, 44, 42, 40, 38, 36, 34,
    32, 30, 28, 26, 24, 22, 20, 18,
    16, 14, 12, 10, 8, 6, 4, 2,
};

__declspec(allocate(".rdata")) int g_Rva01141E08[64] =
{
    170, 162, 152, 150, 140, 130, 125, 121,
    121, 118, 113, 111, 110, 108, 108, 106,
    105, 96, 93, 87, 86, 83, 83, 83,
    83, 78, 78, 78, 66, 66, 63, 63,
    61, 61, 58, 58, 56, 56, 46, 46,
    46, 46, 43, 43, 41, 38, 38, 38,
    38, 38, 35, 24, 24, 24, 23, 23,
    20, 19, 16, 13, 6, 6, 4, 4,
};

__declspec(allocate(".rdata")) int g_Rva01141F08[64] =
{
    170, 162, 152, 150, 140, 130, 125, 121,
    121, 118, 113, 111, 110, 108, 108, 106,
    105, 96, 93, 87, 86, 83, 83, 83,
    83, 78, 78, 78, 66, 66, 63, 63,
    61, 61, 58, 58, 56, 56, 46, 46,
    46, 46, 43, 43, 41, 38, 38, 38,
    38, 38, 35, 24, 24, 24, 23, 23,
    20, 19, 16, 13, 6, 6, 4, 4,
};

__declspec(allocate(".rdata")) int g_Rva01142008[64] =
{
    20, 28, 38, 40, 44, 46, 50, 50,
    51, 57, 59, 61, 62, 64, 66, 67,
    67, 62, 63, 64, 64, 62, 62, 62,
    62, 62, 62, 62, 54, 54, 52, 52,
    50, 50, 48, 48, 46, 46, 38, 38,
    38, 38, 36, 36, 34, 32, 32, 32,
    32, 32, 30, 22, 22, 22, 20, 20,
    18, 16, 14, 10, 6, 6, 4, 4,
};

__declspec(allocate(".rdata")) int g_Rva01142108[64] =
{
    20, 30, 38, 40, 44, 46, 50, 50,
    51, 57, 59, 61, 62, 64, 66, 67,
    67, 62, 63, 64, 64, 62, 62, 62,
    62, 62, 62, 62, 54, 54, 52, 52,
    50, 50, 48, 48, 46, 46, 38, 38,
    38, 38, 36, 36, 34, 32, 32, 32,
    32, 32, 30, 22, 22, 22, 20, 20,
    18, 16, 14, 10, 6, 6, 4, 4,
};

__declspec(allocate(".rdata")) int g_Rva01142208[64] =
{
    -8, 0, 5, 10, 10, 10, 10, 10,
    15, 15, 15, 15, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20,
    20, 20, 20, 20, 20, 20, 20, 20,
    25, 25, 25, 25, 25, 25, 25, 25,
    25, 25, 25, 25, 25, 25, 25, 25,
    30, 30, 30, 30, 30, 30, 30, 30,
};

// The eight-byte selector span ends at the binary64 literal VA01142610.
__declspec(allocate(".rdata")) unsigned char g_Rva01142608[8] =
{
    0, 0, 0, 0, 1, 1, 0, 0
};
extern int g_rva01142308[];
struct Rva009A6780State {
    int index,at0004;
    short at0008[8],at0018[8],at0028[8];
    unsigned char pad0038[0x158];
    int at0190[2][64],at0390[2][64],at0590[2][64],at0790[2][64];
};
// The sole retail direct caller 9A6B8B pushes two cdecl words. The 945-byte
// body reads entryESP+4 and never reads entryESP+8, so the second word is
// deliberately unused in this caller-compatible emission view. Original
// native formal parameter count remains unknown.
void Rva009A6780BuildQuantizers(Rva009A6780State* s, int)
{
    int index=s->index;
    double reciprocal=1.0/(reinterpret_cast<const short *>(g_bfmeApplyTableC)[index]*4);
    reciprocal*=65536.0;
    s->at0190[0][0]=(int)(reciprocal+0.5);
    s->at0390[0][0]=g_Rva01142008[index];
    s->at0590[0][0]=g_Rva01141E08[index];
    int i;
    for(i=1;i<64;++i) {
        reciprocal=1.0/(g_bfmeTableBZ[s->index]*4);
        reciprocal*=65536.0;
        s->at0190[0][i]=(int)(reciprocal+0.5);
        s->at0390[0][i]=g_Rva01141B08[s->index];
        s->at0590[0][i]=g_Rva01141908[s->index];
    }
    index=s->index;
    reciprocal=1.0/(g_bfmeApplyTableD[index]*4);
    reciprocal*=65536.0;
    s->at0190[1][0]=(int)(reciprocal+0.5);
    s->at0390[1][0]=g_Rva01142108[index];
    s->at0590[1][0]=g_Rva01141F08[index];
    for(i=1;i<64;++i) {
        reciprocal=1.0/(g_Rva01141808[s->index]*4);
        reciprocal*=65536.0;
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
        s->at0790[0][i]=(int)(g_bfmeTableBZ[s->index]*g_Rva01142208[i]*4)/100;
        s->at0790[1][i]=(int)(g_Rva01141808[s->index]*g_Rva01142208[i]*4)/100;
    }
}

// Retail 009A6BA0: quantize a 64-coefficient block in table order with a
// dead zone widened by the zero run; the compiler unrolls the loop by three.
void Rva009A6BA0QuantizeBlock(Rva009A6780State* s,const short* src,short* dst,unsigned char mode)
{
    unsigned char run=0;
    int bank=g_Rva01142608[mode];
    int* multipliers=s->at0190[bank];
    int* offsets=s->at0390[bank];
    int* thresholds=s->at0590[bank];
    int* runs=s->at0790[bank];
    memset(dst,0,128);
    int value=src[0];
    int threshold=thresholds[0];
    if(value>=threshold) dst[0]=(short)(((value+offsets[0])*multipliers[0])>>16);
    else if(value<=-threshold) dst[0]=(short)(((value-offsets[0])*multipliers[0]+65535)>>16);
    else run=1;
    for(unsigned int i=1;i<64;i++) {
        int pos=g_rva01142308[i];
        if(src[pos]>=thresholds[pos]+runs[run]) {
            dst[i]=(short)(((src[pos]+offsets[pos])*multipliers[pos])>>16);
            run=0;
        } else if(src[pos]<=-thresholds[pos]-runs[run]) {
            dst[i]=(short)(((src[pos]-offsets[pos])*multipliers[pos]+65535)>>16);
            run=0;
        } else ++run;
    }
}
