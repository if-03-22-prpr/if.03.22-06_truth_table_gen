/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: n/a
 * ---------------------------------------------------------
 * Exercise Number: 08
 * Title:			tt_gen.cpp
 * Author:			S. Schraml
 * Due Date:		n/a
 * ----------------------------------------------------------
 * Description:
 * Implementation of tt_gen.h.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "truth_table_gen.h"
#include "config.h"

#define COL_COUNT MAX_TERMS * 2 + 1

typedef char Label[64];
typedef Label TableRow[COL_COUNT];
typedef int   TableColWidths[COL_COUNT];

struct TableImpl {
    TableRow       label_row;
    TableColWidths col_widths;
    BoolOperand operands[COL_COUNT];
    BoolTerm    terms[COL_COUNT];
    int  operand_cnt;
    int  total_row_width;
    int  col_cnt;
    char col_sep;
    char row_start[4];

};
static struct TableImpl table = {0};

/* Forward declarations */
void _compose_term_caption(Label label, BoolTerm term);

int _place_operands(BoolTerm term, int op_idx);
int _place_terms(BoolTerm term, int term_idx);
int _place_operand_values(BoolTerm term, int col_idx);
int _place_term_values(BoolTerm term, int col_idx);

/** Initializes the table data */
void _init_table() {
    for (int i = 0; i < COL_COUNT; i++) {
        table.label_row[i][0] = '\0';
        table.col_widths[i] = 0;
        table.operands[i] = 0;
        table.terms[i] = 0;
    }
    table.operand_cnt = 0;
    table.total_row_width = 0;
    table.col_cnt = 0;
    table.col_sep = '|';
    sprintf(table.row_start, " |");
}

/** Calculates the width of a row and each column for the given number of columns. */
void _calc_table_widths(int col_cnt) {
    table.total_row_width = 0;
    for (int i = 0; i < col_cnt; i++) {
        table.col_widths[i] = 2 + strlen(table.label_row[i]); /* left and right blanks + caption width */
        table.total_row_width += table.col_widths[i] + 1; /* + sep char */
    }
}

/* Composes the caption of a simple or complex operand */
void _compose_operand_caption(Label label, BoolOperand operand) {
    label[0] = '\0';
    if (bo_is_valid(operand)) {
        if (bo_is_simple(operand)) {
            sprintf(label, "%c", bo_get_label(operand));
        } else {
            Label caption;
            _compose_term_caption(caption, bo_get_term(operand));
            sprintf(label, "(%s)", caption);
        }
    }
}

/* Composes the caption of a term */
void _compose_term_caption(Label label, BoolTerm term) {
    if (bt_is_valid(term)) {
        Label left_op_caption;
        Label right_op_caption;
        _compose_operand_caption(right_op_caption, bt_get_right_operand(term));
        if (bt_get_operation(term) == NOT) {
            sprintf(label, "!%s", right_op_caption);
        } else {
            char op_chr = '?';
            switch (bt_get_operation(term)) {
                case AND: op_chr = '&'; break;
                case OR:  op_chr = 'v'; break;
                case NOT: /* fall-through by intension */
                case INVALID:
                    op_chr = '?'; /* should never be entered */
                    break;
            }
            _compose_operand_caption(left_op_caption, bt_get_left_operand(term));
            sprintf(label, "%s %c %s", left_op_caption, op_chr, right_op_caption);
        }
    }
}


/** 
 * Associates the all direct and indirect simple operands to the table 
 * from the given index on and return the next index.
 */
int _place_operand(BoolOperand operand, int op_idx) {
    if (bo_is_valid(operand)) {
        if (bo_is_simple(operand) && op_idx < COL_COUNT) {
            table.operands[op_idx] = operand;
            op_idx++;
        } else {
            op_idx = _place_operands(bo_get_term(operand), op_idx);
        }
    }
    return op_idx;
}

/** 
 * Associates the all direct and indirect simple operands to the table 
 * from the given index on and return the next index.
 */
int _place_operands(BoolTerm term, int op_idx) {
    if (bt_is_valid(term)) {
        /** apply all simple left operands recursively. */
        if (bt_get_operation(term) != NOT) {
            op_idx = _place_operand(bt_get_left_operand(term), op_idx);
        }
        /** apply all simple right operands recursively. */
        op_idx = _place_operand(bt_get_right_operand(term), op_idx);
    }
    return op_idx;
}

/** 
 * Associates the terms of all direct and indirect complex operands to the table 
 * from the given index on and return the next index.
 */
int _place_term(BoolOperand operand, int term_idx) {
    if (bo_is_valid(operand) && !bo_is_simple(operand)) {
        term_idx = _place_terms(bo_get_term(operand), term_idx);
    }
    return term_idx;
}

/** 
 * Associates the terms of all direct and indirect complex operands to the table 
 * from the given index on and return the next index.
 */
int _place_terms(BoolTerm term, int term_idx) {
    if (bt_is_valid(term)) {
        /** apply all left complex operands recursively. */
        if (bt_get_operation(term) != NOT) {
            term_idx = _place_term(bt_get_left_operand(term), term_idx);
        }
        /** apply all right complex operands recursively. */
        term_idx = _place_term(bt_get_right_operand(term), term_idx);

        if (term_idx < COL_COUNT) {
            /** eventually, associate the the term. */
            table.terms[term_idx] = term;
            term_idx ++;
        }
    }
    return term_idx;
}

/** 
 * Adds the captions of all simple and complex operands of the given term to 
 * the table.row and stores the column count inside the table.
 */
void _place_operands_and_terms(BoolTerm term) {
    if (bt_is_valid(term)) {
        /** apply all simple operands recursively. */
        table.operand_cnt = _place_operands(term, 0);
        /** apply the cpations of all complex operands and this term recursively. */
        int term_cnt = _place_terms(term, 0);
        table.col_cnt = table.operand_cnt + term_cnt;
    }
}

void _generate_captions() {
    int col_idx = 0;
    while (col_idx < table.operand_cnt) {
        _compose_operand_caption(table.label_row[col_idx], table.operands[col_idx]);
        col_idx ++;
    }
    while (col_idx < table.col_cnt) {
        _compose_term_caption(table.label_row[col_idx], table.terms[col_idx - table.operand_cnt]);
        col_idx ++;
    }
}

/* Applies the values to all simple operands for the row of the given index. */
void _load_operands(int row_idx) {
    bool value = false;
    for (int idx = 0; idx < table.operand_cnt; idx++) {
        int exp = table.operand_cnt -1 - idx;
        value = (row_idx / (int)pow(2, exp)) % 2;
        bo_set_value(table.operands[idx], value);
    }
}

/** Prints the given char for a 'count' times. */
void _print_padding(char ch, int count) {
    for (int i = 0; i < count; i++) {
        printf("%c", ch);
    }
}

/** Prints a line with the width of table using the given character */
void _print_table_line(char ch) {
    printf("%s", table.row_start);
    _print_padding(ch, table.total_row_width - 1);
    printf("%c\n", table.col_sep);
}

/** Prints a table row sepeartion line with the given character */
void _print_separator_line(char ch) {
    printf("%s", table.row_start);
    for (int i = 0; i < table.col_cnt; i++) {
        _print_padding(ch, table.col_widths[i]);
        printf("%c", table.col_sep);
    }
    printf("\n");
}

/** Prints the header of the table that has the given number of columns. */
void _print_table_header() {
    _calc_table_widths(table.col_cnt);

    /* prints the top border */
    _print_table_line('=');

    /* prints the column captions */
    printf("%s", table.row_start);
    for (int i = 0; i < table.col_cnt; i++) {
        printf(" %s %c", table.label_row[i], table.col_sep);
    }
    printf("\n");

    /* prints the clomn caption separator line */
    _print_separator_line('-');
}

/* Prints the value of a single cell including the right border. */
void _print_value_cell(int col_idx, bool value) {
    int pre_cnt = table.col_widths[col_idx] / 2;
    _print_padding(' ', pre_cnt);
    printf("%c", (value ? '1' : '0'));
    _print_padding(' ', table.col_widths[col_idx] - pre_cnt - 1);
    printf("%c", table.col_sep);
}

/* Prints the table row of current values. */
void _print_value_row() {
    printf("%s", table.row_start);
    int col_idx = 0;
    while (col_idx < table.operand_cnt) {
        _print_value_cell(col_idx, bo_get_value(table.operands[col_idx]));
        col_idx ++;
    }
    while (col_idx < table.col_cnt) {
        _print_value_cell(col_idx, bt_get_value(table.terms[col_idx - table.operand_cnt]));
        col_idx ++;
    }
    printf("\n");
}

void print_table(BoolTerm term) {
    _init_table();
    _place_operands_and_terms(term);

    /* generate row captions and print the table header*/
    _generate_captions();
    printf("\n\nTruth table for %s:\n", table.label_row[table.col_cnt - 1]);
    _print_table_header();

    /* prints all value rows */
    int lines = pow(2, table.operand_cnt);
    for (int row_idx = 0; row_idx < lines; row_idx++) {
        _load_operands(row_idx);
        _print_value_row();
    }

    /* prints the bottom border */
    _print_table_line('=');
    printf("\n");
}

