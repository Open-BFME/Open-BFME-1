// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/WeaponSet.h
class WeaponTemplateSet
{
};

template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
};

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class Allocator>
class vector
{
};
}

template <class Set, class Flags>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
class SparseMatchFinder
{
	const Set *findBestInfoSlow(_STL::vector<Set, _STL::allocator<Set> > const &, Flags const &) const;
};

class WeaponFindBestInfoSlowShim
{
public:
	const WeaponTemplateSet *findBestInfoSlow(_STL::vector<WeaponTemplateSet, _STL::allocator<WeaponTemplateSet> > const &v, BitFlags<17> const &f) const;
};

template <class Set, class Flags>
const Set *SparseMatchFinder<Set, Flags>::findBestInfoSlow(_STL::vector<Set, _STL::allocator<Set> > const &v, Flags const &f) const
{
	return (const Set *)((WeaponFindBestInfoSlowShim const *)this)->findBestInfoSlow(
		(_STL::vector<WeaponTemplateSet, _STL::allocator<WeaponTemplateSet> > const &)v,
		(BitFlags<17> const &)f);
}

template const WeaponTemplateSet *SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::findBestInfoSlow(_STL::vector<WeaponTemplateSet, _STL::allocator<WeaponTemplateSet> > const &, BitFlags<17> const &) const;
