// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: Parameter scalar-deleting destructor at retail RVA 0x00352CF0
// (30 bytes). The exact constructor at 0x00352510, recovered ScriptEngine
// layout, and Parameter::deleteInstance ownership path establish the concrete
// non-virtual class. The wrapper calls its destructor through ILT 0x0003463A.

class Parameter
{
public:
	~Parameter();
};

void forceParameterDelete(Parameter *parameter)
{
	delete parameter;
}
