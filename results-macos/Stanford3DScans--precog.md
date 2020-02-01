* Command Line: `/Users/vilya/Code/ply-parsing-perf/build-release/ply-parsing-perf --transposed --slowdown --quiet --precognition allplyfiles.txt -o /Users/vilya/Code/ply-parsing-perf/results-macos/Stanford3DScans--precog.md`
* Current Directory: `/Users/vilya/Models/Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |        9.094    (1.00x) |       86.098    (9.47x) |       39.172    (4.31x) |       47.405    (5.21x) |       11.307    (1.24x) |
| ./bunny/reconstruction/bun_zipper.ply       |       10.072    (1.00x) |      261.452   (25.96x) |      124.616   (12.37x) |       32.932    (3.27x) |       28.411    (2.82x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.193    (1.00x) |       58.690   (26.76x) |       34.480   (15.72x) |        7.522    (3.43x) |        6.425    (2.93x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.533    (1.00x) |       13.887   (26.08x) |        6.545   (12.29x) |        1.795    (3.37x) |        1.638    (3.07x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.146    (1.00x) |        3.348   (23.01x) |        1.585   (10.89x) |        0.442    (3.04x) |        0.389    (2.67x) |
| ./dragon_recon/dragon_vrip.ply              |      105.624    (1.00x) |     2798.972   (26.50x) |     1408.846   (13.34x) |      343.063    (3.25x) |      316.954    (3.00x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       22.614    (1.00x) |      621.331   (27.47x) |      324.500   (14.35x) |       80.067    (3.54x) |       71.565    (3.16x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        5.126    (1.00x) |      144.035   (28.10x) |       74.965   (14.62x) |       18.851    (3.68x) |       16.357    (3.19x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.221    (1.00x) |       32.285   (26.45x) |       17.483   (14.32x) |        4.132    (3.38x) |        3.738    (3.06x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.511    (1.00x) |       12.676   (24.81x) |        6.513   (12.75x) |        1.667    (3.26x) |        1.463    (2.86x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.209    (1.00x) |        4.866   (23.26x) |        2.381   (11.38x) |        0.642    (3.07x) |        0.583    (2.79x) |
| ./happy_recon/happy_vrip.ply                |      133.971    (1.00x) |     3468.861   (25.89x) |     1709.679   (12.76x) |      423.083    (3.16x) |      404.770    (3.02x) |
| ./happy_recon/happy_vrip_res2.ply           |       33.789    (1.00x) |      905.632   (26.80x) |      452.085   (13.38x) |      112.970    (3.34x) |      104.525    (3.09x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.839    (1.00x) |      205.352   (26.20x) |      101.900   (13.00x) |       25.628    (3.27x) |       23.432    (2.99x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.713    (1.00x) |       45.471   (26.54x) |       22.756   (13.28x) |        5.711    (3.33x) |        5.243    (3.06x) |
| ./lucy/lucy.ply                             |     1006.694    (1.00x) |     6801.919    (6.76x) |     2589.559    (2.57x) |     3538.768    (3.52x) |     1089.835    (1.08x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      192.200    (1.00x) |     1660.409    (8.64x) |      631.857    (3.29x) |      842.423    (4.38x) |      232.419    (1.21x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      118.284    (1.00x) |     1091.825    (9.23x) |      473.763    (4.01x) |      581.504    (4.92x) |      134.983    (1.14x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      272.895    (1.00x) |     2379.872    (8.72x) |      862.235    (3.16x) |     1196.539    (4.38x) |      395.643    (1.45x) |
| Overall Total                               |     1924.726    (1.00x) |    20596.981   (10.70x) |     8884.919    (4.62x) |     7265.146    (3.77x) |     2849.680    (1.48x) |
