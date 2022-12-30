TODO :
- parse_node_position equivalent for preprocessor ?? or no need ? rename parse_node_position ? also this do not seem to incr new_line for ocmpilation step, only column seems ok
- CPP ext, trigger error on compile but not on preprocessing
- maybe add an on_preprocess and on_compile within ext to alter ctx once before compiler_all and preprocess_all ? 
    or maybe just empty preprocessors
- maybe rename ctx_clone into smth like ctx_save_save_for_ast_node 
- add more info such as name (maybe language and deps) etc for preprocessors / compilers ? 
- add excplicit dependencies per ext (maybe per preprocessors / compilers ?)
- compiler_destroy & leaks, correct exits on error
- static library for compiler
- target language ??