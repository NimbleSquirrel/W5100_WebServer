//--------подключение библиотек-----------------------------------------------------
#include "Chip_W5100.h"
#include <avr/io.h>						//ввод-вывод данных
#include <util/delay.h>					//обработка задержек

//========ОСНОВНЫЕ КОМАНДЫ ДЛЯ РАБОТЫ СОКЕТОВ=======================================
//--------закрытие сокета-----------------------------------------------------------
void close(unsigned char sock){
	if (sock != 0) return;				//проверяем,если сокет открыт
	SPI_WRITE(S0_CR,CR_CLOSE);			//даем команду закрыть сокет
	while(SPI_READ(S0_CR));				//ждем,когда регистр автоматически очистится
}
//**********************************************************************************

//--------разрыв соединения---------------------------------------------------------
void disconnect(unsigned char sock){
	if (sock != 0) return;
	SPI_WRITE(S0_CR,CR_DISCON);			//даем команду на разрыв соединения
	while(SPI_READ(S0_CR));				//ждем,окончания процесса разъединения
}
//**********************************************************************************

//--------настройка передачи данных и сокета----------------------------------------
unsigned char socket(unsigned char sock,unsigned char eth_protocol,unsigned int tcp_port){
	unsigned char retval=0;
	if (sock != 0) return retval;

	if (SPI_READ(S0_SR) == SOCK_CLOSED) {		//проверяем закрыт ли сокет
		close(sock);
	}		
	SPI_WRITE(S0_MR,eth_protocol);				//устанавливаем режим работы для 0 сокета
	SPI_WRITE(S0_PORT,((tcp_port & 0xFF00) >> 8 ));
	SPI_WRITE(S0_PORT + 1,(tcp_port & 0x00FF));
	SPI_WRITE(S0_CR,CR_OPEN);                   //открываем сокет

	while(SPI_READ(S0_CR));						//ждем когда регистр очистится
		if (SPI_READ(S0_SR) == SOCK_INIT)			//проверяем статус сокета
			retval=1;									//если инициализация прошла успешно
		else
			close(sock);								//иначе закрыть сокет

	return retval;
}//end unsigned char socket
//**********************************************************************************

//--------прослушка-----------------------------------------------------------------
unsigned char listen(unsigned char sock){		//ожидаем запрос от клиента
	unsigned char retval = 0;					//присваиваем переменной значение
	if (sock != 0) return retval;
		if (SPI_READ(S0_SR) == SOCK_INIT){		//если сокет настроен верно, равен процессу инициализации
			SPI_WRITE(S0_CR,CR_LISTEN);			//даем команду "прослушать" соединение
			while(SPI_READ(S0_CR));				//ждем завершения процесса прослушки,очищаем регистр
			if (SPI_READ(S0_SR) == SOCK_LISTEN)
			retval=1;
			else
			close(sock);						//команда закрытия сокета
		}
	return retval;
}//unsigned char listen(unsigned char sock)
//*********************************************************************************

//-------отправка данных через сокет-----------------------------------------------
unsigned int send(unsigned char sock,const unsigned *buf,unsigned int buflen){
	unsigned int ptr,offaddr,realaddr,txsize,timeout;

		if (buflen <= 0 || sock != 0) return 0;
		#if SOCKET_TEST					
		USART_STRING("Размер отправляемых данных:");
		CONVERT(SPI_READ(buflen));
		USART_STRING("\n \n");
		#endif
	
		txsize=SPI_READ(S0_TX_FSR);			//убеждаемся, что TX_Free Size Register доступен для использования
		txsize=(((txsize & 0x00FF) << 8 ) + SPI_READ(S0_TX_FSR + 1));
		#if SOCKET_TEST							//выводим данные о размере пакета
		USART_STRING("Размер TX:");
		CONVERT(SPI_READ(txsize));
		USART_STRING("\n \n");
		#endif
	
		timeout=0;
		while (txsize < buflen) {
			_delay_ms(1);
			txsize=SPI_READ(S0_TX_FSR);
			txsize=(((txsize & 0x00FF) << 8 ) + SPI_READ(S0_TX_FSR + 1));
					
			if (timeout++ > 1000) {					//если ожидание более чем 1000 ms
			#if SOCKET_TEST
				USART_STRING("Ошибка передачи данных!");
			#endif
				disconnect(sock);					//разорвать соединение
				return 0;
			}
		}//while (txsize < buflen) 

		ptr = SPI_READ(S0_TX_WR);
		offaddr = (((ptr & 0x00FF) << 8 ) + SPI_READ(S0_TX_WR + 1));
		#if SOCKET_TEST
			USART_STRING("TX Buffer:");
			CONVERT(SPI_READ(offaddr));
		#endif

		while(buflen) {
				buflen--;			
				realaddr = TX_BUF_ADDR + (offaddr & TX_BUF_MASK);		//вычисляем физический адрес для буфера		
				SPI_WRITE(realaddr,*buf);								//производим копирование данных приложения в буфер W5100 Tx
				offaddr++;
				buf++;
		}//while(buflen)

		SPI_WRITE(S0_TX_WR,(offaddr & 0xFF00) >> 8 );					//Увеличиваем значение S0_TX_WR,чтобы могли передаваться новые данные
		SPI_WRITE(S0_TX_WR + 1,(offaddr & 0x00FF));
		SPI_WRITE(S0_CR,CR_SEND);										//отправляем команду "послать данные" регистру работы с сокетами
 		while(SPI_READ(S0_CR));											//ждем отправки	
		return 1;
}//unsigned int send
//******************************************************************************************

//--------обработка данных запроса----------------------------------------------------------
unsigned int recv(unsigned char sock,unsigned char *buf,unsigned int buflen){
		unsigned int ptr,offaddr,realaddr;

		if (buflen <= 0 || sock != 0) return 1;						//проверяем, если
		
		if (buflen > MAX_BUF)										//Если размер запроса> MAX_BUF допутимого размера,обрезаем данные
		buflen=MAX_BUF - 2;
		ptr = SPI_READ(S0_RX_RD);									//прочитываем с указателя
		offaddr = (((ptr & 0x00FF) << 8 ) + SPI_READ(S0_RX_RD + 1));
		#if TEST
		printf("RX Buffer: %x\n",offaddr);
		#endif

		while(buflen){
			buflen--;
			realaddr=RX_BUF_ADDR + (offaddr & RX_BUF_MASK);
			*buf = SPI_READ(realaddr);
			offaddr++;
			buf++;
		}
		*buf='\0';												 //Завершение передачи строки
		
		SPI_WRITE(S0_RX_RD,(offaddr & 0xFF00) >> 8 );			//увеличиваем занчение регистра S0_RX_RD,он указывает на следующего получателя
		SPI_WRITE(S0_RX_RD + 1,(offaddr & 0x00FF));		
		SPI_WRITE(S0_CR,CR_RECV);								 //отправляем командуы 
		_delay_us(5);											 //Ожидание завершения проыесса передачи

		return 1;
}//unsigned int recv
//**********************************************************************************************

//--------размер запроса------------------------------------------------------------------------
unsigned int recv_size(void){														//размер запроса
	return ((SPI_READ(S0_RX_RSR) & 0x00FF) << 8 ) + SPI_READ(S0_RX_RSR + 1);		//считываем размер данных,получаемых в RX
}
//**********************************************************************************************

//--------
int strindex(char *s,char *t){
	unsigned int i,n;

	n=strlen(t);
	for(i=0;*(s+i); i++) {
		if (strncmp(s+i,t,n) == 0)
		return i;
	}
	return -1;
}//end int strindex
//************************************************************************************************
//================================================================================================

