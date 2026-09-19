// cl: /DNDEBUG /MD /EHsc
// BFME retail layout witness: bfme_layout.py UpgradeMuxData, plus the
// removal helper at 0x002D9C40.  The two masks lead the BFME object at +0x00
// and +0x18; activation/conflict name vectors follow at +0x30 and +0x3c.
// stlport

#include <bitset>
#include <string.h>
#include <vector>

template <typename Char>
class StringBase
{
protected:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		Char text[1];
	};

	Header *m_data;

public:
	bool isEmpty() const
	{
		return !m_data || m_data->length == 0;
	}

	void set(const StringBase<Char> &other);
	bool isNone() const;
};

class AsciiString : public StringBase<char>
{
};

extern char Rva006A16B0Empty[];

class BFMERetailAsciiString : public StringBase<char>
{
public:
	~BFMERetailAsciiString();

	BFMERetailAsciiString &operator=(const BFMERetailAsciiString &other)
	{
		set(other);
		return *this;
	}

	const char *str() const
	{
		const char *data = *reinterpret_cast<const char *const *>(this);
		return data ? data + 8 : Rva006A16B0Empty;
	}

private:
};

template <int NUMBITS>
class BitFlags
{
public:
	void clear()
	{
		m_bits.reset();
	}

	void set(unsigned int bit)
	{
		m_bits._Unchecked_set((size_t)bit);
	}

private:
	_STL::bitset<192> m_bits;
};

	typedef BitFlags<128> UpgradeMaskType;

class UpgradeTemplate
{
public:
	unsigned int getUpgradeMask() const
	{
		return *reinterpret_cast<const unsigned int *>(
			reinterpret_cast<const unsigned char *>(this) + 0x20);
	}
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

class INIException
{
public:
	char *m_failureMessage;
	int m_argCount;
	INIException(int argCount, const char *message, ...);
	INIException(const INIException &other);
	~INIException();
};

class Rva002D9FF0UpgradeMuxData
{
public:
	void getUpgradeActivationMasks(UpgradeMaskType &activation,
		UpgradeMaskType &conflicting) const;

private:
	mutable UpgradeMaskType m_activationMask;
	mutable UpgradeMaskType m_conflictingMask;
	mutable _STL::vector<BFMERetailAsciiString> m_activationUpgradeNames;
	mutable _STL::vector<BFMERetailAsciiString> m_conflictingUpgradeNames;
};

// ?getUpgradeActivationMasks@UpgradeMuxData@@QBEXAAV?$BitFlags@$0IA@@@0@Z
void Rva002D9FF0UpgradeMuxData::getUpgradeActivationMasks(
	UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
{
	if (!m_activationUpgradeNames.empty() || !m_conflictingUpgradeNames.empty())
	{
		m_activationMask.clear();
		m_conflictingMask.clear();

		_STL::vector<BFMERetailAsciiString>::const_iterator it;
		for (it = m_activationUpgradeNames.begin();
			it != m_activationUpgradeNames.end(); ++it)
		{
			const UpgradeTemplate *theTemplate =
				TheUpgradeCenter->findUpgrade(*(const AsciiString *)it);
			if (!theTemplate && !it->isEmpty() && !it->isNone())
			{
				throw INIException(3,
					"An upgrade module references %s, which is not an Upgrade",
					it->str());
			}

			m_activationMask.set(theTemplate->getUpgradeMask());
		}

		for (it = m_conflictingUpgradeNames.begin();
			it != m_conflictingUpgradeNames.end(); ++it)
		{
			const UpgradeTemplate *theTemplate =
				TheUpgradeCenter->findUpgrade(*(const AsciiString *)it);
			if (!theTemplate && !it->isEmpty() && !it->isNone())
			{
				throw INIException(3,
					"An upgrade module references %s, which is not an Upgrade",
					it->str());
			}

			m_conflictingMask.set(theTemplate->getUpgradeMask());
		}

		m_activationUpgradeNames.clear();
		m_conflictingUpgradeNames.clear();
	}

	activation = m_activationMask;
	conflicting = m_conflictingMask;
}
