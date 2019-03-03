/*
 *      struct tm {
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


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libAddSubDate.h"

int main(int argc, char *argv[])
{

	int dia = 0;
	int mes = 0;
	int ano = 0;
	int hora = 0;
	int min = 0;
	int seg = 0;
	unsigned long delta = 0;
	a2gs_AddSubOperation_e op;
	struct tm endDate;
	int ret = 0;

	if(argc != 9){
		printf("%s <DIA> <MES> <ANO> <HORA> <MINUTO> <SEGUNDO> [+-] <DELTA SEGUNDOS>\n", argv[0]);
		return(0);
	}

	dia = atoi(argv[1]);
	mes = atoi(argv[2]);
	ano = atoi(argv[3]);

	hora = atoi(argv[4]);
	min  = atoi(argv[5]);
	seg  = atoi(argv[6]);

	delta = atol(argv[8]);

	if     (argv[7][0] == '+') op = ADD;
	else if(argv[7][0] == '-') op = SUB;
	else{
		printf("Only '+' or '-' operations.\n");
		return(0);
	}

	ret = a2gs_AddSubDate(ano, mes, dia, hora, min, seg, op, delta, &endDate);

	if(ret == -1){
		printf("Erro.\n");
		return(-1);
	}

	printf("%02d/%02d/%02d %02d:%02d:%02d %c %ld secs = %02d/%02d/%02d %02d:%02d:%02d, Week: %d, Day in the year: %d, Daylight saving time: %d\n",
	       dia, mes, ano, hora, min, seg,
	       argv[7][0], delta,
	       endDate.tm_mday, endDate.tm_mon + 1, endDate.tm_year + 1900, endDate.tm_hour, endDate.tm_min, endDate.tm_sec, endDate.tm_wday, endDate.tm_yday, endDate.tm_isdst);

	return(0);
}
