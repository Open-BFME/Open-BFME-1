// cl: /O2 /DNDEBUG /MD

// RenderObjClass slot 40 is an empty virtual method in the BFME vtable.
// Keep this body in a focused TU because rendobj.h already defines the slot
// inline for the shared class implementation.
class RenderObjClass
{
public:
    virtual void _bfme_ro_v40(void);
};

// ?_bfme_ro_v40@RenderObjClass@@UAEXXZ
void RenderObjClass::_bfme_ro_v40(void)
{
}
