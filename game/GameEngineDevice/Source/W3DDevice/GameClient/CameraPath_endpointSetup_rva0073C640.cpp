// cl: /O2 /Ob0
// Camera-path endpoint setup at retail RVA 0x0073C640.
//
// Matched constructor 0x00740AE0 installs the three-slot vftable 0x0112171C
// and builds the two path-element arrays at +0x2c and +0x1418.  Its matched
// destructor at 0x00740BC0 destroys those arrays.  The matched path helper at
// 0x00740440 proves cameraAngle[256] at +0x1468 and numWaypoints at +0x2070,
// all relative to this path receiver.  W3DView owns one such object at +0x280.
//
// This TU emits no vtable or lifetime implementation.  The body's only inbound
// reference is incremental-link thunk 0x000392F2, which itself has no inbound
// xref, so the original method and selector type names are not recoverable.
// Ret 12 proves three four-byte arguments; x87 use proves the third is a Real.

typedef float Real;

enum Rva0073C640Selector
{
	RVA0073C640_SELECTOR_0 = 0,
	RVA0073C640_SELECTOR_1 = 1,
	RVA0073C640_SELECTOR_2 = 2
};

class Rva00740AE0
{
public:
	void rva0073C640(Rva0073C640Selector firstSelector,
		Rva0073C640Selector finalSelector, Real angle);

private:
	char m_unmodeled0000[0x1468];
	Real m_cameraAngles[256];
	char m_unmodeled1868[0x2070 - 0x1868];
	int m_numWaypoints;
};

void Rva00740AE0::rva0073C640(Rva0073C640Selector firstSelector,
	Rva0073C640Selector finalSelector, Real angle)
{
	Real *end = &m_cameraAngles[m_numWaypoints + 2];
	m_cameraAngles[1] = angle;

	switch (finalSelector)
	{
		case RVA0073C640_SELECTOR_0:
		// Retail routes out-of-range selector values to the same copy operation.
		selector0Final:
			end[-1] = end[-2];
			break;
		case RVA0073C640_SELECTOR_1:
			end[-1] = end[-2] + (end[-2] - end[-3]);
			break;
		case RVA0073C640_SELECTOR_2:
			end[-2] = angle;
			end[-1] = m_cameraAngles[2];
			break;
		default:
			goto selector0Final;
	}

	switch (firstSelector)
	{
		case RVA0073C640_SELECTOR_0:
		// Keep the observed default-to-copy branch shared with the zero case.
		selector0First:
			m_cameraAngles[0] = m_cameraAngles[1];
			break;
		case RVA0073C640_SELECTOR_1:
			m_cameraAngles[0] =
				m_cameraAngles[1] + (m_cameraAngles[1] - m_cameraAngles[2]);
			break;
		case RVA0073C640_SELECTOR_2:
			m_cameraAngles[0] = end[-3];
			break;
		default:
			goto selector0First;
	}
}
