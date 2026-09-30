import struct
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import data_scaffold  # noqa: E402
import startup_tables as st  # noqa: E402


def test_sections_map_to_the_tables_the_crt_walks():
    assert st.table_of(".CRT$XCU") == "XC"
    assert st.table_of(".CRT$XCAA") == "XC"
    assert st.table_of(".CRT$XIC") == "XI"
    assert st.table_of(".rtc$IMZ") == "RTC_I"
    assert st.table_of(".rtc$TMZ") == "RTC_T"
    assert st.table_of(".CRT$XPA") is None  # the DLL CRT never runs the exe's XP/XT
    assert st.table_of(".rdata") is None


def test_linker_order_sorts_names_and_keeps_input_order_within_one():
    contribs = [{"section": ".CRT$XCU", "id": 1}, {"section": ".CRT$XCC", "id": 2},
                {"section": ".CRT$XCU", "id": 3}, {"section": ".CRT$XCA", "id": 4}]
    assert [c["id"] for c in st.linker_order(contribs)] == [4, 2, 1, 3]


def retail_table(rvas):
    return {"XC": {"entries": [{"rva": r} for r in rvas]}}


def test_compare_matches_only_identical_order():
    rep = st.compare(retail_table([1, 2, 3]), {"XC": [{"rva": 1}, {"rva": 2}, {"rva": 3}]})
    assert rep["XC"]["verdict"] == "match"
    rep = st.compare(retail_table([1, 2, 3, 4]), {"XC": [{"rva": 1}, {"rva": 3}, {"rva": 2}, {"rva": 4}]})
    assert rep["XC"]["verdict"] == "mismatch" and len(rep["XC"]["out_of_order"]) == 1


def test_compare_reports_missing_extra_unresolved_and_duplicates():
    rep = st.compare(retail_table([1, 2, 3]),
                     {"XC": [{"rva": 1}, {"rva": 1}, {"rva": 9}, {"rva": None, "symbol": "_$E1"}]})["XC"]
    assert [e["rva"] for e in rep["missing"]] == [2, 3]
    assert [e["rva"] for e in rep["extra"]] == [9]
    assert len(rep["unresolved"]) == 1 and rep["count_differs"] == {"0x00000001": [1, 2]}
    assert rep["verdict"] == "mismatch"


def test_repeated_targets_compare_as_counts():
    rep = st.compare(retail_table([7, 7, 7]), {"XC": [{"rva": 7}] * 3})["XC"]
    assert rep["verdict"] == "match"
    rep = st.compare(retail_table([7, 7, 7]), {"XC": [{"rva": 7}] * 5})["XC"]
    assert rep["count_differs"] == {"0x00000007": [3, 5]} and rep["verdict"] == "mismatch"


def test_split_sources_flags_a_source_in_two_runs():
    e = [{"kind": "source", "source": s} for s in ("a", "a", "b", "a", "c")]
    assert st.split_sources(e) == {"a": [(0, 2), (3, 1)]}


def test_ordered_common_keeps_a_longest_ordered_subsequence():
    keep = st.ordered_common([1, 2, 3, 4, 5], [2, 1, 3, 5, 4])
    assert len(keep) == 3


def make_object(path, name, text_funcs, crt):
    """An object whose .text holds `ret`s at text_funcs (name -> offset, static)
    and whose sections in `crt` [(section name, [func names])] point at them."""
    coff = data_scaffold.Coff()
    size = max(text_funcs.values()) + 16
    text = coff.add_section(".text", 0x60500020, b"\xC3" * size, size)
    idx = {f: coff.symbol(f, off, text, data_scaffold.STATIC) for f, off in text_funcs.items()}
    if name == "entry":
        coff.symbol("_start", 0, text)
    for sec_name, funcs in crt:
        n = coff.add_section(sec_name, 0xC0300040, bytes(4 * len(funcs)), 4 * len(funcs))
        coff.sections[n - 1]["relocs"] = [(4 * i, idx[f]) for i, f in enumerate(funcs)]
    coff.write(path)
    # type the .text symbols as functions (0x20), as cl does: a map lists
    # static symbols only when they are functions
    raw = bytearray(path.read_bytes())
    symtab, nsym = struct.unpack_from("<II", raw, 8)
    for i in range(nsym):
        at = symtab + 18 * i
        if struct.unpack_from("<h", raw, at + 12)[0] == text:
            struct.pack_into("<H", raw, at + 14, 0x20)
    path.write_bytes(bytes(raw))


def test_link_exe_lays_out_initializers_as_modelled(tmp_path):
    """link.exe 7.1 itself: the table it builds equals linker_order's prediction,
    and swapping two inputs swaps their entries (link order is table order)."""
    try:
        link, env = data_scaffold.linker()
    except SystemExit:
        pytest.skip("VC 7.1 toolchain not present")
    if not Path(link).exists():
        pytest.skip("VC 7.1 linker not present")
    make_object(tmp_path / "entry.obj", "entry", {"_e0": 0}, [(".CRT$XCA", ["_e0"])])
    make_object(tmp_path / "a.obj", "a", {"_$E1": 0, "_$E2": 16}, [(".CRT$XCU", ["_$E1", "_$E2"])])
    make_object(tmp_path / "b.obj", "b", {"_$E1": 0, "_c": 16}, [(".CRT$XCU", ["_$E1"]), (".CRT$XCC", ["_c"])])
    make_object(tmp_path / "c.obj", "c", {"_$E1": 0}, [(".CRT$XCU", ["_$E1"])])
    ids = {("a.obj", "_$E1"): 1, ("a.obj", "_$E2"): 2, ("b.obj", "_$E1"): 3, ("b.obj", "_c"): 4,
           ("c.obj", "_$E1"): 5, ("entry.obj", "_e0"): 0}

    def resolver(obj, name, storage):
        return ids.get((obj, name))

    def run(order, tag):
        exe, mapfile = tmp_path / f"{tag}.exe", tmp_path / f"{tag}.map"
        objs = [str(tmp_path / f"{o}.obj") for o in order]
        proc = subprocess.run([str(link), "/NOLOGO", "/NODEFAULTLIB", "/ENTRY:start", "/SUBSYSTEM:CONSOLE",
                               "/INCREMENTAL:NO", "/FIXED:NO", f"/MAP:{mapfile}", f"/OUT:{exe}", *objs],
                              capture_output=True, text=True, env=env)
        assert proc.returncode == 0, proc.stdout + proc.stderr
        got, _ = st.linked_tables(exe, mapfile, resolver)
        predicted = st.predicted_tables(st.object_contributions([tmp_path / f"{o}.obj" for o in order], resolver))
        return [e["rva"] for e in got["XC"]], [e["rva"] for e in predicted["XC"]]

    got, predicted = run(["entry", "a", "b", "c"], "abc")
    assert got == predicted == [0, 4, 1, 2, 3, 5]
    got, predicted = run(["entry", "c", "b", "a"], "cba")
    assert got == predicted == [0, 4, 5, 3, 1, 2]


def test_retail_delimiters_come_from_the_entry_member():
    if not build.EXE.exists():
        pytest.skip("retail image not present")
    rows = st.matched_rows()
    delim = st.delimiters(st.Retail(), rows)
    if "___xc_a" not in delim:
        pytest.skip("_WinMainCRTStartup is not ledgered in this checkout")
    assert (delim["___xc_a"], delim["___xc_z"]) == (0x012A5000, 0x012A617C)
    assert (delim["___xi_a"], delim["___xi_z"]) == (0x012A6280, 0x012A6384)


def test_hexify_formats_addresses_only():
    out = st.hexify({"rva": 0x10, "count": 3, "entries": [{"slot": 4}]})
    assert out == {"rva": "0x00000010", "count": 3, "entries": [{"slot": "0x00000004"}]}
