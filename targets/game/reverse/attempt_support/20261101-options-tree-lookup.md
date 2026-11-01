# Options LOD getters: bind the real tree lookup

Queue rank 68, claim 0xF3CBE6D5. Three existing caller rows remain unchanged:
getFixedStaticGameDetail 0x00090A00/106, getStaticGameDetail 0x00090970/106,
rva00090900IdealStaticGameDetail 0x00090900/87. No new name or extent claim.

## Repair and independent BFME 1 evidence

All three retail callers reach ILT 0x0000AEAC -> 0x00080600. The existing
194-byte RvaTreeFindAsciiString.cpp row owns that lookup under the
Rva00080600Value/KeyOfValue tree instantiation. Replace the pin-only
CustomPreferenceMapShim::find reference with the real tree's public find.
A static forceinline throw() helper preserves the old call site's exception
contract. It returns the iterator's node, preserving the existing node view
and its value at +0x14. The helper emits no out-of-line body.

Use the provider's existing asciistring_downloadmanager header and less
specialization as well: merely spelling the real tree with the old string
header byte-matched the caller but emitted a WRONG 83-byte lookup. The final
three objects each emit the same 194-byte lookup, digest eeafa8490248;
link_census.RetailTruth judges each retail including relocations. None
references CustomPreferenceMapShim::find. Inline the existing AsciiString
destructor delegation to releaseBuffer so this header selection retains the
callers' original cleanup target. No shared header or pin was edited.

Normal scoped build of three callers plus provider: 28/28 rows, 3 literals,
38 empty strings, 5 DIR32 references pass. A private /showIncludes compile
confirmed asciistring_downloadmanager/Common/AsciiString.h, ascii_string.h,
and string_base.h. All mapped include directories exist. The toolchain is
MSVC 7.1 3077 with each source's existing /DNDEBUG /DWIN32 /D_WINDOWS /MD
/EHsc and STLport; the only flag addition is the existing provider header path.

## Failed controls and limits

A direct _M_find call fails C2248 (private). A declaration-only explicit
specialization with or without __declspec(nothrow), called via public find,
hits C1001 in _tree.h:459, compiler Utc/src/P2/main.c:148. Removing that
specialization avoids the compiler crash; the normal template instantiation
and static throw() helper suffice. Do not add a special compiler or alias.

The available linking census e9a5ae5b4c is stale and current selection has
many missing objects; current linked-byte total remains UNKNOWN. This repair
removes the specific unresolved shim in these three objects and verifies their
provider copies, not whole-program linking. OptionsMenu.cpp retains other
shim users outside this queue packet; no broad rename was attempted.

## BFME 2 reference

Reviewed /home/yannick/projects/Open-BFME-2 at
2e97f871794a7b0cc6463976dd3b6fc3c1d780f8, particularly
Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/
OptionPreferences_getFirewallPortAllocationDelta.cpp and
QuickMatchPreferences_getMaxPing.cpp, plus history 3e15e001ba and
88e44dfcc2. These support using an actual STLport preference map instead of
a private lookup shim; BFME 2 layouts and addresses were not imported.
The address-specific key-only tree identity, offset +0x14 view, helper shape
and verified 194-byte copy all come from BFME 1, not donor naming.
