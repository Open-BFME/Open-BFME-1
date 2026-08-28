// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
struct ModelConditionInfo
{
private:
	char m_data[0xbc];
};

namespace _STL
{
struct __false_type
{
};

template <class T1, class T2>
void _Construct(T1 *destination, const T2 &value);

template <class ForwardIterator, class Size, class T>
ForwardIterator __uninitialized_fill_n(
	ForwardIterator first, Size count, const T &value, const __false_type &)
{
	ForwardIterator current = first;
	while (count > 0)
	{
		_Construct(current, value);
		++current;
		--count;
	}
	return current;
}

template ModelConditionInfo *__uninitialized_fill_n<ModelConditionInfo *, unsigned int, ModelConditionInfo>(
    ModelConditionInfo *, unsigned int, const ModelConditionInfo &, const __false_type &);
}
