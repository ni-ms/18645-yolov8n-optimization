# Hand-in files

Updated: 2 November 2026. [Start here](../README.md) · [Progress](../status.md)

## Open these

- **[Report PDF](submission/report.pdf)** — current four-page report answering all 18 assignment questions.
- [Detailed report](supporting/report_detailed.pdf) — nine-page explanatory companion.
- [Calculations](supporting/calculations.pdf) — twenty-five-page evidence/calculation supplement.
- [Presentation](submission/presentation.pptx) — existing draft; reconciliation and rehearsal remain outstanding.

## Readiness

**Written hand-in: one standalone report PDF.** Separate calculations, detailed notes and source ZIPs are local supporting/reference files, not additional required written submissions. Step123 removes references to unsubmitted notes and explains the necessary strides/packing mapping directly in the open primary source. Built-in compilation passes. The existing exported PDF below remains an earlier revision until a new export is requested.

**Source/preview revision — 1 November 2026 (Step110):** the open [primary LaTeX source](../report/report.tex) now corrects the fusion claims and two notation gaps, and its built-in editor compilation passes. The PDFs and source ZIPs below retain the preceding revision; no separate PDF/export or resource refresh was performed under the user's editor-only instruction. Reconcile companion wording and refresh/check exports when document export is requested.

**Presentation cleanup — 2 November 2026 (Step111):** the same source now removes the repeated course/project headers, subtitle and redundant framing. All18 question prompts and scientific answers remain, and built-in compilation passes. Existing PDFs/source ZIPs remain unchanged.

**Direct-answer wording — 2 November 2026 (Step112):** each answer in the open source now starts with an explicit statement addressing the question. Equations, tables, figures and measured scope are retained; built-in compilation passes. Existing PDFs/source ZIPs remain unchanged.

**Explanation/layout revision — 2 November 2026 (Step114):** the open source now adds workload coverage, caller flow, scoped tile-choice evidence and the original-suite error criterion, and explicitly distinguishes public NCHW/internal spatial-block16 from reported NCHW8c. Direct answers remain; built-in compilation passes. Existing PDFs/source ZIPs retain the preceding export revision.

**Table revision — 2 November 2026 (Step119):** the open source now shows instruction rates/roles and grouped OpenCV/our counted-cycle, useful-throughput and peak metrics from the existing five-shape data. All18 direct answers and original figures remain, with no peer-report references; built-in compilation passes. Existing PDFs/source ZIPs are still the earlier export and do not contain these editor-only revisions.

**Concise validation — 2 November 2026 (Step127):** the open primary source now removes test-volume, corpus-size and alignment audit counts. Accuracy tolerance/error, performance results, measurement design and repeatability limits remain; built-in compilation passes. Existing PDFs/source ZIPs remain the earlier export under the editor-only instruction. Resource refresh and final layout/export/hash checks remain deferred until a requested export.

**Implementation-label clarification — 2 November 2026 (Step128):** the open primary table now identifies the main tile and input handling as Block16, Packed16, Direct or Padded64, with definitions in the report. Numerical metrics and original point data are unchanged; built-in compilation passes. Existing PDF/source ZIP exports remain unchanged under the editor-only instruction.

**Full clarity pass — 2 November 2026 (Step129):** the open report now identifies the main Block16 implementation, earlier author-developed variants and the external OpenCV comparison. It explains experiment scopes, terminology and the separately retained C384 comparison executables. Numerical results remain unchanged; built-in compilation passes. Existing PDF/sourceZIP exports remain the prior revision under the editor-only instruction.

**COCO provenance and best-version scope — 2 November 2026 (Step131):** the open report now identifies COCO2017 validation(val2017) image-derived layer tensors and representative layer replay. Block16 remains the retained primary choice; no universal or end-to-end COCO winner is claimed. Built-in compilation passes. Existing PDF/sourceZIP exports remain unchanged under the editor-only instruction.

**Not marked submission-ready or submitted.** Report content and measured results are unchanged by the folder cleanup. The primary report distinguishes the original 91.190–91.373% result from the latest 90.855–91.019% remeasurement. Presentation reconciliation, rehearsal and human hand-in remain separate tasks in [status.md](../status.md).

Edit [the report source](../report/report.tex) and [the supplement source](../report/calculations.tex), then run `python3 code/tools/refresh_resources.py` from the project root. PDFs already compiled from those sources are copied here. This refresh does not compile LaTeX or execute target kernels.

The separate [Conv+bias+SiLU experiment](../report/findings.md#conv-silu-fusion) passed native safety/accuracy checks and independent timing reconciliation. Neither fused tile improved on the retained convolution plus the same separate SiLU pass. The current convolution baseline and report PDFs remain unchanged; the source snapshot includes the ECE-generated experiment.

The separate [fusion profile](../archives/experiments/56_conv_silu_profile/README.md) verifies432 small-group counter records on the unchanged binary: fewer stores but more loads/constant operands, changed cached-store allocation behavior, and lower input reuse in M5. These overlapping counts do not partition CPU time; the original timing frame and baseline remain unchanged.

## Complete package

| File | Purpose |
|---|---|
| [submission/report.pdf](submission/report.pdf) | Four-page report with explicit direct answers to all 18 assignment questions, matched OpenCV latency/peak/speedup graphs and the current 91% result. |
| [supporting/report_detailed.pdf](supporting/report_detailed.pdf) | Separate nine-page detailed report retaining all compact-report content and adding worked design, instruction, layout, benchmarking and interpretation explanations. |
| [submission/presentation.pptx](submission/presentation.pptx) | Presentation; newer evidence still needs reconciliation. |
| [assignment/project2_handout.pdf](assignment/project2_handout.pdf) | Official problem statement and submission requirements. |
| [assignment/proposal.docx](assignment/proposal.docx) | Original project proposal/reference. |
| [supporting/calculations.pdf](supporting/calculations.pdf) | Twenty-five-page calculation/evidence supplement: historical studies, exact C++ listings, peak derivations and S16 current 91% results with separate run identities. |
| [supporting/technical_report_with_full_matrix.pdf](supporting/technical_report_with_full_matrix.pdf) | Alternate technical report including the full matrix; the primary LaTeX report remains the requested deliverable. |
| [supporting/speaker_notes.txt](supporting/speaker_notes.txt) | Presentation notes; reconcile with the report and updated slide scope. |
| [sources/latex_project.zip](sources/latex_project.zip) | Current LaTeX sources, vector figures, exact code excerpts, full cited code sources, point data and hash manifests, with build instructions. |
| [sources/kernel_sources.zip](sources/kernel_sources.zip) | Kernel/tool/documentation snapshot; frozen datasets, dependencies and experiment bundles remain in the project. |

The assignment requests an individual 3–4-page PDF and a 20-minute presentation. Keep the supplements separate unless an appendix is permitted.

[manifest.json](manifest.json) records source/export hashes and every source-snapshot input. Existing package versions and the full previous readiness discussion are preserved in [the cleanup record](../archives/working_materials/20_simple_project_structure/before/resources/README.md). [Full findings](../report/findings.md) retain every experiment and limitation.

The source ZIPs use the original internal paths for provenance and ECE workflows. The live project uses `code/optimized/` for the retained primary kernel; [code/README.md](../code/README.md) explains its identity and scope. Frozen native experiments, assembly generation and assembly inspection remain ECE-only.
