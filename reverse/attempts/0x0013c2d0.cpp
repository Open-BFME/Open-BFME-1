// ?d_0013c2d0@@YAXXZ
// partial score=0.92 date=2026-09-17
// cl: /EHsc
// stlport
//
// The callers at ModelConditionInfo::+0xac and Gen_t_00776240_p128pod::+0x60
// both pass this 12-byte vector to the same destructor. Retail destroys a
// 20-byte element's AsciiString at +0x0c and releases its embedded object at
// +0x10 before the vector frees its storage.

#include <vector>

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	void *m_data;
};

class Rva0013C2D0Virtual
{
public:
	virtual void destroy(int flags);
};

class Rva0013C2D0Object
{
public:
	void release()
	{
		Rva0013C2D0Object *object = this;
		int refs = object->m_refs;
		--refs;
		int result = refs;
		Rva0013C2D0Virtual *base = &object->m_virtual;
		*(int *)((char *)base + 4) = refs;
		if (result <= 0)
			base->destroy(1);
	}

private:
	char m_padding[0x24];
	Rva0013C2D0Virtual m_virtual;
	int m_refs;
};

struct Rva0013C2D0Element
{
	char m_padding[0x0c];
	BFMERetailAsciiString m_name;
	Rva0013C2D0Object *m_object;

	~Rva0013C2D0Element()
	{
		if (m_object != 0)
			m_object->release();
	}
};

class Rva0013C2D0VectorBase
{
protected:
	Rva0013C2D0Element *m_start;
	Rva0013C2D0Element *m_finish;
	Rva0013C2D0Element *m_end;

	Rva0013C2D0Element *begin()
	{
		return m_start;
	}

	Rva0013C2D0Element *finish()
	{
		return m_finish;
	}

	Rva0013C2D0Element *capacityEnd()
	{
		return m_end;
	}

	__forceinline ~Rva0013C2D0VectorBase()
	{
		Rva0013C2D0Element *start = begin();
		if (start != 0)
		{
			unsigned int bytes = (unsigned int)(capacityEnd() - start) * sizeof(Rva0013C2D0Element);
			if (bytes > 0x80)
				::operator delete(start);
			else
				_STL::allocator<Rva0013C2D0Element>().deallocate(start, bytes);
		}
	}
};

class Rva0013C2D0Vector : public Rva0013C2D0VectorBase
{
public:
	Rva0013C2D0Element *begin()
	{
		return Rva0013C2D0VectorBase::begin();
	}

	Rva0013C2D0Element *end()
	{
		return Rva0013C2D0VectorBase::finish();
	}

	~Rva0013C2D0Vector();
};

__forceinline void Rva0013C2D0DestroyRange(
	Rva0013C2D0Element *first, Rva0013C2D0Element *last)
{
	while (first != last)
	{
		first->~Rva0013C2D0Element();
		++first;
	}
}

Rva0013C2D0Vector::~Rva0013C2D0Vector()
{
	Rva0013C2D0Vector *self = this;
	Rva0013C2D0DestroyRange(self->begin(), self->end());
}
