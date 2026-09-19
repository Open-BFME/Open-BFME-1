// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: the STLport _Destroy(first, last) instantiated for
// ModelConditionInfo*, retail 0x0013C610.
//
// A destroy-the-range loop: test first != last up front, then call the element
// destructor and step. The stride is the fact it carries --
// **sizeof(ModelConditionInfo) is 0x128**, 296 bytes.
//
// Note the packet names this `_Destroy<ModelConditionInfo*>(ModelConditionInfo*)`,
// one parameter. The body takes two -- [esp+4] and [esp+8] before the pushes --
// so it is the two-iterator overload and the decorated name carries a `0`
// backreference for the second parameter.
//
// Worth flagging for whoever owns the destructor: the call goes through ILT
// 0x0002306F, which enters at 0x0013C3F0, but the ledger's
// ??1ModelConditionInfo@@QAE@XZ row starts at 0x0013C3FE -- fourteen bytes
// later, with nothing claiming the gap. Callers enter at the earlier address,
// so that row's boundary is worth rechecking.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ModelConditionInfo
{
	char m_unreconstructed_00[0x128];
	~ModelConditionInfo();
};

namespace _STL
{

template <class _Tp>
inline void _Destroy_one(_Tp *__pointer)
{
	__pointer->~_Tp();
}

template <class _ForwardIterator>
void _Destroy(_ForwardIterator __first, _ForwardIterator __last)
{
	for ( ; __first != __last; ++__first)
		_Destroy_one(&*__first);
}

template void _Destroy<ModelConditionInfo *>(ModelConditionInfo *, ModelConditionInfo *);

}
