# C-_Compiler

### TODO
#### AddEntryToScope currently checks lineNum for duplicates. this doesnt work, esp bc declLists.

need to find a way to check stuff against table. avoiding string compares would be cool? one option maybe is unique IDs? but how would we translate a referenced var back to the same UID? still strcmps. maybe strcmps to check? but thats like a whole 2nd symtbl. answer might just be to compare each fucking string every time. might be good to just remove duplicate check from AddEntryToScope and just never add a duplicate?

currently implemented solution is just add everything regardless of duplicates. we'll see how it goes.

#### Also need to figure out how to deal w vars that are in scope bc theyre in a parent, but not in a particular scope table

One solution: putting a duplicate decl entry in every child scope. tried to do this and came across some bug with entries ending up in parent scopes somehow, ended up just giving up. if we could get this to work, it could possibly make recursion easier?

Solution Two: just treat parent entries as being present in nested scopes somehow. this seems to be how everyone else does it. I guess the solution here would be to do a first-pass where scopes and decls are written (this is already mostly implemented) then do a second pass where entires for references are added to the tables. this would involve going through the tree, traversing the scopes at the same time, then finding a potential entry, then somehow re-traversing the symTbl back to where you are, checking for decls all along the way. the re-traverse sounds especially difficult. an easier method (i think the provided code deals with this by using stacks) might be to add back-pointers in the symTbl tree. this way once we find a potential entry, you just start backtracking from the current scope, up. then once a Decl is found, kill the search and point the new entry to that first decl. 

Both these solutions are still extremely slow requiring strcmps for every entry it checks. makes coding easier though. solution is probably to just do the strcmps and try to come up with another solution once the assgn is finished.
