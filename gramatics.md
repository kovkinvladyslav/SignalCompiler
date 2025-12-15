```
1. <signal-program> --> <program>
2. <program> --> PROGRAM <procedure-identifier> ; <block> ;
3. <block> --> <declarations> BEGIN <statements-list> END
4. <statements-list> --> <empty>
5. <declarations> --> <procedure-declarations>
6. <procedure-declarations> --> <procedure> <proceduredeclarations> | <empty>
7. <procedure> --> PROCEDURE <procedure-identifier><parameters-list> ;
8. <parameters-list> --> ( <declarations-list> ) | <empty>
9. <declarations-list> --> <declaration> <declarationslist> | <empty>
10. <declaration> --><variable-identifier><identifierslist>:<attribute><attributes-list> ;
11. <identifiers-list> --> , <variable-identifier><identifiers-list> | <empty>
12. <attributes-list> --> <attribute> <attributes-list> | <empty>
13. <attribute> --> SIGNAL | COMPLEX | INTEGER | FLOAT | BLOCKFLOAT | EXT
14. <variable-identifier> --> <identifier>
15. <procedure-identifier> --> <identifier>
16. <identifier> --> <letter><string>
17. <string> --> <letter><string> | <digit><string> | <empty>
18. <digit> --> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
19. <letter> --> A | B | C | D | ... | Z
```
