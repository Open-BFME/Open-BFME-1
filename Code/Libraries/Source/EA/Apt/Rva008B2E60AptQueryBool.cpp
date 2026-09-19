// ?aptQueryBool@@YAPAVAptValue@@PAURva008B2E60Value@@H@Z
// cl: /DNDEBUG /MD /EHsc
class AptValue;
AptValue* __cdecl Rva008A53D0MakeBool(int value);
AptValue* __cdecl Rva008A53D0MakeBoolFlag(bool value);
struct Rva008B2E60Target {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
	virtual int query();
};
struct Rva008B2E60Value {
	int m_0;
	union { unsigned int m_flags; struct { unsigned int m_type : 6; }; };
	char m_pad[0x20 - 8];
	Rva008B2E60Target* m_target;
};
AptValue* aptQueryBool(Rva008B2E60Value* v, int argc)
{
	if (v->m_type == 0x20 && v->m_target)
		return Rva008A53D0MakeBoolFlag(v->m_target->query() != 0);
	return Rva008A53D0MakeBool(0);
}
