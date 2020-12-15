/*----------------------------------------------------------
 *				HTBLA-Leonding
 * ---------------------------------------------------------
 * Exercise Number: 08
 * Title:			Test Driver for Truth Table Generator
 * Author:			S. Schraml
 * Due Date:		n/a
 * ----------------------------------------------------------
 * Description:
 * Executes all unit tests of Truth Table Generator.
 * ----------------------------------------------------------
 */

#include "shortcut.h"
#include "test_bool_operand.h"
#include "test_bool_term.h"

int main(int argc, char *argv[])
{

	ADD_TEST(test_bo_reset__shall_not_get_more_than_all_operands);

	ADD_TEST(test_bo_get_simple_operand__shall_be_valid);
	ADD_TEST(test_bo_get_simple_operand__shall_be_simple);
	ADD_TEST(test_bo_get_simple_operand__shall_have_label);
	ADD_TEST(test_bo_get_simple_operand__shall_not_have_term);

	ADD_TEST(test_bo_get_complex_operand__shall_be_valid);
	ADD_TEST(test_bo_get_complex_operand__shall_not_be_simple);
	ADD_TEST(test_bo_get_complex_operand__shall_not_have_label);
	ADD_TEST(test_bo_get_complex_operand__shall_have_term);

	ADD_TEST(test_bo_is_valid__with_null_operand_shall_be_invalid);
	ADD_TEST(test_bo_is_valid__with_simple_operand_without_label_shall_be_invalid);
	ADD_TEST(test_bo_is_valid__with_complex_operand_without_term_shall_be_invalid);

	ADD_TEST(test_bo_get_value__of_simple_operand);
	ADD_TEST(test_bo_get_value__of_complex_operand);
	ADD_TEST(test_bo_get_value__of_invalid_operand);

	ADD_TEST(test_bt_reset__shall_not_get_more_than_all_terms);

	ADD_TEST(test_bt_get_simple_term__shall_be_valid);
	ADD_TEST(test_bt_get_simple_term__shall_have_two_simple_operands_and_op);
	ADD_TEST(test_bt_get_simple_term__unary_shall_have_one_simple_operand_and_op);
	
	ADD_TEST(test_bt_get_complex_term_left__shall_have_two_valid_operands_and_op);
	ADD_TEST(test_bt_get_complex_term_left__unary_shall_have_one_simple_operand_and_op);
	ADD_TEST(test_bt_get_complex_term_right__shall_have_two_valid_operands_and_op);
	ADD_TEST(test_bt_get_complex_term_right__unary_shall_have_one_complex_operand_and_op);
	ADD_TEST(test_bt_get_complex_term__shall_have_two_valid_operands_and_op);
	ADD_TEST(test_bt_get_complex_term__unary_shall_have_one_complex_operand_and_op);

	ADD_TEST(test_bt_get_term__shall_have_two_valid_operands_and_op);
	ADD_TEST(test_bt_get_term__unary_shall_have_one_complex_operand_and_op);
	ADD_TEST(test_bt_get_term__with_identical_opd_shall_be_valid);

	ADD_TEST(test_bt_get_term__with_invalid_term_shall_be_invalid);
	ADD_TEST(test_bt_get_term__with_null_left_opd_shall_be_invalid);
	ADD_TEST(test_bt_get_term__with_invalid_left_simple_opd_shall_be_invalid);
	ADD_TEST(test_bt_get_term__with_invalid_left_cplx_opd_shall_be_invalid);
	ADD_TEST(test_bt_get_term__with_null_right_opd_shall_be_invalid);
	ADD_TEST(test_bt_get_term__with_invalid_right_simple_opd_shall_be_invalid);
	ADD_TEST(test_bt_get_term__with_invalid_right_cplx_opd_shall_be_invalid);
	ADD_TEST(test_bt_get_term__with_invalid_op_shall_be_invalid);

	ADD_TEST(test_bt_get_simple_operand_count__unary_one);
	ADD_TEST(test_bt_get_simple_operand_count__unary_two);
	ADD_TEST(test_bt_get_simple_operand_count__unary_three);
	ADD_TEST(test_bt_get_simple_operand_count__binary_two);
	ADD_TEST(test_bt_get_simple_operand_count__binary_three_left);
	ADD_TEST(test_bt_get_simple_operand_count__binary_three_right);
	ADD_TEST(test_bt_get_simple_operand_count__binary_four);

	ADD_TEST(test_bt_get_value__not);
	ADD_TEST(test_bt_get_value__and);
	ADD_TEST(test_bt_get_value__or);
	
	run_tests();
	return 0;
}
