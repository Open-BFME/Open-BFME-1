"""Pure source-provenance integration; no native compile/link or byte proof.

Use the real WWDownload registry source path and matched caller metadata, with a
synthetic COFF DIR32 site and reference retail operand. Only external tool
runs and reference inputs are substituted; row selection, site extraction,
classification, rewriting and artifact I/O execute the production code.
"""
import csv
import json
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import import_binding as ib  # noqa: E402


SOURCE = "game/Libraries/Source/WWVegas/WWDownload/registry.cpp"
OTHER = "game/Libraries/Source/WWVegas/WWLib/registry.cpp"
SPELLINGS = (SOURCE, "./" + SOURCE, SOURCE.replace("/", "\\"), ".\\" + SOURCE.replace("/", "\\"))
ROW = dict(name="?getUnsignedIntFromRegistry@@YA_NPAXV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@1AAI@Z",
           target_rva="0x00883D00", target_size="394", source=SOURCE, status="matched", notes="")
OPEN, QUERY = "__imp__RegOpenKeyExA@20", "__imp__RegQueryValueExA@24"
ALIAS = "__imp__RegistryOpenAlias@20"
SLOT_OPEN, SLOT_QUERY = 0xF59148, 0xF59154


class ReferenceImports(ib.Imports):
    """Deterministic reference inputs for two actual registry imports."""

    def __init__(self):
        self.slots = {SLOT_OPEN: ("advapi32.dll", "RegOpenKeyExA"),
                      SLOT_QUERY: ("advapi32.dll", "RegQueryValueExA")}
        self.by_import = {identity: slot for slot, identity in self.slots.items()}
        self.imp = {OPEN: self.slots[SLOT_OPEN], QUERY: self.slots[SLOT_QUERY]}
        self.canonical = {identity: {symbol} for symbol, identity in self.imp.items()}
        self.thunk = {symbol[len("__imp_"):]: identity for symbol, identity in self.imp.items()}
        self.foreign, self.oldnames = {}, {}


def write_coff(path, symbol):
    """The actual matched caller name owns one synthetic DIR32 import read."""
    size = int(ROW["target_size"])
    body = b"\xff\x15\0\0\0\0\xc3" + b"\x90" * (size - 7)
    raw, reloc = 60, 60 + size
    table = reloc + 10
    caller_name, cell_name = ROW["name"].encode("ascii") + b"\0", symbol.encode("ascii") + b"\0"
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, table, 2, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, size, raw, reloc, 0, 1, 0, 0x60000020)
    caller = struct.pack("<8sIhHBB", struct.pack("<II", 0, 4), 0, 1, 0x20, ib.EXTERNAL, 0)
    cell = struct.pack("<8sIhHBB", struct.pack("<II", 0, 4 + len(caller_name)), 0, 0, 0, ib.EXTERNAL, 0)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(header + section + body + struct.pack("<IIH", 2, 1, ib.DIR32)
                     + caller + cell + struct.pack("<I", 4 + len(caller_name) + len(cell_name))
                     + caller_name + cell_name)


def source_text(identifier):
    if identifier == "RegQueryValueExA":
        parameters = "void *, const char *, unsigned long *, unsigned long *, unsigned char *, unsigned long *"
        arguments = "0, 0, 0, 0, 0, 0"
    else:
        parameters = "void *, const char *, unsigned long, unsigned long, void **"
        arguments = "0, 0, 0, 0, 0"
    return (f'extern "C" __declspec(dllimport) long __stdcall {identifier}'
            f'({parameters});\n'
            f'long caller() {{ return {identifier}({arguments}); }}\n')


@pytest.fixture
def workflow(monkeypatch, tmp_path):
    monkeypatch.setattr(ib, "ROOT", tmp_path)
    monkeypatch.setattr(ib, "OUT", tmp_path / "build/import_binding")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "BUILD_DIR", tmp_path / "build/match")
    monkeypatch.setattr(build, "_FUNCTION_ROWS_CACHE", {})
    ledger = tmp_path / "targets/game/reverse/functions.csv"
    ledger.parent.mkdir(parents=True)
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    monkeypatch.setattr(ib, "LEDGER", ledger)
    with ledger.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(ROW))
        writer.writeheader()
        writer.writerow(ROW)
    corrections = ledger.with_name("name_corrections.json")
    corrections.write_text("[]\n", encoding="utf-8")
    monkeypatch.setattr(ib, "CORRECTIONS", corrections)
    source = tmp_path / SOURCE
    source.parent.mkdir(parents=True)
    source.write_text(source_text("RegistryOpenAlias"), encoding="ascii")
    other = tmp_path / OTHER
    other.parent.mkdir(parents=True)
    other.write_text("// distinct tracked registry TU\n", encoding="ascii")
    imports = ReferenceImports()
    found = {symbol: {("dir32", slot)} for symbol, slot in ((OPEN, SLOT_OPEN), (QUERY, SLOT_QUERY))}
    monkeypatch.setattr(ib, "load_context", lambda: (imports, found))

    def target_bytes(rva, size):
        assert (rva, size) == (int(ROW["target_rva"], 16), int(ROW["target_size"]))
        return b"\xff\x15" + struct.pack("<I", ib.BASE + SLOT_OPEN) + b"\xc3" + b"\x90" * (size - 7)

    monkeypatch.setattr(build, "read_target_bytes", target_bytes)
    compiled, gates, linked = [], [], []

    def compile_source(path, obj):
        assert path == tmp_path / SOURCE
        text = path.read_text(encoding="ascii")
        symbol = next(symbol for identifier, symbol in (("RegistryOpenAlias", ALIAS),
                      ("RegOpenKeyExA", OPEN), ("RegQueryValueExA", QUERY)) if ib.in_code(identifier, text))
        write_coff(obj, symbol)
        compiled.append(path.relative_to(tmp_path).as_posix())
        return True, "synthetic external compiler", None

    monkeypatch.setattr(build, "try_compile_source", compile_source)

    def byte_gate(command, **kwargs):
        assert command[1] == str(tmp_path / "tools/build.py")
        gates.append(command[-1])
        assert build.select_function_rows([command[-1]], build.load_function_rows()) == [ROW]
        compile_source(tmp_path / command[-1], build.obj_path(tmp_path / command[-1]))
        return SimpleNamespace(returncode=0, stdout="synthetic byte-gate result\n")

    monkeypatch.setattr(ib.subprocess, "run", byte_gate)

    def strict_link(obj, reference, work, label):
        work.mkdir(parents=True, exist_ok=True)
        undefined, _ = ib.object_facts(obj)
        linked.append((label, obj.read_bytes()))
        actual = [reference.imp[symbol] for symbol in sorted(undefined) if symbol in reference.imp]
        return bool(actual), obj.read_bytes().hex(), actual, []

    monkeypatch.setattr(ib, "strict_link", strict_link)
    return SimpleNamespace(root=tmp_path, source=source, imports=imports, found=found,
                           compiled=compiled, gates=gates, linked=linked)


@pytest.mark.parametrize("spelling", SPELLINGS)
def test_repair_keeps_identical_matched_witness_and_artifact_identity(workflow, spelling):
    assert ib.canonical_source(spelling) == SOURCE
    obj, error = ib.fresh_object(SOURCE)
    assert obj is not None, error
    rows = ib.tu_rows(SOURCE)
    assert rows == [ROW]
    assert ib.site_witnesses(obj, rows) == {ALIAS: {SLOT_OPEN}}
    assert ib.site_counts(obj, rows) == {ALIAS: 1}
    expected = json.loads(json.dumps(ib.plan(SOURCE, obj, workflow.imports, workflow.found)))
    before = obj.read_bytes()

    assert ib.cmd_apply(SimpleNamespace(source=spelling, model="")) == 0
    work = ib.work_dir(SOURCE)
    assert (work / "before.obj").read_bytes() == before
    assert json.loads((work / "plan.json").read_text(encoding="utf-8")) == expected
    assert ib.cmd_check(SimpleNamespace(source=spelling)) == 0
    receipt = json.loads((work / "receipt.json").read_text(encoding="utf-8"))
    assert receipt["source"] == SOURCE and receipt["steps"] == expected and receipt["pass"]
    assert receipt["before_strict_link"]["binding_problems"]
    assert workflow.gates == [SOURCE] and set(workflow.compiled) == {SOURCE}
    assert ib.tu_rows(receipt["source"]) == rows
    assert ib.site_witnesses(obj, rows) == {OPEN: {SLOT_OPEN}}
    assert ib.site_counts(obj, rows) == {OPEN: 1}
    assert workflow.linked[-1] == ("before", before)


@pytest.mark.parametrize("spelling", SPELLINGS)
def test_canonical_import_no_repair_control_stays_positive(workflow, spelling):
    workflow.source.write_text(source_text("RegOpenKeyExA"), encoding="ascii")
    original = workflow.source.read_bytes()
    assert ib.cmd_apply(SimpleNamespace(source=spelling, model="")) == 0
    work = ib.work_dir(SOURCE)
    assert not (work / "plan.json").exists()
    before = (work / "before.obj").read_bytes()
    assert ib.cmd_check(SimpleNamespace(source=spelling)) == 0
    receipt = json.loads((work / "receipt.json").read_text(encoding="utf-8"))
    assert receipt["source"] == SOURCE and receipt["steps"] == [] and receipt["pass"]
    assert receipt["before_strict_link"]["binding_problems"] == []
    assert workflow.source.read_bytes() == original
    assert workflow.linked[-1] == ("before", before)
    assert workflow.gates == [SOURCE]


@pytest.mark.parametrize("spelling", SPELLINGS)
def test_wrong_slot_is_rejected_for_every_source_spelling(workflow, spelling):
    workflow.source.write_text(source_text("RegQueryValueExA"), encoding="ascii")
    assert ib.cmd_check(SimpleNamespace(source=spelling)) == 1
    receipt = json.loads((ib.work_dir(SOURCE) / "receipt.json").read_text(encoding="utf-8"))
    assert receipt["source"] == SOURCE and not receipt["pass"]
    assert any(QUERY in failure and "wrong-slot" in failure for failure in receipt["failures"])
    assert receipt["strict_link"]["ok"]  # the local DIR32 witness supplies the negative
    assert ib.site_witnesses(build.obj_path(workflow.root / SOURCE), ib.tu_rows(SOURCE)) == {QUERY: {SLOT_OPEN}}
    assert workflow.gates == [SOURCE]


def test_normalization_keeps_other_compiler_source_identity_distinct(workflow):
    assert ib.canonical_source("./" + OTHER) == OTHER
    assert ib.canonical_source(OTHER) != ib.canonical_source(SOURCE)
    assert ib.work_dir(OTHER) != ib.work_dir(SOURCE)


@pytest.mark.parametrize("spelling", SPELLINGS)
def test_alias_without_its_own_matched_row_is_still_refused(workflow, spelling):
    foreign_row = {**ROW, "source": OTHER}
    with build.FUNCTIONS.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(ROW))
        writer.writeheader()
        writer.writerow(foreign_row)
    original = workflow.source.read_bytes()
    assert ib.tu_rows(SOURCE) == [] and ib.tu_rows(OTHER) == [foreign_row]
    assert ib.cmd_apply(SimpleNamespace(source=spelling, model="")) == 1
    assert workflow.source.read_bytes() == original
    work = ib.work_dir(SOURCE)
    assert "invented" in (work / "refused.txt").read_text(encoding="utf-8")
    assert not (work / "plan.json").exists()
    assert workflow.gates == workflow.linked == []


@pytest.mark.parametrize("command", ("apply", "check"))
@pytest.mark.parametrize("spelling", ("../outside.cpp", "..\\outside.cpp", "absolute"))
def test_outside_checkout_is_refused_before_context_or_artifact_io(workflow, monkeypatch, capsys, command, spelling):
    def unexpected_context():
        raise AssertionError("outside source reached context loading")

    monkeypatch.setattr(ib, "load_context", unexpected_context)
    if spelling == "absolute":
        spelling = str(workflow.root.parent / "outside.cpp")
    assert ib.main([command, spelling]) == 1
    assert "outside this checkout" in capsys.readouterr().out
    assert not ib.OUT.exists()
    assert workflow.compiled == workflow.gates == workflow.linked == []
