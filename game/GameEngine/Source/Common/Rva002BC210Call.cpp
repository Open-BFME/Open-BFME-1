// cl: /O2 /Ob0
//
// 17-byte flag test + tail jmp: test byte [this+0x3F0], 1; if set,
// xor al,al / ret; else jmp ILT 0x000042BE (thiscall, ecx unchanged).

typedef bool Bool;

class Object;
class StateMachine;

class AIUpdateInterface
{
public:
	virtual Bool isIdle() const;

private:
	unsigned char m_unmodelled_04[4];
	Object *m_object;
	unsigned char m_unmodelled_0C[0x30 - 0x0C];
	StateMachine *m_stateMachine;
};

class Rva002BC210
{
	char m_lead[0x3F0];
	unsigned char m_flag;

public:
	bool call();
};

bool Rva002BC210::call()
{
	if (m_flag & 1)
		return false;
	return reinterpret_cast<const AIUpdateInterface *>(this)
		->AIUpdateInterface::isIdle();
}
