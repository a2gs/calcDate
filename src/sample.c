/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 *
 * Sample lib calcDate
 *
 * Public Domain
 *
 */


/* sample.c
 * Sample to lib calcDate
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 03/03/2019 | Creation
 *          |            |
 */


/* *** INCLUDES ************************************************************************ */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "libAddSubDate.h"


/* *** DEFINES AND LOCAL DATA TYPE DEFINATION ****************************************** */


/* *** LOCAL PROTOTYPES (if applicable) ************************************************ */


/* *** EXTERNS / LOCAL / GLOBALS VARIEBLES ********************************************* */


/* *** FUNCTIONS *********************************************************************** */
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

	/* ret = a2gs_AddSubDate(dia, mes, ano, hora, min, seg, op, A2GS_ADDSUBDATE_DAY_TO_SECONDS(delta_in_days), &endDate); */
	ret = a2gs_AddSubDate(dia, mes, ano, hora, min, seg, op, delta, &endDate);

	if(ret == -1){
		printf("Erro.\n");
		return(-1);
	}

	printf("%02d/%02d/%02d %02d:%02d:%02d %c %ld secs = %02d/%s (%02d)/%02d %02d:%02d:%02d, Week: %s (%d), Day in the year: %d, Daylight saving time: %d\n",
	       dia, mes, ano, hora, min, seg,
	       argv[7][0], delta,
	       endDate.tm_mday, A2GS_ADDSUBDATE_N_MONTH_TO_MONTH_STR(endDate.tm_mon), A2GS_ADDSUBDATE_MONTH(endDate.tm_mon), A2GS_ADDSUBDATE_YEAR(endDate.tm_year),
	       endDate.tm_hour, endDate.tm_min, endDate.tm_sec, A2GS_ADDSUBDATE_N_DAY_TO_WEEK_STR(endDate.tm_wday), A2GS_ADDSUBDATE_WEEK(endDate.tm_wday),
	       endDate.tm_yday, endDate.tm_isdst);

	return(0);
}
