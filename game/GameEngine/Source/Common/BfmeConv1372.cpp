// cl: /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5 conversions.

// Retail's bfmeSizeVID calls the bodies at 0x00977870 and 0x009779A0, which
// Rva00977870Arithmetic.cpp and Bfme5TinyNine.cpp already own and define
// (?compute@Rva00977870Object@@QAEHXZ and ?bfmeSlots@Gen_009779A0@@QBEHXZ).
// Both classes are declared here, never defined, so the calls bind to those
// bodies instead of to a TU-local name nothing links.
class Rva00977870Object
{
public:
	int compute(void);
};

class Gen_009779A0
{
public:
	int bfmeSlots(void) const;
};

class BfmeThingVID
{
public:
	int bfmeSizeVID();
	Rva00977870Object *m_bfme00;
	Rva00977870Object *m_bfme04;
	Rva00977870Object *m_bfme08;
	Rva00977870Object *m_bfme0c;
	Rva00977870Object *m_bfme10;
	Rva00977870Object *m_bfme14;
	Rva00977870Object *m_bfme18;
	int m_bfme1c;
	Gen_009779A0 *m_bfme20;
};

int BfmeThingVID::bfmeSizeVID()
{
	int total = 0x24;
	if (m_bfme00)
		total = m_bfme00->compute() + 0x24;
	if (m_bfme04)
		total += m_bfme04->compute();
	if (m_bfme08)
		total += m_bfme08->compute();
	if (m_bfme0c)
		total += m_bfme0c->compute();
	if (m_bfme10)
		total += m_bfme10->compute();
	if (m_bfme14)
		total += m_bfme14->compute();
	if (m_bfme18)
		total += m_bfme18->compute();
	if (m_bfme20)
		total += m_bfme20->bfmeSlots();
	return total;
}