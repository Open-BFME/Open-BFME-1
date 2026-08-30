// ?d_001b27c0@@YAXXZ
// partial score=0.92 date=2026-08-30
// cl: /O2 /Oa
// 25/23 bytes: the two extra are a `mov ecx,eax` copy. Retail loads the value
// straight into the register it pushes; here the load is hoisted above the
// pointer load, so the value lands in eax and needs a copy for the push.
class BfmeThingEBH { public: float bfmeCalcEBH(float value); char m_pad[8]; float m_result; float m_input; };
class BfmeOwner1B27E0 { public: void bfmeSet1B27C0(float value); void bfmeApply1B27E0(); private: char m_pad[0x28]; float m_value; BfmeThingEBH *m_thing; };

void BfmeOwner1B27E0::bfmeSet1B27C0(float value)
{
	BfmeThingEBH *thing = m_thing;

	thing->m_input = value;
	thing->m_result = thing->bfmeCalcEBH(value);
}

void BfmeOwner1B27E0::bfmeApply1B27E0()
{
	BfmeThingEBH *thing = m_thing;

	thing->m_input = m_value;
	thing->m_result = thing->bfmeCalcEBH(m_value);
}
