// cl: /DNDEBUG /MD /EHsc
// Open-BFME: S4Made0090F650::S4Made0090F650, retail 0x0090F650, 48 bytes.
//
// No base and no vftable: six zeroed words, then the global at 0x012D6E2C, then
// four ones. The zero and the 1.0f are each materialised once and reused, which
// is what groups the stores the way retail has them.

typedef float Real;

class BfmeShared012D6E2C;

extern BfmeShared012D6E2C *TheBfmeShared012D6E2C;

class S4Made0090F650
{
public:
	S4Made0090F650();

private:
	void *m_a;						// +0x00
	void *m_b;						// +0x04
	void *m_c;						// +0x08
	void *m_d;						// +0x0C
	void *m_e;						// +0x10
	void *m_f;						// +0x14
	BfmeShared012D6E2C *m_shared;				// +0x18
	Real m_x;						// +0x1C
	Real m_y;						// +0x20
	Real m_z;						// +0x24
	Real m_w;						// +0x28
};

S4Made0090F650::S4Made0090F650()
{
	m_a = 0;
	m_b = 0;
	m_c = 0;
	m_d = 0;
	m_e = 0;
	m_f = 0;
	m_shared = TheBfmeShared012D6E2C;
	m_x = 1.0f;
	m_y = 1.0f;
	m_z = 1.0f;
	m_w = 1.0f;
}
