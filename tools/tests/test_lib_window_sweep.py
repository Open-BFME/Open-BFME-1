"""The parts of the library sweep that decide identity, not just bytes.

A lib row is proved by a MASKED byte comparison, so two different functions
that differ only inside their relocation slots are indistinguishable to the
gate. Everything here guards the decisions the gate cannot check: which of
several identical spans gets which symbol, and what name the row carries so
check_csv can still tell one claim from another.
"""
import sys
import types
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import lib_window_sweep as S

REL32 = S.REL32
DIR32 = 0x0006


def image_of(mapping, base=0x400000):
    """An `image(rva, n)` over a flat dict of {rva: bytes} chunks."""
    blob = bytearray(0x1000)
    for rva, data in mapping.items():
        blob[rva - base:rva - base + len(data)] = data

    def image(rva, count):
        start = rva - base
        if start < 0:
            return b""
        return bytes(blob[start:start + count])
    return image


def instance(tag="d3dx9", member="a.obj", symbol="?f@@YAXXZ", span=b"", relocs=()):
    return S.Instance(tag, member, symbol, span, list(relocs), span, list(relocs), 0)


class MaskedComparison(unittest.TestCase):
    def test_a_relocation_slot_may_hold_anything(self):
        span = b"\xb8\x00\x00\x00\x00\xc3"
        self.assertTrue(S.masked_eq(b"\xb8\xef\xbe\xad\xde\xc3", span, [(1, DIR32, "x")]))

    def test_a_difference_outside_a_slot_is_a_mismatch(self):
        span = b"\xb8\x00\x00\x00\x00\xc3"
        self.assertFalse(S.masked_eq(b"\xb9\xef\xbe\xad\xde\xc3", span, [(1, DIR32, "x")]))

    def test_a_body_shorter_than_the_span_never_matches(self):
        self.assertFalse(S.masked_eq(b"\x90\x90", b"\x90\x90\x90", []))

    def test_upto_compares_only_the_requested_prefix(self):
        span = b"\x90\x90\xcc\xcc"
        self.assertTrue(S.masked_eq(b"\x90\x90\x00\x00", span, [], upto=2))


class Needle(unittest.TestCase):
    def test_the_search_key_is_the_longest_relocation_free_run(self):
        span = bytes(range(40))
        self.assertEqual(S.longest_needle(span, [(4, REL32, "x"), (30, REL32, "y")], 8),
                         (8, 30))

    def test_a_span_with_no_long_enough_run_has_no_needle(self):
        span = bytes(range(16))
        self.assertIsNone(S.longest_needle(span, [(4, REL32, "x"), (10, REL32, "y")], 8))


class ConcreteBytes(unittest.TestCase):
    def test_it_counts_what_build_py_would_leave_outside_the_mask(self):
        # build.py clips a slot at the row's end the same way; a 4-byte reloc at
        # offset 18 of a 20-byte row covers 2 bytes, not 4.
        self.assertEqual(S.concrete_bytes([(0, REL32, "x"), (18, DIR32, "y")], 20), 14)


class CalleeTargets(unittest.TestCase):
    """Retail has the relocation slots RESOLVED; the archive says what should be there."""

    CALLEE = b"\x55\x8b\xec\x5d\xc3\x90\x90\x90"

    def setUp(self):
        self.caller = instance(span=b"\xe8\x00\x00\x00\x00\xc3",
                               relocs=[(1, REL32, "?callee@@YAXXZ")])
        self.callees = {("d3dx9", "?callee@@YAXXZ"): [
            instance(symbol="?callee@@YAXXZ", span=self.CALLEE)]}
        self.text = (0x400000, 0x401000)

    def verdict(self, mapping, size=6):
        return S.callee_verdict(0x400100, size, self.caller, self.callees,
                                image_of(mapping), self.text)

    def call_to(self, destination):
        displacement = (destination - (0x400100 + 5)).to_bytes(4, "little", signed=True)
        return b"\xe8" + displacement + b"\xc3"

    def test_the_callee_being_where_the_call_points_corroborates(self):
        ok, bad = self.verdict({0x400100: self.call_to(0x400200), 0x400200: self.CALLEE})
        self.assertEqual((ok, bad), (1, []))

    def test_a_call_to_something_else_contradicts_the_pairing(self):
        ok, bad = self.verdict({0x400100: self.call_to(0x400200),
                                0x400200: b"\x33\xc0\xc3\x90\x90\x90\x90\x90"})
        self.assertEqual(ok, 0)
        self.assertEqual([(offset, name) for offset, name, _ in bad],
                         [(1, "?callee@@YAXXZ")])

    def test_a_jmp_veneer_is_followed_one_hop(self):
        veneer = b"\xe9" + (0x400300 - 0x400205).to_bytes(4, "little", signed=True)
        ok, bad = self.verdict({0x400100: self.call_to(0x400200), 0x400200: veneer,
                                0x400300: self.CALLEE})
        self.assertEqual((ok, bad), (1, []))

    def test_an_import_stub_is_evidence_about_the_link_not_the_placement(self):
        # `jmp dword ptr [__imp__x]` means the linker took the DLL's copy and
        # never pulled the archive member in. Neither corroborates nor refutes.
        ok, bad = self.verdict({0x400100: self.call_to(0x400200),
                                0x400200: b"\xff\x25\x00\x00\x00\x01"})
        self.assertEqual((ok, bad), (0, []))

    def test_a_call_leaving_text_contradicts(self):
        ok, bad = self.verdict({0x400100: self.call_to(0x4FF000)})
        self.assertEqual(ok, 0)
        self.assertEqual(len(bad), 1)

    def test_a_callee_the_archive_does_not_define_is_silent(self):
        caller = instance(span=b"\xe8\x00\x00\x00\x00\xc3",
                          relocs=[(1, REL32, "_imported@4")])
        ok, bad = S.callee_verdict(0x400100, 6, caller, self.callees,
                                   image_of({0x400100: self.call_to(0x400200)}), self.text)
        self.assertEqual((ok, bad), (0, []))

    def test_a_slot_past_the_claimed_extent_is_not_read(self):
        ok, bad = self.verdict({0x400100: self.call_to(0x400200)}, size=4)
        self.assertEqual((ok, bad), (0, []))


class Dir32Bases(unittest.TestCase):
    """A DIR32 says where a named symbol lives, and a symbol has one address.

    build.py's verify_dir32_consistency runs this arithmetic over the whole
    ledger, but only in the FULL gate; a ledger-only commit gets a scoped build
    from both hooks and never reaches it. The sweep has to apply the same test
    at placement time or it lands rows that check will blame afterwards.
    """

    SYM = "??_7CVSProgram@D3DXShader@@6B@"

    def caller(self, addend, member="cvsprogram.obj"):
        span = b"\xb8" + addend.to_bytes(4, "little") + b"\xc3"
        return instance(member=member, span=span, relocs=[(1, DIR32, self.SYM)])

    def retail(self, final):
        return image_of({0x400100: b"\xb8" + final.to_bytes(4, "little") + b"\xc3"})

    def test_a_base_matching_the_anchor_corroborates(self):
        ok, bad = S.dir32_verdict(0x400100, 6, self.caller(0),
                                  self.retail(0x1158598), {self.SYM: {0x1158598}})
        self.assertEqual((ok, bad), (1, []))

    def test_a_base_the_ledger_pins_elsewhere_contradicts(self):
        ok, bad = S.dir32_verdict(0x400100, 6, self.caller(0),
                                  self.retail(0x1158808), {self.SYM: {0x1158598}})
        self.assertEqual(ok, 0)
        self.assertEqual([(offset, name) for offset, name, _ in bad], [(1, self.SYM)])

    def test_the_addend_is_subtracted_before_comparing(self):
        ok, bad = S.dir32_verdict(0x400100, 6, self.caller(0x20),
                                  self.retail(0x11585B8), {self.SYM: {0x1158598}})
        self.assertEqual((ok, bad), (1, []))

    def test_a_symbol_with_no_anchor_is_silent(self):
        ok, bad = S.dir32_verdict(0x400100, 6, self.caller(0), self.retail(0x999), {})
        self.assertEqual((ok, bad), (0, []))

    def test_a_symbol_the_ledger_already_shows_at_two_bases_is_silent(self):
        # Already known-multi (whitelisted, or a static this key failed to
        # scope): it decides nothing, so it must not decide against us either.
        ok, bad = S.dir32_verdict(0x400100, 6, self.caller(0), self.retail(0x1),
                                  {self.SYM: {0x1158598, 0x1158808}})
        self.assertEqual((ok, bad), (0, []))

    def test_a_slot_past_the_claimed_extent_is_not_read(self):
        ok, bad = S.dir32_verdict(0x400100, 4, self.caller(0),
                                  self.retail(0x1158808), {self.SYM: {0x1158598}})
        self.assertEqual((ok, bad), (0, []))

    def test_a_string_literal_slot_is_not_an_identity_witness(self):
        caller = instance(span=b"\xb8\x00\x00\x00\x00\xc3",
                          relocs=[(1, DIR32, "??_C@_05ABCDE@hello@")])
        ok, bad = S.dir32_verdict(0x400100, 6, caller, self.retail(0x999),
                                  {"??_C@_05ABCDE@hello@": {0x1}})
        self.assertEqual((ok, bad), (0, []))

    def test_a_tu_local_static_is_keyed_by_member_not_by_name(self):
        # __NEG_ is IMAGE_SYM_CLASS_STATIC in BOTH d3dxmathsse.obj and
        # d3dxmathsse2.obj. One name, two objects, two legitimate addresses:
        # keyed by name alone this reads as a contradiction and retracts ten
        # byte-verified placements.
        caller = instance(member="d3dxmathsse2.obj", span=b"\xb8\x00\x00\x00\x00\xc3",
                          relocs=[(1, DIR32, "__NEG_")])
        anchors = {("d3dxmathsse.obj", "__NEG_"): {0x12E4350}}
        statics = {("d3dx9", "d3dxmathsse.obj"): {"__NEG_"},
                   ("d3dx9", "d3dxmathsse2.obj"): {"__NEG_"}}
        ok, bad = S.dir32_verdict(0x400100, 6, caller, self.retail(0x12E4580),
                                  anchors, statics)
        self.assertEqual((ok, bad), (0, []))


class GhidraWitness(unittest.TestCase):
    """Ghidra has never seen these archives, so a name it recovers is independent."""

    PAIR = ["__RTC_Initialize", "__RTC_Terminate"]

    def test_a_ghidra_name_matching_one_candidate_settles_the_class(self):
        self.assertEqual(
            S.witnessed_candidates(0x9F7F0A, self.PAIR, {0x9F7F0A: "__RTC_Initialize"}),
            ["__RTC_Initialize"])

    def test_a_ghidra_name_matching_none_of_them_decides_nothing(self):
        self.assertEqual(
            S.witnessed_candidates(0x9F7F0A, self.PAIR, {0x9F7F0A: "_something_else"}),
            self.PAIR)

    def test_an_unnamed_address_decides_nothing(self):
        self.assertEqual(S.witnessed_candidates(0x9F7F0A, self.PAIR, {}), self.PAIR)

    def test_the_real_table_never_offers_a_FUN_placeholder_as_a_witness(self):
        self.assertFalse([n for n in S.ghidra_names().values() if n.startswith("FUN_")])


class GateAgreement(unittest.TestCase):
    """The sweep must refuse what verify_dir32_consistency will refuse.

    That check keys by symbol NAME, so a static defined in two objects reads to
    it as one symbol at two addresses. The sweep scopes statics by member and so
    would happily emit the pair -- and the FULL gate, which a ledger-only commit
    never runs, would then fail for everyone.
    """

    # A name of this shape is deliberately not in the real whitelist: the point
    # is the rule, and pinning the test to a listed symbol makes it pass for the
    # wrong reason the moment somebody lists or unlists it.
    STATIC = "__test_only_tu_local_"

    def test_a_static_two_members_define_is_blamed_because_the_gate_blames_it(self):
        bases = {("d3dxmathsse.obj", self.STATIC): {0x12E4350},
                 ("d3dxmathsse2.obj", self.STATIC): {0x12E4580}}
        self.assertEqual(S.gate_disagreements(bases, {}), set(bases))

    def test_one_member_resolving_one_static_once_is_left_alone(self):
        bases = {("d3dxmathsse.obj", self.STATIC): {0x12E4350}}
        self.assertEqual(S.gate_disagreements(bases, {}), set())

    def test_an_anchor_counts_toward_the_gate_view_too(self):
        bases = {("d3dxmathsse2.obj", self.STATIC): {0x12E4580}}
        anchors = {("d3dxmathsse.obj", self.STATIC): {0x12E4350}}
        self.assertEqual(S.gate_disagreements(bases, anchors), set(bases))

    def test_a_symbol_already_on_the_gate_whitelist_is_not_blamed_twice(self):
        listed = next(iter(
            line.strip() for line in S.DIR32_WHITELIST.read_text().splitlines()
            if line.strip() and not line.startswith("#")))
        bases = {("a.obj", listed): {1}, ("b.obj", listed): {2}}
        self.assertEqual(S.gate_disagreements(bases, {}), set())


class RowNames(unittest.TestCase):
    """check_csv rejects one name at two RVAs, and a twin is the common case here."""

    SOURCE = "inputs/vendor/d3dx9/d3dx9.lib"
    TWIN = "?build_ycc_rgb_table@D3DX@@YGXPAUjpeg_decompress_struct@1@@Z"

    def build(self, rows, held=()):
        ledger = types.SimpleNamespace(names=set(held))
        report = types.SimpleNamespace(warnings=[], warn=lambda t: report.warnings.append(t))
        return S.row_names(rows, ledger, {self.SOURCE}, report) + (report,)

    def row(self, symbol, member, rva, candidates=None):
        return {"symbol": symbol, "member": member, "rva": rva, "tag": "d3dx9",
                "owner": "d3dx9", "source": self.SOURCE,
                "candidates": list(candidates) if candidates else [symbol]}

    def test_a_symbol_claimed_once_keeps_its_real_mangled_name(self):
        named, refused, _ = self.build([self.row(self.TWIN, "obj\\i386\\jdcolor.obj", 0xAC5BE0)])
        self.assertEqual(refused, [])
        self.assertEqual(named[0]["name"], self.TWIN)
        self.assertNotIn("object-symbol=", named[0]["notes"])

    def test_two_members_defining_one_symbol_both_get_a_unique_name(self):
        named, refused, _ = self.build([
            self.row(self.TWIN, "obj\\i386\\jdcolor.obj", 0xAC5BE0),
            self.row(self.TWIN, "obj\\i386\\jdmerge.obj", 0xAC7430)])
        self.assertEqual(refused, [])
        self.assertEqual(len({row["name"] for row in named}), 2)
        for row in named:
            self.assertNotEqual(row["name"], self.TWIN)
            self.assertIn(f"object-symbol={self.TWIN}", row["notes"])

    def test_a_symbol_the_ledger_already_names_yields_an_alias(self):
        named, _, _ = self.build([self.row(self.TWIN, "obj\\i386\\jdmerge.obj", 0xAC7430)],
                                 held={self.TWIN})
        self.assertNotEqual(named[0]["name"], self.TWIN)
        self.assertIn(f"object-symbol={self.TWIN}", named[0]["notes"])

    def test_a_row_two_symbols_could_own_carries_neither_name(self):
        # ?MatchIFCOND and ?MatchBREAK_COND are 532 masked-identical bytes in one
        # member. Archive order picks one; nothing in the image seconds it. The
        # name column is what every other tool resolves an identity through, so
        # it must assert nothing the evidence does not pin.
        pair = ["?MatchBREAK_COND@CShaderProgram@D3DXShader@@IAEJXZ",
                "?MatchIFCOND@CShaderProgram@D3DXShader@@IAEJXZ"]
        named, refused, _ = self.build([
            self.row(pair[1], "obj\\i386\\cshaderprogram.obj", 0xAB2F10, pair),
            self.row(pair[0], "obj\\i386\\cshaderprogram.obj", 0xAB3D6F, pair)])
        self.assertEqual(refused, [])
        self.assertEqual(len({row["name"] for row in named}), 2)
        for row in named:
            self.assertNotIn(row["name"], pair)
            self.assertIn(f"object-symbol={row['symbol']}", row["notes"])
            self.assertIn("lib-twin=2", row["notes"])
        # a gen- marker would move these bytes into progress.py's generated lane
        self.assertNotIn("gen-", named[0]["notes"])

    def test_one_symbol_from_two_members_still_keeps_the_real_name(self):
        # The member is ambiguous, the FUNCTION is not: both candidates are the
        # same symbol, so `<symbol>$<member>` still says something true.
        named, _, _ = self.build([
            self.row(self.TWIN, "obj\\i386\\jdcolor.obj", 0xAC5BE0, [self.TWIN]),
            self.row(self.TWIN, "obj\\i386\\jdmerge.obj", 0xAC7430, [self.TWIN])])
        for row in named:
            self.assertTrue(row["name"].startswith(self.TWIN + "$"))

    def test_an_untracked_archive_is_refused_rather_than_git_added(self):
        row = self.row(self.TWIN, "obj\\i386\\jdcolor.obj", 0xAC5BE0)
        row["source"] = "inputs/toolchains/vs2003/nowhere.lib"
        named, refused, report = self.build([row])
        self.assertEqual(named, [])
        self.assertEqual(len(refused), 1)
        self.assertTrue(report.warnings)

    def test_a_csv_hostile_symbol_is_refused_rather_than_corrupting_the_ledger(self):
        named, refused, _ = self.build([self.row("?f,g@@YAXXZ", "obj\\i386\\x.obj", 0xA00000)])
        self.assertEqual(named, [])
        self.assertEqual(len(refused), 1)


class Windows(unittest.TestCase):
    def test_the_four_library_runs_tile_the_territory_without_overlapping(self):
        runs = sorted(S.WINDOWS.values())
        self.assertEqual(runs[0][0], S.WIN_LO)
        self.assertEqual(runs[-1][1], S.WIN_HI)
        for first, second in zip(runs, runs[1:]):
            self.assertEqual(first[1], second[0])

    def test_every_emittable_tag_names_a_window_that_exists(self):
        for _source, key in S.LEDGER_SOURCE.values():
            self.assertIn(key, S.WINDOWS)


if __name__ == "__main__":
    unittest.main()
