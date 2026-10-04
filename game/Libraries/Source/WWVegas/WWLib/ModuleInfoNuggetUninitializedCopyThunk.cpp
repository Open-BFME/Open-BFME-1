// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

// Retail 0x0001819C is the ModuleInfo::Nugget __uninitialized_copy ILT.
// Its five-byte tail jump reaches the matched 0x0076B010 body, which the
// owning translation unit (Common/Containers/Rva0013B8F0Vector.cpp) emits as
// _STL::__uninitialized_copy<const Rva0013B8F0Element *, Rva0013B8F0Element *>.
// Only that instantiation's declaration belongs here: defining the template
// in this TU would emit a second body for an address retail has once.
struct Rva0013B8F0Element;

namespace _STL
{
struct __false_type;

template <class _InputIter, class _ForwardIter>
Rva0013B8F0Element *__cdecl __uninitialized_copy(
	const Rva0013B8F0Element *first,
	const Rva0013B8F0Element *last,
	Rva0013B8F0Element *result,
	const __false_type &tag);
}

void Rva0001819CModuleInfoNuggetUninitializedCopyThunk(void)
{
	typedef Rva0013B8F0Element *(__cdecl *UninitializedCopy)(
		const Rva0013B8F0Element *, const Rva0013B8F0Element *,
		Rva0013B8F0Element *, const _STL::__false_type &);
	typedef void (__cdecl *UninitializedCopyThunk)(void);

	UninitializedCopy copy =
		&_STL::__uninitialized_copy<const Rva0013B8F0Element *,
			Rva0013B8F0Element *>;

	((UninitializedCopyThunk)(void *)copy)();
}