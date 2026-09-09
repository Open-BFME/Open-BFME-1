// ?bfmeSetZH@BfmeObjZH@@QAEXPBUBfmeVecZH@@PBVBFMERetailAsciiString@@@Z
// partial score=0.96 date=2026-09-09
// ?bfmeSetZH@BfmeObjZH@@QAEXPBUBfmeVecZH@@PBVBFMERetailAsciiString@@@Z
// Retail stores a 16-byte ZH element in the vector at +0x38.

inline void *operator new(unsigned int, void *where)
{
	return where;
}

class BFMERetailAsciiString
{
public:
	void *m_data;
};

class UnicodeStringZH
{
public:
	UnicodeStringZH() : m_data(0) {}
	UnicodeStringZH(const UnicodeStringZH &other);
	void set(const BFMERetailAsciiString &other);
	void releaseBuffer();

private:
	void *m_data;
};

#pragma comment(linker, "/alternatename:??0UnicodeStringZH@@QAE@ABV0@@Z=??0GameSpyGroupRoom@@QAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?set@UnicodeStringZH@@QAEXABVBFMERetailAsciiString@@@Z=?set@UnicodeString@@QAEXABV1@@Z")
#pragma comment(linker, "/alternatename:?releaseBuffer@UnicodeStringZH@@AAEXXZ=?releaseBuffer@BFMERetailAsciiString@@AAEXXZ")

struct BfmeVecZH
{
	float x;
	float y;
	float z;
};

struct BfmeFalseZH
{
};

struct BfmeZHElement
{
	float x;
	float y;
	float z;
	UnicodeStringZH name;
};

class BfmeVecZHStorage
{
public:
	void overflow(BfmeZHElement *position, const BfmeZHElement &value,
		const BfmeFalseZH &, unsigned int fill, bool atEnd);

	BfmeZHElement *m_start;
	BfmeZHElement *m_finish;
	BfmeZHElement *m_end;
};

#pragma comment(linker, "/alternatename:?overflow@BfmeVecZHStorage@@QAEXPAUBfmeZHElement@@ABU2@ABUBfmeFalseZH@@I_N@Z=?overflow@BfmeVecCD@@QAEXPAUBfmeElemCD@@ABU2@ABUBfmeFalseCD@@I_N@Z")

class BfmeObjZH
{
public:
	void bfmeSetZH(const BfmeVecZH *value,
		const BFMERetailAsciiString *name);

private:
	unsigned char m_pad[0x38];
	BfmeVecZHStorage m_values;
};

void BfmeObjZH::bfmeSetZH(const BfmeVecZH *value,
	const BFMERetailAsciiString *name)
{
	BfmeZHElement local;
	local.x = value->x;
	BfmeObjZH *owner = this;
	local.y = value->y;
	local.z = value->z;
	local.name.set(*name);

	BfmeVecZHStorage *values = &owner->m_values;
	BfmeZHElement *position = values->m_finish;
	if (position != values->m_end)
	{
		if (position != 0)
			new (position) BfmeZHElement(local);
		++values->m_finish;
	}
	else
	{
		BfmeFalseZH tag;
		values->overflow(position, local, tag, 1, true);
	}

	local.name.releaseBuffer();
}
