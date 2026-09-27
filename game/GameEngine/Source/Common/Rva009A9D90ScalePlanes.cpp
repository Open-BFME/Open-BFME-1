// Retail 009A9D90 scales three planes then extends their right/bottom borders.
struct Rva009A9D90Planes {
    int width,height,pitch,chromaWidth,chromaHeight,chromaPitch;
    char *y,*u,*v;
};
void Rva009A9AD0Scale2D(unsigned char*,int,unsigned,unsigned,unsigned char*,int,unsigned,unsigned,unsigned char*,unsigned char,unsigned,unsigned,unsigned,unsigned,unsigned);
extern "C" void* memcpy(void*,const void*,unsigned);
extern "C" void* memset(void*,int,unsigned);
void Rva009A9D90ScalePlanes(Rva009A9D90Planes* src,Rva009A9D90Planes* dst,unsigned char* temp,unsigned char tempHeight,unsigned hs,unsigned hr,unsigned vs,unsigned vr,unsigned interlaced)
{
    int row;
    int width=(src->width*hr+hs-1)/hs;
    int height=(src->height*vr+vs-1)/vs;
    Rva009A9AD0Scale2D((unsigned char*)src->y,src->pitch,src->width,src->height,(unsigned char*)dst->y,dst->pitch,width,height,temp,tempHeight,hs,hr,vs,vr,interlaced);
    if(width<dst->width) {
        for(row=0;row<height;++row) {
            memset(dst->y+dst->pitch*row+width-1,dst->y[dst->pitch*row+width-2],dst->width-width+1);
        }
    }
    if(height<dst->height) {
        for(row=height-1;row<dst->height;++row)
            memcpy(dst->y+dst->pitch*row,dst->y+dst->pitch*(height-2),dst->width+1);
    }
int chromaHeight=height/2;
int chromaWidth=width/2;

    Rva009A9AD0Scale2D((unsigned char*)src->u,src->chromaPitch,src->chromaWidth,src->chromaHeight,(unsigned char*)dst->u,dst->chromaPitch,chromaWidth,chromaHeight,temp,tempHeight,hs,hr,vs,vr,interlaced);
    if(chromaWidth<dst->chromaWidth) {
        for(row=0;row<dst->chromaHeight;++row) {
            memset(dst->u+dst->chromaPitch*row+chromaWidth-1,dst->u[dst->chromaPitch*row+chromaWidth-2],dst->chromaWidth-chromaWidth+1);
        }
    }
    if(chromaHeight<dst->chromaHeight) {
        for(row=chromaHeight-1;row<dst->height/2;++row)
            memcpy(dst->u+dst->chromaPitch*row,dst->u+dst->chromaPitch*(chromaHeight-2),dst->chromaWidth);
    }
    Rva009A9AD0Scale2D((unsigned char*)src->v,src->chromaPitch,src->chromaWidth,src->chromaHeight,(unsigned char*)dst->v,dst->chromaPitch,chromaWidth,chromaHeight,temp,tempHeight,hs,hr,vs,vr,interlaced);
    if(chromaWidth<dst->chromaWidth) {
        for(row=0;row<dst->chromaHeight;++row) {
            memset(dst->v+dst->chromaPitch*row+chromaWidth-1,dst->v[dst->chromaPitch*row+chromaWidth-2],dst->chromaWidth-chromaWidth+1);
        }
    }
    if(chromaHeight<dst->chromaHeight) {
        for(row=chromaHeight-1;row<dst->height/2;++row)
            memcpy(dst->v+dst->chromaPitch*row,dst->v+dst->chromaPitch*(chromaHeight-2),dst->chromaWidth);
    }

}
