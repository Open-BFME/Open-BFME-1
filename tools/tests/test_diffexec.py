"""Differential execution must see the wrong-code commits the byte gate missed.

Positive controls are the 2026-10 gate exploits rebuilt as real COFF objects:
wrong callee via a symbols.csv pin, wrong global (DIR32 operands are copied
from retail by the byte gate), swapped switch case, truncated string literal.
Each has a negative control -- the correct version of the same fixture shows
no divergence. The retail image is an in-memory Image; objects go through the
repo's own COFF reader (build.read_object_symbol_bytes).
"""
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

diffexec = pytest.importorskip("diffexec")
pytest.importorskip("unicorn")
import build  # noqa: E402


@pytest.fixture(autouse=True, scope="module")
def quiet_faulthandler():
    # Unicorn's TCG probes memory on Windows and takes (and handles) a
    # first-chance access violation per engine; pytest's faulthandler prints
    # each as a "fatal exception". Mute it for this module only.
    import faulthandler
    was = faulthandler.is_enabled()
    faulthandler.disable()
    yield
    if was:
        faulthandler.enable()

TEXT = 0x60500020
RDATA = 0x40301040
BASE = 0x400000


def coff(sections, symbols):
    """sections: [(name, characteristics, data, [(offset, symbol_index, type)])]
    symbols: [(name, value, section, type, storage, aux)]."""
    strings = bytearray()
    head = 20 + 40 * len(sections)
    blobs, offsets = bytearray(), []
    for _, _, data, relocs in sections:
        start = head + len(blobs)
        blobs += data
        reloc_at = head + len(blobs)
        for offset, index, rtype in relocs:
            blobs += struct.pack("<IIH", offset, index, rtype)
        offsets.append((start, reloc_at))
    table = bytearray()
    count = 0
    for name, value, section, stype, storage, aux in symbols:
        raw = name.encode()
        if len(raw) <= 8:
            field = raw.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, 4 + len(strings))
            strings += raw + b"\0"
        table += field + struct.pack("<IhHBB", value, section, stype, storage, aux)
        table += b"\0" * 18 * aux
        count += 1 + aux
    out = bytearray(struct.pack("<HHIIIHH", 0x14C, len(sections), 0,
                                head + len(blobs), count, 0, 0))
    for (name, chars, data, relocs), (start, reloc_at) in zip(sections, offsets):
        out += name.encode().ljust(8, b"\0")
        out += struct.pack("<IIIIIIHHI", 0, 0, len(data), start, reloc_at, 0,
                           len(relocs), 0, chars)
    out += blobs + table + struct.pack("<I", 4 + len(strings)) + strings
    return bytes(out)


def row(name, rva, size):
    return {"name": name, "export_rva": "", "target_rva": f"0x{rva:08X}",
            "target_size": str(size), "source": "Code/x.cpp", "status": "matched", "notes": ""}


def verdict(tmp_path, obj, memory, rows, under_test, pins=(), data=None):
    path = tmp_path / "x.obj"
    path.write_bytes(obj)
    image = diffexec.Image.from_memory(BASE, memory, exec_ranges=[(0x1000, 0x5000)])
    ctx = diffexec.Context(image, rows, pins, data_ledger=data)
    compiled, relocs, info = build.read_object_symbol_bytes(path, "_f", None, detail=True)
    stat = path.stat()
    objdata, sections, _ = build._object_layout(str(path), stat.st_mtime_ns, stat.st_size)
    record = diffexec.diff_row(ctx, under_test, compiled, relocs, info, objdata, sections)
    return record["verdict"], record


# --- wrong callee via a pin --------------------------------------------------------

PROLOGUE, EPILOGUE = b"\x55\x8b\xec\x83\xec\x08", b"\x8b\xe5\x5d\xc3"


def call_case(tmp_path, retail_callee, *, pins=(), twin=False):
    code = PROLOGUE + b"\xe8\x00\x00\x00\x00" + EPILOGUE
    obj = coff([(".text", TEXT, code, [(7, 3, 0x14)])],
               [(".text", 0, 1, 0, 3, 1), ("_f", 0, 1, 0x20, 2, 0),
                ("?Callee@@YAXXZ", 0, 0, 0x20, 2, 0)])
    retail = PROLOGUE + b"\xe8" + struct.pack("<i", retail_callee - 0x100B) + EPILOGUE
    memory = {0x1000: retail, 0x2000: b"\x33\xc0\xc3",
              0x3000: b"\x33\xc0\xc3" if twin else b"\xb0\x01\xc3"}
    rows = [row("_f", 0x1000, len(code)), row("?Callee@@YAXXZ", 0x2000, 3),
            row("?Other@@YAXXZ", 0x3000, 3)]
    return verdict(tmp_path, obj, memory, rows, rows[0], pins)


def test_wrong_callee_via_pin_diverges(tmp_path):
    # The byte gate passes this (test_gate_exploits): the pin is one more
    # REL32 candidate. The linker binds ?Callee to its row, so behaviour differs.
    result, record = call_case(tmp_path, 0x3000, pins=[("?Callee@@YAXXZ", 0x3000)])
    assert result == "binding", record
    assert "?Other@@YAXXZ" in record["reason"]


def test_wrong_twin_callee_is_flagged_as_twin(tmp_path):
    result, record = call_case(tmp_path, 0x3000, pins=[("?Callee@@YAXXZ", 0x3000)], twin=True)
    assert result == "binding" and "twin" in record["reason"], record


def test_right_callee_shows_no_divergence(tmp_path):
    result, record = call_case(tmp_path, 0x2000)
    assert result == "none", record


def test_callee_through_incremental_thunk_is_the_same_identity(tmp_path):
    thunk = 0x1800
    result, record = call_case(tmp_path, thunk)
    assert result != "none"   # no thunk mapped yet: a call to 0x1800 is a different target
    code = PROLOGUE + b"\xe8\x00\x00\x00\x00" + EPILOGUE
    obj = coff([(".text", TEXT, code, [(7, 3, 0x14)])],
               [(".text", 0, 1, 0, 3, 1), ("_f", 0, 1, 0x20, 2, 0),
                ("?Callee@@YAXXZ", 0, 0, 0x20, 2, 0)])
    memory = {0x1000: PROLOGUE + b"\xe8" + struct.pack("<i", thunk - 0x100B) + EPILOGUE,
              thunk: b"\xe9" + struct.pack("<i", 0x2000 - thunk - 5),
              0x2000: b"\x33\xc0\xc3"}
    rows = [row("_f", 0x1000, len(code)), row("?Callee@@YAXXZ", 0x2000, 3)]
    result, record = verdict(tmp_path, obj, memory, rows, rows[0])
    assert result == "none", record   # only the call operand differs: same code, linked apart


def test_equivalent_encoding_is_regalloc_only(tmp_path):
    obj = coff([(".text", TEXT, b"\x31\xc0\xc3", [])],      # xor eax,eax (31 /r form)
               [(".text", 0, 1, 0, 3, 1), ("_f", 0, 1, 0x20, 2, 0)])
    rows = [row("_f", 0x1000, 3)]
    result, record = verdict(tmp_path, obj, {0x1000: b"\x33\xc0\xc3"}, rows, rows[0])
    assert result == "regalloc-only", record


# --- wrong global --------------------------------------------------------------------

def global_case(tmp_path, retail_global):
    code = b"\xa1\x00\x00\x00\x00\xc3"                    # mov eax, [g]; ret
    obj = coff([(".text", TEXT, code, [(1, 3, 6)])],
               [(".text", 0, 1, 0, 3, 1), ("_f", 0, 1, 0x20, 2, 0),
                ("?TheWrong@@3HA", 0, 0, 0, 2, 0)])
    memory = {0x1000: b"\xa1" + struct.pack("<I", BASE + retail_global) + b"\xc3",
              0x5000: b"\0" * 0x10 + struct.pack("<I", 7) + b"\0" * 12 + struct.pack("<I", 9)}
    rows = [row("_f", 0x1000, len(code))]
    return verdict(tmp_path, obj, memory, rows, rows[0], data={"?TheWrong@@3HA": 0x5020})


def test_wrong_global_diverges(tmp_path):
    # The byte gate copies every DIR32 operand from retail, so this matches.
    result, record = global_case(tmp_path, 0x5010)
    assert result == "binding", record


def test_right_global_shows_no_divergence(tmp_path):
    result, record = global_case(tmp_path, 0x5020)
    assert result == "none", record


# --- swapped switch case -------------------------------------------------------------

def switch_case(tmp_path, retail_order):
    code = (b"\x8b\x44\x24\x04" b"\xff\x24\x85\x00\x00\x00\x00"
            b"\xb8\x01\x00\x00\x00\xc3" b"\xb8\x02\x00\x00\x00\xc3"
            b"\x00\x00\x00\x00\x00\x00\x00\x00")
    obj = coff([(".text", TEXT, code, [(7, 5, 6), (23, 3, 6), (27, 4, 6)])],
               [(".text", 0, 1, 0, 3, 1), ("_f", 0, 1, 0x20, 2, 0), ("$L1", 11, 1, 0, 6, 0),
                ("$L2", 17, 1, 0, 6, 0), ("$L3", 23, 1, 0, 6, 0)])
    va = BASE + 0x1000
    labels = {"L1": va + 11, "L2": va + 17}
    retail = bytearray(code[:23])
    retail[7:11] = struct.pack("<I", va + 23)
    retail += b"".join(struct.pack("<I", labels[k]) for k in retail_order)
    rows = [row("_f", 0x1000, 31)]
    return verdict(tmp_path, obj, {0x1000: bytes(retail), 0x5000: b"\0" * 16}, rows, rows[0])


def test_swapped_switch_case_diverges(tmp_path):
    result, record = switch_case(tmp_path, ["L2", "L1"])
    assert result == "logic", record


def test_correct_switch_shows_no_divergence(tmp_path):
    result, record = switch_case(tmp_path, ["L1", "L2"])
    assert result == "none", record


# --- truncated string literal -----------------------------------------------------------

def string_case(tmp_path, source_literal, retail_literal=b"Default \0"):
    code = b"\x68\x00\x00\x00\x00" b"\xe8\x00\x00\x00\x00" b"\x83\xc4\x04" b"\xc3"
    obj = coff([(".text", TEXT, code, [(1, 3, 6), (6, 4, 0x14)]),
                (".rdata", RDATA, source_literal, [])],
               [(".text", 0, 1, 0, 3, 1), ("_f", 0, 1, 0x20, 2, 0),
                ("??_C@_08KLMNOPQR@Default?5?$AA@", 0, 2, 0, 2, 0),
                ("?Use@@YAXPBD@Z", 0, 0, 0x20, 2, 0)])
    retail = (b"\x68" + struct.pack("<I", BASE + 0x5000) +
              b"\xe8" + struct.pack("<i", 0x3000 - 0x100A) + b"\x83\xc4\x04\xc3")
    memory = {0x1000: retail, 0x3000: b"\xc3", 0x5000: retail_literal}
    rows = [row("_f", 0x1000, len(code)), row("?Use@@YAXPBD@Z", 0x3000, 1)]
    return verdict(tmp_path, obj, memory, rows, rows[0])


def test_truncated_string_literal_diverges(tmp_path):
    result, record = string_case(tmp_path, b"Default\0")
    assert result == "binding", record
    assert record["sites"].get("content-mismatch") == 1


def test_complete_string_literal_shows_no_divergence(tmp_path):
    result, record = string_case(tmp_path, b"Default \0")
    assert result == "none", record
    assert record["sites"] == {"content": 1, "ledger": 1}


# --- harness properties -------------------------------------------------------------

def test_runs_are_deterministic(tmp_path):
    first = call_case(tmp_path, 0x3000, pins=[("?Callee@@YAXXZ", 0x3000)])[1]["reason"]
    second = call_case(tmp_path, 0x3000, pins=[("?Callee@@YAXXZ", 0x3000)])[1]["reason"]
    assert first == second


def test_stratified_sample_is_seeded():
    rows = [row(f"_r{i}", 0x1000 + 16 * i, 1 + i % 900) for i in range(3000)]
    a = diffexec.stratified_sample(rows, 200, 7)
    b = diffexec.stratified_sample(rows, 200, 7)
    assert [r["name"] for r in a] == [r["name"] for r in b]
    assert len({diffexec.stratum(r) for r in a}) == len({diffexec.stratum(r) for r in rows})


def test_runtime_helper_swap_is_build_env(tmp_path):
    code = PROLOGUE + b"\xe8\x00\x00\x00\x00" + EPILOGUE
    obj = coff([(".text", TEXT, code, [(7, 3, 0x14)])],
               [(".text", 0, 1, 0, 3, 1), ("_f", 0, 1, 0x20, 2, 0),
                ("__ftol2", 0, 0, 0x20, 2, 0)])
    memory = {0x1000: PROLOGUE + b"\xe8" + struct.pack("<i", 0x3000 - 0x100B) + EPILOGUE,
              0x2000: b"\x33\xc0\xc3", 0x3000: b"\xb0\x01\xc3"}
    rows = [row("_f", 0x1000, len(code)), row("__ftol2", 0x2000, 3), row("__ftol", 0x3000, 3)]
    result, record = verdict(tmp_path, obj, memory, rows, rows[0])
    assert result == "build_env", record
