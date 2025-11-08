/**
	Initially used double pointer sliding frame algorithm. Really only need single pointer.

	should run O(n) after algorithm simplification and dependent on point distance calculation
*/
---------------------------------------------
0_._|_._1_._|_._2_._|_._3_._|_._ ...        
 x      xx   x  x    x
^
VAL

idx = -1
val = 0

	```
	idx == -1 
	idx = val
	```
idx = 0
val = 0
----------------------------------------------

0_._|_._1_._|_._2_._|_._3_._|_._ ...        
 x      xx   x  x    x
^		^
idx		VAL

idx = 0
val = 1

	```
	// perform interval calculation on points in character range
	idx = val
	```

idx = 1
val = 1
----------------------------------------------
0_._|_._1_._|_._2_._|_._3_._|_._ ...        
 x      xx   x  x    x
		^		^
		idx		VAL

l_idx = 1
val = 2

	```
	// perform interval calculation on points in character range
	idx = val
	```

idx = 2
val = 2