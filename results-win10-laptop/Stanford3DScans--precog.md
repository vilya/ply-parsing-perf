* Command Line: `C:\Users\vilya\Code\ply-parsing-perf\build-release\ply-parsing-perf.exe --transposed --slowdown --quiet --precognition allplyfiles.txt -o C:/Users/vilya/Code/ply-parsing-perf/results-win10-laptop/Stanford3DScans--precog.md`
* Current Directory: `C:\Users\vilya\Models\Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       14.462    (1.00x) |      129.410    (8.95x) |       84.549    (5.85x) |       64.654    (4.47x) |       14.429    (1.00x) |
| ./bunny/reconstruction/bun_zipper.ply       |       10.507    (1.00x) |      484.420   (46.11x) |      197.211   (18.77x) |       53.650    (5.11x) |       66.340    (6.31x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.686    (1.00x) |      109.923   (40.92x) |       62.155   (23.14x) |       11.871    (4.42x) |       14.471    (5.39x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.700    (1.00x) |       25.643   (36.65x) |       10.380   (14.84x) |        2.866    (4.10x) |        3.329    (4.76x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.269    (1.00x) |        6.031   (22.42x) |        2.693   (10.01x) |        0.717    (2.66x) |        0.836    (3.11x) |
| ./dragon_recon/dragon_vrip.ply              |      106.303    (1.00x) |     5006.284   (47.09x) |     2306.339   (21.70x) |      506.058    (4.76x) |      651.419    (6.13x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       24.131    (1.00x) |     1167.502   (48.38x) |      545.480   (22.60x) |      121.757    (5.05x) |      145.836    (6.04x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        5.565    (1.00x) |      263.479   (47.35x) |      125.874   (22.62x) |       25.528    (4.59x) |       33.834    (6.08x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.330    (1.00x) |       59.985   (45.09x) |       27.485   (20.66x) |        5.664    (4.26x) |        7.442    (5.59x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.749    (1.00x) |       30.977   (41.38x) |        9.899   (13.22x) |        2.467    (3.29x) |        3.030    (4.05x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.298    (1.00x) |        9.110   (30.55x) |        3.956   (13.27x) |        1.061    (3.56x) |        1.280    (4.29x) |
| ./happy_recon/happy_vrip.ply                |      129.702    (1.00x) |     6315.248   (48.69x) |     2935.423   (22.63x) |      627.033    (4.83x) |      814.497    (6.28x) |
| ./happy_recon/happy_vrip_res2.ply           |       34.999    (1.00x) |     1688.686   (48.25x) |      785.668   (22.45x) |      175.955    (5.03x) |      224.105    (6.40x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.829    (1.00x) |      406.453   (51.91x) |      173.231   (22.13x) |       38.484    (4.92x) |       49.306    (6.30x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.815    (1.00x) |       95.114   (52.42x) |       43.536   (23.99x) |        8.782    (4.84x) |       10.108    (5.57x) |
| ./lucy/lucy.ply                             |     1118.861    (1.00x) |     9716.475    (8.68x) |     4975.488    (4.45x) |     4635.917    (4.14x) |     1122.423    (1.00x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      289.022    (1.00x) |     2505.991    (8.67x) |     1336.422    (4.62x) |     1186.083    (4.10x) |      293.483    (1.02x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      190.113    (1.00x) |     1675.338    (8.81x) |     1010.603    (5.32x) |      765.278    (4.03x) |      181.677    (0.96x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      394.465    (1.00x) |     3388.533    (8.59x) |     1837.394    (4.66x) |     1633.952    (4.14x) |      398.219    (1.01x) |
| Overall Total                               |     2333.806    (1.00x) |    33084.601   (14.18x) |    16473.786    (7.06x) |     9867.777    (4.23x) |     4036.066    (1.73x) |
