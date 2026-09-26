// cl: /O2
//
// Retail 0x0045BB60 contains only `ret`.  The carved boundary and its nearby
// rows provide no class or method identity, so this empty RVA-derived method
// preserves only the proven no-op behavior.

class Rva0045BB60
{
public:
	void noOp();
};

void Rva0045BB60::noOp()
{
}
