"""Shape matching against compiled Zero Hour functions (no compiler or image needed)."""
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import zh_fuzzy_twins as twins  # noqa: E402

LOOP = ["push", "mov", "xor", "cmp", "jge", "mov", "add", "inc", "cmp", "jl", "pop", "ret"] * 3
CALLS = ["push", "push", "call", "add", "test", "je", "mov", "call", "mov", "pop", "ret", "nop"] * 3
OTHER = ["fld", "fmul", "fstp", "fld", "fadd", "fstp", "fld", "fsub", "fstp", "ret", "nop", "nop"] * 3


def library():
    lib = {"?loop@A@@QAEXXZ": (LOOP, 120), "?calls@B@@QAEXXZ": (CALLS, 120), "?math@C@@QAEXXZ": (OTHER, 120)}
    return lib, twins.build_index(lib)


def test_a_changed_body_still_finds_its_twin():
    lib, index = library()
    changed = LOOP[:10] + ["mov", "mov", "lea"] + LOOP[10:]      # BFME added three instructions
    similarity, margin, symbol = twins.best(changed, 130, lib, index)
    assert symbol == "?loop@A@@QAEXXZ"
    assert similarity > 0.85 and margin > 0.3


def test_size_must_be_comparable():
    lib, index = library()
    assert twins.best(LOOP, 1000, lib, index) is None             # a 120 B function is not an 1,000 B body's twin


def test_nothing_in_common_gives_no_answer():
    lib, index = library()
    assert twins.best(["int3", "hlt", "cli", "sti", "cld", "std"] * 6, 120, lib, index) is None


def test_table_round_trip(tmp_path):
    path = tmp_path / "twins.tsv"
    path.write_text(twins.HEADER + "0x00747670\t202\t0.97\t0.41\t?setDrawOrg@WorldHeightMap@@QAE_NHH@Z\treference/x/WorldHeightMap.cpp\n"
                    "not a row\n", encoding="utf-8")
    got = twins.load_twins(path)
    assert got == {0x00747670: dict(similarity=0.97, margin=0.41, symbol="?setDrawOrg@WorldHeightMap@@QAE_NHH@Z",
                                     source="reference/x/WorldHeightMap.cpp")}
    assert twins.load_twins(tmp_path / "absent.tsv") == {}
