// Retail 0x009FB02D, 44 bytes. This four-float scaler sits in the
// statically linked d3dx9 region; no named caller proves its source identity.
// Keep the owner address-derived. The inline four-argument assignment makes
// VC7.1 evaluate all products before writing the destination, as retail does.
// cl: /Oy-
class Rva009FB02DFloat4
{
public:
    float x, y, z, w;

    __forceinline void assign(float xx, float yy, float zz, float ww)
    {
        x = xx;
        y = yy;
        z = zz;
        w = ww;
    }

    void scaleInto(Rva009FB02DFloat4 *destination, float scale) const;
};

void Rva009FB02DFloat4::scaleInto(Rva009FB02DFloat4 *destination,
                                  float scale) const
{
    destination->assign(x * scale, y * scale, z * scale, w * scale);
}
