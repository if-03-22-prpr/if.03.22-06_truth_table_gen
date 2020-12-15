/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: 08
 * Title:			Implementation of UTs for Boolean Operand
 * Author:			S. Schraml
 * Due Date:		n/a
 * ----------------------------------------------------------
 * Description:
 * Test functions for ADT BoolTerm.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

#include "test_bool_term.h"
#include "shortcut.h"
#include "config.h"
#include "bool_operand.h"
#include "bool_term.h"


/* note: 'const' in 'const char*' is NOT a valid C keyword.
   But unit test framework requires C++ compiler, which warns about non-const strings */


#define ASSERT_VALID_TERM(term) assert_valid_term(tc, term)
void assert_valid_term(struct TestCase* tc, BoolTerm term) {
	ASSERT_TRUE(term != 0, "Term expected");
	ASSERT_TRUE(bt_is_valid(term), "Valid term expected");
}

#define ASSERT_VALID_SIMPLE_OPERAND(opd, label, side) assert_valid_simple_operand(tc, opd, label, side)
void assert_valid_simple_operand(struct TestCase* tc, BoolOperand opd, char label, const char* side) {
	char msg[64];
	sprintf(msg, "Valid %s operand expected", side);
	ASSERT_TRUE(bo_is_valid(opd), msg);
	sprintf(msg, "Simple %s operand expected", side);
	ASSERT_TRUE(bo_is_simple(opd), msg);
	sprintf(msg, "%s operand label mismatch", side);
	ASSERT_TRUE(bo_get_label(opd) == label, msg);
}

#define ASSERT_VALID_COMPLEX_OPERAND(opd, term, side) assert_valid_complex_operand(tc, opd, term, side)
void assert_valid_complex_operand(struct TestCase* tc, BoolOperand opd, BoolTerm term, const char* side) {
	char msg[64];
	sprintf(msg, "Valid %s operand expected", side);
	ASSERT_TRUE(bo_is_valid(opd), msg);
	sprintf(msg, "Complex %s operand expected", side);
	ASSERT_TRUE(!bo_is_simple(opd), msg);
	sprintf(msg, "%s operand term mismatch", side);
	ASSERT_TRUE(bo_get_term(opd) == term, msg);
}

#define ASSERT_INVALID_OPERAND(opd, side) assert_invalid_operand(tc, opd, side)
void assert_invalid_operand(struct TestCase* tc, BoolOperand opd, const char* side) {
	char msg[64];
	sprintf(msg, "Invalid %s operand expected", side);
	ASSERT_TRUE(!bo_is_valid(opd), "Invalid left operand expected");
}

#define GET_VALID_SIMPLE_TERM(label_left, op, label_right) get_valid_simple_term(tc, label_left, op, label_right)
BoolTerm get_valid_simple_term(struct TestCase* tc, char label_left, Operation op, const char label_right) {
	BoolTerm term = bt_get_simple_term(label_left, op, label_right);
	ASSERT_VALID_TERM(term);
	return term;
}

/* ==================================================================== */

TEST(test_bt_reset__shall_not_get_more_than_all_terms)
{
	char msg[128];
	BoolTerm term = 0;

	bt_reset();
	for (int i = 0; i < MAX_TERMS; i++) {
		term = bt_get_simple_term('A', AND, 'B');
		ASSERT_TRUE(term != 0, "Term expected");
	}
	term = bt_get_simple_term('C', AND, 'D');
	sprintf(msg, "Already retrieved %d terms, no further terms expected", MAX_TERMS);
	ASSERT_TRUE(term == 0, msg);
	
	bt_reset();
	for (int i = 0; i < MAX_TERMS; i++) {
		term = bt_get_simple_term('E', OR, 'F');
		ASSERT_TRUE(term != 0, "Term expected after reset");
	}
	term = bt_get_simple_term('G', OR, 'H');
	sprintf(msg, "Retrieved %d terms after reset, no further term expected", MAX_TERMS);
	ASSERT_TRUE(term == 0, msg);
}

TEST(test_bt_get_simple_term__shall_be_valid)
{
	bt_reset();
	GET_VALID_SIMPLE_TERM('E', OR, 'F');
}

TEST(test_bt_get_simple_term__shall_have_two_simple_operands_and_op)
{
	char label_left = 'G';
	char label_right = 'H';
	Operation op = AND;

	bt_reset();
	BoolTerm term = GET_VALID_SIMPLE_TERM(label_left, op, label_right);
	ASSERT_VALID_SIMPLE_OPERAND(bt_get_left_operand(term), label_left, "left");
	ASSERT_VALID_SIMPLE_OPERAND(bt_get_right_operand(term), label_right, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_simple_term__unary_shall_have_one_simple_operand_and_op)
{
	char label_left = 'X';
	char label_right = 'H';
	Operation op = NOT;

	bt_reset();
	BoolTerm term = GET_VALID_SIMPLE_TERM(label_left, op, label_right);
	ASSERT_INVALID_OPERAND(bt_get_left_operand(term), "left");
	ASSERT_VALID_SIMPLE_OPERAND(bt_get_right_operand(term), label_right, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_complex_term_left__shall_have_two_valid_operands_and_op)
{
	bt_reset();
	char label = 'I';
	Operation op = OR;

	BoolTerm opd_term = GET_VALID_SIMPLE_TERM('X', OR, 'Y');
	ASSERT_VALID_TERM(opd_term);
	BoolTerm term = bt_get_complex_term_left(opd_term, op, label);
	ASSERT_VALID_TERM(term);

	ASSERT_VALID_COMPLEX_OPERAND(bt_get_left_operand(term), opd_term, "left");
	ASSERT_VALID_SIMPLE_OPERAND(bt_get_right_operand(term), label, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_complex_term_left__unary_shall_have_one_simple_operand_and_op)
{
	bt_reset();
	char label = 'J';
	Operation op = NOT;

	BoolTerm left_term = GET_VALID_SIMPLE_TERM('X', OR, 'Y');
	ASSERT_VALID_TERM(left_term);
	BoolTerm term = bt_get_complex_term_left(left_term, op, label);
	ASSERT_VALID_TERM(term);

	ASSERT_INVALID_OPERAND(bt_get_left_operand(term), "left");
	ASSERT_VALID_SIMPLE_OPERAND(bt_get_right_operand(term), label, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_complex_term_right__shall_have_two_valid_operands_and_op)
{
	bt_reset();
	char label = 'L';
	Operation op = OR;

	BoolTerm opd_term = GET_VALID_SIMPLE_TERM('Y', OR, 'Z');
	ASSERT_VALID_TERM(opd_term);
	BoolTerm term = bt_get_complex_term_right(label, op, opd_term);
	ASSERT_VALID_TERM(term);

	ASSERT_VALID_SIMPLE_OPERAND(bt_get_left_operand(term), label, "left");
	ASSERT_VALID_COMPLEX_OPERAND(bt_get_right_operand(term), opd_term, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_complex_term_right__unary_shall_have_one_complex_operand_and_op)
{
	bt_reset();
	char label = 'M';
	Operation op = NOT;

	BoolTerm opd_term = GET_VALID_SIMPLE_TERM('Y', OR, 'Z');
	ASSERT_VALID_TERM(opd_term);
	BoolTerm term = bt_get_complex_term_right(label, op, opd_term);
	ASSERT_VALID_TERM(term);

	ASSERT_INVALID_OPERAND(bt_get_left_operand(term), "left");
	ASSERT_VALID_COMPLEX_OPERAND(bt_get_right_operand(term), opd_term, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_complex_term__shall_have_two_valid_operands_and_op)
{
	bt_reset();
	Operation op = OR;

	BoolTerm opd_term_1 = GET_VALID_SIMPLE_TERM('Y', OR, 'Z');
	BoolTerm opd_term_2 = GET_VALID_SIMPLE_TERM('X', OR, 'Z');
	ASSERT_VALID_TERM(opd_term_1);
	ASSERT_VALID_TERM(opd_term_2);
	BoolTerm term = bt_get_complex_term(opd_term_1, op, opd_term_2);
	ASSERT_VALID_TERM(term);

	ASSERT_VALID_COMPLEX_OPERAND(bt_get_left_operand(term), opd_term_1, "left");
	ASSERT_VALID_COMPLEX_OPERAND(bt_get_right_operand(term), opd_term_2, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_complex_term__unary_shall_have_one_complex_operand_and_op)
{
	bt_reset();
	Operation op = NOT;

	BoolTerm opd_term_1 = GET_VALID_SIMPLE_TERM('Y', OR, 'Z');
	BoolTerm opd_term_2 = GET_VALID_SIMPLE_TERM('X', OR, 'Z');
	ASSERT_VALID_TERM(opd_term_1);
	ASSERT_VALID_TERM(opd_term_2);
	BoolTerm term = bt_get_complex_term(opd_term_1, op, opd_term_2);
	ASSERT_VALID_TERM(term);

	ASSERT_INVALID_OPERAND(bt_get_left_operand(term), "left");
	ASSERT_VALID_COMPLEX_OPERAND(bt_get_right_operand(term), opd_term_2, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_term__shall_have_two_valid_operands_and_op)
{
	bt_reset();
	Operation op = OR;

	BoolTerm opd_term_1 = GET_VALID_SIMPLE_TERM('Z', OR, 'X');
	BoolTerm opd_term_2 = GET_VALID_SIMPLE_TERM('Z', OR, 'Y');
	ASSERT_VALID_TERM(opd_term_1);
	ASSERT_VALID_TERM(opd_term_2);
	BoolOperand left_opd = bo_get_complex_operand(opd_term_1);
	ASSERT_VALID_COMPLEX_OPERAND(left_opd, opd_term_1, "OPD-1");
	BoolOperand right_opd = bo_get_complex_operand(opd_term_2);
	ASSERT_VALID_COMPLEX_OPERAND(right_opd, opd_term_2, "OPD-2");

	BoolTerm term = bt_get_term(left_opd, op, right_opd);
	ASSERT_VALID_TERM(term);

	ASSERT_VALID_COMPLEX_OPERAND(bt_get_left_operand(term), opd_term_1, "left");
	ASSERT_VALID_COMPLEX_OPERAND(bt_get_right_operand(term), opd_term_2, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_term__unary_shall_have_one_complex_operand_and_op)
{
	bt_reset();
	Operation op = NOT;

	BoolTerm opd_term = GET_VALID_SIMPLE_TERM('Z', OR, 'X');
	ASSERT_VALID_TERM(opd_term);
	BoolOperand opd = bo_get_complex_operand(opd_term);
	ASSERT_VALID_COMPLEX_OPERAND(opd, opd_term, "OPD");

	BoolTerm term = bt_get_term(0, op, opd);
	ASSERT_VALID_TERM(term);
	ASSERT_INVALID_OPERAND(bt_get_left_operand(term), "left");
	ASSERT_VALID_COMPLEX_OPERAND(bt_get_right_operand(term), opd_term, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_term__with_identical_opd_shall_be_valid)
{
	bt_reset();
	Operation op = OR;

	BoolTerm opd_term = GET_VALID_SIMPLE_TERM('Z', OR, 'X');
	ASSERT_VALID_TERM(opd_term);
	BoolOperand opd = bo_get_complex_operand(opd_term);
	ASSERT_VALID_COMPLEX_OPERAND(opd, opd_term, "OPD");

	BoolTerm term = bt_get_term(opd, op, opd);
	ASSERT_VALID_TERM(term);

	ASSERT_VALID_COMPLEX_OPERAND(bt_get_left_operand(term), opd_term, "left");
	ASSERT_VALID_COMPLEX_OPERAND(bt_get_right_operand(term), opd_term, "right");
	ASSERT_TRUE(bt_get_operation(term) == op, "Operation mismatch");
}

TEST(test_bt_get_term__with_invalid_term_shall_be_invalid)
{
	bt_reset();
	ASSERT_FALSE(bt_is_valid(0), "Invalid term expected");
}

TEST(test_bt_get_term__with_null_left_opd_shall_be_invalid)
{
	bt_reset();
	char label = 'U';
	Operation op = OR;

	BoolOperand valid_opd = bo_get_simple_operand(label);
	ASSERT_VALID_SIMPLE_OPERAND(valid_opd, label, "valid OPD");

	BoolTerm term = bt_get_term(0, op, valid_opd);
	ASSERT_FALSE(bt_is_valid(term), "Invalid term expected");
}

TEST(test_bt_get_term__with_invalid_left_simple_opd_shall_be_invalid)
{
	bt_reset();
	char label = 'U';
	Operation op = OR;

	BoolOperand invalid_opd = bo_get_simple_operand('\0');
	ASSERT_INVALID_OPERAND(invalid_opd, "invalid OPD");
	BoolOperand valid_opd = bo_get_simple_operand(label);
	ASSERT_VALID_SIMPLE_OPERAND(valid_opd, label, "valid OPD");

	BoolTerm term = bt_get_term(invalid_opd, op, valid_opd);
	ASSERT_FALSE(bt_is_valid(term), "Invalid term expected");
}

TEST(test_bt_get_term__with_invalid_left_cplx_opd_shall_be_invalid)
{
	bt_reset();
	char label = 'V';
	Operation op = AND;

	BoolTerm invalid_opd_term = bt_get_simple_term('\0', AND, '\0');
	BoolOperand invalid_opd = bo_get_complex_operand(invalid_opd_term);
	ASSERT_INVALID_OPERAND(invalid_opd, "invalid OPD");
	BoolOperand valid_opd = bo_get_simple_operand(label);
	ASSERT_VALID_SIMPLE_OPERAND(valid_opd, label, "valid OPD");

	BoolTerm term = bt_get_term(invalid_opd, op, valid_opd);
	ASSERT_FALSE(bt_is_valid(term), "Invalid term expected");
}

TEST(test_bt_get_term__with_null_right_opd_shall_be_invalid)
{
	bt_reset();
	char label = 'U';
	Operation op = OR;

	BoolOperand valid_opd = bo_get_simple_operand(label);
	ASSERT_VALID_SIMPLE_OPERAND(valid_opd, label, "valid OPD");

	BoolTerm term = bt_get_term(valid_opd, op, 0);
	ASSERT_FALSE(bt_is_valid(term), "Invalid term expected");
}

TEST(test_bt_get_term__with_invalid_right_simple_opd_shall_be_invalid)
{
	bt_reset();
	char label = 'U';
	Operation op = OR;

	BoolOperand invalid_opd = bo_get_simple_operand('\0');
	ASSERT_INVALID_OPERAND(invalid_opd, "invalid OPD");
	BoolOperand valid_opd = bo_get_simple_operand(label);
	ASSERT_VALID_SIMPLE_OPERAND(valid_opd, label, "valid OPD");

	BoolTerm term = bt_get_term(valid_opd, op, invalid_opd);
	ASSERT_FALSE(bt_is_valid(term), "Invalid term expected");
}

TEST(test_bt_get_term__with_invalid_right_cplx_opd_shall_be_invalid)
{
	bt_reset();
	char label = 'V';
	Operation op = AND;

	BoolTerm invalid_opd_term = bt_get_simple_term('\0', AND, '\0');
	BoolOperand invalid_opd = bo_get_complex_operand(invalid_opd_term);
	ASSERT_INVALID_OPERAND(invalid_opd, "invalid OPD");
	BoolOperand valid_opd = bo_get_simple_operand(label);
	ASSERT_VALID_SIMPLE_OPERAND(valid_opd, label, "valid OPD");

	BoolTerm term = bt_get_term(valid_opd, op, invalid_opd);
	ASSERT_FALSE(bt_is_valid(term), "Invalid term expected");
}

TEST(test_bt_get_term__with_invalid_op_shall_be_invalid)
{
	bt_reset();
	BoolTerm term = bt_get_simple_term('Q', INVALID, 'Q');
	ASSERT_FALSE(bt_is_valid(term), "Invalid term expected");
}

TEST(test_bt_get_simple_operand_count__unary_one)
{
	bt_reset();
	BoolTerm term = GET_VALID_SIMPLE_TERM('-', NOT, 'A');
	ASSERT_TRUE(bt_get_simple_operand_count(term) == 1, "Expected simple operand count of 1");
}

TEST(test_bt_get_simple_operand_count__unary_two)
{
	bt_reset();
	BoolTerm opd_term = GET_VALID_SIMPLE_TERM('A', OR, 'B');
	ASSERT_VALID_TERM(opd_term);
	BoolTerm term = bt_get_complex_term_right('-', NOT, opd_term);
	ASSERT_VALID_TERM(term);
	ASSERT_TRUE(bt_get_simple_operand_count(term) == 2, "Expected simple operand count of 2");
}

TEST(test_bt_get_simple_operand_count__unary_three)
{
	bt_reset();
	BoolTerm opd_term_1 = GET_VALID_SIMPLE_TERM('A', OR, 'B');
	ASSERT_VALID_TERM(opd_term_1);
	BoolTerm opd_term_2 = bt_get_complex_term_right('C', AND, opd_term_1);
	ASSERT_VALID_TERM(opd_term_2);
	BoolTerm term = bt_get_complex_term_right('-', NOT, opd_term_2);
	ASSERT_VALID_TERM(term);
	ASSERT_TRUE(bt_get_simple_operand_count(term) == 3, "Expected simple operand count of 3");
}

TEST(test_bt_get_simple_operand_count__binary_two)
{	
	bt_reset();
	BoolTerm term = GET_VALID_SIMPLE_TERM('A', AND, 'B');
	ASSERT_TRUE(bt_get_simple_operand_count(term) == 2, "Expected simple operand count of 2");
}

TEST(test_bt_get_simple_operand_count__binary_three_left)
{
	bt_reset();
	BoolTerm opd_term = GET_VALID_SIMPLE_TERM('A', OR, 'B');
	ASSERT_VALID_TERM(opd_term);
	BoolTerm term = bt_get_complex_term_left(opd_term, OR, 'C');
	ASSERT_VALID_TERM(term);
	ASSERT_TRUE(bt_get_simple_operand_count(term) == 3, "Expected simple operand count of 3, 2 at the left");
}

TEST(test_bt_get_simple_operand_count__binary_three_right)
{
	bt_reset();
	BoolTerm opd_term = GET_VALID_SIMPLE_TERM('A', OR, 'B');
	ASSERT_VALID_TERM(opd_term);
	BoolTerm term = bt_get_complex_term_right('C', OR, opd_term);
	ASSERT_VALID_TERM(term);
	ASSERT_TRUE(bt_get_simple_operand_count(term) == 3, "Expected simple operand count of 3, 2 at the right");
}

TEST(test_bt_get_simple_operand_count__binary_four)
{
	bt_reset();
	BoolTerm opd_term_1 = GET_VALID_SIMPLE_TERM('A', OR, 'B');
	ASSERT_VALID_TERM(opd_term_1);
	BoolTerm opd_term_2 = GET_VALID_SIMPLE_TERM('X', AND, 'Y');
	ASSERT_VALID_TERM(opd_term_2);
	BoolTerm term = bt_get_complex_term(opd_term_1, OR, opd_term_2);
	ASSERT_VALID_TERM(term);
	ASSERT_TRUE(bt_get_simple_operand_count(term) == 4, "Expected simple operand count of 4");
}

TEST(test_bt_get_value__not)
{
	bt_reset();
	BoolTerm term = GET_VALID_SIMPLE_TERM('-', NOT, 'B');
	ASSERT_VALID_TERM(term);
	bo_set_value(bt_get_left_operand(term),  true);
	bo_set_value(bt_get_right_operand(term), true);
	ASSERT_TRUE(bt_get_value(term) == false, "Expected correct result 1");
	bo_set_value(bt_get_left_operand(term),  true);
	bo_set_value(bt_get_right_operand(term), false);
	ASSERT_TRUE(bt_get_value(term) == true,  "Expected correct result 2");
	bo_set_value(bt_get_left_operand(term),  false);
	bo_set_value(bt_get_right_operand(term), true);
	ASSERT_TRUE(bt_get_value(term) == false, "Expected correct result 3");
	bo_set_value(bt_get_left_operand(term),  false);
	bo_set_value(bt_get_right_operand(term), false);
	ASSERT_TRUE(bt_get_value(term) == true,  "Expected correct result 4");
}

TEST(test_bt_get_value__and)
{
	bt_reset();
	BoolTerm term = GET_VALID_SIMPLE_TERM('A', AND, 'B');
	ASSERT_VALID_TERM(term);
	bo_set_value(bt_get_left_operand(term),  true);
	bo_set_value(bt_get_right_operand(term), true);
	ASSERT_TRUE(bt_get_value(term) == true,  "Expected correct result 1");
	bo_set_value(bt_get_left_operand(term),  true);
	bo_set_value(bt_get_right_operand(term), false);
	ASSERT_TRUE(bt_get_value(term) == false, "Expected correct result 2");
	bo_set_value(bt_get_left_operand(term),  false);
	bo_set_value(bt_get_right_operand(term), true);
	ASSERT_TRUE(bt_get_value(term) == false, "Expected correct result 3");
	bo_set_value(bt_get_left_operand(term),  false);
	bo_set_value(bt_get_right_operand(term), false);
	ASSERT_TRUE(bt_get_value(term) == false, "Expected correct result 4");
}

TEST(test_bt_get_value__or)
{
	bt_reset();
	BoolTerm term = GET_VALID_SIMPLE_TERM('A', OR, 'B');
	ASSERT_VALID_TERM(term);
	bo_set_value(bt_get_left_operand(term),  true);
	bo_set_value(bt_get_right_operand(term), true);
	ASSERT_TRUE(bt_get_value(term) == true,  "Expected correct result 1");
	bo_set_value(bt_get_left_operand(term),  true);
	bo_set_value(bt_get_right_operand(term), false);
	ASSERT_TRUE(bt_get_value(term) == true,  "Expected correct result 2");
	bo_set_value(bt_get_left_operand(term),  false);
	bo_set_value(bt_get_right_operand(term), true);
	ASSERT_TRUE(bt_get_value(term) == true,  "Expected correct result 3");
	bo_set_value(bt_get_left_operand(term),  false);
	bo_set_value(bt_get_right_operand(term), false);
	ASSERT_TRUE(bt_get_value(term) == false, "Expected correct result 4");
}