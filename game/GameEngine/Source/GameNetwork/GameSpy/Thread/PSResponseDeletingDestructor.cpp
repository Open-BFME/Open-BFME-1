// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: PSResponse scalar-deleting destructor at retail RVA 0x00654CB0
// (30 bytes). Its exact default and copy constructors, 0x1F0-byte recovered
// layout, and deque/queue lifecycle paths establish the non-virtual response
// type. The wrapper calls its destructor through ILT 0x0003B0CF before delete.

class PSResponse
{
public:
	~PSResponse();
};

void forcePSResponseDelete(PSResponse *response)
{
	delete response;
}
