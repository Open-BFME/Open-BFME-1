// Retail [0x0025FD80,0x0025FDAA): 42 bytes, RET0 then INT3 padding.
// Caller 0x00260060+0xBB passes this callback to the contained-object iterator
// with module data as userData. Object+0x1FC is the witnessed m_contain field;
// virtual slot0xFC takes ContainIterateFunc(Object*,void*), userData, reverse.
// cl: /DNDEBUG /MD /EHsc
class Object;
class FXList {
public:
    // BFME-only culling predicate at0x0042DAA0, not the ZH isEmpty query.
    bool bfmeIsBlocked();
    void doFXObj(const Object *, const Object *) const;
};
struct Rva0025FD80Data {
    unsigned char prefix[0x264];
    FXList *fx;
};
void __cdecl containedFXAt0025FD80(Object *object, void *context)
{
    FXList *fx=static_cast<Rva0025FD80Data *>(context)->fx;
    if(fx && !fx->bfmeIsBlocked())
        fx->doFXObj(object,0);
}
