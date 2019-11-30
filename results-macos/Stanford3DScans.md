* Command Line: `/Users/vilya/Code/ply-parsing-perf/build-release/ply-parsing-perf --slowdown --quiet -o results.md allplyfiles.txt`
* Current Directory: `/Users/vilya/Models/Stanford3DScans`

| Filename                                    |      miniply (Slowdown) |       happly (Slowdown) |      tinyply (Slowdown) |         rply (Slowdown) |      msh_ply (Slowdown) |
| :------------------------------------------ | ----------------------: | ----------------------: | ----------------------: | ----------------------: | ----------------------: |
| ./armadillo/Armadillo.ply                   |       22.619    (1.00x) |       86.153    (3.81x) |       64.375    (2.85x) |       41.306    (1.83x) |       failed            |
| ./bunny/reconstruction/bun_zipper.ply       |        9.497    (1.00x) |      262.537   (27.64x) |      171.949   (18.11x) |       34.106    (3.59x) |       30.584    (3.22x) |
| ./bunny/reconstruction/bun_zipper_res2.ply  |        2.034    (1.00x) |       60.319   (29.65x) |       38.461   (18.91x) |        7.597    (3.73x) |        6.856    (3.37x) |
| ./bunny/reconstruction/bun_zipper_res3.ply  |        0.497    (1.00x) |       13.930   (28.04x) |        8.990   (18.10x) |        1.804    (3.63x) |        1.658    (3.34x) |
| ./bunny/reconstruction/bun_zipper_res4.ply  |        0.128    (1.00x) |        3.367   (26.23x) |        2.205   (17.18x) |        0.457    (3.56x) |        0.425    (3.31x) |
| ./dragon_recon/dragon_vrip.ply              |       99.416    (1.00x) |     2745.001   (27.61x) |     1904.920   (19.16x) |      356.336    (3.58x) |      346.049    (3.48x) |
| ./dragon_recon/dragon_vrip_res2.ply         |       20.751    (1.00x) |      616.280   (29.70x) |      435.672   (20.99x) |       82.527    (3.98x) |       76.742    (3.70x) |
| ./dragon_recon/dragon_vrip_res3.ply         |        4.930    (1.00x) |      145.478   (29.51x) |      101.973   (20.68x) |       18.664    (3.79x) |       17.673    (3.58x) |
| ./dragon_recon/dragon_vrip_res4.ply         |        1.093    (1.00x) |       32.970   (30.18x) |       23.577   (21.58x) |        4.246    (3.89x) |        4.073    (3.73x) |
| ./drill/reconstruction/drill_shaft_vrip.ply |        0.447    (1.00x) |       12.290   (27.48x) |        8.473   (18.94x) |        1.688    (3.77x) |        1.585    (3.54x) |
| ./drill/reconstruction/drill_shaft_zip.ply  |        0.173    (1.00x) |        4.870   (28.17x) |        3.460   (20.01x) |        0.651    (3.77x) |        0.607    (3.51x) |
| ./happy_recon/happy_vrip.ply                |      125.189    (1.00x) |     3438.107   (27.46x) |     2381.024   (19.02x) |      445.387    (3.56x) |      434.216    (3.47x) |
| ./happy_recon/happy_vrip_res2.ply           |       29.511    (1.00x) |      916.346   (31.05x) |      637.535   (21.60x) |      118.128    (4.00x) |      113.504    (3.85x) |
| ./happy_recon/happy_vrip_res3.ply           |        7.511    (1.00x) |      201.138   (26.78x) |      143.149   (19.06x) |       27.247    (3.63x) |       25.346    (3.37x) |
| ./happy_recon/happy_vrip_res4.ply           |        1.500    (1.00x) |       45.731   (30.48x) |       32.157   (21.43x) |        5.983    (3.99x) |        5.648    (3.76x) |
| ./lucy/lucy.ply                             |     1621.105    (1.00x) |     6629.960    (4.09x) |     4540.166    (2.80x) |     3356.027    (2.07x) |     4126.266    (2.55x) |
| ./xyzrgb/xyzrgb_dragon.ply                  |      311.079    (1.00x) |     1620.613    (5.21x) |     1091.936    (3.51x) |      815.680    (2.62x) |      975.076    (3.13x) |
| ./xyzrgb/xyzrgb_manuscript.ply              |      222.400    (1.00x) |     1098.372    (4.94x) |      864.681    (3.89x) |      561.593    (2.53x) |      587.935    (2.64x) |
| ./xyzrgb/xyzrgb_statuette.ply               |      518.610    (1.00x) |     2235.564    (4.31x) |     1502.632    (2.90x) |     1192.202    (2.30x) |     1394.228    (2.69x) |
| Overall Total                               |     2998.491    (1.00x) |    20169.027    (6.73x) |    13957.332    (4.65x) |     7071.629    (2.36x) |     8148.622    (2.72x) |
