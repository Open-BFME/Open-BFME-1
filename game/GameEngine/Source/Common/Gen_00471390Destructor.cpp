// cl: /DNDEBUG /MD /EHsc
//
// The deleting-destructor caller at 0x00471850 pairs this body with the
// credited constructor at 0x00471390.  The vtable at 0x010F756C identifies
// the object, and the destructor releases both pointer ranges, the owned
// object, and the name string.

namespace _STL {

template <bool Threads, int Instance>
class __node_alloc {
  static void _M_deallocate(void *memory, unsigned int bytes);

public:
  static void deallocate(void *memory, unsigned int bytes) {
    if (bytes > 128)
      ::operator delete(memory);
    else
      _M_deallocate(memory, bytes);
  }
};

}

class BfmeOwnedWB {
public:
  virtual ~BfmeOwnedWB();
};

class BFMERetailAsciiString {
public:
  __forceinline ~BFMERetailAsciiString() { releaseBuffer(); }
  void releaseBuffer();

private:
  char *m_data;
};

struct BfmePointerVectorWB {
  BfmeOwnedWB **m_start;
  BfmeOwnedWB **m_finish;
  BfmeOwnedWB **m_capacity;

  __forceinline ~BfmePointerVectorWB() {
    BfmeOwnedWB **start = m_start;
    if (start != 0) {
      unsigned int bytes = (unsigned int)((m_capacity - start) * 4);
      _STL::__node_alloc<true, 0>::deallocate(start, bytes);
    }
  }
};

class BfmeEmptyWB {
public:
  __forceinline ~BfmeEmptyWB() {}
};

__declspec(novtable) class BfmeGuardWB {
public:
  __forceinline virtual ~BfmeGuardWB() {}
  virtual void method1() = 0;
  virtual void method2() = 0;
  virtual void method3() = 0;
  virtual void method4() = 0;

public:
  char m_padding[0x18];
};

class Gen_00471390 : public BfmeGuardWB {
public:
  virtual ~Gen_00471390();

private:
  BfmePointerVectorWB m_first;
  BfmePointerVectorWB m_second;
  BfmeOwnedWB *m_owned;
  int m_unused;
  BFMERetailAsciiString m_name;
  char m_tail[0x10];
};

// ??1Gen_00471390@@UAE@XZ
Gen_00471390::~Gen_00471390() {
  BfmeOwnedWB **finish = m_second.m_finish;
  for (BfmeOwnedWB **it = m_second.m_start; it != finish; ++it) {
    BfmeOwnedWB *owned = *it;
    if (owned)
      delete owned;
  }

  if (m_owned)
    delete m_owned;
  m_owned = 0;
}

void bfmeInvokeGen00471390Dtor(Gen_00471390 *object) {
  object->~Gen_00471390();
}
