"""Collecting a tool's tests must preserve its shared dependency modules."""
import subprocess
import sys
from pathlib import Path

import pytest


TOOLS = Path(__file__).resolve().parents[1]


@pytest.mark.parametrize("loader", ["test_pin_consistency", "test_reloc_names"])
@pytest.mark.parametrize("loader_first", [False, True], ids=["census-first", "loader-first"])
def test_collection_keeps_census_and_receipt_fixtures_on_one_build(loader, loader_first):
    # A fresh process models both collection orders without relying on which
    # of these modules the outer pytest run has already imported. The receipt
    # helper is imported last, just as the currency tests import it at run time.
    order = ["test_link_census_currency", loader]
    if loader_first:
        order.reverse()
    order.append("test_census_receipts")
    result = subprocess.run(
        [sys.executable, "-c", """
import importlib
import sys

sys.path[:0] = sys.argv[1:3]
for name in sys.argv[3:]:
    importlib.import_module(name)

import build
import census_receipts
import link_census
import test_build_include_inventory
import test_census_receipts

for name, module in (
    ("census", link_census.build),
    ("receipts", census_receipts.build),
    ("include fixture", test_build_include_inventory.build),
    ("receipt fixture", test_census_receipts.build),
):
    assert module is build, f"{name} retained a replaced build module"
""", str(TOOLS), str(TOOLS / "tests"), *order],
        cwd=TOOLS.parent, capture_output=True, text=True, timeout=30,
    )
    assert result.returncode == 0, result.stdout + result.stderr
