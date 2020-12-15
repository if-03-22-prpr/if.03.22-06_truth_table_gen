/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: 08
 * Title:			Unit Tests for Boolean Operand
 * Author:			S. Schraml
 * Due Date:		n/a
 * ----------------------------------------------------------
 * Description:
 * Test functions of ADT 'BoolOperand'.
 * ----------------------------------------------------------
 */
#ifndef ___TEST_BOOL_OPERAND_H
#define ___TEST_BOOL_OPERAND_H

#include "shortcut.h"

TEST(test_bo_reset__shall_not_get_more_than_all_operands);

TEST(test_bo_get_simple_operand__shall_be_valid);
TEST(test_bo_get_simple_operand__shall_be_simple);
TEST(test_bo_get_simple_operand__shall_have_label);
TEST(test_bo_get_simple_operand__shall_not_have_term);

TEST(test_bo_get_complex_operand__shall_be_valid);
TEST(test_bo_get_complex_operand__shall_not_be_simple);
TEST(test_bo_get_complex_operand__shall_not_have_label);
TEST(test_bo_get_complex_operand__shall_have_term);

TEST(test_bo_is_valid__with_null_operand_shall_be_invalid);
TEST(test_bo_is_valid__with_simple_operand_without_label_shall_be_invalid);
TEST(test_bo_is_valid__with_complex_operand_without_term_shall_be_invalid);

TEST(test_bo_get_value__of_simple_operand);
TEST(test_bo_get_value__of_complex_operand);
TEST(test_bo_get_value__of_invalid_operand);

#endif
