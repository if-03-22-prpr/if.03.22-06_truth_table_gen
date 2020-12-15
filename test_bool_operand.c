/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: 08
 * Title:			Implementation of UTs for Boolean Operand
 * Author:			S. Schraml
 * Due Date:		n/a
 * ----------------------------------------------------------
 * Description:
 * Test functions for ADT BoolOperand.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>

#include "test_bool_operand.h"
#include "shortcut.h"
#include "config.h"
#include "bool_operand.h"
#include "bool_term.h"

#define MAX_OPDS MAX_TERMS * 2

TEST(test_bo_reset__shall_not_get_more_than_all_operands)
{
	char msg[128];
	BoolOperand opd = 0;

	bo_reset();
	for (int i = 0; i < MAX_OPDS; i++) {
		opd = bo_get_simple_operand('A');
		ASSERT_TRUE(opd != 0, "Simple operand expected");
	}
	opd = bo_get_simple_operand('B');
	sprintf(msg, "Already retrieved %d operands, no further simple operand expected", MAX_OPDS);
	ASSERT_TRUE(opd == 0, msg);

	BoolTerm term = bt_get_simple_term('E', AND, 'F');
	ASSERT_TRUE(term != 0, "Term expected");

	opd = bo_get_complex_operand(term);
	sprintf(msg, "Retrieved %d operands, no further complex operand expected", MAX_OPDS);
	ASSERT_TRUE(opd == 0, msg);
	
	bo_reset();
	for (int i = 0; i < MAX_OPDS; i++) {
		opd = bo_get_complex_operand(term);
		ASSERT_TRUE(opd != 0, "Complex operand expected after reset");
	}
	opd = bo_get_simple_operand('G');
	sprintf(msg, "Retrieved %d operands after reset, no further operand expected", MAX_OPDS);
	ASSERT_TRUE(opd == 0, msg);

	opd = bo_get_complex_operand(term);
	sprintf(msg, "Retrieved %d operands after reset, no further complex operand expected", MAX_OPDS);
	ASSERT_TRUE(opd == 0, msg);
}

TEST(test_bo_get_simple_operand__shall_be_valid)
{
	bo_reset();
	char label = 'B';
	BoolOperand opd1 = bo_get_simple_operand(label);
	ASSERT_TRUE(opd1 != 0, "Operand expected");
	ASSERT_TRUE(bo_is_valid(opd1), "Valid operand expected");
}

TEST(test_bo_get_simple_operand__shall_be_simple)
{
	bo_reset();
	char label = 'C';
	BoolOperand opd1 = bo_get_simple_operand(label);
	ASSERT_TRUE(opd1 != 0, "Operand expected");
	ASSERT_TRUE(bo_is_simple(opd1), "Simple operand expected");
}

TEST(test_bo_get_simple_operand__shall_have_label)
{
	bo_reset();
	char label = 'D';
	BoolOperand opd1 = bo_get_simple_operand(label);
	ASSERT_TRUE(opd1 != 0, "Operand expected");
	ASSERT_TRUE(bo_get_label(opd1) == label, "Label mismatch");
}

TEST(test_bo_get_simple_operand__shall_not_have_term)
{
	bo_reset();
	char label = 'E';
	BoolOperand opd1 = bo_get_simple_operand(label);
	ASSERT_TRUE(opd1 != 0, "Operand expected");
	ASSERT_TRUE(bo_get_term(opd1) == 0, "Term of simple operand must be 0");
}

TEST(test_bo_get_complex_operand__shall_be_valid)
{
	bt_reset();
	bo_reset();
	BoolTerm term = bt_get_simple_term('X', AND, 'Y');
	ASSERT_TRUE(term != 0, "Term expected");

	BoolOperand opd1 = bo_get_complex_operand(term);
	ASSERT_TRUE(opd1 != 0, "Operand expected");
	ASSERT_TRUE(bo_is_valid(opd1), "Valid operand expected");
}

TEST(test_bo_get_complex_operand__shall_not_be_simple)
{
	bt_reset();
	bo_reset();
	BoolTerm term = bt_get_simple_term('X', AND, 'Y');
	ASSERT_TRUE(term != 0, "Term expected");

	BoolOperand opd1 = bo_get_complex_operand(term);
	ASSERT_TRUE(opd1 != 0, "Operand expected");
	ASSERT_TRUE(!bo_is_simple(opd1), "Complex operand expected");
}

TEST(test_bo_get_complex_operand__shall_not_have_label)
{
	bt_reset();
	bo_reset();
	BoolTerm term = bt_get_simple_term('X', AND, 'Y');
	ASSERT_TRUE(term != 0, "Term expected");

	BoolOperand opd1 = bo_get_complex_operand(term);
	ASSERT_TRUE(opd1 != 0, "Operand expected");
	ASSERT_TRUE(bo_get_label(opd1) == '\0', "Complex operand shall have no label");
}

TEST(test_bo_get_complex_operand__shall_have_term)
{
	bt_reset();
	bo_reset();
	BoolTerm term = bt_get_simple_term('X', AND, 'Y');
	ASSERT_TRUE(term != 0, "Term expected");

	BoolOperand opd1 = bo_get_complex_operand(term);
	ASSERT_TRUE(opd1 != 0, "Operand expected");
	ASSERT_TRUE(bo_get_term(opd1) == term, "Term of complex operand expected");
}

TEST(test_bo_is_valid__with_null_operand_shall_be_invalid)
{
	bo_reset();
	ASSERT_FALSE(bo_is_valid(0), "Null operand shall be invalid");
}

TEST(test_bo_is_valid__with_simple_operand_without_label_shall_be_invalid)
{
	bo_reset();
	BoolOperand opd1 = bo_get_simple_operand('\0');
	ASSERT_TRUE(opd1 != 0, "Operand expected");
	ASSERT_FALSE(bo_is_valid(opd1), "Simple operand with label shall be invalid");
}

TEST(test_bo_is_valid__with_complex_operand_without_term_shall_be_invalid)
{
	bo_reset();
	BoolOperand opd1 = bo_get_complex_operand(0);
	ASSERT_FALSE(bo_is_valid(opd1), "Complex operand without term shall be invalid");
}

TEST(test_bo_get_value__of_simple_operand)
{
	bo_reset();
	BoolOperand opd = bo_get_simple_operand('A');
	ASSERT_TRUE(bo_is_valid(opd), "Valid operand expected");
	ASSERT_FALSE(bo_get_value(opd), "False is expected as initial value of a simple operand");
	bo_set_value(opd, true);
	ASSERT_TRUE(bo_get_value(opd), "True is expected as value of the simple operand");
}

TEST(test_bo_get_value__of_complex_operand)
{
	bt_reset();
	bo_reset();
	BoolTerm term = bt_get_simple_term('X', AND, 'Y');
	ASSERT_TRUE(term != 0, "Term expected");
	bo_set_value(bt_get_left_operand(term), true);
	bo_set_value(bt_get_right_operand(term), true);

	BoolOperand opd = bo_get_complex_operand(term);
	ASSERT_TRUE(bo_is_valid(opd), "Valid operand expected");
	ASSERT_TRUE(bo_get_value(opd) == bt_get_value(term), "The value of the term is expected as value of the complex operand");
	bo_set_value(opd, false);
	ASSERT_TRUE(bo_get_value(opd), "The value of complex operand is not expected being affected by setter");

	bo_set_value(bt_get_left_operand(term), false);
	ASSERT_TRUE(bo_get_value(opd) == bt_get_value(term), "The value of the term is expected as value of the complex operand");
}

TEST(test_bo_get_value__of_invalid_operand)
{
	ASSERT_FALSE(bo_get_value(0), "False is expected as value of an invalid operand");
}
