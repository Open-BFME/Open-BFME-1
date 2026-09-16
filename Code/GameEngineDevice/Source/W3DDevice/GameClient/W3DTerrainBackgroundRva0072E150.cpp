// ?rva0072E150@W3DTerrainBackground@@QAEXH@Z
// Complete retail 0x0072E150..0x0072E1C3, 115 bytes and RET 4.
// Owner witnessed by setFlipRecursive/freeTerrainBuffers calls and matched
// neighbouring terrain-background layouts. Method name remains address-derived.
// Updates +78/+7C, clears map bits, rebuilds flips, frees buffers and sends
// the full integer region to the four-argument update at 0x0072D210.
// That callee stores argument 4 at +51, treats argument 2 as a refcounted
// WorldHeightMap, forwards region/map/argument3 to its tessellation update,
// and ends in RET 16 at 0x0072D98D (full extent 1920, not Ghidra's 1912).
struct Rva0072E150Region { int loX,loY,hiX,hiY; };
class WorldHeightMap;
class Gen_007498B0 { public: void bfmeClearBits(); };
class W3DTerrainBackground {
public:
    void rva0072E150(int value);
    void rva0072D210(const Rva0072E150Region &, WorldHeightMap *, bool, bool);
protected:
    void setFlipRecursive(int,int,int);
    void freeTerrainBuffers();
private:
    char pad00[0x40];
    int m_xOrigin,m_yOrigin,m_width;
    Gen_007498B0 *m_map;
    unsigned char m_initialized;
    bool option;
    char pad52[0x26];
    int current,previous;
};
void W3DTerrainBackground::rva0072E150(int value) {
    previous=current;
    current=value;
    m_map->bfmeClearBits();
    setFlipRecursive(0,0,m_width);
    freeTerrainBuffers();
    Rva0072E150Region region;
    region.loX=0;
    region.loY=0;
    region.hiX=m_xOrigin+m_width;
    region.hiY=m_yOrigin+m_width;
    rva0072D210(region,0,0,option);
}
