# C-_Compiler

### TODO
#### Figure out all this Operator shit

Issue 1: Once you're at an operator node, you need to compare both sides for matching DataTypes. 

Issue 2: either side of an opnode just be another opnodes. its fucking opnodes all the way down dude

this can be solved by, on OpNode, enter new func that adds each side to the symTbl, then compares each side and prints error if something's bogus. if either side is an opnode, just recurse, and have the recurses return the DataType. at the root OpNode func call, we cease traversing opnode's children. this is maybe a big assumption that there will only be opnodes under opnodes, but it THINK its a fine assumption. ass time??
hey, worst case scenario (maybe), recursions under that opnodes call can just call WriteRefs again, which should solve the issue of it NOT being "fucking opnodes all the way down"