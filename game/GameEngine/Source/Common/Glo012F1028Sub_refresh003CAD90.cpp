// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Glo012F1028Sub::refresh003CAD90, retail 0x003CAD90, 88 bytes.
// The existing ILT pin at 0x00040016 is shared by this body and the older
// neutral owner alias; the named caller at 0x003B41A0 selects this method on
// Glo012F1028->m_bfmeSub after changing the campaign.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

void j_00022f48(void);
void j_00028290(void);
void j_0000ebb5(void);
void j_0002de89(void);

struct Glo012F1028Holder
{
	AsciiString m_name;
	char m_pad04[0x2C];
	void **m_bfmeStart;
	void **m_bfmeFinish;
	char m_pad38[8];
	char m_bfmeOwner[0x20];
};

struct Rva003CAD90CreateCall
{
	void call(void *output, AsciiString name, int flag, int mode);
};

struct Rva003CAD90RebuildCall
{
	void call(void *output, void *owner);
};

struct Rva003CAD90OwnerCall
{
	void call();
};

struct Rva003CAD90NotifyCall
{
	void call();
};

class Glo012F1028Sub
{
public:
	void refresh003CAD90();

private:
	char m_pad00[4];
	Glo012F1028Holder *m_bfmeHolder;
	int m_at08;
	int m_at0C;
	unsigned char m_at10;
	char m_pad11[0x13];
	void *m_at24;
};

void Glo012F1028Sub::refresh003CAD90()
{
	typedef void (Rva003CAD90CreateCall::*CreateAction)(
		void *, AsciiString, int, int);
	union { void (*asFunction)(); CreateAction asMember; } createCast;
	createCast.asFunction = j_00022f48;

	(reinterpret_cast<Rva003CAD90CreateCall *>(this)->*createCast.asMember)(
		&m_at24, AsciiString(*(const AsciiString *)m_bfmeHolder), 0, 0);

	typedef void (Rva003CAD90RebuildCall::*RebuildAction)(void *, void *);
	union { void (*asFunction)(); RebuildAction asMember; } rebuildCast;
	rebuildCast.asFunction = j_00028290;
	(reinterpret_cast<Rva003CAD90RebuildCall *>(m_bfmeHolder)->*rebuildCast.asMember)(
		m_at24, this);

	typedef void (Rva003CAD90OwnerCall::*OwnerAction)();
	union { void (*asFunction)(); OwnerAction asMember; } ownerCast;
	ownerCast.asFunction = j_0000ebb5;
	(reinterpret_cast<Rva003CAD90OwnerCall *>(
		(char *)m_bfmeHolder + 0x40)->*ownerCast.asMember)();

	typedef void (Rva003CAD90NotifyCall::*NotifyAction)();
	union { void (*asFunction)(); NotifyAction asMember; } notifyCast;
	notifyCast.asFunction = j_0002de89;
	(reinterpret_cast<Rva003CAD90NotifyCall *>(this)->*notifyCast.asMember)();

	m_at10 = 1;
	m_at08 = 0;
	m_at0C = 0;
}
