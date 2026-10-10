// cl: /DNDEBUG /MD /EHsc

// Native unique insert: ECX tree; output pair, value ref; RET8.
extern "C" void __identifier("?insert_unique@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@U?$_Nonconst_traits@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@2@@Z")();

// Retail 0x00343EB0, 22 bytes: forward this, the hidden result buffer, and
// one value pointer through ILT 0x0002EA7D to the body at 0x00341C70.
// That body walks a tree and compares string-backed keys; it is not the
// integer hash-table equal_range named by the former generated claim.
// Its precise container identity remains unknown, so retain address names.
struct Rva00343EB0Result
{
    // Construct the result in the caller-provided return storage. This source-only
    // constructor avoids a second aggregate-return temporary.
    template <class Tree>
    __forceinline Rva00343EB0Result(Tree *tree, const void *value)
    {
        union
        {
            void (*address)();
            void (Tree::*member)(Rva00343EB0Result *, const void *);
        } route = { __identifier("?insert_unique@?$_Rb_tree@U?$pair@VAsciiString@@V1@@_STL@@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@2@U?$_Select1st@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@@2@U?$less@U?$pair@VAsciiString@@V1@@_STL@@@2@V?$allocator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Rb_tree_iterator@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@U?$_Nonconst_traits@U?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBU?$pair@VAsciiString@@V1@@_STL@@_N@2@@Z") };
        (tree->*route.member)(this, value);
    }

    void *m_00;
    bool m_04;
};

// Both callee exits write result+0 and result+4, return the hidden buffer
// in EAX, and use ret 8. The pointer/bool result occupies eight bytes.
class Rva00341C70
{
public:
    Rva00343EB0Result invoke(const void *value);
};

class Rva00343EB0
{
public:
    Rva00343EB0Result invoke(const void *value);
};

Rva00343EB0Result Rva00343EB0::invoke(const void *value)
{
    return Rva00343EB0Result(this, value);
}
