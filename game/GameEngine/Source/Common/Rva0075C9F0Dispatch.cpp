// Neutral raw-ABI reconstruction for retail 0x0075C9F0 (101 bytes).
//
// No named caller, constructor/vtable store, RTTI owner, or emitted C++
// function identifies this small dispatch member.  The body does establish a
// __thiscall receiver plus one pointer argument and two target virtual slots;
// the names below intentionally describe only those proven roles.  novtable
// keeps this TU from inventing a target vtable.

typedef float Real;

extern Real g_bfmeDefaultBU; // retail VA 0x01075334; existing canonical pin

class __declspec(novtable) Rva0075C9F0DispatchTarget
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43(void *first, void *second, void *third, void *fourth,
		Real value) = 0; // target vtable +0xac
	virtual void slot44(void *first, void *second, int value) = 0; // +0xb0
};

class Rva0075C9F0DispatchOwner
{
public:
	void update(Rva0075C9F0DispatchTarget *target);

private:
	unsigned char m_000[0x74];
	Real m_value74;
	Real m_value78;
	unsigned char m_07c[0x60];
	void *m_context;
	void *m_value;
	unsigned char m_0e4[0x14];
	void *m_optional;
	void *m_resource;
};

void Rva0075C9F0DispatchOwner::update(Rva0075C9F0DispatchTarget *target)
{
	if (target == 0 || m_context == 0)
	{
		return;
	}

	if (m_optional != 0)
	{
		const Real value = g_bfmeDefaultBU - m_value74 / m_value78;
		target->slot43(m_context, m_value, m_optional, m_resource, value);
		return;
	}

	target->slot44(m_context, m_value, 0);
}
