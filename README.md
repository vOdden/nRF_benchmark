# Master
Master Thesis

TODO:
- Read papers and figure out what the papers does similar or different.
- Any other benchmark used?
- Write on the report
- 
- Does increased number of tensorflows affect the results?
- Does the model perfoms differently when stored in FLASH contra SRAM for this benchmark?
- 


DONE:
- Added benchmark implementation for Keyword Spotting (KWS)
- Added benchmark implementation for Visual Wake Words (VWW) 
- Include EnergyRunner dataset for running the benchmark
- Ran the models on both nRF52 and nRF53 at 64MHz.
- Ran the models on nRF53 with 128MHz.


Minimum Tensor arena sizes for all the models;
- AD: 3
- IC: 54
- KWS : 23
- VWW : 100
Maximum tensor arena:
-
-
-
-

--

- VWW 17/2 conflict solved by implementing model directly into main file submitter_implemented | idk why, but it works.
- Same solution also works for KWS, IC and AD.

---

Sigurd Odden
