// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep


#include	"always.h"
#include	"straw.h"
#include	<stddef.h>


Straw::~Straw(void)
{
	if (ChainTo != NULL) {
		ChainTo->ChainFrom = ChainFrom;
	}
	if (ChainFrom != NULL) {
		ChainFrom->Get_From(ChainTo);
	}

	ChainFrom = NULL;
	ChainTo = NULL;
}


void Straw::Get_From(Straw * straw)
{
	if (ChainTo != straw) {
		if (straw != NULL && straw->ChainFrom != NULL) {
			straw->ChainFrom->Get_From(NULL);
			straw->ChainFrom = NULL;
		}

		if (ChainTo != NULL) {
			ChainTo->ChainFrom = NULL;
		}

		ChainTo = straw;
		if (ChainTo != NULL) {
			ChainTo->ChainFrom = this;
		}
	}
}


int Straw::Get(void * source, int slen)
{
	if (ChainTo != NULL) {
		return(ChainTo->Get(source, slen));
	}
	return(0);
}
