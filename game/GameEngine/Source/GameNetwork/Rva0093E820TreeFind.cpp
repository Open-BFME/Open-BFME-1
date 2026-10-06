// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// Retail passes the unchanged receiver and a reference to the unsigned-short
// key to 0093DCE0. The wrapper returns its node pointer in the caller's result
// buffer. Neither this ABI nor the search proves the original mapped type.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>
#include "../../../Libraries/Source/WWVegas/WW3D2/Rva0093DCE0TreeFind.h"

typedef unsigned short Rva0093E820Key;

struct Rva0093E820Result
{
    void *m_node;
    explicit Rva0093E820Result(void *node) : m_node(node) {}
};

class Rva0093E820Find
{
public:
    Rva0093E820Result find(const Rva0093E820Key &key) const;
};

Rva0093E820Result Rva0093E820Find::find(const Rva0093E820Key &key) const
{
    return Rva0093E820Result(
        reinterpret_cast<const Rva0093DCE0Tree *>(this)->find(key));
}
