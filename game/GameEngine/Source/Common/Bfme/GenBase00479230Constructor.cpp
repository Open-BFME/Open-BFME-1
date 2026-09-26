// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GenBase00479230::GenBase00479230, retail 0x00479230, 17 bytes.
//
// A vftable store and two zeroed words -- no base to run, so `this' goes
// straight into eax and the zero is materialised once for both stores.

class GenBase00479230
{
public:
	GenBase00479230();

	virtual ~GenBase00479230();

private:
	void *m_a;						// +0x04
	void *m_b;						// +0x08
};

GenBase00479230::GenBase00479230()
{
	m_a = 0;
	m_b = 0;
}
