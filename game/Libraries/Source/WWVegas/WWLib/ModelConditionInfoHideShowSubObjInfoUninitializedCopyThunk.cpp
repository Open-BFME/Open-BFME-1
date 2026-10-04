// ?Rva000032A6HideShowSubObjInfoUninitializedCopyThunk@@YAXXZ
// Retail RVA 0x000032A6 is a five-byte ILT tail jump to the matched
// HideShowSubObjInfo uninitialized-copy body at RVA 0x003AA480.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

// Declaration-only mirror of the layout the target body was recovered with:
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class ModelConditionInfo
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct HideShowSubObjInfo
	{
		int m_raw[2];
	};
};

namespace _STL
{
struct __false_type
{
};

// Declaration only, no definition here: the body is the explicit
// instantiation in
// game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/HideShowSubObjInfoUninitializedCopyBody.cpp,
// the matched 0x003AA480 row. Spelled with the real four parameters so this
// TU's reference to the specialization mangles to exactly that symbol; the
// union below then calls it through a no-argument signature, which is what
// keeps the jump five bytes instead of pushing the arguments.
template <class In, class Out>
Out __uninitialized_copy(In first, In last, Out result, const __false_type &tag);
}

// The ILT thunk forwards whatever arguments its caller left in place, and
// __uninitialized_copy never reads its trailing __false_type tag, so a bare
// tail jump is byte-exact. The voidcall member keeps the call argument-free
// while `copy` carries the real signature the address is typed with, the same
// shape game/GameEngine/Source/GameNetwork/TransportQueueSendThunk.cpp uses.
union ModelConditionInfoHideShowSubObjInfoUninitializedCopyTarget
{
	void (*voidcall)();
	ModelConditionInfo::HideShowSubObjInfo *(*copy)(
		const ModelConditionInfo::HideShowSubObjInfo *,
		const ModelConditionInfo::HideShowSubObjInfo *,
		ModelConditionInfo::HideShowSubObjInfo *, const _STL::__false_type &);
};

void Rva000032A6HideShowSubObjInfoUninitializedCopyThunk(void)
{
	ModelConditionInfoHideShowSubObjInfoUninitializedCopyTarget target;
	target.copy = &_STL::__uninitialized_copy<const ModelConditionInfo::HideShowSubObjInfo *,
		ModelConditionInfo::HideShowSubObjInfo *>;
	target.voidcall();
}