// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: NoString scalar-deleting destructor at retail RVA 0x004374D0
// (30 bytes). The exact default constructor at 0x0010DB40, the recovered
// GameTextManager list layout, and deinit's owned-node deletion establish this
// non-virtual type. The wrapper calls its destructor through ILT 0x0002349D.

struct NoString
{
	~NoString();
};

void forceNoStringDelete(NoString *node)
{
	delete node;
}
