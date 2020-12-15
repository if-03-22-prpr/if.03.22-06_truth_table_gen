/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class>
 * ---------------------------------------------------------
 * Exercise Number: 08
 * Title:			Boolean Operand Data Type Declaration
 * Author:			*/<your name>/*
 * Due Date:		Dec. 20, 2020
 * ----------------------------------------------------------
 * Description:
 * The declaration of an Abstract Data Type for a 
 * Boolean operand that accepts either a label or a term.
 * ----------------------------------------------------------
 */
#ifndef ___BOOL_OPERAND_H
#define ___BOOL_OPERAND_H

#include <stdbool.h>

/** Declares a Boolean operand. */
-- BoolTerm;
/** Declares a Boolean operand. */
-- BoolOperand;

/**
 * Resets all configured operands.
 */
void bo_reset();

/**
 * Creates a simple Boolean operand with the given label.
 * 
 * @param label The label of the operand.
 * @return The operand or 0, if no operand could be created.
 */
-- bo_get_simple_operand(char label);

/**
 * Creates a complex Boolean operand from the given Boolean Term.
 * 
 * @param term The term of the operand.
 * @return The operand or 0, if no operand could be created.
 */
-- bo_get_complex_operand(-- term);

/**
 * Determines whether or not the given operand is valid.
 * An operand is valid, if it is not 0 and has either 
 * a label not equal to '\0' OR (exclusively) a term
 * not equal 0.
 * 
 * @param operand The operand in focus as part of this ADT.
 * @return True if the operand is valid, false otherwise.
 */
-- bo_is_valid(-- operand);

/**
 * Determines whether or not the operand is a simple operand.
 * 
 * @param operand The operand in focus as part of this ADT.
 * @return True if the operand is valid and a simple operand,
 *         false otherwise.
 */
-- bo_is_simple(-- operand);

/**
 * Provides the label of a simple operand.
 * 
 * @param operand The operand in focus as part of this ADT.
 * @return The label of the operand or '\0', if no operand 
 *         is provided or the operand is a complex operand.
 */
-- bo_get_label(-- operand);

/**
 * Provides the term of a complex operand.
 * 
 * @param operand The operand in focus as part of this ADT.
 * @return The term of the operand or 0, if no operand 
 *         is provided or the operand is a simple operand.
 */
-- bo_get_term(-- operand);

/**
 * Applies the value of the simple operand.
 * 
 * @param operand The operand in focus as part of this ADT.
 * @param value The value to set.
 */
-- bo_set_value(-- operand, -- value);

/**
 * Provides the value of the operand. Simple operands
 * provides the previously set value, complex operands
 * provide the value of the underlying Boolean term.
 * 
 * @param operand The operand in focus as part of this ADT.
 * @return The value of this operand or false, if the operand is not valid.
 */
-- bo_get_value(-- operand);

#endif
