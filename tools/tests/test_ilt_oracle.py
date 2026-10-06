#!/usr/bin/env python3
"""ilt_oracle: link.exe's symbol hash, table growth and insertion order, reproduced on synthetic
links, and the frozen retail windows."""
import json
import os
import random
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import ilt_oracle as O  # noqa: E402

FIXTURE = ROOT / "tools/tests/fixtures/ilt_synthetic.json"
VS = ROOT / "inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003"
LINK = VS / "Vc7/bin/link.exe"


def test_hash_matches_link_exe_values():
    # values from an independent re-implementation of link.exe 0x445330 (_audit/scratch_v_ilt/vh.py)
    assert O.vhash("_main") == 0x0DCDE6C4 % O.MOD or O.vhash("_main") == O.vhash(b"_main")
    assert O.vhash(b"\xe9x") != O.vhash(b"\x69x")                  # signed chars: the high bit matters
    assert O.vhash("") == 0
    assert O.vhash("A") == 65 * 0x40001 % O.MOD


def test_bucket_uses_the_split_pointer():
    h = 32768 * 5 + 100                                               # h % 32768 == 100
    assert O.bucket(h, 32768 + 50) == 100                             # bucket 100 not split yet
    assert O.bucket(h, 32768 + 101) == h % 65536                      # split: rehash with 2*maxp
    assert O.bucket(7, 1024) == 7


def test_table_is_lifo_and_splits_keep_order():
    t = O.Table()
    for i in range(4000):
        t.lookup(f"?n{i}@@YAXXZ")
    order = t.order()
    assert len(order) == 4000 and len(t.chains) > 1024
    rank = {n: i for i, n in enumerate(f"?n{i}@@YAXXZ" for i in range(4000))}
    for chain in t.chains:                                            # newest first in every chain
        assert [rank[n] for n in chain] == sorted((rank[n] for n in chain), reverse=True)


def coff(defs, comdats, undefs, order):
    """A raw i386 COFF object. defs live in .text (16 bytes apart), each comdat in its own
    COMDAT section (sections numbered in `comdats` order), and a stub in .text calls every undef.
    `order` lists ('D'|'C'|'U', name) in symbol-table order."""
    strtab = bytearray(b"\0\0\0\0")

    def short(n):
        if len(n) <= 8:
            return n.ljust(8, b"\0")
        off = len(strtab)
        strtab.extend(n + b"\0")
        return b"\0\0\0\0" + struct.pack("<I", off)

    text, pos = bytearray(), {}
    for n in defs:
        pos[n] = len(text)
        text += b"\xc3" + b"\xcc" * 15
    stub = len(text)
    text += b"\xe8\0\0\0\0" * len(undefs) + b"\xc3"
    sections = [[b".text", 0x60500020, bytes(text), []]] + [[b".text", 0x60501020, b"\xc3", []] for _ in comdats]
    syms = []

    def sym(name, value, sec, typ, sclass, aux=b""):
        syms.append(short(name) + struct.pack("<IhHBB", value, sec, typ, sclass, len(aux) // 18) + aux)

    count = lambda: sum(1 + s[17] for s in syms)
    sym(b".text", 0, 1, 0, 3, struct.pack("<IHHIHB3x", len(text), len(undefs), 0, 0, 0, 0))
    for k in range(len(comdats)):
        sym(b".text", 0, 2 + k, 0, 3, struct.pack("<IHHIHB3x", 1, 0, 0, 0, 0, 2))
    index = {}
    for kind, n in order:
        index[n] = count()
        if kind == "D":
            sym(n, pos[n], 1, 0x20, 2)
        elif kind == "C":
            sym(n, 0, 2 + comdats.index(n), 0x20, 2)
        else:
            sym(n, 0, 0, 0x20, 2)
    sections[0][3] = [struct.pack("<IIH", stub + j * 5 + 1, index[n], 0x14) for j, n in enumerate(undefs)]
    offset, body, headers = 20 + 40 * len(sections), bytearray(), bytearray()
    for name, flags, data, relocs in sections:
        ptr = offset + len(body)
        body += data
        rptr = offset + len(body) if relocs else 0
        for r in relocs:
            body += r
        headers += name.ljust(8, b"\0") + struct.pack("<IIIIIIHHI", 0, 0, len(data), ptr, rptr, 0, len(relocs), 0, flags)
    return (struct.pack("<HHIIIHH", 0x14C, len(sections), 0, offset + len(body), count(), 0, 0)
            + bytes(headers) + bytes(body) + b"".join(syms) + struct.pack("<I", len(strtab)) + bytes(strtab[4:]))


def synthetic(seed=7, nobj=3, per=1100):
    """Deterministic objects whose COMDAT, plain and undefined externals are interleaved in the
    symbol table, with cross-object references, ~3,300 externals (crosses the 1024->2048 doubling)."""
    rnd = random.Random(seed)
    alphabet = [bytes([c]) for c in range(0x21, 0x7F) if chr(c) not in '"'] + [b"\xa7", b"\xe9"]
    names = [[b"?" + b"".join(rnd.choice(alphabet) for _ in range(rnd.randint(3, 14))) + b"%d@@YAXXZ" % (o * per + i)
              for i in range(per)] for o in range(nobj)]
    objects = []
    for o in range(nobj):
        mine = names[o]
        defs, comdats = mine[: per // 2], mine[per // 2:]
        rnd.shuffle(comdats)
        others = [n for k in range(nobj) if k != o for n in names[k]]
        undefs = rnd.sample(others, 60)
        order = [("D", n) for n in defs] + [("C", n) for n in comdats] + [("U", n) for n in undefs]
        rnd.shuffle(order)                                            # symbol order != section order
        objects.append(coff(defs, sorted(comdats, key=lambda n: rnd.random()), undefs, order))
    return objects, names[0][0]


def test_insertion_order_puts_comdats_first_by_section_number():
    data = coff([b"_d1", b"_d2"], [b"_c2", b"_c1"], [b"_u1"], [("U", b"_u1"), ("C", b"_c1"), ("D", b"_d2"),
                                                               ("C", b"_c2"), ("D", b"_d1")])
    assert O.coff_externals(data) == [(b"_c2", "C"), (b"_c1", "C"), (b"_u1", "U"), (b"_d2", "D"), (b"_d1", "D")]


def test_synthetic_fixture_order_is_predicted_exactly():
    objects, entry = synthetic()
    want = [n.encode("latin1") for n in json.loads(FIXTURE.read_text())["thunks"]]
    got = O.predict_thunks(objects, entry=entry)
    assert len(got) == len(want) == 3300
    assert got == want


def run_link(objects, entry, work):
    """Thunk order of a fresh link (a leftover .ilk would make it an incremental relink that
    keeps the old table)."""
    work = tempfile.mkdtemp(dir=work)
    paths = []
    for k, data in enumerate(objects):
        p = Path(work) / f"o{k}.obj"
        p.write_bytes(data)
        paths.append(p.name)
    env = dict(os.environ, PATH=f"{VS / 'Vc7/bin'};{VS / 'Common7/IDE'};{os.environ.get('PATH', '')}")
    subprocess.run([str(LINK), "/nologo", "/INCREMENTAL", "/NODEFAULTLIB", "/SUBSYSTEM:CONSOLE",
                    "/ENTRY:" + entry.decode("latin1"), "/MAP:s.map", "/OUT:s.exe", *paths],
                   cwd=work, env=env, check=True, capture_output=True)
    at = {}
    for line in (Path(work) / "s.map").read_bytes().splitlines():
        m = re.match(rb"\s*0001:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\s", line)
        if m:
            at[int(m.group(2), 16)] = m.group(1)
    data = (Path(work) / "s.exe").read_bytes()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    sec = pe + 24 + struct.unpack_from("<H", data, pe + 20)[0]
    va, raw = struct.unpack_from("<I", data, sec + 12)[0], struct.unpack_from("<I", data, sec + 20)[0]
    i = raw
    while data[i] == 0xCC:
        i += 1
    out = []
    while data[i] == 0xE9:
        out.append(at[0x400000 + va + (i - raw) + 5 + struct.unpack_from("<i", data, i + 1)[0]])
        i += 5
    return out


@pytest.mark.skipif(sys.platform != "win32" or not LINK.exists(), reason="needs the VS2003 link.exe")
def test_real_link_matches_fixture_and_prediction():
    objects, entry = synthetic()
    with tempfile.TemporaryDirectory() as work:
        actual = run_link(objects, entry, work)
        reverse = run_link(objects[::-1], entry, work)
    assert actual == O.predict_thunks(objects, entry=entry)
    assert actual == [n.encode("latin1") for n in json.loads(FIXTURE.read_text())["thunks"]]
    assert reverse == O.predict_thunks(objects[::-1], entry=entry)        # object order changes chains


@pytest.mark.skipif(not O.WINDOWS.exists(), reason="no frozen window file")
def test_frozen_windows_check_known_names():
    o = O.Oracle()
    assert len(o.target) == 60965 and o.first_thunk == 0x401005
    stl = ("??$?5DV?$char_traits@D@_STL@@V?$allocator@D@1@@_STL@@YAAAV?$basic_istream@DV?$char_traits@D@_STL@@@0@"
           "AAV10@AAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@0@@Z")
    v, p, _ = o.check(stl, 0x0053C820)
    assert v == O.CONFIRMED and p < 1e-3
    assert o.check(stl.replace("YAAAV", "YGAAV"), 0x0053C820)[0] == O.CONTRADICTED
    assert o.check(stl, 0x00C1FC1D)[0] == O.UNTESTABLE                      # lib region: no thunk


@pytest.mark.skipif(not O.EXE.exists() or not O.WINDOWS.exists(), reason="needs the retail baseline")
def test_frozen_windows_belong_to_the_retail_baseline():
    import hashlib
    o = O.Oracle()
    assert o.meta["exe_sha256"] == hashlib.sha256(O.EXE.read_bytes()).hexdigest()
    assert O.retail_ilt()[1] == o.target


def test_access_variants_and_tiers():
    assert "?f@C@@QBEHXZ" in O.access_variants("?f@C@@QAEHXZ")
    assert "??_GC@@UAEPAXI@Z" in O.access_variants("??_GC@@MAEPAXI@Z")
    assert O.access_variants("?f@@YAHXZ") == []
    assert O.tier("?b_000659e0@@YAXXZ") == "placeholder"
    assert O.tier("??_GGen_dtor_00075d40@@UAEPAXI@Z") == "placeholder"
    assert O.tier("??1BfmeOwnerBZ@@QAE@XZ") == "invented"
    assert O.tier("??1ControlBar@@UAE@XZ") == "real"
