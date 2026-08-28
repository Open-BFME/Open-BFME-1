// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the gen-asm dump for ScriptConditions.cpp's local helper
// class ObjectTypesTemp::ObjectTypesTemp() to a standalone C++ thunk.

// Local minimal replica of GameLogic/ObjectTypes.h's ObjectTypes. Only its
// size (20 bytes, matching the retail `push 0x14` allocation size) and the
// mangled default constructor matter here -- ObjectTypes itself is fully
// defined and matched elsewhere.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ObjectTypes.h
class ObjectTypes
{
public:
	ObjectTypes();
private:
	int m_pad[5];
};

// ScriptConditions.cpp: a scope guard that default-constructs an ObjectTypes
// on the heap and frees it (via deleteInstance(), not part of this ctor) when
// the guard goes out of scope.
class ObjectTypesTemp
{
public:
	ObjectTypes *m_types;

	ObjectTypesTemp();
};

// ??0ObjectTypesTemp@@QAE@XZ
ObjectTypesTemp::ObjectTypesTemp() : m_types(0)
{
	m_types = new ObjectTypes;
}
