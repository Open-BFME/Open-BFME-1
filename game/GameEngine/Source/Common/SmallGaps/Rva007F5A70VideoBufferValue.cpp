// Existing outer identity and int return remain unproved historical debt.
// Only the independently proven 0x007E88A0 callee identity is corrected.
// ?videoBufferValue@Rva007F5A70Owner@@QAEHPAVW3DVideoBuffer@@@Z
class W3DVideoBuffer { public: virtual bool valid(); };
class Rva007E88A0 { public: bool method(); };
class Gen_007e88b0 { public: int m(); };
struct Rva007F5A70Target {
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17();
	virtual void s18();
	virtual int apply(int value);
};
struct Rva007F5A70Owner {
	char m_pad[0x1c];
	Rva007F5A70Target* m_target;
	int videoBufferValue(W3DVideoBuffer* buffer);
};
int Rva007F5A70Owner::videoBufferValue(W3DVideoBuffer* buffer)
{
	if (reinterpret_cast<Rva007E88A0 *>(buffer)->method()) {
		int value = ((Gen_007e88b0*)buffer)->m();
		return m_target->apply(value);
	}
	return m_target->apply(0);
}
