// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 0x00901F80, 351 bytes: three-argument Create_Render_Obj wrapper.
// Identity is carried by the matched W3DDebrisDraw and ModelConditionInfo
// callers. The descriptor parser at 0x009013A0 proves the string/vector
// types. The third vector shares their destructor at 0x007556A0.
// Helper 0x009016A0 has seven cdecl arguments, independently witnessed by
// ModelConditionInfo::validateCachedBones at 0x00778590 (+0x3d9 call and
// +0x3de add esp,0x1c). Its body checks/copies the first argument as text,
// consumes argument two with fld, and tests vector begin/end pointers.
// Keep its identity address-derived; no semantic helper name is proven.
#include <string>
#include <vector>
class RenderObjClass;
typedef _STL::vector<_STL::string> Rva009013A0StringVector;
bool parseDescriptor009013A0(const char *, _STL::string &, float &, int &,
    Rva009013A0StringVector &, Rva009013A0StringVector &, int &);
RenderObjClass *Rva009016A0(const char *, float, int,
    Rva009013A0StringVector &, Rva009013A0StringVector &,
    Rva009013A0StringVector &, int);
RenderObjClass *Create_Render_Obj(const char *name, float scale, int color)
{
    if (!name) return 0;
    _STL::string parsedName(name);
    float parsedScale = scale;
    int parsedColor = color;
    Rva009013A0StringVector field1;
    Rva009013A0StringVector field2;
    Rva009013A0StringVector field3;
    int field5 = 0;
    if (*name == '#')
        parseDescriptor009013A0(name, parsedName, parsedScale, parsedColor,
            field1, field3, field5);
    return Rva009016A0(parsedName.c_str(), parsedScale, parsedColor,
        field1, field2, field3, field5);
}
