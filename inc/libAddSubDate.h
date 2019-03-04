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
#define A2GS_ADDSUBDATE_DAY_TO_SECONDS(__a2gs_addsubdate_dayToSec__)   			((time_t)((60*60*24) * __a2gs_addsubdate_dayToSec__))
#define A2GS_ADDSUBDATE_N_DAY_TO_WEEK_STR(__a2gs_addsubdate_nWeekDay__)			(a2gs_AddSubDate_weekDay[__a2gs_addsubdate_nWeekDay__])
#define A2GS_ADDSUBDATE_N_MONTH_TO_MONTH_STR(__a2gs_addsubdate_nMonth__)		(a2gs_AddSubDate_Months[__a2gs_addsubdate_nMonth__])
#define A2GS_ADDSUBDATE_YEAR(__a2gs_addsubdate_nYear__)								(__a2gs_addsubdate_nYear__ + 1900)
#define A2GS_ADDSUBDATE_MONTH(__a2gs_addsubdate_nMonth__)							(__a2gs_addsubdate_nMonth__ + 1)
#define A2GS_ADDSUBDATE_WEEK(__a2gs_addsubdate_nWeek__)								(__a2gs_addsubdate_nWeek__ + 1)


/* *** DATA TYPES ********************************************************************** */
typedef enum{
	ADD = 1,
	SUB
}a2gs_AddSubOperation_e;

static char *a2gs_AddSubDate_weekDay[] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
static char *a2gs_AddSubDate_Months[]  = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};


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

/* int a2gs_AddSubDate_isLeapYear(int year)
 *
 * Return if a year (YYYY) is lead or not.
 *
 * INPUT:
 *  year - year to check
 * OUTPUT:
 *  0 - is not a leap year
 *  1 - is a leap year
 */
int a2gs_AddSubDate_isLeapYear(int year);

/* *** EXAMPLE ************************************************************************* */
#if 0
#endif

#endif

