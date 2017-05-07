//--------подключение библиотек--------------------------------------------------------
#include "Chip_W5100.h"		//содержит имена и прототипы	
#include <avr/io.h>			//ввод-вывод данных
#include <util/delay.h>		//обработка задержек


//--------базовые настройки W5100------------------------------------------------------
void W5100_init(void){
	CHIP_SETTINGS ethernet_settings;
	
	//--------выбор режима --------------------------------------------------------------
	SPI_WRITE(MR,0x80);								//для генерирования прерываний на чипе и разрешение операции ping
	_delay_ms(1);
	#if NET_TEST
	USART_STRING("Reading me MR:");
	CONVERT(SPI_READ(MR));
	USART_STRING("\n \n");
	#endif
	
	//--------GAR-----------------------------------------------------------------------
	#if NET_TEST
	USART_STRING("Setting Gateway Address (GAR):");		//GAR регистр устанавливаеn адрес шлюза по умолчанию
	USART_STRING("\r");

	CONVERT(ethernet_settings.gtw_addr[0]=192);				
	USART_STRING(".\r");
	CONVERT(ethernet_settings.gtw_addr[1]=168);
	USART_STRING(".\r");
	CONVERT(ethernet_settings.gtw_addr[2]=1);
	USART_STRING(".\r");
	CONVERT(ethernet_settings.gtw_addr[3]=1);
	USART_STRING("\n");
	#endif
	
	SPI_WRITE(GAR + 0,ethernet_settings.gtw_addr[0]=192);			
	SPI_WRITE(GAR + 1,ethernet_settings.gtw_addr[1]=168);
	SPI_WRITE(GAR + 2,ethernet_settings.gtw_addr[2]=1);
	SPI_WRITE(GAR + 3,ethernet_settings.gtw_addr[3]=1);
	_delay_ms(1);
	
	#if NET_TEST
	USART_STRING("Reading GAR:");
	CONVERT(SPI_READ(GAR + 0));
	USART_STRING(".\r");
	CONVERT(SPI_READ(GAR + 1));
	USART_STRING(".\r");
	CONVERT(SPI_READ(GAR + 2));
	USART_STRING(".\r");
	CONVERT(SPI_READ(GAR + 3));
	USART_STRING("\n \n");
	#endif
	
	//--------SHAR-----------------------------------------------------------------------
	#if NET_TEST
	USART_STRING("Setting Source Address (SHAR):");			//SHAR- регистр устанавливает адрес исходного оборудования
	USART_STRING("\r");										//мак адрес оборудования

	CONVERT(ethernet_settings.mac_addr[0]=0xB8);		
	USART_STRING(":\r");
	CONVERT(ethernet_settings.mac_addr[1]=0x88);
	USART_STRING(":\r");
	CONVERT(ethernet_settings.mac_addr[2]=0xE3);
	USART_STRING(":\r");
	CONVERT(ethernet_settings.mac_addr[3]=0xB7);
	USART_STRING(":\r");
	CONVERT(ethernet_settings.mac_addr[4]=0xE7);
	USART_STRING(":\r");
	CONVERT(ethernet_settings.mac_addr[5]=0xFF);
	USART_STRING("\n");
	#endif
	
	SPI_WRITE(SHAR + 0,ethernet_settings.mac_addr[0]=0xB8);		
	SPI_WRITE(SHAR + 1,ethernet_settings.mac_addr[1]=0x88);
	SPI_WRITE(SHAR + 2,ethernet_settings.mac_addr[2]=0xE3);
	SPI_WRITE(SHAR + 3,ethernet_settings.mac_addr[3]=0xB7);
	SPI_WRITE(SHAR + 4,ethernet_settings.mac_addr[4]=0xE7);
	SPI_WRITE(SHAR + 5,ethernet_settings.mac_addr[5]=0xFF);
	_delay_ms(1);
	
	#if NET_TEST
	USART_STRING("Reading SHAR:");
	USART_STRING(":\r");
	CONVERT(SPI_READ(SHAR + 0));
	USART_STRING(":\r");
	CONVERT(SPI_READ(SHAR + 1));
	USART_STRING(":\r");
	CONVERT(SPI_READ(SHAR + 2));
	USART_STRING(":\r");
	CONVERT(SPI_READ(SHAR + 3));
	USART_STRING(":\r");
	CONVERT(SPI_READ(SHAR + 4));
	USART_STRING(":\r");
	CONVERT(SPI_READ(SHAR + 5));
	USART_STRING("\n \n");
	#endif
	
	//--------SUBR----------------------------------------------------------------------
	#if NET_TEST
	USART_STRING("Setting Sub Mask Address (SUBR):");			//SUBR-регистр устанавливает адрес маски подсети
	USART_STRING("\r");

	CONVERT(ethernet_settings.sub_mask[0]=255);
	USART_STRING(".\r");
	CONVERT(ethernet_settings.sub_mask[1]=255);
	USART_STRING(".\r");
	CONVERT(ethernet_settings.sub_mask[2]=0);
	USART_STRING(".\r");
	CONVERT(ethernet_settings.sub_mask[3]=0);
	USART_STRING("\n");
	#endif
	
	SPI_WRITE(SUBR + 0,ethernet_settings.sub_mask[0]=255);		
	SPI_WRITE(SUBR + 1,ethernet_settings.sub_mask[1]=255);
	SPI_WRITE(SUBR + 2,ethernet_settings.sub_mask[2]=0);
	SPI_WRITE(SUBR + 3,ethernet_settings.sub_mask[3]=0);
	_delay_ms(1);

	#if NET_TEST
	USART_STRING("Reading SUBR:");
	USART_STRING("\r");
	CONVERT(SPI_READ(SUBR + 0));
	USART_STRING(".\r");
	CONVERT(SPI_READ(SUBR + 1));
	USART_STRING(".\r");
	CONVERT(SPI_READ(SUBR + 2));
	USART_STRING(".\r");
	CONVERT(SPI_READ(SUBR + 3));
	USART_STRING("\n \n");
	#endif
	
	//--------SIPR----------------------------------------------------------------------
	#if NET_TEST
	USART_STRING("Setting IP Address (SIPR):");		//SIPR-регистр утсанавливает ip адрес
	USART_STRING("\r");

	CONVERT(ethernet_settings.ip_addr[0]=192);
	USART_STRING(".\r");
	CONVERT(ethernet_settings.ip_addr[1]=168);
	USART_STRING(".\r");
	CONVERT(ethernet_settings.ip_addr[2]=1);
	USART_STRING(".\r");
	CONVERT(ethernet_settings.ip_addr[3]=2);
	USART_STRING("\n");
	#endif
	
	SPI_WRITE(SIPR + 0,ethernet_settings.ip_addr[0]=192);		
	SPI_WRITE(SIPR + 1,ethernet_settings.ip_addr[1]=168);
	SPI_WRITE(SIPR + 2,ethernet_settings.ip_addr[2]=1);
	SPI_WRITE(SIPR + 3,ethernet_settings.ip_addr[3]=2);
	_delay_ms(1);
	
	#if NET_TEST
	USART_STRING("Reading SIPR:");
	USART_STRING("\r");
	CONVERT(SPI_READ(SIPR + 0));
	USART_STRING(".\r");
	CONVERT(SPI_READ(SIPR + 1));
	USART_STRING(".\r");
	CONVERT(SPI_READ(SIPR + 2));
	USART_STRING(".\r");
	CONVERT(SPI_READ(SIPR + 3));
	USART_STRING("\n \n");
	#endif
	
	//-------RX_TX_MEMORY---------------------------------------------------------------
	#if NET_TEST
	USART_STRING("Setting Wiznet RMSR and TMSR\n\n");
	#endif
	SPI_WRITE(RMSR,0x55);					//используем 2КВ для RX/TX стр.23 dtsh
	SPI_WRITE(TMSR,0x55);
	
}//end W5100_init
//**********************************************************************************

