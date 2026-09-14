// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: NamedReveal scalar-deleting destructor at retail RVA 0x0033AE00
// (30 bytes). The wrapper calls the exact three-AsciiString complete
// destructor at 0x00339C30 through ILT 0x000244DD; its 16-byte record layout,
// copy constructor, and ScriptEngine vector insert/erase users establish the
// authentic value type.

class NamedReveal
{
public:
	~NamedReveal();
};

void forceNamedRevealDeletingDestructor(NamedReveal *value)
{
	delete value;
}
