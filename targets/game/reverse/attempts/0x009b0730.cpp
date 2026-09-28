// _Rva009B0730
// partial score=0.39 date=2026-09-28
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// RVA 009B0730..009B0D5F. Isolated by ret/int3 on both sides.
// Seven cdecl arguments; all calls are through three witnessed callback slots.
// The last row belongs INSIDE the plane loop, unlike sibling RVA 009B0100.
struct Rva009B0730Context {
    unsigned char pad00[12];
    int field0C, field10, field14;
    unsigned char *field18;
    int field1C, field20;
    unsigned char pad24[0x78-0x24];
    unsigned char *field78, *field7C, *field80;
    int field84, field88, field8C;
    unsigned int field90, field94;
    int field98, field9C;
};
typedef int *(__cdecl *Setup009B0730)(Rva009B0730Context *,int);
typedef void (__cdecl *Filter009B0730)(Rva009B0730Context *,unsigned char *,int,const int *);
extern int g_rva012D7B58[];
extern Setup009B0730 g_rva01356E68;
extern Filter009B0730 g_rva01356E9C, g_rva01356EBC;

extern "C" void __cdecl Rva009B0730(Rva009B0730Context *ctx,int mode,int offset,
    int field14,unsigned char *flags,int flagStride,int mask)
{
    struct Frame { unsigned char *base; int rowWidth; int planeOffset; int planeWidth; int planeHeight; };
    Frame frame;
    ctx->field10=offset;
    frame.planeWidth=ctx->field90; frame.planeHeight=ctx->field94;
    ctx->field14=field14;
    ctx->field18=flags;
    ctx->field0C=mode;
    ctx->field1C=flagStride;
    ctx->field20=mask;
    int row=0, stride=0; frame.planeOffset=0;
    frame.base=0;
    frame.rowWidth=0;
    int limit=g_rva012D7B58[mode];
    if (!limit) return;
    int *work=g_rva01356E68(ctx,limit);
    for(int plane=0; plane<3; ++plane) {
        switch(plane) {
        case 0:
            frame.planeOffset=0;
            frame.planeWidth=ctx->field90; frame.planeHeight=ctx->field94;
            frame.rowWidth=frame.planeWidth;
            stride=ctx->field98;
            frame.base=ctx->field78+ctx->field10;
            break;
        case 1:
            frame.planeOffset=ctx->field84;
            frame.planeWidth=ctx->field90>>1;
            frame.planeHeight=ctx->field94>>1; frame.rowWidth=frame.planeWidth;
            stride=ctx->field9C;
            frame.base=ctx->field7C+ctx->field10;
            break;
        case 2:
            frame.planeHeight=ctx->field94>>1;
            frame.planeWidth=ctx->field90>>1;
            frame.planeOffset=ctx->field84+ctx->field88;
            frame.rowWidth=frame.planeWidth;
            stride=ctx->field9C;
            frame.base=ctx->field80+ctx->field10;
            break;
        }
        row=frame.planeOffset;
        if(ctx->field18[row*ctx->field1C] & ctx->field20) {
            if(!(ctx->field18[(row+1)*ctx->field1C] & ctx->field20))
                g_rva01356E9C(ctx,frame.base+6,stride,work);
            if(!(ctx->field18[(row+frame.rowWidth)*ctx->field1C] & ctx->field20))
                g_rva01356EBC(ctx,frame.base+stride*8,stride,work);
        }
        ++row;
        int column=1;
        for(;column<frame.planeWidth-1;++column,++row) {
            unsigned char *cursor=frame.base+column*8;
            if(ctx->field18[row*ctx->field1C] & ctx->field20) {
                g_rva01356E9C(ctx,cursor-2,stride,work);
                if(!(ctx->field18[(row+1)*ctx->field1C] & ctx->field20))
                    g_rva01356E9C(ctx,cursor+6,stride,work);
                if(!(ctx->field18[(row+frame.rowWidth)*ctx->field1C] & ctx->field20))
                    g_rva01356EBC(ctx,cursor+stride*8,stride,work);
            }
        }
        if(ctx->field18[row*ctx->field1C] & ctx->field20) {
            g_rva01356E9C(ctx,frame.base+column*8-2,stride,work);
            if(!(ctx->field18[(row+frame.rowWidth)*ctx->field1C] & ctx->field20))
                g_rva01356EBC(ctx,frame.base+column*8+stride*8,stride,work);
        }
        frame.base+=stride*8;
        ++row;
        for(int y=1;y<frame.planeHeight-1;++y) {
            if(ctx->field18[row*ctx->field1C] & ctx->field20) {
                g_rva01356EBC(ctx,frame.base,stride,work);
                if(!(ctx->field18[(row+1)*ctx->field1C] & ctx->field20))
                    g_rva01356E9C(ctx,frame.base+6,stride,work);
                if(!(ctx->field18[(row+frame.rowWidth)*ctx->field1C] & ctx->field20))
                    g_rva01356EBC(ctx,frame.base+stride*8,stride,work);
            }
            ++row;
            for(column=1;column<frame.planeWidth-1;++column,++row) {
                unsigned char *cursor=frame.base+column*8;
                if(ctx->field18[row*ctx->field1C] & ctx->field20) {
                    g_rva01356E9C(ctx,cursor-2,stride,work);
                    g_rva01356EBC(ctx,cursor,stride,work);
                    if(!(ctx->field18[(row+1)*ctx->field1C] & ctx->field20))
                        g_rva01356E9C(ctx,cursor+6,stride,work);
                    if(!(ctx->field18[(row+frame.rowWidth)*ctx->field1C] & ctx->field20))
                        g_rva01356EBC(ctx,cursor+stride*8,stride,work);
                }
            }
            if(ctx->field18[row*ctx->field1C] & ctx->field20) {
                unsigned char *cursor=frame.base+column*8;
                g_rva01356E9C(ctx,cursor-2,stride,work);
                g_rva01356EBC(ctx,cursor,stride,work);
                if(!(ctx->field18[(row+frame.rowWidth)*ctx->field1C] & ctx->field20))
                    g_rva01356EBC(ctx,frame.base+column*8+stride*8,stride,work);
            }
            frame.base+=stride*8;
            ++row;
        }
        if(ctx->field18[row*ctx->field1C] & ctx->field20) {
            g_rva01356EBC(ctx,frame.base,stride,work);
            if(!(ctx->field18[(row+1)*ctx->field1C] & ctx->field20))
                g_rva01356E9C(ctx,frame.base+6,stride,work);
        }
        ++row;
        for(column=1;column<frame.planeWidth-1;++column,++row) {
            unsigned char *cursor=frame.base+column*8;
            if(ctx->field18[row*ctx->field1C] & ctx->field20) {
                g_rva01356E9C(ctx,cursor-2,stride,work);
                g_rva01356EBC(ctx,cursor,stride,work);
                if(!(ctx->field18[(row+1)*ctx->field1C] & ctx->field20))
                    g_rva01356E9C(ctx,cursor+6,stride,work);
            }
        }
        if(ctx->field18[row*ctx->field1C] & ctx->field20) {
            unsigned char *cursor=frame.base+column*8;
            g_rva01356E9C(ctx,cursor-2,stride,work);
            g_rva01356EBC(ctx,cursor,stride,work);
        }
    }
}
