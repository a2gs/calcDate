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
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

long calcNDays(int ano, int mes, int dia, int nDias, int *retAno, int *retMes, int *retDia)
{
	struct tm dataIn, *dataOut;
	time_t dataInBroken, dataOutBroken; 

	memset(&dataIn, 0, sizeof(struct tm));

	dataIn.tm_sec = 0;
	dataIn.tm_min = 0;
	dataIn.tm_hour = 0;
	dataIn.tm_mday = dia;
	dataIn.tm_mon = mes - 1;
	dataIn.tm_year = ano - 1900;
	dataIn.tm_isdst = 0;

	dataInBroken = mktime(&dataIn);
	if(dataInBroken == (time_t)-1)
		return(-1);

	dataOutBroken = dataInBroken + ((60*60*24) * nDias); /* um dia */

	dataOut = gmtime(&dataOutBroken);

	*retDia = dataOut->tm_mday;
	*retMes = (dataOut->tm_mon + 1);
	*retAno = dataOut->tm_year + 1900;

	/*return(((dataOut->tm_mday * 1000000) + (dataOut->tm_mon+1) * 10000) + (dataOut->tm_year+1900));*/
	return(0);
}

int wrapperData(int dia, int mes, int ano, int hora, int min, int seg, long DELTA, struct tm *ret)
{
	return(0);
}

int main(int argc, char *argv[])
{

	int dia = 0, retDia = 0;
	int mes = 0, retMes = 0;
	int ano = 0, retAno = 0;
	int nDias = 0;
	struct tm endDate;

	int ret = 0l;

	if(argc != 5){
		printf("%s <DIA> <MES> <ANO> <HORA> <MINUTO> <SEGUNDO> <[+-]nDIAS (((SEGUNDOS)))>\n", argv[0]);
		return(0);
	}

	dia = atoi(argv[1]);
	mes = atoi(argv[2]);
	ano = atoi(argv[3]);
	nDias = atoi(argv[4]);

	/* ret = wrapperData(dia, mes, ano, hora, min, seg, nSegs, &endDate); */
	ret = calcNDays(ano, mes, dia, nDias, &retAno, &retMes, &retDia);

	if(ret == -1){
		printf("Erro.\n");
		return(-1);
	}

	printf("%02d/%02d/%02d + (%d dias) = %02d/%02d/%02d\n", dia, mes, ano, nDias, retDia, retMes, retAno);

	return(0);
}
