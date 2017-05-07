//-------��������� ��������������� ������-----------------------------------------
#ifndef CHIP_W5100_H
	#define CHIP_W5100_H
//---------------------------------------------------------------------------------
	
//========����������������========================================================
//--------����� ��� USART----------------------------------------------------------
#define SS				2		//����� �������� ����������
#define MOSI			3		//����� ������.�������� ������
#define MISO			4		//���� ������.������ ������
#define SCK				5		//����� ������������� �������� ������

//-------USART---------------------------------------------------------------------
#define FOSC			16000000 // Clock Speed
#define BAUD			9600
#define NET_TEST		0		//��������� ���� ��� ������ � USART � ������ ������ ����� COM ����
								//0-����� ����� ��������, 1- ����� ����� �������, �������� �������� ����
#define SOCKET_TEST		1		//��������� ����, ��������� ��������� �������
//--------������� �������� ������--------------------------------------------------
#define MSB_FIRST		1		//�������� �������� ����
#define LSB_FIRST		0		//�������� ��������� ����

//--------W5100 op-code------------------------------------------------------------
#define WRITE_OPCODE	0xF0	//�������������� �������� ������
#define READ_OPCODE		0x0F	//�������������� �������� ������

//--------W5100 ������ ����� ���������---------------------------------------------
#define MR				0x0000		// ������� ������
#define GAR				0x0001		// ����� �����: 0x0001 �� 0x0004
#define SUBR			0x0005		// ����� ����� �������: 0x0005 �� 0x0008
#define SHAR			0x0009		// ���������� ����� (MAC): 0x0009 �� 0x000E
#define SIPR			0x000F		// IP �����: 0x000F to 0x0012
#define RMSR			0x001A		// RX ������� ������� ������
#define TMSR			0x001B		// TX ������� ������� ������

//--------W5100 ������ ��������� �������-------------------------------------------
#define S0_MR			0x0400		//��� ��� � �������� ��������� ��� ������� ������
#define S0_CR			0x0401		//��� ������������� ������, ��������� ��� ��������/��������� ������(OPEN/LISTEN,CONNECT)
#define S0_IR			0x0402		//��� ����������� �� ���. � ������ ����������
#define S0_SR			0x0403		//�������� ��������� ������,���� �������� TCP
#define S0_PORT			0x0404		//���. ����� ��������� ����� ��� ������� ������ 0x0404-0x0405
#define S0_DHAR			0x0406		//mac ����� ������� ������ 0x0406-0x040B
#define S0_DIPR			0x040C		//ip ������� ������ 0x040C-0x040F
#define S0_DPORT		0x0410		//���.����� ����� ������������ ��� ������
#define S0_MSSR			0x0412		//���������� ������������ ������ �������� TCP
#define S0_TTL			0x0416		//������������� � ���� TTL
#define S0_TX_FSR		0x0420		//����������� ������������ � ������� ������,������� �� ����� ���������
#define S0_TX_RD		0x0422      //���������� �����,������� ��������� �������� � ������ TX
#define S0_TX_WR		0x0424      //��� ���������� MAC ������� �������
#define S0_RX_RSR		0x0426      //�������� ������ ������, ���������� � RX
#define S0_RX_RD		0x0428      //��� � �������������� ����������� ������

#define TX_BUF_ADDR		0x4000      // ������� ������ ���������� ��� ������
#define RX_BUF_ADDR		0x6000      // 

#define MR_CLOSE		0x00		// Unused socket
#define MR_TCP			0x01		// TCP
#define MR_UDP			0x02		// UDP 
#define MR_IPRAW		0x03		// IP LAYER RAW SOCK
#define MR_MACRAW		0x04		// MAC LAYER RAW SOCK
#define MR_PPPOE		0x05		// PPPoE
#define MR_ND			0x20		// Ack(TCP) flag
#define MR_MULTI		0x80		// ��������� ������������� ��������

#define CR_OPEN			0x01		//��� ������������� ������ 
#define CR_LISTEN		0x02		//��������� ������� �� �������
#define CR_CONNECT		0x04		//���������� ����� �� ���������� ���������� ����
#define CR_DISCON		0x08		//������ �� ����������� ��������� 
#define CR_CLOSE		0x10		//��������� �����
#define CR_SEND			0x20		//������ � ��������� ������ Soket TX write
#define CR_SEND_MAC		0x21		//�������� ������ �� ��� ������
#define CR_KEEP			0x22		//��������� ���������� 
#define CR_RECV			0x40		//��������� �������� ������ �� RX

//---------������� ��������� �������------------------------------------------------
#define SOCK_CLOSED      0x00		// ������
#define SOCK_INIT        0x13		// ��������� �������������
#define SOCK_LISTEN      0x14		// ���������
#define SOCK_SYNSENT     0x15		// ���������� 
#define SOCK_SYNRECV     0x16		// ���������� 
#define SOCK_ESTABLISHED 0x17		// �������� ���������� ����������
#define SOCK_FIN_WAIT    0x18		// ��������� ������
#define SOCK_CLOSING     0x1A		// �������� ������
#define SOCK_TIME_WAIT	 0x1B		// ����� �������� ��� ������
#define SOCK_CLOSE_WAIT  0x1C		// �������� ��� �������� ������
#define SOCK_LAST_ACK    0x1D		// ��������� ������
#define SOCK_UDP         0x22		// UDP �����
#define SOCK_IPRAW       0x32		// IP raw ����� ������ ������
#define SOCK_MACRAW      0x42		// MAC raw ����� ������ ������
#define SOCK_PPPOE       0x5F		// PPPOE socket

#define TX_BUF_MASK      0x07FF		// Tx 2K Buffer Mask:
#define RX_BUF_MASK      0x07FF		// Rx 2K Buffer Mask:
#define NET_MEMALLOC     0x05		// ���������� 2k Rx/Tx buffer

#define TCP_PORT		 80			// TCP/IP ���� 

#define MAX_BUF			 512		// ���������� ������ ������ 

//-------���������� ����������----------------------------------------------------
unsigned sockreg;					//���������� ������� ������� � ���������� �������� W5100	
unsigned char buf[MAX_BUF];	
//=================================================================================

//--------��������� �������--------------------------------------------------------
void W5100_init(void);									//������� ��������� W5100
void USART_INIT(void);                                  //������������� ������ usart
void USART_Transmitt(unsigned char value);				//�������� ������ �� USART
void USART_STRING(char *string);						//�������� ������ �� USART
void CONVERT(int n);									//�������������� �������� �� DEC � HEX
void SPI_MASTER(void);									//������� ��������� spi
void SPI_WRITE(unsigned int addr,unsigned char Data);	//�������� ������ �� spi
unsigned char SPI_READ(unsigned int addr);				//����� ������ �� spi
void close(unsigned char sock);							//������� ������� �����
void disconnect(unsigned char sock);					//���� ������� �� ������ ����������
//��������� ������ ������ ������,�������� ��� �������
unsigned char socket(unsigned char sock,unsigned char eth_protocol,unsigned int tcp_port);
unsigned char listen(unsigned char sock);				//��������� ������, ������� ������ �� �������
//��������� �������� ������, ����������� ������� ������ ��������
unsigned int send(unsigned char sock,const unsigned *buf,unsigned int buflen);
void close(unsigned char sock);							//������� �������� ������
void disconnect(unsigned char sock);					//������ �������������� ����������
//��������� �������� ������,�������� �������� ������ ������
unsigned char socket(unsigned char sock,unsigned char eth_protocol,unsigned int tcp_port);
unsigned char listen(unsigned char sock);				//"���������"�������� ������� �� �������
//�������� ������ ����� �����,���������� ������
unsigned int send(unsigned char sock,const unsigned *buf,unsigned int buflen);
//��������� �������� ������
unsigned int recv(unsigned char sock,unsigned char *buf,unsigned int buflen);
unsigned int recv_size(void);							//����������
int strindex(char *s,char *t);							//����������
//************************************************************************************

//--------���������-------------------------------------------------------------------
typedef struct chip_w5100	{			//���������� ��������� � ������ chip_w5100
	unsigned char mac_addr[6];			//��������� �������� ��������
	unsigned char ip_addr[4];			//����� ����� ��������� ������ � �������
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
#endif	//��������� ��������������� �������	