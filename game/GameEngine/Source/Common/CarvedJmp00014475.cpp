// cl: /DNDEBUG /MD /O2 /EHsc
// Retail 0x00014475 is a five-byte ILT to Dict::releaseData at RVA 0x000681C0.
// The tail jump forwards the incoming `this` in ecx, so the reference needs no
// argument setup of its own.
class Dict
{
	friend void j_00014475(void);

private:
	void releaseData(void);
};

void j_00014475(void)
{
	union Call
	{
		void (Dict::*member_function)(void);
		void (*generic_function)(void);
	} call;

	call.member_function = &Dict::releaseData;
	call.generic_function();
}
