# Retained optimized primary kernel

Open **[candidate.cpp](candidate.cpp)** for the complete operator and **[fixed_tiles.h](fixed_tiles.h)** for the arithmetic kernel.

Use **variant 1 (`nt_block_major`)** as the retained primary C256/S400/O256 research baseline. Variant 0 is its matched control. The original source, headers, configuration, workflow, proof and manifest bytes are unchanged.

The original run measured 91.190–91.373% of arithmetic peak; the latest separate Step94 remeasurement observed 90.855–91.019%. The later scratch shift and pipeline candidates were rejected. These studies are kept separate; no timings were rerun for the cleanup.

[Baseline identity](../configs/research_baseline.json) · [Original evidence](../../archives/experiments/38_block_major_input_packing/) · [Latest evidence](../../archives/experiments/54_scratch_halfline_phase/) · [Code guide](../README.md)

For original ECE commands, enter `.project` from the project root and use `diagnostics/block_major_input_v1/` as recorded. Generate/build/run target code and inspect assembly on ECE only. This folder is the same source reached by that compatibility path.
