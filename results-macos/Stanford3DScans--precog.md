* Command Line: `/Users/vilya/Code/ply-parsing-perf/build-release/ply-parsing-perf --slowdown --quiet --precognition -o results-precog.md allplyfiles.txt`
* Current Directory: `/Users/vilya/Models/Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |        7.929    (1.00x) |       84.180   (10.62x) |       34.961    (4.41x) |       41.781    (5.27x) |        9.317    (1.18x) |
| ./bunny/reconstruction/bun_zipper.ply       |        9.068    (1.00x) |      260.544   (28.73x) |      120.815   (13.32x) |       33.867    (3.73x) |       28.575    (3.15x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.110    (1.00x) |       60.273   (28.57x) |       26.718   (12.66x) |        7.627    (3.62x) |        6.407    (3.04x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.490    (1.00x) |       13.895   (28.36x) |        6.200   (12.66x) |        1.810    (3.69x) |        1.531    (3.12x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.133    (1.00x) |        3.415   (25.59x) |        1.531   (11.47x) |        0.459    (3.44x) |        0.389    (2.91x) |
| ./dragon_recon/dragon_vrip.ply              |       95.814    (1.00x) |     2742.607   (28.62x) |     1361.961   (14.21x) |      356.768    (3.72x) |      320.003    (3.34x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       21.359    (1.00x) |      611.279   (28.62x) |      312.851   (14.65x) |       81.330    (3.81x) |       70.853    (3.32x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        4.842    (1.00x) |      143.861   (29.71x) |       72.830   (15.04x) |       18.808    (3.88x) |       16.340    (3.37x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.123    (1.00x) |       32.203   (28.69x) |       16.533   (14.73x) |        4.301    (3.83x) |        3.704    (3.30x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.452    (1.00x) |       12.359   (27.34x) |        5.990   (13.25x) |        1.689    (3.74x) |        1.489    (3.29x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.180    (1.00x) |        4.870   (27.06x) |        2.360   (13.11x) |        0.652    (3.62x) |        0.564    (3.14x) |
| ./happy_recon/happy_vrip.ply                |      118.381    (1.00x) |     3413.447   (28.83x) |     1705.246   (14.40x) |      446.604    (3.77x) |      400.221    (3.38x) |
| ./happy_recon/happy_vrip_res2.ply           |       30.252    (1.00x) |      905.839   (29.94x) |      455.220   (15.05x) |      118.481    (3.92x) |      104.724    (3.46x) |
| ./happy_recon/happy_vrip_res3.ply           |        6.867    (1.00x) |      207.841   (30.27x) |      102.555   (14.93x) |       29.650    (4.32x) |       23.700    (3.45x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.514    (1.00x) |       45.568   (30.10x) |       23.074   (15.24x) |        5.931    (3.92x) |        5.134    (3.39x) |
| ./lucy/lucy.ply                             |      809.626    (1.00x) |     6660.429    (8.23x) |     2544.467    (3.14x) |     3510.552    (4.34x) |     1213.063    (1.50x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      168.859    (1.00x) |     1789.260   (10.60x) |      582.593    (3.45x) |      832.923    (4.93x) |      193.914    (1.15x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |       96.639    (1.00x) |     1113.506   (11.52x) |      459.138    (4.75x) |      549.417    (5.69x) |      115.726    (1.20x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      273.748    (1.00x) |     2259.080    (8.25x) |      808.265    (2.95x) |     1217.432    (4.45x) |      269.953    (0.99x) |
| Overall Total                               |     1649.384    (1.00x) |    20364.455   (12.35x) |     8643.306    (5.24x) |     7260.083    (4.40x) |     2785.606    (1.69x) |
