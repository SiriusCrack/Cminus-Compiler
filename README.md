# C-_Compiler

### TODO
#### Figure out all this Operator shit

Issue 1: Once you're at an operator node, you need to compare both sides for matching DataTypes. 

Issue 2: either side of an opnode just be another opnodes. its fucking opnodes all the way down dude

this can be solved by, on OpNode, enter new func that adds each side to the symTbl, then compares each side and prints error if something's bogus. if either side is an opnode, just recurse, and have the recurses return the DataType. at the root OpNode func call, we cease traversing opnode's children. this is maybe a big assumption that there will only be opnodes under opnodes, but it THINK its a fine assumption. ass time??
hey, worst case scenario (maybe), recursions under that opnodes call can just call WriteRefs again, which should solve the issue of it NOT being "fucking opnodes all the way down"

looks like we've solved recursion on either side, as long as it's just operators and ints. need to work on unary, which will probably just be a UnaryHandler() that recurses down, also accounting for Ops recursion and whatever else, just passing the datatype up as well. also need to add comparisons, which can also contain ops i suppose. probably just and CompHandler() that potentially recurses into OpHandler. *maybe* this should be consolidated into fewer functions? if so, that should be done after, when less pressed for time. for now, just put the top cases at the top (in WriteRefs()). we also need to account for calls with returntypes.this should just be adding the reference to the table, then finding what it references, then passing its decl's datatype up.