// cl: /DNDEBUG /MD /EHsc

// The complete retail body is a five-byte incremental-link tail jump to the
// matched GenericSLNode pool free routine at 0x006D1480.
class GenericSLNode;

template <class T, int BLOCK_SIZE>
class ObjectPoolClass
{
public:
	void Free_Object_Memory(T *object);
};

class Rva00011103Thunk
{
public:
	void forward(GenericSLNode *object);
};

void Rva00011103Thunk::forward(GenericSLNode *object)
{
	((ObjectPoolClass<GenericSLNode, 256> *)this)->Free_Object_Memory(object);
}
