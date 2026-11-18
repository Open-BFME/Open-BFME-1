// cl: /DNDEBUG /MD /EHsc
// readable body of ?getAsciiString@Dict@@: game/GameEngine/Source/Common/Dict.cpp
// Open-BFME: Dict::getAsciiString, retail 0x00068580, 96 bytes.

#include "../../Include/Common/ScalarTypes.h"



#include "../../Include/Common/NameKeyType.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
public:
	enum DataType
	{
		DICT_NONE = -1,
		DICT_BOOL,
		DICT_INT,
		DICT_REAL,
		DICT_ASCIISTRING,
		DICT_UNICODESTRING
	};

	DataType getType(NameKeyType key) const;
	bool known(NameKeyType key, DataType type) const;
	AsciiString getAsciiString(NameKeyType key, Bool *exists = 0) const;

private:
	enum DictPairKeyType { DICTPAIRKEY_ILLEGAL = 0 };

	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
	struct DictPair
	{
		DictPairKeyType m_key;					// this+0x00, type in the low byte
		void *m_value;						// this+0x04

		inline static DataType getTypeFromKey(DictPairKeyType nk)
		{
			return (DataType)(((UnsignedInt)nk) & 0xff);
		}

		inline AsciiString *asAsciiString() { return (AsciiString *)&m_value; }
	};

	DictPair *findPairByKey(NameKeyType key) const;		// ILT 0x0003451D

	void *m_data;
};

AsciiString Dict::getAsciiString(NameKeyType key, Bool *exists /*=NULL*/) const
{
	DictPair *pair = findPairByKey(key);
	if (pair && DictPair::getTypeFromKey(pair->m_key) == DICT_ASCIISTRING)
	{
		if (exists) *exists = true;
		return *pair->asAsciiString();
	}
	if (exists) *exists = false;
	return AsciiString::TheEmptyString;
}

bool Dict::known(NameKeyType key, DataType type) const
{
	return getType(key) == type;
}
