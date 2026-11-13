"""Read-only proof checks; pass independently compiled, same-source-path COFF inputs.

Run through the experiment launcher before project imports. No linked image runs.
"""
import argparse
import collections
import csv
import hashlib
import json
import struct
import sys
import unittest
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[5]
sys.path.insert(0, str(ROOT / "tools"))
import build
import link_census
import reloc_ledger

TARGET = "?doXfer@AICommandParmsStorage@@QAEXPAVXfer@@@Z"
HELPERS = {
    "?getName@CommandButton@@QBEABVAsciiString@@XZ",
    "??2Path@@SAPAXIW4PathMagicEnum@0@@Z",
    "??3Path@@SAXPAXW4PathMagicEnum@0@@Z",
    "?getTriggerName@PolygonTrigger@@QBE?AVAsciiString@@XZ",
}


def coff_graph(path):
    data = path.read_bytes()
    build.validate_coff(data)
    sections, symbols = reloc_ledger.parse_coff(data)
    _, _, _, pointer, count, _, _ = struct.unpack_from("<HHIIIHH", data)
    aux = {}
    index = 0
    while index < count:
        record = pointer + 18 * index
        extra = data[record + 17]
        aux[index] = data[record + 18:record + 18 * (extra + 1)]
        index += extra + 1
    section_aux = {}
    for index, symbol in symbols.items():
        if symbol["storage"] == 3 and symbol["section"] > 0 and aux[index] and symbol["value"] == 0:
            section = sections[symbol["section"] - 1]
            if symbol["name"] == section["name"]:
                section_aux[symbol["section"]] = struct.unpack("<IHHIHBBH", aux[index])

    def section_key(number):
        sec = sections[number - 1]
        defined = sorted(s["name"] for s in symbols.values()
                         if s["section"] == number and s["storage"] == 2)
        if defined:
            return (sec["name"], tuple(defined))
        record = section_aux.get(number)
        if record and record[5] == 5:
            return (sec["name"], section_key(record[4]))
        local = sorted(s["name"] for s in symbols.values()
                       if s["section"] == number and s["storage"] == 3
                       and s["name"] != sec["name"])
        return (sec["name"], tuple(local))

    def symbol_key(index):
        s = symbols[index]
        sec = section_key(s["section"]) if s["section"] > 0 else s["section"]
        # Compiler-local EH label ordinals move when an earlier function disappears.
        name = "$local" if s["storage"] == 3 and s["name"].startswith("$") else s["name"]
        return (name, s["value"], sec, s["type"], s["storage"])

    records = []
    sxdata = []
    sxdata_metadata = []
    for sec in sections:
        if sec["name"].startswith(".debug"):
            continue
        body = sec["body"]
        if sec["name"] == ".sxdata":
            assert body is not None and len(body) % 4 == 0
            sxdata.extend(symbol_key(i[0]) for i in struct.iter_unpack("<I", body))
            record = section_aux[sec["number"]]
            assert record[3] == zlib.crc32(body, 0xFFFFFFFF) ^ 0xFFFFFFFF
            sxdata_metadata.append((sec["flags"], record))
            continue
        members = []
        for index, s in symbols.items():
            if s["section"] != sec["number"]:
                continue
            extra = aux[index]
            if extra:
                assert s["storage"] == 3 and s["name"] == sec["name"], (s, extra.hex())
                length, nr, nl, checksum, associated, selection, reserved, high = struct.unpack("<IHHIHBBH", extra)
                associated = section_key(associated) if selection == 5 else associated
                extra = (length, nr, nl, checksum, associated, selection, reserved, high)
            else:
                extra = None
            members.append((symbol_key(index), extra))
        record = {"key": section_key(sec["number"]), "size": sec["size"], "flags": sec["flags"],
                  "body": body.hex() if body is not None else None,
                  "relocations": [(w, k, symbol_key(i)) for w, i, k in sec["relocs"]],
                  "symbols": sorted(members, key=repr)}
        records.append(record)
    undefined = []
    for index, s in symbols.items():
        if s["section"] > 0:
            continue
        extra = aux[index]
        if s["storage"] == 105:
            assert len(extra) == 18
            target, characteristic = struct.unpack_from("<II", extra)
            extra = (symbol_key(target), characteristic, extra[8:].hex())
        elif s["storage"] == 103:
            extra = extra.hex()
        else:
            assert not extra, (s, extra.hex())
            extra = None
        undefined.append((symbol_key(index), extra))
    return {"sha256": hashlib.sha256(data).hexdigest(), "records": records,
            "sxdata": sxdata, "sxdata_metadata": sxdata_metadata, "undefined_common_weak": undefined,
            "sections": sections, "symbols": symbols}


def encoded(value):
    return json.dumps(value, sort_keys=True)


def delta(before, after):
    b = collections.Counter(map(encoded, before))
    a = collections.Counter(map(encoded, after))
    return [json.loads(x) for x in (b - a).elements()], [json.loads(x) for x in (a - b).elements()]


class AIStatesRetirement(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.before = coff_graph(ARGS.before)
        cls.after = coff_graph(ARGS.after)
        cls.provider = coff_graph(ARGS.provider)
        cls.consumer = coff_graph(ARGS.consumer)

    def test_only_wrong_body_exclusive_helpers_and_associated_eh_removed(self):
        removed, added = delta(self.before["records"], self.after["records"])
        self.assertEqual(added, [])
        self.assertEqual(len(removed), 7)
        root_keys = {encoded(x["key"]): x for x in removed if x["key"][0] == ".text"}
        expected = {TARGET, *HELPERS}
        self.assertEqual({x["key"][1][0] for x in root_keys.values()}, expected)
        for record in removed:
            if record["key"][0] != ".text":
                self.assertIn(record["key"][0], (".text$x", ".xdata$x"))
                self.assertEqual(record["key"][1], [".text", [TARGET]])
        self.assertEqual(next(x["size"] for x in removed if x["key"] == [".text", [TARGET]]), 968)
        self.report_removed = removed

    def test_safeseh_table_loses_only_wrong_handler(self):
        removed, added = delta(self.before["sxdata"], self.after["sxdata"])
        self.assertEqual(added, [])
        self.assertEqual(len(removed), 1)
        self.assertEqual(removed[0][0], "__ehhandler$" + TARGET)
        self.assertEqual(len(self.before["sxdata_metadata"]), 1)
        self.assertEqual(len(self.after["sxdata_metadata"]), 1)
        before_flags, before_aux = self.before["sxdata_metadata"][0]
        after_flags, after_aux = self.after["sxdata_metadata"][0]
        self.assertEqual(before_flags, after_flags)
        self.assertEqual(before_aux[0] - 4, after_aux[0])
        self.assertEqual(before_aux[1:3], after_aux[1:3])
        self.assertEqual(before_aux[4:], after_aux[4:])

    def test_no_new_undefined_common_or_weak_symbols(self):
        _, added = delta(self.before["undefined_common_weak"], self.after["undefined_common_weak"])
        self.assertEqual(added, [])

    def test_no_retained_local_relocations_use_removed_helper_or_wrong_body(self):
        for record in self.after["records"]:
            for _, _, target in record["relocations"]:
                self.assertNotIn(target[0], HELPERS | {TARGET})

    def test_canonical_native_identity_and_real_consumer_route(self):
        provider_path = ARGS.provider
        body, relocs = build.read_object_symbol_bytes(provider_path, TARGET, require_code=True)
        self.assertEqual(len(body), 805)
        self.assertEqual(len(relocs), 21)
        self.assertEqual(body[-3:], b"\xc2\x04\x00")
        image = reloc_ledger.Image()
        self.assertEqual(image.read(image.base + 0x2DEC, 1), b"\xe9")
        jump = image.read(image.base + 0x2DED, 4)
        self.assertEqual(0x2DEC + 5 + struct.unpack("<i", jump)[0], 0x187860)
        names = {s["name"] for s in self.consumer["symbols"].values() if s["section"] == 0}
        self.assertIn(TARGET, names)
        sites = [(sec, w, k) for sec in self.consumer["sections"] for w, i, k in sec["relocs"]
                 if self.consumer["symbols"][i]["name"] == TARGET]
        self.assertEqual(len(sites), 2)
        self.assertTrue(all(k == 0x14 for _, _, k in sites))

    def test_current_normal_provider_consumer_and_after_objects_match_private_graphs(self):
        cases = (
            ("game/GameEngine/Source/GameLogic/AI/AIStates.cpp", self.after),
            ("game/GameEngine/Source/GameLogic/AI/AICommandParmsStorageXfer.cpp", self.provider),
            ("game/GameEngine/Source/Common/S3VersionBlocks.cpp", self.consumer),
        )
        for source, private in cases:
            with self.subTest(source=source):
                obj = build.row_object({"source": source, "notes": ""})
                self.assertTrue(link_census.object_current(ROOT / source, obj))
                current = coff_graph(obj)
                for key in ("records", "sxdata", "sxdata_metadata", "undefined_common_weak"):
                    self.assertEqual(current[key], private[key])

    def test_no_ledger_row_owned_by_aistates_was_retired(self):
        before_names = {s["name"] for s in self.before["symbols"].values() if s["section"] > 0}
        after_names = {s["name"] for s in self.after["symbols"].values() if s["section"] > 0}
        with (ROOT / "targets/game/reverse/functions.csv").open(newline="") as handle:
            rows = [r for r in csv.DictReader(handle)
                    if r["source"] == "game/GameEngine/Source/GameLogic/AI/AIStates.cpp" and r["status"] == "matched"]
        self.assertEqual(len(rows), 103)
        self.assertTrue(all(build.ledger_object_symbol(r) in before_names & after_names for r in rows))


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ("before", "after", "provider", "consumer"):
        parser.add_argument("--" + name, type=Path, required=True)
    parser.add_argument("--receipt", type=Path, required=True)
    ARGS = parser.parse_args()
    suite = unittest.defaultTestLoader.loadTestsFromTestCase(AIStatesRetirement)
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    before = coff_graph(ARGS.before)
    after = coff_graph(ARGS.after)
    removed, added = delta(before["records"], after["records"])
    ARGS.receipt.write_text(json.dumps({
        "passed": result.wasSuccessful(), "tests": result.testsRun,
        "before_sha256": before["sha256"], "after_sha256": after["sha256"],
        "retained_runtime_sections": len(after["records"]),
        "removed_sections": removed, "added_sections": added,
        "safeseh_delta": delta(before["sxdata"], after["sxdata"]),
        "undefined_common_weak_delta": delta(before["undefined_common_weak"], after["undefined_common_weak"]),
    }, indent=2))
    raise SystemExit(0 if result.wasSuccessful() else 1)
