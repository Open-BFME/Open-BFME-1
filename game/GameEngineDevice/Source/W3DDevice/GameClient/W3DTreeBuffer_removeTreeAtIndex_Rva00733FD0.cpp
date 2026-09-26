// cl: /DNDEBUG /MD /EHsc
// BFME W3DTreeBuffer indexed tree removal, retail 0x00733FD0 (341 bytes).
// The neighboring 0x00734790 update path passes its tree index here through
// ILT 0x0001512C.  Records are 0xE8 bytes and the count/dirty fields are at
// +0x2A7CB0/+0x2A7CB4, as witnessed by the adjacent tree-buffer bodies.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// BFME RenderObjClass: Delete_This is slot 0, Remove is slot +0x40 and the
// reference count is the first data word at +4.
class Rva00733FD0RenderObjClass
{
public:
	virtual void Delete_This(void);
	virtual void slot04(void);
	virtual void slot08(void);
	virtual void slot0c(void);
	virtual void slot10(void);
	virtual void slot14(void);
	virtual void slot18(void);
	virtual void slot1c(void);
	virtual void slot20(void);
	virtual void slot24(void);
	virtual void slot28(void);
	virtual void slot2c(void);
	virtual void slot30(void);
	virtual void slot34(void);
	virtual void slot38(void);
	virtual void slot3c(void);
	virtual void Remove(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	Int m_refCount;
};

class Rva00733FD0TerrainLogic
{
public:
	void clear(Int key);
};

#define TheTerrainLogic (*(Rva00733FD0TerrainLogic **)0x012EF4CC)
extern void j_0001d0ac(void);

struct Rva00733FD0Tree
{
	unsigned char m_pad0000[0x1F0];
	Int m_treeType;
	unsigned char m_pad01F4[0x230 - 0x1F4];
	Int m_renderState;
	unsigned char m_pad0234[0x274 - 0x234];
	UnsignedByte m_visible;
	unsigned char m_pad0275[0x278 - 0x275];
	Int m_toppleState;
	Int m_uprightType;
	Int m_toppledType;
	unsigned char m_pad0288[0x288 - 0x284];
	Rva00733FD0RenderObjClass *m_toppleObject;
	Rva00733FD0RenderObjClass *m_pushAsideObject;
	unsigned char m_pad0290[0x2A0 - 0x290];
};

class Rva00733FD0W3DTreeBuffer
{
public:
	void removeTreeAtIndex(const Int index);

private:
	unsigned char m_pad0000[0x2A7CB0];
	Int m_numTrees;
	UnsignedByte m_anythingChanged;
};

// ?removeTreeAtIndex@W3DTreeBuffer@@QAEXH@Z
void Rva00733FD0W3DTreeBuffer::removeTreeAtIndex(const Int index)
{
	if (index < m_numTrees) {
		if (*(Int *)(reinterpret_cast<unsigned char *>(this) +
			index * 0xE8 + 0x1F0) >= 0) {
			if (*(UnsignedByte *)(reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x274) == 0 &&
				*(Int *)(reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x230) == 0) {
				if (*(Int *)(reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x278) == 1) {
					if (*(Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x28C) != 0)
						*(Int *)(reinterpret_cast<unsigned char *>(this) +
							index * 0xE8 + 0x1F0) =
							*(Int *)(reinterpret_cast<unsigned char *>(this) +
							index * 0xE8 + 0x280);
				} else {
					*(Int *)(reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x1F0) =
						*(Int *)(reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x27C);
				}

				if (*(Rva00733FD0RenderObjClass **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x288) != 0) {
					(*(Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x288))->Remove();
					if (*(Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x288) != 0) {
						(*(Rva00733FD0RenderObjClass **)(
							reinterpret_cast<unsigned char *>(this) +
							index * 0xE8 + 0x288))->Release_Ref();
						*(Rva00733FD0RenderObjClass **)(
							reinterpret_cast<unsigned char *>(this) +
							index * 0xE8 + 0x288) = 0;
					}
					*(volatile Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x288) = 0;
					_ReadWriteBarrier();
				}

				if (*(Rva00733FD0RenderObjClass **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x28C) != 0) {
					(*(Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x28C))->Remove();
					if (*(Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x28C) == 0)
						goto rva00733fd0_store_push;
					(*(Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x28C))->Release_Ref();
					*(Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x28C) = 0;
					goto rva00733fd0_store_push;
				} else {
					typedef void (Rva00733FD0TerrainLogic::*ClearOperation)(Int);
					union {
						void (*function)(void);
						ClearOperation member;
					} clearCast;
					clearCast.function = j_0001d0ac;
					Int key = *(Int *)(reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x208);
					(TheTerrainLogic->*clearCast.member)(key);
				}
				*(volatile Int *)(reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x278) = 0;
				*(volatile UnsignedByte *)(reinterpret_cast<unsigned char *>(this) +
					0x2A7CB4) = 1;
				return;
			}

			if (*(Rva00733FD0RenderObjClass **)(
				reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x288) != 0) {
				(*(Rva00733FD0RenderObjClass **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x288))->Remove();
				if (*(Rva00733FD0RenderObjClass **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x288) != 0) {
					(*(Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x288))->Release_Ref();
					*(volatile Rva00733FD0RenderObjClass **)(
						reinterpret_cast<unsigned char *>(this) +
						index * 0xE8 + 0x288) = 0;
					_ReadWriteBarrier();
				}
			}

			if (*(Rva00733FD0RenderObjClass **)(
				reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x28C) != 0) {
				(*(Rva00733FD0RenderObjClass **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x28C))->Remove();
				if (*(Rva00733FD0RenderObjClass **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x28C) == 0)
					goto rva00733fd0_finish;
				(*(Rva00733FD0RenderObjClass **)(
					reinterpret_cast<unsigned char *>(this) +
					index * 0xE8 + 0x28C))->Release_Ref();
			goto rva00733fd0_store_push;
			}

			goto rva00733fd0_finish;

	rva00733fd0_store_push:
			*(Rva00733FD0RenderObjClass **)(
				reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x28C) = 0;

	rva00733fd0_finish:
			*(Int *)(reinterpret_cast<unsigned char *>(this) +
				index * 0xE8 + 0x278) = 0;
			m_anythingChanged = 1;
		}
	}
}
