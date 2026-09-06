// stlport

#include <bitset>
#include <vector>

typedef int Int;

template <size_t NUMBITS>
class BitFlags
{
private:
	std::bitset<29> m_bits;

public:
	inline Int count() const { return m_bits.count(); }

	inline Int countIntersection(const BitFlags &that) const
	{
		BitFlags tmp = *this;
		tmp.m_bits &= that.m_bits;
		return tmp.m_bits.count();
	}

	inline Int countInverseIntersection(const BitFlags &that) const
	{
		BitFlags tmp = *this;
		tmp.m_bits.flip();
		tmp.m_bits &= that.m_bits;
		return tmp.m_bits.count();
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponTemplateSet
{
public:
	Int getConditionsYesCount() const { return 1; }
	const BitFlags<17> &getNthConditionsYes(Int) const
	{
		return *(const BitFlags<17> *)((const char *)this + 4);
	}

private:
	char m_padding00[4];
	BitFlags<17> m_types;
	char m_padding08[0xe4];
};

class WeaponFindBestInfoSlowShim
{
public:
	const WeaponTemplateSet *findBestInfoSlow(std::vector<WeaponTemplateSet> const &, BitFlags<17> const &) const;
};

// ?findBestInfoSlow@WeaponFindBestInfoSlowShim@@QBEPBVWeaponTemplateSet@@ABV?$vector@VWeaponTemplateSet@@V?$allocator@VWeaponTemplateSet@@@_STL@@@_STL@@ABV?$BitFlags@$0BB@@@@Z
const WeaponTemplateSet *WeaponFindBestInfoSlowShim::findBestInfoSlow(
	std::vector<WeaponTemplateSet> const &v, BitFlags<17> const &bits) const
{
	const WeaponTemplateSet *result = 0;
	Int bestYesMatch = 0;
	Int bestYesExtraneousBits = 999;

	for (std::vector<WeaponTemplateSet>::const_iterator it = v.begin(); it != v.end(); ++it)
	{
		for (Int i = it->getConditionsYesCount() - 1; i >= 0; --i)
		{
			const BitFlags<17> &yesFlags = it->getNthConditionsYes(i);
			Int yesMatch = bits.countIntersection(yesFlags);
			Int yesExtraneousBits = bits.countInverseIntersection(yesFlags);

			if ((yesMatch > bestYesMatch) ||
				(yesMatch >= bestYesMatch && yesExtraneousBits < bestYesExtraneousBits))
			{
				result = &(*it);
				bestYesMatch = yesMatch;
				bestYesExtraneousBits = yesExtraneousBits;
			}
		}
	}

	return result;
}

template <class Set, class Flags>
class SparseMatchFinder
{
	const Set *findBestInfoSlow(std::vector<Set> const &, Flags const &) const;
};

template <class Set, class Flags>
const Set *SparseMatchFinder<Set, Flags>::findBestInfoSlow(
	std::vector<Set> const &v, Flags const &f) const
{
	return (const Set *)((WeaponFindBestInfoSlowShim const *)this)->findBestInfoSlow(
		(const std::vector<WeaponTemplateSet> &)v, (const BitFlags<17> &)f);
}

template const WeaponTemplateSet *SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::findBestInfoSlow(
	const std::vector<WeaponTemplateSet> &, const BitFlags<17> &) const;
