# C-_Compiler

### TODO
#### Determine if a var has been assigned

Part of this is I think we dont care if parms were assigned? we'll deal with that later.
For now we'll need to check if things have been assigned. adding an assignflag to the nodes and setting it whenever we come across n assign flag should let us know if Decls have been assigned. is this the only time things are assigned? maybe. we'll see.
also need to add an error for "accessed non-assigned thing" maybe just any time its added to scope, if it's added and still not assigned, error?