* Command Line: `/Users/vilya/Code/ply-parsing-perf/build-release/ply-parsing-perf --slowdown --quiet --precognition allplyfiles.txt -o /Users/vilya/Code/ply-parsing-perf/results-macos/Stanford3DScans--precog.md`
* Current Directory: `/Users/vilya/Models/Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |        8.715    (1.00x) |       83.965    (9.64x) |       49.170    (5.64x) |       41.692    (4.78x) |        9.041    (1.04x) |
| ./bunny/reconstruction/bun_zipper.ply       |        9.177    (1.00x) |      259.066   (28.23x) |      121.239   (13.21x) |       32.979    (3.59x) |       30.724    (3.35x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.327    (1.00x) |       59.017   (25.36x) |       26.390   (11.34x) |        7.470    (3.21x) |        6.388    (2.75x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        1.090    (1.00x) |       17.001   (15.60x) |        6.125    (5.62x) |        1.871    (1.72x) |        1.592    (1.46x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.221    (1.00x) |        4.517   (20.40x) |        1.823    (8.23x) |        0.535    (2.42x) |        0.428    (1.93x) |
| ./dragon_recon/dragon_vrip.ply              |       95.491    (1.00x) |     2733.569   (28.63x) |     1339.521   (14.03x) |      349.132    (3.66x) |      321.313    (3.36x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       21.392    (1.00x) |      606.433   (28.35x) |      310.803   (14.53x) |       79.138    (3.70x) |       73.499    (3.44x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        4.749    (1.00x) |      140.835   (29.65x) |       72.757   (15.32x) |       18.263    (3.85x) |       16.687    (3.51x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        2.277    (1.00x) |       33.693   (14.80x) |       16.200    (7.12x) |        4.114    (1.81x) |        3.718    (1.63x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        1.007    (1.00x) |       15.923   (15.81x) |        5.913    (5.87x) |        1.689    (1.68x) |        1.453    (1.44x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.184    (1.00x) |        4.677   (25.39x) |        2.359   (12.80x) |        0.644    (3.49x) |        0.570    (3.09x) |
| ./happy_recon/happy_vrip.ply                |      118.323    (1.00x) |     3422.517   (28.93x) |     1679.352   (14.19x) |      434.323    (3.67x) |      398.817    (3.37x) |
| ./happy_recon/happy_vrip_res2.ply           |       30.635    (1.00x) |      910.349   (29.72x) |      453.642   (14.81x) |      116.577    (3.81x) |      106.254    (3.47x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.912    (1.00x) |      204.425   (25.84x) |      101.594   (12.84x) |       26.163    (3.31x) |       23.697    (3.00x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.688    (1.00x) |       45.820   (27.15x) |       23.169   (13.73x) |        5.918    (3.51x) |        5.154    (3.05x) |
| ./lucy/lucy.ply                             |      841.072    (1.00x) |     6840.205    (8.13x) |     3626.989    (4.31x) |     3583.870    (4.26x) |     1091.652    (1.30x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      155.552    (1.00x) |     1703.085   (10.95x) |      811.903    (5.22x) |      845.528    (5.44x) |      194.225    (1.25x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |       96.159    (1.00x) |     1123.574   (11.68x) |      612.486    (6.37x) |      547.991    (5.70x) |      115.421    (1.20x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      269.888    (1.00x) |     2243.999    (8.31x) |     1126.247    (4.17x) |     1225.303    (4.54x) |      269.574    (1.00x) |
| Overall Total                               |     1667.859    (1.00x) |    20452.671   (12.26x) |    10387.680    (6.23x) |     7323.200    (4.39x) |     2670.208    (1.60x) |
