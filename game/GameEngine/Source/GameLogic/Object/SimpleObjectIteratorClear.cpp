// readable body of ?makeEmpty@SimpleObjectIterator@@QAEXXZ: game/GameEngine/Source/GameLogic/Object/SimpleObjectIterator.cpp
// BFME deletes unpooled clumps through their virtual destructor; the pooled reference uses freeBlock.
// ?makeEmpty@SimpleObjectIterator@@QAEXXZ
struct Rva001DDD60Node { virtual ~Rva001DDD60Node(); Rva001DDD60Node* m_next; };
extern "C" void free(void *);

class Object;
class ObjectIterator
{
public:
    virtual ~ObjectIterator();
    virtual Object* first() = 0;
    virtual Object* next() = 0;
};

struct SimpleObjectIterator : public ObjectIterator
{
    struct Clump
    {
        enum ClumpMagicEnum { Clump_GLUE_NOT_IMPLEMENTED = 0 };
        static void operator delete(void *pointer, ClumpMagicEnum);
    };

    Object* first();
    Object* next();
    Rva001DDD60Node* m_firstClump;
    Rva001DDD60Node* m_currentClump;
    int m_clumpCount;
    void makeEmpty();
};
void SimpleObjectIterator::makeEmpty()
{
	while (m_firstClump) {
		Rva001DDD60Node* next = m_firstClump->m_next;
		delete m_firstClump;
		m_firstClump = next;
		--m_clumpCount;
	}
	m_firstClump = 0;
	m_currentClump = 0;
	m_clumpCount = 0;
}

// The placement-delete glue uses CRT free; ordinary operator delete remains separate.
void SimpleObjectIterator::Clump::operator delete(void *pointer, ClumpMagicEnum)
{
    free(pointer);
}
