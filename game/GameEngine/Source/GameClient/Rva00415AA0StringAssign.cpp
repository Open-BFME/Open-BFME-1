// Retail RVA 0x00415AA0, 46 bytes; VA 0x00815AA0 in the unpacked 1.03 image.
// TooltipUpgrade::upgradeImplementation (0x002D9510) reaches this through
// ILT 0x00025162 as its second target updater. The owner and method name remain
// address-derived: neither that caller nor the field offset proves an EA name.
#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" void _WriteBarrier();
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_WriteBarrier, _ReadWriteBarrier)

class Rva00415AA0 {
public:
  void assign(const StringBase<char> &value);

private:
  unsigned char m_unreconstructed000[0x2d8];
  StringBase<char> m_stringAt2D8;
};

/**
 * Clear or assign the string at retail receiver offset 0x2d8.
 *
 * The null-buffer guard uses StringBase's witnessed one-pointer representation;
 * getLength() supplies the canonical unsigned-short header field at buffer+4.
 * Both clear returns use the same zero-code marker so they merge, while the
 * different assignment marker preserves retail's clear-before-tail-jump layout.
 * The callees are StringBase<char>::releaseBuffer (RVA 0x00887940) and
 * StringBase<char>::set(const StringBase<char>&) (RVA 0x00887C90), not
 * UnicodeString.
 *
 * @ai-generated
 */
void Rva00415AA0::assign(const StringBase<char> &value) {
  if (*reinterpret_cast<const void *const *>(&value) == 0) {
    _WriteBarrier();
    m_stringAt2D8.clear();
    return;
  }
  if (value.getLength() == 0) {
    _WriteBarrier();
    m_stringAt2D8.clear();
    return;
  }
  _ReadWriteBarrier();
  m_stringAt2D8.set(value);
}
