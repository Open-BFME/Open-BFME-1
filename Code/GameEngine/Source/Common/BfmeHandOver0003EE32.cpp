// cl: /O2 /Ob2 /DNDEBUG /MD /EHs-c-

class Xfer
{
};

class GameClientRandomVariable
{
};

class BfmeSeedTarget
{
};

extern Xfer &xferRandomVariable(
	Xfer &xfer, GameClientRandomVariable &variable);

// ?bfmeHandOver_0003EE32@@YAXPAVBfmeSeedTarget@@PAX@Z
void bfmeHandOver_0003EE32(BfmeSeedTarget *target, void *item)
{
	xferRandomVariable(
		*reinterpret_cast<Xfer *>(target),
		*reinterpret_cast<GameClientRandomVariable *>(item));
}
