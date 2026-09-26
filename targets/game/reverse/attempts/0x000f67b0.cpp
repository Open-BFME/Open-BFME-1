// ?refresh@Rva000F72D0FrameCachedValue@@AAEXM@Z
// partial score=0.8189 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>


extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3D
{
	float x, y, z;
};

class BfmeTeamXQ
{
public:
	void bfmeEstimateXQ(Coord3D *outPos);
};

class GameLogicFrameSlice
{
public:
	unsigned char m_unmodelled_000[0x3c];
	unsigned int m_frame;
};

extern GameLogicFrameSlice *TheGameLogic;

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	const Overridable *getFinalOverride() const;
};

struct WideResultEntry
{
	Overridable *node;
	unsigned int unused;
};

class WideResultHandle
{
public:
	_STL::vector<WideResultEntry> m_values;
	WideResultEntry *m_cursor;
	unsigned int m_refCount;
};

struct BfmeWideResult
{
	WideResultHandle *m_value;
	__forceinline ~BfmeWideResult()
	{
		if (--m_value->m_refCount == 0)
			delete m_value;
	}
};

class PartitionFilter
{
public:
	PartitionFilter *link(PartitionFilter *next);
	volatile unsigned int m_vptr;
	PartitionFilter *m_next;
};

class PartitionFilterA : public PartitionFilter
{
public:
	PartitionFilterA(void *object) { m_next = 0; m_vptr = 0x1085DD0; m_data = object; }
	~PartitionFilterA() { m_vptr = 0x1083B5C; }
	void *m_data;
};

class PartitionFilterB : public PartitionFilter
{
public:
	PartitionFilterB() { m_next = 0; m_vptr = 0x1083B80; }
	~PartitionFilterB() { m_vptr = 0x1083B5C; }
};

class PartitionFilterC : public PartitionFilter
{
public:
	PartitionFilterC(void *object) { m_next = 0; m_vptr = 0x1085DC0; m_data = object; m_mode = 1; m_flag = 0; }
	~PartitionFilterC() { m_vptr = 0x1083B5C; }
	void *m_data;
	int m_mode;
	unsigned char m_flag;
};

class BfmeWideForwardC
{
public:
	BfmeWideResult bfmeForwardWideC(int a, int b, int c, int d, int e);
};

extern BfmeWideForwardC *ThePartitionManager;

class Rva000F72D0FrameCachedValue : public BfmeTeamXQ
{
public:
	float value(float range);

private:
	void refresh(float range);

	unsigned char m_unmodelled_000[0xc];
	void *m_object;
	unsigned char m_unmodelled_010[0xe4];
	float m_value;
	unsigned int m_frame;
};

float Rva000F72D0FrameCachedValue::value(float range)
{
	if (m_frame < TheGameLogic->m_frame)
		refresh(range);
	return m_value;
}

void Rva000F72D0FrameCachedValue::refresh(float range)
{
	Coord3D estimate;
	bfmeEstimateXQ(&estimate);

	void *object = m_object;
	if (object == 0)
		return;

	BfmeWideResult result = ThePartitionManager->bfmeForwardWideC(
		(int)&estimate, *(int *)&range, 0,
		(int)PartitionFilterC(object).link(
			PartitionFilterB().link(&PartitionFilterA(object))), 0);

	volatile float newValue = 0.0f;
	_ReadWriteBarrier();
	WideResultHandle *handle = result.m_value;
	WideResultEntry *cursor = handle->m_cursor;
	WideResultEntry *end = handle->m_values.end();
	if (cursor != end)
	{
		Overridable *node = cursor->node;
		++cursor;
		handle->m_cursor = cursor;
		if (node != 0)
		{
			Overridable *override_ = node->m_nextOverride;
			if (override_ != 0)
			{
				const Overridable *final_ = override_->m_nextOverride != 0 ? override_->getFinalOverride() : override_;
				newValue += *(float *)((char *)final_ + 0x3fc);
			}
			else
			{
				newValue += *(float *)((char *)0 + 0x3fc);
			}
		}
	}

	m_value = newValue;
	m_frame = TheGameLogic->m_frame + 25;
}
