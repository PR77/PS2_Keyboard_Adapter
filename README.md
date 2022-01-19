# PS2_Keyboard_Adapter
PS2 Keyboard Interface based on the ATTiny with Arduino framework

# Warning
This design has not been compliance tested and will not be. It may cause damage to your Amiga. I take no responsibility for this. I accept no responsibility for any damage to any equipment that results from the use of this design and its components. IT IS ENTIRELY AT YOUR OWN RISK!

# Overview
The main purpose of this design is to provide basic PS2 Keyboard support to an Amiga. It is developed using the Arduino framework to keep the design very simple.

### Appearance
Installed in A600:
![Installation](/Images/InstalledInA600.jpg)

### Design
Schematics will be published - once drawn. The design is very simple and only basic connections for the PS/2 Keyboard and Amiga are required. For the A600 / A1200 Version (pictured above) I used a NPN with 3 signal diodes forward biased wrt. the keyboard controller inputs to assert the /KBRESET signal.