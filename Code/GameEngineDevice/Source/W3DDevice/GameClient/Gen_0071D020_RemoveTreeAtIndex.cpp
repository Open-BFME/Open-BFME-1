// cl: /DNDEBUG /MD /EHsc
//
// BFME's indexed tree removal path.  The 0xA4 records start at +0x1548;
// their render-object pair occupies the final two pointer slots.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/refcount.h
class RefCountClass
{
public:
	virtual void Delete_This(void);
	virtual ~RefCountClass(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

private:
	int m_refCount;
};

// The BFME RenderObjClass vtable places Remove at slot 16 (+0x40).
class RenderObjClass : public RefCountClass
{
public:
	virtual ~RenderObjClass(void);
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
	virtual void slot40(void);
	virtual void Remove(void);
};

struct BfmeTree
{
	char m_pad00[0x40];
	int m_treeType;
	char m_pad44[0x18];
	int m_matchingKey;
	char m_pad60[0x28];
	int m_toppleState;
	int m_uprightType;
	int m_toppledType;
	char m_pad94[4];
	RenderObjClass *m_toppleObject;
	RenderObjClass *m_pushAsideObject;
	char m_padA0[4];
};

class BaseHeightMapResetBuffer
{
public:
	void removeTreeAtIndex(const int index);
	void resetMatchingRow(int key);

private:
	char m_pad00[0x1e1cc8];
	int m_numTrees;
	unsigned char m_anythingChanged;
};

void BaseHeightMapResetBuffer::removeTreeAtIndex(const int index)
{
	if (index < m_numTrees) {
		if (*(int *)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x1588) >= 0) {

		if (*(int *)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15d0) == 1) {
			if (*(int *)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e4))
				*(int *)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x1588) =
					*(int *)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15d8);
		} else {
			*(int *)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x1588) =
				*(int *)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15d4);
		}

		if (*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e0)) {
			(*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e0))->Remove();
			if (*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e0)) {
				(*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e0))->Release_Ref();
				*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e0) = 0;
			}
		}

		if (*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e4)) {
			(*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e4))->Remove();
			if (*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e4)) {
				(*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e4))->Release_Ref();
				*(RenderObjClass **)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15e4) = 0;
			}
		} else {
			resetMatchingRow(*(int *)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15a4));
		}

			*(int *)(reinterpret_cast<char *>(this) + index * 0xa4 + 0x15d0) = 0;
			m_anythingChanged = 1;
		}
	}
}
