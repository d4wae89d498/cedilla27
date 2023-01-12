
#ifndef CONFIG_EXT_POSITION_H
# define CONFIG_EXT_POSITION_H

# define NEW_LINE               "\n"
# define TAB                    "\t"
# define TAB_LENGTH             4

# define IS_NEW_LINE(STR)       str_is_prefixed(STR, NEW_LINE)
# define IS_TAB(STR)            str_is_prefixed(STR, TAB)
# define IS_SPACE(STR)          isspace(*STR)             

#endif