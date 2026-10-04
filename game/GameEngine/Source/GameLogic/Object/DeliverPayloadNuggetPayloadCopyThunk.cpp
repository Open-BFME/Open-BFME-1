// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

// Retail RVA 0x000097CD jumps to the matched Payload copy body at 0x0036D980.
// The symbol pin and ObjectCreationList.cpp callers identify this as the
// DeliverPayloadNugget Payload STLport copy specialization.
//
// retail: _STL::__copy<Payload *, Payload *, int>, i.e. STLport's random-access
// __copy with the third parameter the Distance type, exactly the shape
// HideShowSubObjInfoCopyBody.cpp writes for the HideShowSubObjInfo twin. The
// third template argument is the *type* int and not a value, which is what makes
// the mangled name come out with `H@` where retail has it.
//
// Only the mangled retail signature is reproduced here, so the jump names the
// pinned copy body directly instead of through a stand-in. Payload's layout is
// irrelevant on this side -- only its name reaches the mangling -- so the nested
// type stays forward declared and no member is invented. _STL is opened before
// DeliverPayloadNugget so the `0` backreference in the retail symbol resolves to
// _STL.

namespace _STL
{

struct random_access_iterator_tag
{
};

}

// retail: ??$__copy@PAUPayload@DeliverPayloadNugget@@PAU12@H@_STL@@YAPAUPayload@DeliverPayloadNugget@@PAU12@00ABUrandom_access_iterator_tag@0@PAH@Z
class DeliverPayloadNugget
{
public:
	struct Payload;
};

namespace _STL
{

template <class InputIterator, class OutputIterator, class Distance>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	const random_access_iterator_tag &, Distance *);

// Declaration only, no body: the specialization is linked from the matched body
// at 0x0036D980, so nothing is emitted here and no second definition of that
// address is created.
template DeliverPayloadNugget::Payload *__copy<DeliverPayloadNugget::Payload *,
	DeliverPayloadNugget::Payload *, int>(DeliverPayloadNugget::Payload *, DeliverPayloadNugget::Payload *,
	DeliverPayloadNugget::Payload *, const random_access_iterator_tag &, int *);

}

typedef DeliverPayloadNugget::Payload *(__cdecl *DeliverPayloadNuggetCopy)(
	DeliverPayloadNugget::Payload *, DeliverPayloadNugget::Payload *, DeliverPayloadNugget::Payload *,
	const _STL::random_access_iterator_tag &, int *);

void Rva000097CDDeliverPayloadCopyThunk(void)
{
	// retail 0x000097CD is not a body of its own: it is the incremental-link jump
	// stub, five bytes, `jmp 0x0036D980`. It pushes nothing and builds no frame,
	// so the copy's arguments are already in place in the caller's stack and this
	// address is entered with a tail jump.
	//
	// Spelling the call with the real signature would make the compiler push five
	// arguments here, which both breaks the five bytes and cannot be spelled
	// honestly anyway -- an incomplete Payload has no value to pass. Going in
	// through the pinned entry address keeps the zero-argument shape, so what is
	// emitted is still a bare tail jump to the copy body.
	DeliverPayloadNuggetCopy copy =
		&_STL::__copy<DeliverPayloadNugget::Payload *, DeliverPayloadNugget::Payload *, int>;

	typedef void (__cdecl *DeliverPayloadNuggetCopyEntry)(void);
	((DeliverPayloadNuggetCopyEntry)copy)();
}