/* Token Types */
typedef enum { nulsym = 1, identsym, numbersym, plussym, minussym, 
    multsym, slashsym, oddsym, eqsym, neqsym, lessym, leqsym, 
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym, 
    periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
    whilesym, dosym, callsym, constsym, varsym, procsym, writesym, 
    readsym, elsesym 
} token_type;

/* Token structure */
typedef struct token {
    char *name;
    token_type type;
} token;