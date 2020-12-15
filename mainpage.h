/**
* @mainpage
* @section intro Einleitung
* Es soll ein Generator von Wahrheitstabellen für Attrbibute und Operationen 
* der Boolschen Algebra implementiert werden. Die Boolschen Operationen 
* - Negation    __NOT__: '!' (entspr. C/C#/C++/Java/... Nicht-Operator)
* - Konjunktion __AND__: '&' (entspr. C/C#/C++/Java/... bitweisem UND)
* - Disjunktion __OR__:  'v' (entspr. 'ODER' der Aussagenlogik, wird hier zur besseren Unterscheidung zu Trennsymbol '|' verwendet)
* 
* sollen als mit ein (NOT) bzw. zwei (OR, AND) einfachen oder komplexen Operanden 
* als <i>Abstrakter Datentyp</i> realisiert werden. Als Werte werden `0` für `FALSCH` und `1` für `TRUE` verwendet.
* 
* Für die Operanden soll ebenfalls ein ADT erstellt werden, mit dem die Art der
* Operanden (einfach oder komplex) vereinheitlicht wird. 
*
* @section example Beispiel
* Die Operation `A & B v C` liefert die Wahrheitstabelle
* | A | B | C | A & B | ( A & B) v C |
* |:-:|:-:|:-:|:-----:|:------------:|
* | 0 | 0 | 0 |   0   |       0      |
* | 0 | 1 | 1 |   0   |       1      |
* | 0 | 1 | 0 |   0   |       0      |
* | 1 | 0 | 1 |   0   |       1      |
* | 1 | 0 | 0 |   0   |       0      |
* | 1 | 1 | 1 |   1   |       1      |
* | 1 | 1 | 0 |   1   |       1      |
* \n
* wobei 
* - `A`, `B` und `C` jeweils einfache Operanden
* - `A & B` als auch `( A & B) v C` Terme sind
* - wobei `(A & B)` ein komplexer Operand des Terms `( A & B) v C` ist.
* 
* D.h. Terme können Operanden anderer Terme sein.
* 
* @code
*  
* BoolTerm a_and_b =      bt_get_simple_term('A', AND, 'B');
* BoolTerm a_and_b_or_c = bt_get_complex_term_left(a_and_b, OR, 'C');
* print_table(a_and_b_or_c);
*  
* @endcode
*
* @section assignment Aufgabe
* -# Definieren Sie das `enum` `Operation` zur Identifikation der Operation
* mit den Werten **INVALID**, **NOT**, **AND**, **OR**.
* -# Erstellen Sie die forward-Deklarationen für die ADTs `BoolOperand` und `BoolTerm`
* in den jeweiligen Header-Files, damit die Prototypen in den .h Dateien vom Compiler akzeptiert werden.
*   - **ADT `BoolOperand`** repräsentiert entweder einen einfachen Operanden, der als einbuchstabiger Label erfasst wird
* oder einen komplexen Operanden vom Typ `BoolTerm`. D.h. dieser ADT vereint beide Varianten in sich
*   - **ADT `BoolTerm`** repräsentiert einen Term bestehend aus einem (optionalem) linken und einem rechten Operanden
* sowie der Verknüpfungsoperation (aus Enum). 
* Der linke Operand wird auch für unäre Operationen (NOT) angegeben, er ist aber nicht erforderlich (-> optional).
*   .
* **Achtung:** Die beiden ADTs sind wechselseitig voneinander abhängig, das bedeutet dass sowohl
* bool_operand.h in Datei bool_term.h als auch bool_term.h in bool_operand.h inkludiert werden müssten.
* Dies führt jedoch zu Compilefehlern (Include-Cycles).\n
* __Abhilfe__ schafft  
*   -# ENTWEDER das Inkludieren des Header-Files in eine Richtung (zB bool_operand.h in bool_term.h aber nicht umgekehrt)\n
* UND die Forward-Deklaration des fehlenden Typs im Header File, welches das andere nicht inkludiert,
*   -# ODER die beiden Forward-Deklarationen in ein separates Header-File auszulagern, dass dann in BEIDEN
* Header-Files der ADTs inkludiert wird (_Achtung:_ Ergänzung im Makefile nicht vergessen).
* -# Erstellen bzw. vervollständigen Sie die minimalen Leerimplementierungen für alle erforderlichen Funktionen beider ADTs. \n
* -- **COMMIT** --
* -# Implementieren Sie die `structs` der beiden ADTs aus der Forward-Deklaration in den jeweiligen Source-Files (.cpp).\n
* -- **COMMIT** --
* -# Erstellen Sie je ein lokales Array in den jeweiligen Source-Files für eine Menge von Instancen der ADTs.
* Die maximale Anzahl der Instanzen von `BoolTerm` ist in 'config.h' (`MAX_TERMS`) definiert (verwenden statt kopieren!), 
* die maximale Anzahl der Instanzen von `BoolOperand` soll daraus abgeleitet werden 
* (Tipp: Jeder Term hat [maximal] 2 Operanden).\n
* -- **COMMIT** --
* -# Implementieren Sie alle fehlenden Elemente, damit das Gesamtprojekt kompiliert.\n
* -- **COMMIT** --
* -# Implementieren Sie sukzessive alle erforderlichen Funktionen, bis alle Unit Tests ein positives Ergebnis liefern.
* Einige Funktionen bauen aufeinander auf; achten Sie auf eine redunzanzfreie Implementierung (verwenden statt kopieren!)!
* Einige Funktionen werden Funktionen des jeweils anderen ADTs benötigen, verwenden Sie diese. \n
* -- **COMMIT nach jedem positivem UT** --
* -# Erstellen Sie in der Funktion `ui_branch()` im File `tt_gen_main_driver.cpp` mindestens folgende Ausdrücke 
* und geben Sie diese mittels `print_table(term)` aus `truth_table_gen.h` aus:
*   - !A
*   - !(!A)
*   - A & B
*   - A v B
*   - !(A & B)
*   - !(A v B)
*   - (!A & !B)
*   - (!A v !B)
*/