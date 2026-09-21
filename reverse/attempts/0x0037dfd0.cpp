// ?rva0037dfd0@@YGXPAVRva0037DFD0Container@@PAVObject@@@Z
// partial score=0.26 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc

// Retail 0x0037DFD0: a free __stdcall helper (2 stack params, callee-cleaned,
// no ecx/this) that walks a (FXList*, AsciiString boneName) pair vector held
// by its first argument and, for each entry, either fires FXList::doFXObj
// directly on the primary object (when the paired bone name is empty) or
// resolves a client bone transform through the primary's slot-10 interface
// and fires FXList::doFXPos there, finally forwarding to an
// ObjectCreationList::createInternal if the container carries one at +0x40.
// The FXList helpers (bfmeIsBlocked/doFXPos/doFXObj) reuse the already-landed
// FXList_bfmeIsBlocked.cpp / FXListDoFXPosPublic.cpp / FXListDoFXObjThunk.cpp
// signatures; ObjectCreationList::createInternal reuses
// ObjectCreationList_createInternal.cpp; the bone-position path reuses
// DrawableGetCurrentWorldspaceClientBonePositions.cpp's ABI via alternatename
// rather than redeclaring Drawable.

typedef bool Bool;

class Object;

struct Coord3D
{
	float x, y, z;
};

struct Matrix3D
{
	float m[3][4];
};

extern const char Rva006A16B0Empty[];

class BFMERetailAsciiString
{
public:
	const char *str() const { return m_data; }

private:
	char *m_data;
};

__forceinline const char *bfmeNameText(const BFMERetailAsciiString &name)
{
	const char *text = name.str();
	return text != 0 ? text + 8 : Rva006A16B0Empty;
}

class FXList
{
public:
	bool bfmeIsBlocked();
	void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;
	void doFXObj(const Object *primary, const Object *secondary) const;
};

struct FXEntry
{
	FXList *fx;
	BFMERetailAsciiString boneName;
};

class ObjectCreationList
{
public:
	void createInternal(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;
};

// The primary object's interface at this call site: slot 10 (+0x28) takes
// (boneName, transform) and its result is used directly as the receiver of
// the already-landed getCurrentWorldspaceClientBonePositions body, called
// with no further stack arguments at this call site.
class Rva0037E028Interface
{
public:
	virtual void _pad00();
	virtual void _pad04();
	virtual void _pad08();
	virtual void _pad0c();
	virtual void _pad10();
	virtual void _pad14();
	virtual void _pad18();
	virtual void _pad1c();
	virtual void _pad20();
	virtual void _pad24();
	virtual void *rva0037E028(const char *boneName, Matrix3D *transform);
};

class Rva0037E0BoneTarget
{
public:
	void rva0037E0GetBonePositions();
};

#pragma comment(linker, "/alternatename:?rva0037E0GetBonePositions@Rva0037E0BoneTarget@@QAEXXZ=?j_0003ec11@@YAXXZ")

class Rva0037DFD0Container
{
public:
	FXEntry *begin() const { return m_beginSlot; }
	FXEntry *end() const { return m_endSlot; }
	ObjectCreationList *ocl() const { return *(ObjectCreationList *const *)((const char *)this + 0x40); }

private:
	unsigned char m_pad0[0x34];
	FXEntry *volatile m_beginSlot;
	FXEntry *volatile m_endSlot;
};

__forceinline unsigned int rva0037dfd0Count(Rva0037DFD0Container *container)
{
	return (unsigned int)(container->end() - container->begin());
}

// ?rva0037dfd0@@YGXPAVRva0037DFD0Container@@PAVObject@@@Z
void __stdcall rva0037dfd0(Rva0037DFD0Container *container, Object *primary)
{
	for (unsigned int i = 0; i < rva0037dfd0Count(container); ++i)
	{
		FXEntry *entry = container->begin() + i;

			if (entry->boneName.str() == 0 || *(const unsigned short *)(entry->boneName.str() + 4) == 0)
			{
				FXList *fx = entry->fx;
				if (fx)
				{
					if (!fx->bfmeIsBlocked())
						fx->doFXObj(primary, 0);
				}
			}
			else
			{
				Rva0037E028Interface *iface = (Rva0037E028Interface *)primary;
				if (iface->rva0037E028(0, 0) != 0)
				{
					Matrix3D transform = { { { 1.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f, 0.0f } } };
					const char *text = bfmeNameText(entry->boneName);

					Rva0037E0BoneTarget *target = (Rva0037E0BoneTarget *)iface->rva0037E028(text, &transform);
					target->rva0037E0GetBonePositions();

					const Coord3D *pos = (const Coord3D *)((const char *)&transform + 8);
					FXList *fx = entry->fx;
					fx->doFXPos(pos, &transform, 0.0f, 0);
				}
			}
	}

	ObjectCreationList *ocl = container->ocl();
	if (ocl)
		ocl->createInternal(primary, 0, 0);
}
