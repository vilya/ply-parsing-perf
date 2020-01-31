* Command Line: `C:\Users\vilya\Code\ply-parsing-perf\build-release\ply-parsing-perf.exe --slowdown --quiet --precognition allplyfiles.txt -o C:/Users/vilya/Code/ply-parsing-perf/results-win10-laptop/Stanford3DScans--precog.md`
* Current Directory: `C:\Users\vilya\Models\Stanford`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       15.598    (1.00x) |      121.891    (7.81x) |       90.008    (5.77x) |       55.178    (3.54x) |       13.001    (0.83x) |
| ./bunny/reconstruction/bun_zipper.ply       |        8.931    (1.00x) |      452.334   (50.65x) |      181.850   (20.36x) |       49.281    (5.52x) |       62.236    (6.97x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.151    (1.00x) |      102.906   (47.83x) |       42.686   (19.84x) |       11.286    (5.25x) |       13.637    (6.34x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.591    (1.00x) |       23.453   (39.68x) |        9.574   (16.20x) |        2.695    (4.56x) |        3.110    (5.26x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.224    (1.00x) |        5.652   (25.24x) |        2.462   (11.00x) |        0.669    (2.99x) |        0.786    (3.51x) |
| ./dragon_recon/dragon_vrip.ply              |       98.353    (1.00x) |     4592.772   (46.70x) |     2131.274   (21.67x) |      468.496    (4.76x) |      614.768    (6.25x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       22.414    (1.00x) |     1054.696   (47.05x) |      484.015   (21.59x) |      106.056    (4.73x) |      134.956    (6.02x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        5.104    (1.00x) |      247.810   (48.55x) |      111.451   (21.84x) |       24.668    (4.83x) |       30.736    (6.02x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.152    (1.00x) |       54.982   (47.74x) |       25.190   (21.87x) |        5.451    (4.73x) |        6.965    (6.05x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.586    (1.00x) |       22.117   (37.76x) |        9.323   (15.92x) |        2.439    (4.16x) |        2.826    (4.83x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.296    (1.00x) |        8.431   (28.49x) |        3.603   (12.18x) |        0.993    (3.35x) |        1.178    (3.98x) |
| ./happy_recon/happy_vrip.ply                |      125.395    (1.00x) |     5732.758   (45.72x) |     2665.241   (21.25x) |      588.167    (4.69x) |      767.400    (6.12x) |
| ./happy_recon/happy_vrip_res2.ply           |       33.119    (1.00x) |     1538.012   (46.44x) |      707.122   (21.35x) |      157.700    (4.76x) |      201.326    (6.08x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.326    (1.00x) |      346.469   (47.29x) |      158.287   (21.61x) |       34.795    (4.75x) |       44.924    (6.13x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.623    (1.00x) |       77.290   (47.64x) |       36.082   (22.24x) |        7.663    (4.72x) |        9.404    (5.80x) |
| ./lucy/lucy.ply                             |     1053.088    (1.00x) |     8913.652    (8.46x) |     6447.129    (6.12x) |     4263.176    (4.05x) |     1064.243    (1.01x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      267.558    (1.00x) |     2274.750    (8.50x) |     1625.309    (6.07x) |     1097.358    (4.10x) |      274.140    (1.02x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      181.235    (1.00x) |     1579.976    (8.72x) |     1195.038    (6.59x) |      712.965    (3.93x) |      169.068    (0.93x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      370.011    (1.00x) |     3154.472    (8.53x) |     2245.363    (6.07x) |     1513.785    (4.09x) |      379.385    (1.03x) |
| Overall Total                               |     2194.756    (1.00x) |    30304.422   (13.81x) |    18171.008    (8.28x) |     9102.821    (4.15x) |     3794.090    (1.73x) |
