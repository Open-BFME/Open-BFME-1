// cl: /O2 /Ob0
// Glo012F4B98Type::after, retail RVA 0x0058EFF0, 129 bytes.

void __cdecl operator delete(void *block) throw();

class Glo012F4B98Type
{
public:
	void after();

private:
	char m_pad00[0x460];
	int m_head0;
	int m_head1;
	volatile bool m_flag;
	char m_pad469[3];
	int m_index0;
	int m_index1;
	int m_index2;
	volatile int m_value;
	int m_optionalMarker;
	void *m_optional;
	void *m_second;
	char m_pad488[0x44];
	void *m_first;
};

void Glo012F4B98Type::after()
{
	operator delete(m_first);

	int zero = 0;
	volatile int *firstSlot = (volatile int *)&m_first;
	*firstSlot = 0;
	*(volatile unsigned char *)&m_flag = 0;
	int invalid = -2;
	m_index0 = invalid;
	m_index1 = invalid;
	m_index2 = invalid;
	m_value = zero;

	void *optional = *(void * volatile *)&m_optional;
	if (optional)
		operator delete(optional);
	*(void * volatile *)&m_optional = 0;

	// Retail at +0x57 is `mov ecx,[esi+484h] / push ecx / call ??3@YAXPAX@Z /
	// mov [esi+484h],ebx / add esp,4`: a second unguarded deallocation whose
	// pointer is loaded into ECX (not EAX, unlike the guarded one above), whose
	// nulling store lands after the call and before the `add esp,4`.  Reading
	// and clearing the slot through a `void * volatile *` is what keeps that
	// load in ECX and the cleanup below the store; a plain `m_second = 0` puts
	// the `add esp,4` first.  The callee is retail's own operator delete,
	// declared at the top of this file.
	{
		void * volatile *slot = &m_second;
		operator delete(*slot);
		*slot = 0;
	}

	m_head0 = 0;
	m_head1 = 0;
	m_optionalMarker = 0;
}
