// cl: /DNDEBUG /MD /EHsc
// Structural BFME recovery, retail 0x0080EE80 (106 bytes).
// Query tags select the corresponding state word in the address-derived view.

struct Rva0080EE80View
{
	unsigned char m_unmodelled_000[0x6C];
	unsigned m_state;
	unsigned m_first;
	unsigned m_second;
	unsigned m_third;
};

// The retail helper retains a frame while comparing each tag in source order.
#pragma optimize("", off)
int Rva0080EE80Query(Rva0080EE80View *object, unsigned tag)
{
	if (tag == 0x686F7374u)
		return object->m_state == 0;
	if (tag == 0x6A6F696Eu)
		return object->m_state == 1;
	if (tag == 0x686F6970u)
		return object->m_first;
	if (tag == 0x70656970u)
		return object->m_second;
	if (tag == 0x736F636Bu)
		return object->m_third;
	return 0;
}
#pragma optimize("", on)
