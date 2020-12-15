/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 08
 * Title:			Boolean Term Data Type Declaration
 * Author:			*/<your name>/*
 * Due Date:		Dec. 20, 2020
 * ----------------------------------------------------------
 * Description:
 * The declaration of an Abstract Data Type for a 
 * Boolean operation with two operands.
 * ----------------------------------------------------------
 */

#ifndef ___BOOL_TERM_H
#define ___BOOL_TERM_H

/** Declares a Boolean operation term with two operands */
-- BoolTerm;

/**
 * Resets all configured terms.
 */
-- bt_reset();

/**
 * Creates a Boolean term with the given operation and Boolean operands.
 * Unary operations (e.g. NOT) shall ignore the left operand.
 * 
 * @param left_operand The left operand of the term.
 * @param op The operation of the term.
 * @param right_operand The right operand of the term.
 * @return The term or 0, if no term could be created.
 */
-- bt_get_term(-- left_operand, -- op, -- right_operand);

/**
 * Creates a Boolean term with the given operation and operands.
 * Unary operations (e.g. NOT) shall ignore the left operand.
 * This is a convenience operation to avoid the necessity to allocate Boolean operands explicitly.
 * 
 * @param left_operand The name of the left operand of the term.
 * @param op The operation of the term.
 * @param right_operand The name of the right operand of the term.
 * @return The term or 0, if no term could be created.
 */
-- bt_get_simple_term(-- left_operand, -- op, -- right_operand);

/**
 * Creates a Boolean term with the given operation having one operand term 
 * and one operand name. Unary operations (e.g. NOT) shall ignore the left operand.
 * This is a convenience operation to avoid the necessity to allocate Boolean operands explicitly.
 * 
 * @param left_operand The sub-term being the left operand of the term.
 * @param op The operation of the term.
 * @param right_operand The name of the right operand of the term.
 * @return The term or 0, if no term could be created.
 */
-- bt_get_complex_term_left(-- left_operand, -- op, -- right_operand);

/**
 * Creates a Boolean term with the given operation having one operand term 
 * and one operand name. Unary operations (e.g. NOT) shall ignore the left operand.
 * This is a convenience operation to avoid the necessity to allocate Boolean operands explicitly.
 * 
 * @param left_operand The name of the left operand of the term.
 * @param op The operation of the term.
 * @param right_operand The sub-term being the right operand of the term.
 * @return The term or 0, if no term could be created.
 */
-- bt_get_complex_term_right(-- left_operand, Operation op, -- right_operand);

/**
 * Creates a Boolean term with the given operation having one operand term 
 * and one operand name. Unary operations (e.g. NOT) shall ignore the left operand.
 * This is a convenience operation to avoid the necessity to allocate Boolean operands explicitly.
 * 
 * @param left_operand The sub-term being the left operand of the term.
 * @param op The operation of the term.
 * @param right_operand The sub-term being the right operand of the term.
 * @return The term or 0, if no term could be created.
 */
-- bt_get_complex_term(-- left_operand, -- op, -- right_operand);

/**
 * Determines whether or not the given term is valid.
 * A term is valid, if it is not 0, has a valid operation,
 * and the required number of operands.
 * 
 * @param operand The operand in focus as part of this ADT.
 * @return True if the term is valid, false otherwise.
 */
-- bt_is_valid(-- term);

/**
 * Provides the operation of the Boolean term.
 * 
 * @param term The term in focus as part of this ADT.
 * @return The operation.
 */
-- bt_get_operation(-- term);

/**
 * Provides the left operand of the operation of the Boolean term.
 * 
 * @param term The term in focus as part of this ADT.
 * @return The left operand of the operation or 0,
 *         if the left operand is not applicable 
 *         (e.g. for unary operations).
 */
-- bt_get_left_operand(-- term);

/**
 * Provides the right operand of the operation of the Boolean term.
 * 
 * @param term The term in focus as part of this ADT.
 * @return The right operand of the operation, should not be 0.
 */
-- bt_get_right_operand(-- term);

/**
 * Provides the number of simple operands that are directly or indirectly
 * defined by the term. Unary operations with simple operands have one and
 * binary operations with simple operands have two simple operands.
 * Complex operations count the simple operands of their sub-terms.
 * 
 * @param term The term in focus as part of this ADT.
 * @return int The number of named operands, or 0 if the term is 0.
 */
-- bt_get_simple_operand_count(-- term);

/**
 * Provides the result of the operation expressed by this term
 * depending on values applied to simple operands of the term.
 * 
 * @param term The term in focus as part of this ADT.
 * @return bool The result of the operation, or false if the term is 0.
 */
-- bt_get_value(-- term);

#endif
