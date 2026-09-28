// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x008FF290, 278 bytes: the BFME free Create_Render_Obj(const char *).
//
// Forty-one landed callers (W3DBridgeBuffer, W3DInGameUI::drawPlaceAngle,
// BfmeRenderObjectHolderCreate, PalantirSceneInit0079E0F0, ...) declare and
// call this exact cdecl free function, so the name and the single-argument
// return-pointer boundary are carried by named callers rather than guessed.
//
// Identity of the pieces is address-derived and witnessed by the call sites:
// the name is copied into a 0x800 scratch buffer and lower-cased for the
// global prototype registry lookup at 0x009EBCE0, the returned reference is
// held by the Gen008FF1B0 owner from 0x008FF1B0, the prototype vtable slot
// +0x3C builds the instance, and the instance then takes the ORIGINAL name
// through BfmeThingVGK::bfmeGoVGK (0x0091FCC0) -- the same five-step sequence
// the matched CreateModifiedRenderObj00901B00 body performs at 0x00901B00.
#include <string.h>

class RenderObjClass;

class TextureClass
{
public:
	void Release_Ref();
};

class BfmeThingVGK
{
public:
	void bfmeGoVGK(const char *name);
};

// The registry prototype the lookup hands back. Slot +0x3C is the create call
// the body makes; the fifteen slots below it are named for their offsets only.
class Prototype008FF290
{
public:
	virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
	virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
	virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
	virtual void s30(); virtual void s34(); virtual void s38();
	virtual BfmeThingVGK *create();
};

// By-value result of the registry lookup: the caller supplies this storage,
// so the temporary owns the reference until its own destructor fires.
class Rva009EBCE0AssetReference
{
public:
	~Rva009EBCE0AssetReference()
	{
		if (m_object != 0)
			((TextureClass *)m_object)->Release_Ref();
	}

	Prototype008FF290 *m_object;
};

extern Rva009EBCE0AssetReference Rva009EBCE0_GetPrototype(const char *name);

// The owner the registry returns: one reference held for the block's extent.
class Gen008FF1B0
{
public:
	Gen008FF1B0(void *reference);
	~Gen008FF1B0()
	{
		if (m_object != 0)
			((TextureClass *)m_object)->Release_Ref();
	}

	Prototype008FF290 *m_object;
};

RenderObjClass *Create_Render_Obj(const char *name)
{
	if (name == 0)
		return 0;

	char lowered[2048];
	strcpy(lowered, name);
	_strlwr(lowered);

	Gen008FF1B0 prototype((void *)&Rva009EBCE0_GetPrototype(lowered));

	if (prototype.m_object)
	{
		RenderObjClass *render_obj = (RenderObjClass *)prototype.m_object->create();
		if (render_obj)
		{
			((BfmeThingVGK *)render_obj)->bfmeGoVGK(name);
			return render_obj;
		}
	}

	return 0;
}
