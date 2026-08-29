// Open-BFME: two-argument member overload reconstructed from retail RVA
// 0x002F73B0.  ScriptActions vtable and load-postprocess xrefs prove that this
// virtual reapplies a saved human-impassable-area state through the three-
// argument target at 0x002F7340.  The original method spelling is not
// recovered, so this translation-unit-local declaration remains address-derived.

class AsciiString;

class Rva002F73B0Owner
{
public:
    void applyAreaState(const AsciiString &areaName, bool blocked, bool recordState);
    virtual void applyAreaState(const AsciiString &areaName, bool blocked);
};

void Rva002F73B0Owner::applyAreaState(const AsciiString &areaName, bool blocked)
{
    applyAreaState(areaName, blocked, true);
}
