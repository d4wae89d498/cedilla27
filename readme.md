TODO :
- [x]  parse_node_position equivalent for preprocessor ?? -> choix ds les implemantation des preprocesseurs 
- [x]  rename parse_node_position ->  ? also 
- [x?] parse_node_position do not seem to incr new_line for ocmpilation step, only column seems ok
- [x?] CPP ext, trigger error on compile but not on preprocessing
- [no] maybe add an on_preprocess and on_compile within ext to alter ctx once before compiler_all and preprocess_all ? 
  [ ]  or maybe just empty preprocessors
- [WIP]  add more info such as name (maybe language and deps) etc for preprocessors / compilers ? 
        -> meta ext
- [WIP] add excplicit dependencies per ext (maybe per preprocessors / compilers ?)
- compiler_destroy & leaks, correct exits on error
- static library for compiler
- target language ?? --> depands on compiler exts ? (or per compiler?)