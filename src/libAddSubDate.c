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

/*
 * 1 - is
 * 0 - is not
 */
int a2gs_AddSubDate_isLeapYear(int year)
{
	/* ugly but little less computation */
	if(year % 4 == 0){
		if(year % 100 == 0){
			if(year % 400 == 0)
				return(1);
			return(0);
		}
		return(1);
	}

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

	if     (mes == 1  && (dia < 1 || dia > 31)) return(-1);
	else if(mes == 2  && (dia < 1 || dia > 29)) return(-1);
	else if(mes == 3  && (dia < 1 || dia > 31)) return(-1);
	else if(mes == 4  && (dia < 1 || dia > 30)) return(-1);
	else if(mes == 5  && (dia < 1 || dia > 31)) return(-1);
	else if(mes == 6  && (dia < 1 || dia > 30)) return(-1);
	else if(mes == 7  && (dia < 1 || dia > 31)) return(-1);
	else if(mes == 8  && (dia < 1 || dia > 31)) return(-1);
	else if(mes == 9  && (dia < 1 || dia > 30)) return(-1);
	else if(mes == 10 && (dia < 1 || dia > 31)) return(-1);
	else if(mes == 11 && (dia < 1 || dia > 30)) return(-1);
	else if(mes == 12 && (dia < 1 || dia > 31)) return(-1);

	if(seg  < 0 || seg  > 59) return(-1);
	if(min  < 0 || min  > 59) return(-1);
	if(hora < 0 || hora > 23) return(-1);

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
