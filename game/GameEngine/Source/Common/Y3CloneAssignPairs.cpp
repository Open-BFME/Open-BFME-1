// cl: /DNDEBUG /MD /EHsc
// Two 94-byte copy-assignment operators: the TWO-POINTER arity of the shape
// U1CloneAssignOperators.cpp documents at 60 bytes.  Retail:
//
//     push ebx / mov ebx,[esp+8] / push esi / mov esi,ecx
//     mov ecx,[ebx] / test ecx,ecx / push edi / je none0
//     mov eax,[ecx] / call dword ptr [eax+4] / mov edi,eax / jmp have0
//     none0: xor edi,edi
//     have0: mov ecx,[esi] / test ecx,ecx / je gone0
//            mov edx,[ecx] / push 1 / call dword ptr [edx]
//     gone0: mov [esi],edi
//     ... the same again over [ebx+4] and [esi+4] ...
//     add ebx,8 / push ebx / lea ecx,[esi+8] / mov [esi+4],edi
//     call <REL32>
//     pop edi / mov eax,esi / pop esi / pop ebx / ret 4
//
// WHAT THE BYTES SHOW is what that file already established, twice over: SLOT
// 1 with no arguments on the right-hand side's member is a clone, SLOT 0 with
// a literal 1 pushed on the receiver's member is `delete` through a virtual
// destructor, and the clone is taken BEFORE the delete -- the self-assignment-
// safe spelling.  `mov eax,esi` and `ret 4` make it `operator=` returning a
// reference to the receiver.  The two pointers are at offsets 0 and 4 and the
// member tail follows them at 8; `add ebx,8` with a bare `lea ecx,[esi+8]` is
// a member subobject on both sides, not a base.
//
// THE STORE OF THE SECOND POINTER IS SCHEDULED after the tail's arguments are
// already pushed.  It is still the same assignment; MSVC 7.1 does not reorder
// straight-line stores, but it does fill the slot between an address
// computation and a call.
//
// THE TWO ROWS CHAIN.  0x005CE550 calls 0x005CD820 and 0x005CD820 calls
// 0x005CBEE0, so each row's tail member is the next row's class.  0x005CD820
// is defined here and therefore marked __declspec(noinline): retail's `call`
// proves it stayed out of line.  0x005CBEE0 is NOT converted -- it is the same
// 94-byte body except that it computes the right-hand subobject address with
// `lea eax,[ebx+8] / push eax` instead of `add ebx,8 / push ebx`.  That is the
// same unexplained register choice U1CloneAssignOperators.cpp records at
// 0x005CB1D0, and none of the spellings tried here (member through an empty
// intermediate class, a bound reference local, an explicit `operator=` call, a
// pointer argument) reproduces it.  It is declared only, and pinned.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class Y3Clonable
{
public:
	virtual ~Y3Clonable();
	virtual Y3Clonable *clone();
};

class Y3AssignTail_005CBEE0
{
public:
	Y3AssignTail_005CBEE0 &operator=( const Y3AssignTail_005CBEE0 &rhs );
};

#define Y3_CLONE_ASSIGN_PAIR( ROW, TAIL, DECORATION )                         \
	class Y3Assign_##ROW                                                      \
	{                                                                         \
	public:                                                                   \
		DECORATION Y3Assign_##ROW &operator=( const Y3Assign_##ROW &rhs );    \
                                                                              \
		Y3Clonable *m_first;                                                  \
		Y3Clonable *m_second;                                                 \
		TAIL m_tail;                                                          \
	};                                                                        \
	Y3Assign_##ROW &Y3Assign_##ROW::operator=( const Y3Assign_##ROW &rhs )    \
	{                                                                         \
		Y3Clonable *sourceFirst = rhs.m_first;                                \
		Y3Clonable *copyFirst = sourceFirst ? sourceFirst->clone() : 0;       \
		delete m_first;                                                       \
		m_first = copyFirst;                                                  \
		Y3Clonable *sourceSecond = rhs.m_second;                              \
		Y3Clonable *copySecond = sourceSecond ? sourceSecond->clone() : 0;    \
		delete m_second;                                                      \
		m_second = copySecond;                                                \
		m_tail = rhs.m_tail;                                                  \
		return *this;                                                         \
	}

Y3_CLONE_ASSIGN_PAIR( 005CD820, Y3AssignTail_005CBEE0, __declspec(noinline) )
Y3_CLONE_ASSIGN_PAIR( 005CE550, Y3Assign_005CD820, )
