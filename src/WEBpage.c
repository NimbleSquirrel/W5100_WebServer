//--------подключение библиотек------------------------------------------------------
/*#include "Chip_W5100.h"		//содержит имена и прототипы
#include <avr/io.h>			//ввод-вывод данных
#include <util/delay.h>		//обработка задержек

//-------оформление HTTP запроса------------------------------------------------------
strcpy_P((char *)buf,PSTR("HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n"));		//оформляем состав запроса
strcat_P((char *)buf,PSTR("<h1>HELLO WORLD</h1>\r\n"));
strcat_P((char *)buf,PSTR("<p><form method=\"POST\">\r\n"));
 
if (send(sockreg,buf,strlen((char *)buf)) <= 0) break;	*/								//Теперь отправояем HTTP-ответ
 
 