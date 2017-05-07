//--------подключение библиотек----------------------------------------------------
#include <avr/io.h>			//ввод/вывод данных
#include <util/delay.h>		//обработка задержек
#include <stdio.h>			//библиотека стандартного ввода-вывода printf
#include <avr/pgmspace.h>	//обепечивает возможность обращения к данным хранимым во flash
#include "Chip_W5100.h"		//библиотека для управления чипом w5100
//---------------------------------------------------------------------------------

//========ГЛАВНАЯ ФУНКЦИЯ===========================================================
//==================================================================================
int main(void){
//---------локальные переменные-----------------------------------------------------
unsigned char sockstat;			//режим в котором находится сокет
unsigned int rsize;				//размер данных
int getidx,postidx;				//переменные get и post запросов

sockreg=0;						//значение переменной

//---------отключение предделителя--------------------------------------------------
CLKPR|= (1<<CLKPCE);				//разрешаем изменения предделителя
CLKPR = 0x00;						//отключаем предделитель
//*********************************************************************************

//-------инициализация работы устройств--------------------------------------------
USART_INIT();						//инициализация работы usart 
SPI_MASTER();						//инициализируем spi
W5100_init();						//инициализируем работу w5100
//*********************************************************************************

//--------фоновая программа---------------------------------------------------------
	for(;;){
			sockstat=SPI_READ(S0_SR);
			switch(sockstat) {
				case SOCK_CLOSED:
				if (socket(sockreg,MR_TCP,TCP_PORT) > 0) {					
					if (listen(sockreg) <= 0)		//слушаем сокет,ожидаем запроса от клиента
					_delay_ms(1);
					#if SOCKET_TEST
						USART_STRING("Socket Listen!\n");
					#endif
				}
				break;
				case SOCK_ESTABLISHED:				
				rsize=recv_size();					//получить размер клиентского запроса
				#if SOCKET_TEST
					USART_STRING("Size: %d\n");
					CONVERT(SPI_READ(rsize));
				#endif
				if (rsize > 0) {					
					if (recv(sockreg,buf,rsize) <= 0) break;		//читаем клиенский запрос
					#if SOCKET_TEST
						USART_STRING("Content:\n%s\n");
						CONVERT(SPI_READ(buf));
					#endif					
					getidx=strindex((char *)buf,"GET /");			//проверка заголовка запроса
					postidx=strindex((char *)buf,"POST /");
					if (getidx >= 0 || postidx >= 0) {
						#if SOCKET_TEST
							USART_STRING("Request Checked!\n");
						#endif
										
						#if SOCKET_TEST
							USART_STRING("Request Send!\n");
						#endif
						/*--------------------формируем структуру веб-страницы-----------------------*/	
						 strcpy_P((char *)buf,PSTR("<html><body><h1>HELLO WORLD!</h1></body></html>"));
						 //strcpy_P((char *)buf,PSTR("HTTP/text/html"));
						 //strcat_P((char *)buf,PSTR("<h1>HELLO!</h1>"));						 
																	
						if (send(sockreg,buf,strlen((char *)buf)) <= 0) break;			//отвечаем на запрос
					if (send(sockreg,buf,strlen((char *)buf)) <= 0) break;
					}					
					disconnect(sockreg);			//разрыв соедиения
				} else
				_delay_us(10);						//ожидание запроса
				break;
				case SOCK_FIN_WAIT:
				case SOCK_CLOSING:
				case SOCK_TIME_WAIT:
				case SOCK_CLOSE_WAIT:
				case SOCK_LAST_ACK:				
				close(sockreg);						//закрытие сокета
				#if SOCKET_TEST
					USART_STRING("Socket Close!\n");
				#endif
				break;
			}
		}//for(;;)
		return 0;
}//end main
//==================================================================================

