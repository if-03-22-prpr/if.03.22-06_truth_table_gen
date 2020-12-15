/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: 08
 * Title:			Unit Tests for Boolean Term
 * Author:			S. Schraml
 * Due Date:		n/a
 * ----------------------------------------------------------
 * Description:
 * Test functions of ADT 'BoolTerm'.
 * ----------------------------------------------------------
 */
#ifndef ___TEST_BOOL_TERM_H
#define ___TEST_BOOL_TERM_H

#include "shortcut.h"

TEST(test_bt_reset__shall_not_get_more_than_all_terms);

TEST(test_bt_get_simple_term__shall_be_valid);
TEST(test_bt_get_simple_term__shall_have_two_simple_operands_and_op);
TEST(test_bt_get_simple_term__unary_shall_have_one_simple_operand_and_op);

TEST(test_bt_get_complex_term_left__shall_have_two_valid_operands_and_op);
TEST(test_bt_get_complex_term_left__unary_shall_have_one_simple_operand_and_op);
TEST(test_bt_get_complex_term_right__shall_have_two_valid_operands_and_op);
TEST(test_bt_get_complex_term_right__unary_shall_have_one_complex_operand_and_op);
TEST(test_bt_get_complex_term__shall_have_two_valid_operands_and_op);
TEST(test_bt_get_complex_term__unary_shall_have_one_complex_operand_and_op);

TEST(test_bt_get_term__shall_have_two_valid_operands_and_op);
TEST(test_bt_get_term__unary_shall_have_one_complex_operand_and_op);
TEST(test_bt_get_term__with_identical_opd_shall_be_valid);

TEST(test_bt_get_term__with_invalid_term_shall_be_invalid);
TEST(test_bt_get_term__with_null_left_opd_shall_be_invalid);
TEST(test_bt_get_term__with_invalid_left_simple_opd_shall_be_invalid);
TEST(test_bt_get_term__with_invalid_left_cplx_opd_shall_be_invalid);
TEST(test_bt_get_term__with_null_right_opd_shall_be_invalid);
TEST(test_bt_get_term__with_invalid_right_simple_opd_shall_be_invalid);
TEST(test_bt_get_term__with_invalid_right_cplx_opd_shall_be_invalid);
TEST(test_bt_get_term__with_invalid_op_shall_be_invalid);

TEST(test_bt_get_simple_operand_count__unary_one);
TEST(test_bt_get_simple_operand_count__unary_two);
TEST(test_bt_get_simple_operand_count__unary_three);
TEST(test_bt_get_simple_operand_count__binary_two);
TEST(test_bt_get_simple_operand_count__binary_three_left);
TEST(test_bt_get_simple_operand_count__binary_three_right);
TEST(test_bt_get_simple_operand_count__binary_four);

TEST(test_bt_get_value__not);
TEST(test_bt_get_value__and);
TEST(test_bt_get_value__or);
#endif
