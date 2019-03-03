/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 *
 * Lib calcDate
 *
 * Public Domain
 *
 */


/* libAddSubDate.h
 * Library calcDate include file
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 03/03/2019 | Creation
 *          |            |
 */


#ifndef __LIB_A2GS_ADDSUBDATE_H__
#define __LIB_A2GS_ADDSUBDATE_H__


/* *** INCLUDES ************************************************************************ */
#include <time.h>


/* *** DEFINES ************************************************************************* */
#define A2GS_ADDSUBDATE_DAY_TO_SECONDS(__dayToSec)	((time_t)((60*60*24) * __dayToSec))


/* *** DATA TYPES ********************************************************************** */
typedef enum{
	ADD = 1,
	SUB
}a2gs_AddSubOperation_e;


/* *** INTERFACES / PROTOTYPES ********************************************************* */
/* int wrapperData(int dia, int mes, int ano, int hora, int min, int seg, a2gs_AddSubOperation_e op, long delta, struct tm *ret)
 *
 * <Description>
 *
 * INPUT:
 *  dia - 
 *  mes - 
 *  ano -
 *  hora -
 *  min - 
 *  seg - 
 *  op - 
 *  delta - 
 * OUTPUT:
 *  ret - 
 *  0 - 
 *  -1 - 
 */
int a2gs_AddSubDate(int dia, int mes, int ano, int hora, int min, int seg, a2gs_AddSubOperation_e op, long delta, struct tm *ret);


/* *** EXAMPLE ************************************************************************* */
#if 0
#endif

#endif

