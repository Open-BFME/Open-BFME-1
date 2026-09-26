// Retail RVA 0x00733E30..0x00733F15, full 229-byte RET 20 body.
// Address-derived identity: no semantic method name is asserted.
// Tree/type array extents and strides agree with matched destructor 0x00736590.
// The retail output copies are component-wise; struct assignment adds an
// address temporary and changes register allocation. Constants 0.9f and 60.0f
// are read directly from retail VA 0x010A13C0 and 0x0108882C.
// cl: /DNDEBUG /MD /EHsc
struct Rva00733E30Coord3 { float x,y,z; };
struct Rva00733E30Coord2 { float x,y; };
struct Rva00733E30Record {
    Rva00733E30Coord3 position;
    float scale;
    char pad10[0x30];
    int type;
    unsigned char visible;
    char pad45[0x0f];
    float radius;
    char pad58[0x28];
    int state;
    char pad84[0x64];
};
struct Rva00733E30Type {
    void *mesh;
    char pad04[0x20];
    Rva00733E30Coord2 primary[2];
    Rva00733E30Coord2 secondary[2];
    unsigned char textureFlags[4];
    char pad48[0x14];
};
class Rva00733E30Owner {
public:
    bool query(int index, Rva00733E30Coord3 *position, float *radius,
        Rva00733E30Coord2 *primary, Rva00733E30Coord2 *secondary);
    char pad000[0x1b0];
    Rva00733E30Record records[12000];
    int count;
    char pad2a7cb4[8];
    Rva00733E30Type types[64];
};
bool Rva00733E30Owner::query(int index, Rva00733E30Coord3 *position,
    float *radius, Rva00733E30Coord2 *primary, Rva00733E30Coord2 *secondary)
{
    if (index < count) {
        int typeIndex = records[index].type;
        if (typeIndex >= 0 && records[index].visible &&
            types[typeIndex].mesh && types[typeIndex].textureFlags[0] &&
            !records[index].state) {
            position->x = records[index].position.x;
            position->y = records[index].position.y;
            position->z = records[index].position.z;
            float value = records[index].radius * records[index].scale * 0.9f;
            if (60.0f < value) value = 60.0f;
            *radius = value;
            *primary = types[typeIndex].primary[1];
            *secondary = types[typeIndex].secondary[1];
            return true;
        }
    }
    return false;
}
