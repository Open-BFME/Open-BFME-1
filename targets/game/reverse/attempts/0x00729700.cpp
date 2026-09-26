// ?setFlipRecursive@W3DTerrainBackground@@IAEXHHH@Z
// partial score=0.24 date=2026-09-22
// cl: /DNDEBUG /MD /EHsc
// Full retail729700/792. BFME adds cliff/bit-plane tests and aligned corners.
class Rva00729370BitPlane { public: bool test(int,int) const; };
class BfmeMaskAX { public: void bfmeMarkAX(int,int,unsigned char); };
struct Rva00729700Map {
    char pad00[8];
    int width, height;
    char pad10[0x10];
    int count;
    unsigned short *heights;
    char pad28[0xc];
    int pitch;
    char pad38[0x18];
    unsigned char *bits, *bitsEnd;
    char pad58[0x3c];
    void **cliffs;
    char pad98[0x12048];
    int originX, originY;
    unsigned short getHeight(int x,int y) const {
        int index=y*width+x;
        if(index<0 || index>=count || !heights) return 0;
        return heights[index];
    }
    bool isCliffMappedTexture(int x,int y) const {
        int index=(originY+y)*width+originX+x;
        if(index<0 || index>=count) return false;
        return cliffs[index]!=0;
    }
    bool getFlip(int x,int y) const {
        if(x<0 || y<0 || y>=height || x>=width) return false;
        int index=pitch*y+(x>>3);
        if((unsigned)index >= (unsigned)(bitsEnd-bits)) return false;
        int mask=1;
        mask <<= x&7;
        unsigned char value=bits[index];
        return (value&mask)!=0;
    }
};
class W3DTerrainBackground {
public:
    char pad00[0x40];
    int m_xOrigin,m_yOrigin,m_width;
    Rva00729700Map *m_map;
    char pad50[0x28];
    int m_78;
    bool isEdgeAligned(int,int,int);
protected:
    void setFlipRecursive(int,int,int);
};
void W3DTerrainBackground::setFlipRecursive(int xOffset,int yOffset,int width) {
    int limitX[2];
    limitX[1]=m_map->width-1;
    int limitY=m_map->height-1;
    bool match=true;
    int minX=m_xOrigin+xOffset;
    int minY=m_yOrigin+yOffset;
    int cornerHeight=m_map->getHeight(minX,minY);
    Rva00729700Map *map=m_map;
    bool cornerFlip=((Rva00729370BitPlane*)map)->test(minX,minY);
    for(int i=0;i<=width;i+=m_78) {
        for(int j=0;j<=width;j+=m_78) {
            int k=minX+i;
            k=k<limitX[1]?k:limitX[1];
            int l=minY+j;
            l=l<limitY?l:limitY;
            if(cornerHeight!=map->getHeight(k,l) || map->isCliffMappedTexture(k,l)) {
                match=false;
                break;
            }
            if(i<width && j<width && map->getFlip(k,l)!=cornerFlip) {
                match=false;
                break;
            }
        }
    }
    if(width==m_78 || match) {
        int maxX=minX+width;
        maxX=maxX<limitX[1]?maxX:limitX[1];
        int maxY=minY+width;
        maxY=maxY<limitY?maxY:limitY;
        int savedOriginY=m_yOrigin;
        int localMinX=minX-m_xOrigin;
        int localMaxY=maxY-savedOriginY;
        bool leftTop=isEdgeAligned(localMinX,localMaxY,width);
        int localMaxX=maxX-m_xOrigin;
        bool rightTop=isEdgeAligned(localMaxX,localMaxY,width);
        int localMinY=minY-savedOriginY;
        bool rightBottom=isEdgeAligned(localMaxX,localMinY,width);
        bool leftBottom=isEdgeAligned(localMinX,localMinY,width);
        if(leftBottom) ((BfmeMaskAX*)m_map)->bfmeMarkAX(minX,minY,1);
        if(rightBottom) ((BfmeMaskAX*)m_map)->bfmeMarkAX(maxX,minY,1);
        if(rightTop) ((BfmeMaskAX*)m_map)->bfmeMarkAX(maxX,maxY,1);
        if(leftTop) ((BfmeMaskAX*)m_map)->bfmeMarkAX(minX,maxY,1);
        return;
    }
    int halfWidth=width/2;
    setFlipRecursive(xOffset,yOffset,halfWidth);
    setFlipRecursive(xOffset,yOffset+halfWidth,halfWidth);
    setFlipRecursive(xOffset+halfWidth,yOffset,halfWidth);
    setFlipRecursive(xOffset+halfWidth,yOffset+halfWidth,halfWidth);
}
