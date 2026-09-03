// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Same family as Code/Libraries/Source/WWVegas/WWLib/ThreadClassCtorThunk.cpp: a
// __thiscall constructor whose first act is Rva899F00Base(id, kind) at 0x00899F00.
// ThreadClass passed a runtime name pointer as id and kind=8; this one passes the
// compiled-in constant id=0x2A (42) and the same kind=8, so it is a sibling derived
// class, not ThreadClass itself.
//
// Unlike ThreadClass, the base call here can be followed by a THROWING operation
// (retail carries a full SEH frame, scope table @ 0x0105A0? [DIR32, resolved by the
// patcher] and an explicit try-state store of 0 right before the risky call), so the
// generated code must protect the just-completed Rva899F00Base subobject: if the
// call throws, its destructor must still run. That only happens automatically when
// the compiler sees code in the constructor BODY (not the init list) that can throw
// while a base subobject is already alive.
//
// Retail, byte for byte:
//
//   [SEH prologue, scope table, push regs]
//   push 8 ; mov esi,ecx ; push 0x2A ; mov [esp+0x10],esi
//   call 0x00899F00                   ; Rva899F00Base(0x2A, 8)
//   mov edi,[esp+0x1C]                ; edi = ctor's own stack parameter (a pointer)
//   mov dword ptr [esi],0x01137180    ; derived vtable (this class overrides ~dtor)
//   mov eax,[edi] ; mov ecx,edi ; mov [esp+0x14],0 (EH try-state -> 0)
//   call dword ptr [eax]              ; edi->vtbl[0]() -- thiscall, no explicit args
//   mov ecx,[esp+0xC]                 ; saved old SEH handler
//   mov [esi+0x20],edi                ; store the pointer AFTER the virtual call
//   [SEH epilogue] ; ret 4
//
// so the parameter is stashed at this+0x20 only once the virtual call it made has
// returned without throwing -- i.e. the constructor body reads "cb->Method(); this->
// field = cb;", not a member initializer (an initializer would store before the call).
//
// The callee's real identity, and the field's true type, are not known: no RTTI, and
// every caller in this address range is still an unconverted gen_asm dump. Spelled
// with an address-derived placeholder per the same policy as the ThreadClass sibling
// and Rva89A110DeletingDestructorThunk.cpp. Only the shape and the two calls are
// claimed.

struct _EXCEPTION_POINTERS;

// Unknown identity; named for its address.  ctor(id, kind) at 0x00899F00,
// subobject size 0x20 (vptr + 0x1C).  Local ABI-slice replica, same as the
// ThreadClass sibling -- ODR is not violated across translation units for an
// address-derived placeholder that no header ever declares.
class Rva899F00Base
{
public:
	Rva899F00Base(const char *id, int kind);
	virtual ~Rva899F00Base();

private:
	char	_bfme_base_slice[0x1c];
};

// Unknown identity; the object passed to this constructor.  Only vtbl slot 0
// is exercised, called thiscall with no explicit stack arguments.
class Rva8CB6D0Callback
{
public:
	virtual void Rva8CB6D0Invoke();
};

// Unknown identity; named for its address.  Derived from Rva899F00Base with
// id=0x2A, kind=8, and one extra pointer field at this+0x20.
class Rva8CB6D0Derived : public Rva899F00Base
{
public:
	Rva8CB6D0Derived(Rva8CB6D0Callback *callback);

private:
	Rva8CB6D0Callback	*_callback;	// retail this+0x20
};

Rva8CB6D0Derived::Rva8CB6D0Derived(Rva8CB6D0Callback *callback) :
	Rva899F00Base(reinterpret_cast<const char *>(0x2a), 8)
{
	callback->Rva8CB6D0Invoke();
	_callback = callback;
}
