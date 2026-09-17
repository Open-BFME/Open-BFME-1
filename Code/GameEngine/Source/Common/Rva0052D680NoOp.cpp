// ?run@Rva0052D680NoOp@@QAEXXZ
// cl: /O2 /MD /EHsc-
//
// Retail 0x0052D680 contains only ret.
// The carved boundary proves the one-byte extent, but no evidence proves a
// semantic owner, so the source keeps the address-derived identity.

class Rva0052D680NoOp
{
public:
	void run();
};

void Rva0052D680NoOp::run()
{
}
