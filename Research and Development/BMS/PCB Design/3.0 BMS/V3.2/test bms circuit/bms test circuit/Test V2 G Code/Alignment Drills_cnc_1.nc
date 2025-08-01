(G-CODE GENERATED BY FLATCAM v8.994 - www.flatcam.org - Version Date: 2020/11/7)
(Name: Alignment Drills_cnc)
(Type: G-code from Geometry)
(Units: MM)
(Created on Tuesday, 09 July 2024 at 16:39)
(This preprocessor is the default preprocessor used by FlatCAM.)
(It is made to work with MACH3 compatible motion controllers.)
(TOOLS DIAMETER: )
(Tool: 1 -> Dia: 3.0)
(FEEDRATE Z: )
(Tool: 1 -> Feedrate: 300)
(FEEDRATE RAPIDS: )
(Tool: 1 -> Feedrate Rapids: 1500)
(Z_CUT: )
(Tool: 1 -> Z_Cut: -8.0)
(Tools Offset: )
(Tool: 1 -> Offset Z: 0.0)
(Z_MOVE: )
(Tool: 1 -> Z_Move: 2)
(Z Toolchange: 15 mm)
(X,Y Toolchange: 0.0000, 0.0000 mm)
(Z Start: None mm)
(Z End: 0.5 mm)
(X,Y End: None mm)
(Steps per circle: 64)
(Preprocessor Excellon: default)
(X range:   -5.5000 ...  105.5000  mm)
(Y range:    1.5000 ...   60.5460  mm)
(Spindle Speed: 10000 RPM)
G21
G90
G94
G01 F300.00
M5
G00 Z15.0000
T1
G00 X0.0000 Y0.0000
G00 Z15.0000
G01 F300.00
M03 S10000
G00 X-4.0000 Y3.0000
G01 Z-8.0000
G01 Z0
G00 Z2.0000
G00 X-4.0000 Y59.0460
G01 Z-8.0000
G01 Z0
G00 Z2.0000
G00 X104.0000 Y59.0460
G01 Z-8.0000
G01 Z0
G00 Z2.0000
G00 X104.0000 Y3.0000
G01 Z-8.0000
G01 Z0
G00 Z2.0000
M05
G00 Z0.50
