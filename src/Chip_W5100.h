//-------структура препроцессорной обёртки-----------------------------------------
#ifndef CHIP_W5100_H
	#define CHIP_W5100_H
//---------------------------------------------------------------------------------
	
//========макроподстановки========================================================
//--------порты для USART----------------------------------------------------------
#define SS				2		//выбор ведомого устройства
#define MOSI			3		//выход послед.передачи данных
#define MISO			4		//вход послед.приема данных
#define SCK				5		//выход синхронизации передачи данных

//-------USART---------------------------------------------------------------------
#define FOSC			16000000 // Clock Speed
#define BAUD			9600
#define NET_TEST		0		//объявляем тест для работы с USART и вывода данных через COM порт
								//0-режим теста отключен, 1- режим теста включен, провнрка настроек сети
#define SOCKET_TEST		1		//объявляем тест, проверяем настройки сокетов
//--------порядок передачи данных--------------------------------------------------
#define MSB_FIRST		1		//передача старшего бита
#define LSB_FIRST		0		//передача младешего бита

//--------W5100 op-code------------------------------------------------------------
#define WRITE_OPCODE	0xF0	//инициализируем операцию записи
#define READ_OPCODE		0x0F	//инициализируем операцию чтения

//--------W5100 адреса общих регистров---------------------------------------------
#define MR				0x0000		// регистр режима
#define GAR				0x0001		// адрес шлюза: 0x0001 до 0x0004
#define SUBR			0x0005		// адрес маски подсети: 0x0005 до 0x0008
#define SHAR			0x0009		// аппаратный адрес (MAC): 0x0009 до 0x000E
#define SIPR			0x000F		// IP адрес: 0x000F to 0x0012
#define RMSR			0x001A		// RX регистр размера памяти
#define TMSR			0x001B		// TX регистр размера памяти

//--------W5100 адреса регистров сокетов-------------------------------------------
#define S0_MR			0x0400		//уст тип и операцию протокола для каждого сокета
#define S0_CR			0x0401		//для инициализации сокета, настройка для передачи/получения команд(OPEN/LISTEN,CONNECT)
#define S0_IR			0x0402		//для уведомления об уст. и обрыве соединения
#define S0_SR			0x0403		//проверка состояния сокета,если протокол TCP
#define S0_PORT			0x0404		//уст. номер исходного порта для каждого сокета 0x0404-0x0405
#define S0_DHAR			0x0406		//mac адрес каждого сокета 0x0406-0x040B
#define S0_DIPR			0x040C		//ip каждого сокета 0x040C-0x040F
#define S0_DPORT		0x0410		//уст.номер порта назначенного для сокета
#define S0_MSSR			0x0412		//определяет максимальный размер сегмента TCP
#define S0_TTL			0x0416		//настраивается в поле TTL
#define S0_TX_FSR		0x0420		//уведомление пользователя о размере данных,которые он может отправить
#define S0_TX_RD		0x0422      //показывает адрес,который завершает передачу в память TX
#define S0_TX_WR		0x0424      //для вычислений MAC адресов вручную
#define S0_RX_RSR		0x0426      //сообщает размер данных, полученных в RX
#define S0_RX_RD		0x0428      //инф о местоположении считываемых файлов

#define TX_BUF_ADDR		0x4000      // область данных выделяемая для сокета
#define RX_BUF_ADDR		0x6000      // 

#define MR_CLOSE		0x00		// Unused socket
#define MR_TCP			0x01		// TCP
#define MR_UDP			0x02		// UDP 
#define MR_IPRAW		0x03		// IP LAYER RAW SOCK
#define MR_MACRAW		0x04		// MAC LAYER RAW SOCK
#define MR_PPPOE		0x05		// PPPoE
#define MR_ND			0x20		// Ack(TCP) flag
#define MR_MULTI		0x80		// поддержка многоадресной рассылки

#define CR_OPEN			0x01		//для инициализации сокета 
#define CR_LISTEN		0x02		//получение запроса от клиента
#define CR_CONNECT		0x04		//отправляет запрс на соединение удаленному узлу
#define CR_DISCON		0x08		//запрос на прекращение соеднения 
#define CR_CLOSE		0x10		//закрывает сокет
#define CR_SEND			0x20		//связан с передачей данных Soket TX write
#define CR_SEND_MAC		0x21		//отправка данных по мак адресу
#define CR_KEEP			0x22		//проверяет соединение 
#define CR_RECV			0x40		//обработка принятых данных из RX

//---------регистр состояния сокетов------------------------------------------------
#define SOCK_CLOSED      0x00		// закрыт
#define SOCK_INIT        0x13		// состояние инициализации
#define SOCK_LISTEN      0x14		// прослушка
#define SOCK_SYNSENT     0x15		// соединение 
#define SOCK_SYNRECV     0x16		// соедниение 
#define SOCK_ESTABLISHED 0x17		// проверка успешности соединения
#define SOCK_FIN_WAIT    0x18		// состояние закрыт
#define SOCK_CLOSING     0x1A		// закрытие сокета
#define SOCK_TIME_WAIT	 0x1B		// время ожидания для сокета
#define SOCK_CLOSE_WAIT  0x1C		// ожидание для закрытия сокета
#define SOCK_LAST_ACK    0x1D		// состояние закрыт
#define SOCK_UDP         0x22		// UDP сокет
#define SOCK_IPRAW       0x32		// IP raw режим работы сокета
#define SOCK_MACRAW      0x42		// MAC raw режим работы сокета
#define SOCK_PPPOE       0x5F		// PPPOE socket

#define TX_BUF_MASK      0x07FF		// Tx 2K Buffer Mask:
#define RX_BUF_MASK      0x07FF		// Rx 2K Buffer Mask:
#define NET_MEMALLOC     0x05		// используем 2k Rx/Tx buffer

#define TCP_PORT		 80			// TCP/IP порт 

#define MAX_BUF			 512		// определяем размер буфера 

//-------ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ----------------------------------------------------
unsigned sockreg;					//определяем регистр сокетов и используем регистры W5100	
unsigned char buf[MAX_BUF];	
//=================================================================================

//--------прототипы функций--------------------------------------------------------
void W5100_init(void);									//базовые настройки W5100
void USART_INIT(void);                                  //инициализация работы usart
void USART_Transmitt(unsigned char value);				//передача данных по USART
void USART_STRING(char *string);						//передача строки по USART
void CONVERT(int n);									//преобразование значений из DEC в HEX
void SPI_MASTER(void);									//базовые настройки spi
void SPI_WRITE(unsigned int addr,unsigned char Data);	//передача данных по spi
unsigned char SPI_READ(unsigned int addr);				//прием данных по spi
void close(unsigned char sock);							//команда закрыть сокет
void disconnect(unsigned char sock);					//даем команду на разрыв соединения
//настройка режима работы сокета,пррверка его статуса
unsigned char socket(unsigned char sock,unsigned char eth_protocol,unsigned int tcp_port);
unsigned char listen(unsigned char sock);				//прослушка сокета, ожидаем запрос от клиента
//настройка отправки данных, определение размера пакета передачи
unsigned int send(unsigned char sock,const unsigned *buf,unsigned int buflen);
void close(unsigned char sock);							//команда закрытия сокета
void disconnect(unsigned char sock);					//разрыв установленного соединения
//настройка передачи данных,отправка основных команд сокету
unsigned char socket(unsigned char sock,unsigned char eth_protocol,unsigned int tcp_port);
unsigned char listen(unsigned char sock);				//"прослушка"ожидание запроса от клиента
//отправка данных через сокет,заполнение буфера
unsigned int send(unsigned char sock,const unsigned *buf,unsigned int buflen);
//обработка принятых данных
unsigned int recv(unsigned char sock,unsigned char *buf,unsigned int buflen);
unsigned int recv_size(void);							//вычисление
int strindex(char *s,char *t);							//индексация
//************************************************************************************

//--------структуры-------------------------------------------------------------------
typedef struct chip_w5100	{			//определяем структуру с именем chip_w5100
	unsigned char mac_addr[6];			//структура является шаблоном
	unsigned char ip_addr[4];			//здесь будут храниться данные о подсети
	unsigned char sub_mask[4];
	unsigned char gtw_addr[4];
}CHIP_SETTINGS;

//*************************************************************************************

/*chip_w5100 ethernet_config={
	{0xB8,0x88,0xE3,0xB7,0xE7,0xFF},
	{192,168,1,2},
	{255,255,0,0},
	{192,168,1,1},
};*/
#endif	//структура препроцессорной обертки	