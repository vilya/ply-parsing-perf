* Command Line: `/Users/vilya/Code/ply-parsing-perf/build-release/ply-parsing-perf --transposed --slowdown --quiet --precognition allplyfiles.txt -o /Users/vilya/Code/ply-parsing-perf/results-macos/Stanford3DScans--precog.md`
* Current Directory: `/Users/vilya/Models/Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |        9.563    (1.00x) |       88.369    (9.24x) |       37.964    (3.97x) |       46.990    (4.91x) |       11.971    (1.25x) |
| ./bunny/reconstruction/bun_zipper.ply       |        9.383    (1.00x) |      264.134   (28.15x) |      119.892   (12.78x) |       33.751    (3.60x) |       28.565    (3.04x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.390    (1.00x) |       61.257   (25.63x) |       34.573   (14.47x) |        7.472    (3.13x) |        6.436    (2.69x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.554    (1.00x) |       14.102   (25.44x) |        6.316   (11.39x) |        1.903    (3.43x) |        1.595    (2.88x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.149    (1.00x) |        3.378   (22.64x) |        1.533   (10.27x) |        0.540    (3.62x) |        0.390    (2.62x) |
| ./dragon_recon/dragon_vrip.ply              |      104.493    (1.00x) |     2793.676   (26.74x) |     1370.686   (13.12x) |      348.032    (3.33x) |      325.056    (3.11x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       22.080    (1.00x) |      621.702   (28.16x) |      314.735   (14.25x) |       79.840    (3.62x) |       72.250    (3.27x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        5.203    (1.00x) |      151.455   (29.11x) |       73.250   (14.08x) |       18.401    (3.54x) |       18.198    (3.50x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.265    (1.00x) |       33.153   (26.21x) |       16.850   (13.32x) |        4.142    (3.27x) |        3.918    (3.10x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.565    (1.00x) |       13.298   (23.55x) |        5.997   (10.62x) |        1.669    (2.95x) |        1.770    (3.13x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.279    (1.00x) |        4.976   (17.85x) |        2.346    (8.41x) |        0.640    (2.30x) |        0.605    (2.17x) |
| ./happy_recon/happy_vrip.ply                |      132.957    (1.00x) |     3539.755   (26.62x) |     1724.545   (12.97x) |      430.997    (3.24x) |      413.895    (3.11x) |
| ./happy_recon/happy_vrip_res2.ply           |       33.772    (1.00x) |      929.765   (27.53x) |      457.159   (13.54x) |      115.333    (3.42x) |      107.640    (3.19x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.931    (1.00x) |      208.067   (26.24x) |      103.341   (13.03x) |       26.010    (3.28x) |       23.529    (2.97x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.903    (1.00x) |       44.862   (23.57x) |       22.750   (11.95x) |        5.961    (3.13x) |        5.277    (2.77x) |
| ./lucy/lucy.ply                             |      946.609    (1.00x) |     6948.228    (7.34x) |     2660.806    (2.81x) |     3618.619    (3.82x) |     1133.325    (1.20x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      195.658    (1.00x) |     1713.632    (8.76x) |      650.285    (3.32x) |      853.737    (4.36x) |      241.996    (1.24x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      120.698    (1.00x) |     1094.383    (9.07x) |      482.883    (4.00x) |      591.896    (4.90x) |      137.971    (1.14x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      278.514    (1.00x) |     2396.475    (8.60x) |      891.485    (3.20x) |     1228.987    (4.41x) |      401.332    (1.44x) |
| Overall Total                               |     1873.967    (1.00x) |    20924.666   (11.17x) |     8977.394    (4.79x) |     7414.921    (3.96x) |     2935.719    (1.57x) |
