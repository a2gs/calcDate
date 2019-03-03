/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 *
 * Lib calcDate
 *
 * Public Domain
 *
 */


/* libAddSubDate.c
 * Lib do add/subtract date.
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 03/03/2019 | Creation
 *          |            |
 */


/* *** INCLUDES ************************************************************************ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "libAddSubDate.h"


/* *** DEFINES AND LOCAL DATA TYPE DEFINATION ****************************************** */


/* *** LOCAL PROTOTYPES (if applicable) ************************************************ */


/* *** EXTERNS / LOCAL / GLOBALS VARIEBLES ********************************************* */


/*
        struct tm {
         int tm_sec;     * Seconds (0-60) * 
         int tm_min;     * Minutes (0-59) * 
         int tm_hour;    * Hours (0-23) * 
         int tm_mday;    * Day of the month (1-31) * 
         int tm_mon;     * Month (0-11) * 
         int tm_year;    * Year - 1900 * 
         int tm_wday;    * Day of the week (0-6, Sunday = 0) * 
         int tm_yday;    * Day in the year (0-365, 1 Jan = 0) * 
         int tm_isdst;   * Daylight saving time * 
     };

 The members of the tm structure are:
 tm_sec    The number of seconds after the minute, normally in the range 0 to 59, but can be up to 60 to allow for leap seconds.
 tm_min    The number of minutes after the hour, in the range 0 to 59.
 tm_hour   The number of hours past midnight, in the range 0 to 23.
 tm_mday   The day of the month, in the range 1 to 31.
 tm_mon    The number of months since January, in the range 0 to 11.
 tm_year   The number of years since 1900.
 tm_wday   The number of days since Sunday, in the range 0 to 6.
 tm_yday   The number of days since January 1, in the range 0 to 365.
 tm_isdst  A flag that indicates whether daylight saving time is in effect at the time described.  The value is positive if daylight saving time is in effect, zero if it is not, and negative if the information is not available.
*/

/* *** FUNCTIONS *********************************************************************** */
/* int a2gs_DateCalculation(struct tm *dataStart, a2gs_AddSubOperation_e op, long delta, struct tm *dataEnd)
 *
 *
 *
 * INPUT:
 *  dataStart -
 *  op -
 *  delta -
 * OUTPUT:
 *  dataEnd -
 *  0 -
 *  -1 -
 */
int a2gs_DateCalculation(struct tm *dataStart, a2gs_AddSubOperation_e op, long delta, struct tm *dataEnd)
{
	struct tm *dataOut;
	time_t dataInBroken, dataOutBroken; 

	dataInBroken = mktime(dataStart);
	if(dataInBroken == (time_t)-1)
		return(-1);

	if     (op == ADD) dataOutBroken = dataInBroken + delta;
	else if(op == SUB) dataOutBroken = dataInBroken - delta;

	dataOut = gmtime(&dataOutBroken);

	memcpy(dataEnd, dataOut, sizeof(struct tm));

	return(0);
}

int a2gs_AddSubDate(int dia, int mes, int ano, int hora, int min, int seg, a2gs_AddSubOperation_e op, long delta, struct tm *dataEnd)
{
	struct tm dataStart;
	char *tzname_save[2];
	long timezone_save;
	int daylight_save;
	char *envTZ_save = NULL;
	char fullEnvTZ_save[80] = {0};

	extern long timezone;
	extern char *tzname[2];
   extern int daylight;

	memset(&dataStart, 0, sizeof(struct tm));
	memset(dataEnd,    0, sizeof(struct tm));

	/* Saving the TimeZone */
	tzset();
	tzname_save[0] = tzname[0]; tzname_save[1] = tzname[1];
	timezone_save = timezone; daylight_save = daylight;
	envTZ_save = secure_getenv("TZ");

	/* Setting timezone to UTC */
	daylight = 0;
	timezone = 0;
	tzname[0] = tzname[1] = "GMT";

	if(setenv("TZ", "UTC", 1) == -1)
		return(-1);

	dataStart.tm_sec = seg;
	dataStart.tm_min = min;
	dataStart.tm_hour = hora;
	dataStart.tm_mday = dia;
	dataStart.tm_mon = mes - 1;
	dataStart.tm_year = ano - 1900;
	dataStart.tm_isdst = 0;

	if(a2gs_DateCalculation(&dataStart, op, delta, dataEnd) == -1)
		return(-1);

	/* Restoring the TimeZone */
	tzname[0] = tzname_save[0]; tzname[1] = tzname_save[1];
	timezone = timezone_save; daylight = daylight_save;
	snprintf(fullEnvTZ_save, sizeof(fullEnvTZ_save), "TZ=%s", envTZ_save);

	if(putenv(fullEnvTZ_save) != 0)
		return(-1);

	return(0);
}
