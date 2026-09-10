"""The closed accessor lane must reject drift before it writes a claim."""
import importlib.util
import sys
from pathlib import Path

import pytest


TOOLS = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("gen_small_accessor_test", TOOLS / "gen_small.py")
gen_small = importlib.util.module_from_spec(spec)
sys.modules[spec.name] = gen_small
spec.loader.exec_module(gen_small)


def row(rva, size):
    return {
        "target_rva": f"0x{rva:08X}",
        "target_size": str(size),
        "source": "Code/gen_asm/example.asm",
        "status": "matched",
        "notes": "gen-dump;bounds=high",
    }


def test_population_is_closed_and_exact(monkeypatch):
    monkeypatch.setattr(gen_small, "ACCESSOR_BATCH", ((0x100, "access-pred-ne"),))
    body = bytes.fromhex("8b 51 38 33 c0 85 d2 0f 95 c0 c3")
    picked = gen_small.accessor_population([row(0x100, len(body))],
                                            lambda rva, size: body)
    assert picked[0][0] == 0x100
    assert picked[0][3].key == "access-pred-ne"
    assert gen_small.render_accessors(picked).count("Gen_00000100") == 2


def test_population_fails_closed_on_shape_drift(monkeypatch):
    monkeypatch.setattr(gen_small, "ACCESSOR_BATCH", ((0x100, "access-pred-ne"),))
    with pytest.raises(gen_small.FormatError, match="no longer matches"):
        gen_small.accessor_population([row(0x100, 11)],
                                      lambda rva, size: b"\xC3" * size)


def test_batch_is_the_expected_245_bytes():
    assert len(gen_small.ACCESSOR_BATCH) == 21
    rows = {int(r["target_rva"], 16): int(r["target_size"])
            for r in gen_small.B.load_all_function_rows()}
    assert sum(rows[rva] for rva, _ in gen_small.ACCESSOR_BATCH) == 245
