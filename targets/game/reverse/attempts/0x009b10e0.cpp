// ?d_009b10e0@@YAXXZ
// partial score=0.783 date=2026-09-28
// ?filterBlock009B10E0@@YAXPAXPAE1HIPBH@Z
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Actual extent is 2030 bytes: ret at RVA009B18CD followed by CC CC.
// The next independent entry at RVA009B18D0 belongs to another dispatch slot.
// Address-derived identities until independent native names are proved.
typedef unsigned char byte;
extern const int g_rva012D8158[];
#define ABS(a) ((a)>0 ? (a) : -(a))
#define LIMIT(v) ((v)<-64 ? fallback : ((v)<0 ? 0 : ((v)>high ? high : (v))))
#define CLIP(v) ((v)<0 ? 0 : ((v)>255 ? 255 : (v)))
void filterBlock009B10E0(void *context, byte *src, byte *dst, int stride,
    unsigned qindex, const int *quant)
{
    int q = quant[qindex];
    int fallback = g_rva012D8158[qindex];
    int high;
    short lr[8][9], ud[9][8];
    int out[8];
    int row,col;
    byte *p;
    int v;
    short *ur=&ud[0][0], *hr=&lr[0][0];
    byte *above=src-stride; byte *below=src+stride;
    high=q*3;
    if(high>32) high=32;
    p=src;
    for(row=0;row<9;row++) {
        for(col=0;col<8;col++) {
            v=q+32-ABS(p[col]-p[col-stride]);
            ur[col]=(short)LIMIT(v);
        }
        p+=stride; ur+=8;
    }
    p=src;
    for(row=0;row<8;row++) {
        for(col=0;col<9;col++) {
            v=q+32-ABS(p[col]-p[col-1]);
            hr[col]=(short)LIMIT(v);
        }
        p+=stride; hr+=9;
    }
    p=src;
    for(row=0;row<8;row++) {

            v=((128-lr[row][0+1]-ud[row+1][0]-ud[row][0]-lr[row][0])*p[0]
               +ud[row+1][0]*below[0]
               +lr[row][0]*p[0-1]
               +ud[row][0]*above[0]
               +lr[row][0+1]*p[0+1]+64)>>7;
            out[0]=CLIP(v);
        
            v=((128-lr[row][1+1]-ud[row+1][1]-ud[row][1]-lr[row][1])*p[1]
               +ud[row+1][1]*below[1]
               +lr[row][1]*p[1-1]
               +ud[row][1]*above[1]
               +lr[row][1+1]*p[1+1]+64)>>7;
            out[1]=CLIP(v);
        
            v=((128-lr[row][2+1]-ud[row+1][2]-ud[row][2]-lr[row][2])*p[2]
               +ud[row+1][2]*below[2]
               +lr[row][2]*p[2-1]
               +ud[row][2]*above[2]
               +lr[row][2+1]*p[2+1]+64)>>7;
            out[2]=CLIP(v);
        
            v=((128-lr[row][3+1]-ud[row+1][3]-ud[row][3]-lr[row][3])*p[3]
               +ud[row+1][3]*below[3]
               +lr[row][3]*p[3-1]
               +ud[row][3]*above[3]
               +lr[row][3+1]*p[3+1]+64)>>7;
            out[3]=CLIP(v);
        
            v=((128-lr[row][4+1]-ud[row+1][4]-ud[row][4]-lr[row][4])*p[4]
               +ud[row+1][4]*below[4]
               +lr[row][4]*p[4-1]
               +ud[row][4]*above[4]
               +lr[row][4+1]*p[4+1]+64)>>7;
            out[4]=CLIP(v);
        
            v=((128-lr[row][5+1]-ud[row+1][5]-ud[row][5]-lr[row][5])*p[5]
               +ud[row+1][5]*below[5]
               +lr[row][5]*p[5-1]
               +ud[row][5]*above[5]
               +lr[row][5+1]*p[5+1]+64)>>7;
            out[5]=CLIP(v);
        
            v=((128-lr[row][6+1]-ud[row+1][6]-ud[row][6]-lr[row][6])*p[6]
               +ud[row+1][6]*below[6]
               +lr[row][6]*p[6-1]
               +ud[row][6]*above[6]
               +lr[row][6+1]*p[6+1]+64)>>7;
            out[6]=CLIP(v);
        
            v=((128-lr[row][7+1]-ud[row+1][7]-ud[row][7]-lr[row][7])*p[7]
               +ud[row+1][7]*below[7]
               +lr[row][7]*p[7-1]
               +ud[row][7]*above[7]
               +lr[row][7+1]*p[7+1]+64)>>7;
            out[7]=CLIP(v);
                dst[0]=(byte)out[0];
        dst[1]=(byte)out[1];
        dst[2]=(byte)out[2];
        dst[3]=(byte)out[3];
        dst[4]=(byte)out[4];
        dst[5]=(byte)out[5];
        dst[6]=(byte)out[6];
        dst[7]=(byte)out[7];
        p+=stride;
        dst+=stride; above+=stride; below+=stride;
    }
}
