class ArmorTemplateSet;
class WeaponTemplateSet;

template <int Bits>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	unsigned int m_bits;
	bool test(int pos) const { return (m_bits & (1u << (pos & 0x1f))) != 0; }
};

template <class Set, class Flags>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
class SparseMatchFinder
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
	class MapHelper
	{
	public:
		bool operator()(const Flags &, const Flags &) const;
	};
};

class ArmorMapHelperShim
{
public:
	bool call(const BitFlags<11> &a, const BitFlags<11> &b) const;
};

class WeaponMapHelperShim
{
public:
	bool call(const BitFlags<17> &a, const BitFlags<17> &b) const;
};

// ?call@ArmorMapHelperShim@@QBE_NABV?$BitFlags@$0L@@@0@Z
//
// Retail's loop runs to 0x1d (29), not the 11 the declared BitFlags<11>
// parameter type would suggest -- the 11/17 here are just what makes the
// already-matched 5-byte forwarding thunks below mangle correctly; they say
// nothing about the real per-game bit count, which this TU has no header
// for. The loop bound is hardcoded to match retail directly rather than
// wired through BitFlags<Bits>::size().
bool ArmorMapHelperShim::call(const BitFlags<11> &a, const BitFlags<11> &b) const
{
	int i;
	for (i = 0; i < 29; ++i)
	{
		bool aVal = a.test(i);
		bool bVal = b.test(i);
		if (aVal && bVal) continue;
		if (!aVal && !bVal) continue;
		if (!aVal) return true;
		return false;
	}
	return false; // all bits match.
}

// ?call@WeaponMapHelperShim@@QBE_NABV?$BitFlags@$0BB@@@0@Z
//
// Same shape as ArmorMapHelperShim::call above; retail's loop runs to 0xb
// (11) here, independent of the declared BitFlags<17> parameter type for
// the same reason noted there.
bool WeaponMapHelperShim::call(const BitFlags<17> &a, const BitFlags<17> &b) const
{
	int i;
	for (i = 0; i < 11; ++i)
	{
		bool aVal = a.test(i);
		bool bVal = b.test(i);
		if (aVal && bVal) continue;
		if (!aVal && !bVal) continue;
		if (!aVal) return true;
		return false;
	}
	return false; // all bits match.
}

template <class Set, class Flags>
bool SparseMatchFinder<Set, Flags>::MapHelper::operator()(const Flags &a, const Flags &b) const
{
	return ((ArmorMapHelperShim const *)this)->call((const BitFlags<11> &)a, (const BitFlags<11> &)b);
}

template class SparseMatchFinder<ArmorTemplateSet, BitFlags<11> >;

template <>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
class SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SparseMatchFinder.h
	class MapHelper
	{
	public:
		bool operator()(const BitFlags<17> &, const BitFlags<17> &) const;
	};
};

bool SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper::operator()(const BitFlags<17> &a, const BitFlags<17> &b) const
{
	return ((WeaponMapHelperShim const *)this)->call(a, b);
}
