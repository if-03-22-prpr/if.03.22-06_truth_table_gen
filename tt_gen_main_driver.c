/*----------------------------------------------------------
 *				HTBLA-Leonding / Klasse: n/a
 * ---------------------------------------------------------
 * Exercise Number: 08
 * Title:			Truth Table
 * Author:			S. Schraml
 * Due Date:		n/a
 * ----------------------------------------------------------
 * Description:
 * Truth Table Generator Application.
 * ----------------------------------------------------------
 */

/** ui_branch handles the user interface mode of the application.
 * @see main, test_branch.
 */
void ui_branch();

/* Main function evaluates the number of command line arguments.
 * If the user passed one main switches into test mode, i.e., that
 * the function test_branch() is called and the command line argument
 * is handed over to this function. If no command line argument is given
 * main switches into user interface mode and delegates the handling
 * of this to the function ui_branch().
 * @see test_branch, ui_branch.
 */
int main(int argc, char *argv[])
{
	ui_branch();
	return 0;
}

void ui_branch()
{
	/* PLACE YOUR CODE HERE */
}
