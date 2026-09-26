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

class BfmeObjZH;
struct BfmeElemCD;

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	StringBase(const StringBase &other);
	void set(const StringBase &other);

private:
	void releaseBuffer();
	friend struct BfmeElemCD;
	friend class BfmeObjZH;

private:
	void *m_data;
};

#pragma comment(linker, "/alternatename:??0AsciiString@@QAE@ABV0@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")
#pragma comment(linker, "/alternatename:?set@AsciiString@@QAEXABV1@@Z=?set@?$StringBase@D@@QAEXABV1@@Z")
#pragma comment(linker, "/alternatename:?releaseBuffer@AsciiString@@AAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

struct BfmeVecZH
{
	float x;
	float y;
	float z;
};

struct BfmeFalseCD
{
};

struct BfmeElemCD
{
	float x;
	float y;
	float z;
	StringBase<char> name;
};

class BfmeVecCD
{
public:
	void overflow(BfmeElemCD *position, const BfmeElemCD &value,
		const BfmeFalseCD &, unsigned int fill, bool atEnd);

	BfmeElemCD *m_start;
	BfmeElemCD *m_finish;
	BfmeElemCD *m_end;
};

#pragma comment(linker, "/alternatename:?overflow@BfmeVecBE@@QAEXPAUBfmeElemBE@@ABU2@ABUBfmeFalseBE@@I_N@Z=?overflow@BfmeVecCD@@QAEXPAUBfmeElemCD@@ABUBfmeFalseCD@@I_N@Z")

#pragma comment(linker, "/alternatename:?overflow@BfmeVecZHStorage@@QAEXPAUBfmeZHElement@@ABU2@ABUBfmeFalseZH@@I_N@Z=?overflow@BfmeVecCD@@QAEXPAUBfmeElemCD@@ABU2@ABUBfmeFalseCD@@I_N@Z")

class BfmeObjZH
{
public:
	void bfmeSetZH(const BfmeVecZH *value,
		const BFMERetailAsciiString *name);

private:
	unsigned char m_pad[0x38];
	BfmeVecCD m_values;
};

void BfmeObjZH::bfmeSetZH(const BfmeVecZH *value,
	const BFMERetailAsciiString *name)
{
	BfmeElemCD local;
	BfmeObjZH *owner = this;
	volatile const BfmeVecZH *vector = value;
	local.x = vector->x;
	local.y = vector->y;
	local.z = vector->z;
	local.name.set(reinterpret_cast<const StringBase<char> &>(*name));

	BfmeVecCD *values = &owner->m_values;
	BfmeElemCD *position = values->m_finish;
	if (position != values->m_end)
	{
		if (position != 0)
			new (position) BfmeElemCD(local);
		++values->m_finish;
	}
	else
	{
		BfmeFalseCD tag;
		values->overflow(position, local, tag, 1, true);
	}

	local.name.releaseBuffer();
}
