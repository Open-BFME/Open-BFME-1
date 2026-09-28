// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Complete reconstruction of retail RVA 00938150, 1231 bytes.
// Existing name is anchored by Load_Asset_Dat's three catalog calls.
// The binary, rather than an available Zero Hour twin, defines this BFME catalog format.
#define _STLP_NO_EXCEPTIONS 1
#include <stdio.h>
#include <string.h>
#include <set>
struct Rva001408C0Target;
typedef _STL::_Rb_tree<Rva001408C0Target*, Rva001408C0Target*,
    _STL::_Identity<Rva001408C0Target*>, _STL::less<Rva001408C0Target*>,
    _STL::allocator<Rva001408C0Target*> > CatalogTree;
class BfmeList950B {
public:
    BfmeList950B();
    ~BfmeList950B() { ((CatalogTree*)this)->~CatalogTree(); }
    void *m_bfmeHead;
    int m_bfme04;
    char m_bfmePad[4];
    volatile int m_bfme0c;
    volatile char m_bfme10;
};
class Rva006CEE30PointerSet {
public:
    Rva006CEE30PointerSet &insert(void *name);
private:
    _STL::set<Rva001408C0Target*> m_values;
    unsigned int m_treeLayoutPad;
    volatile bool m_changed;
};
bool Render_Obj_Exists(const char *);
void rva0090e690RegisterSJThing(const char *);
void Register_Rva009723C0_Prototype(const char *, int, int);
void Register_Aggregate_Prototype(const char *, int, int);
void Register_Animation_Prototype(const char *, int, int);
void Register_Hierarchy_Prototype(const char *, int, int);
void Register_Particle_Prototype(const char *, int, int);
void Register_Mesh_Prototype(const char *, int, int);
void Register_HLOD_Prototype(const char *, int, int);
void bfmeDispatch_009EBA60(void *, void *);

bool Load_Asset_Catalog(void *stream)
{
    FILE *f = (FILE *)stream;
    unsigned int magic, version, files, groups;
    char name[256], group[256], dependency[256], filename[264];
    setvbuf(f, 0, _IOFBF, 0x200000);
    if (fread(&magic, 4, 1, f) != 1 || magic != 0x45414c41 ||
        fread(&version, 4, 1, f) != 1 || version != 0x102 ||
        fread(&files, 4, 1, f) != 1 || fread(&groups, 4, 1, f) != 1) {
        fclose(f);
        return false;
    }
    while (files) {
        unsigned int entries = 0;
        if (fread(&entries, 1, 1, f) != 1) break;
        fread(filename, entries + 8, 1, f);
        if (fread(&entries, 2, 1, f) != 1) break;
        while (entries) {
            unsigned int length = 0;
            unsigned int type;
            int offset;
            if (fread(&length, 1, 1, f) != 1) break;
            if (fread(name, length, 1, f) != 1) break;
            name[length] = 0;
            if (fread(&type, 4, 1, f) != 1) break;
            if (fread(&offset, 4, 1, f) != 1) break;
            if (fread(&length, 4, 1, f) != 1) break;
            _strlwr(name);
            if (!Render_Obj_Exists(name)) {
                switch (type) {
                case 0x544558: rva0090e690RegisterSJThing(name); break;
                case 0x424f58: Register_Rva009723C0_Prototype(name, offset, length); break;
                case 0x41474752: Register_Aggregate_Prototype(name, offset, length); break;
                case 0x414e494d: Register_Animation_Prototype(name, offset, length); break;
                case 0x48494552: Register_Hierarchy_Prototype(name, offset, length); break;
                case 0x50415254: Register_Particle_Prototype(name, offset, length); break;
                case 0x4d455348: Register_Mesh_Prototype(name, offset, length); break;
                case 0x484c4f44: Register_HLOD_Prototype(name, offset, length); break;
                }
            }
            --entries;
        }
        if (entries) break;
        --files;
    }
    while (groups) {
        unsigned int length = 0;
        if (fread(&length, 1, 1, f) != 1) break;
        if (fread(group, length, 1, f) != 1) break;
        if (fread(&length, 1, 1, f) != 1) break;
        if (fread(group, length, 1, f) != 1) break;
        group[length] = 0;
        if (!Render_Obj_Exists(group)) break;
        {
            // Retail destroys this set before decrementing the group count.
            BfmeList950B list;
            unsigned int count = 0;
            if (fread(&count, 2, 1, f) != 1) break;
            while (count) {
                unsigned int len = 0;
                if (fread(&len, 1, 1, f) != 1) break;
                if (fread(dependency, len, 1, f) != 1) break;
                dependency[len] = 0;
                // Retail checks the group name here as well, not the dependency.
                if (Render_Obj_Exists(group))
                    ((Rva006CEE30PointerSet*)&list)->insert(dependency);
                --count;
            }
            if (count) break;
            if (list.m_bfme04) bfmeDispatch_009EBA60(group, &list);
        }
        --groups;
    }
    return files == 0 && groups == 0;
}
