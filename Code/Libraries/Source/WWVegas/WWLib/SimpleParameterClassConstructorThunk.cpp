template<class Type, int Flags>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad/simpleparameter.h
class SimpleParameterClass
{
public:
	SimpleParameterClass(void *, char const *);
};

template<class Type, int Flags>
__declspec(naked) SimpleParameterClass<Type, Flags>::SimpleParameterClass(void *, char const *)
{
	__asm {
		_emit 0E9h
		_emit 027h
		_emit 015h
		_emit 011h
		_emit 000h
	}
}

template __declspec(naked) SimpleParameterClass<int, 0>::SimpleParameterClass(void *, char const *);
