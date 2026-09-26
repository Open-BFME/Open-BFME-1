// Clean recovery of the STLport-style deque block advance at 0x0069E880.
// The retiring element is reference counted; the exhausted 128-byte block is
// returned to the retail small-block allocator before the next map slot wins.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *value);
extern void rva379ec0SmallDeallocate(void *block, unsigned int bytes);

class Rva0069E880Reference
{
public:
	virtual ~Rva0069E880Reference();
	void release()
	{
		if (InterlockedDecrement(&refCount) <= 0) {
			delete this;
		}
	}
	long refCount;
};

struct Rva0069E880ReferenceHolder
{
	~Rva0069E880ReferenceHolder()
	{
		if (value != 0) {
			value->release();
		}
	}
	Rva0069E880Reference *value;
};

struct Rva0069E880Deque
{
	Rva0069E880Reference **current;
	Rva0069E880Reference **block;
	Rva0069E880Reference **end;
	Rva0069E880Reference ***mapCursor;
};

extern "C" Rva0069E880Reference **__fastcall Rva0069E880DequeAdvance(Rva0069E880Deque *self)
{
	((Rva0069E880ReferenceHolder *)self->current)->~Rva0069E880ReferenceHolder();

	if (self->block != 0) {
		rva379ec0SmallDeallocate(self->block, 128);
	}
	++self->mapCursor;
	self->block = *self->mapCursor;
	self->end = self->block + 32;
	self->current = self->block;
	return self->current;
}
