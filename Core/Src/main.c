#include"stm32f4xx_hal.h"
#include"main.h"


void Error_handler(void);
void SystemClockConfig(void);
void UART2_Init(void);


uint8_t read_data;
uint16_t buffer[10];
uint16_t count = 0;

UART_HandleTypeDef huart2;
int main(void)
{
	HAL_Init();

	SystemClockConfig();

	UART2_Init();

	char *send_data = "Hello - world\n";

	HAL_UART_Transmit(&huart2, (uint8_t *)send_data, strlen(send_data), HAL_MAX_DELAY);

	HAL_UART_Receive_IT(&huart2, &read_data, sizeof(read_data));

	while(1);

	return 0;
}


void UART2_Init(void)
{
	huart2.Instance        = USART2;
	huart2.Init.BaudRate   = 19200;
	huart2.Init.Parity     = UART_PARITY_NONE;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits   = UART_STOPBITS_1;
	huart2.Init.Mode       = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl  = UART_HWCONTROL_NONE;


	if(HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_handler();
	}
}

void Error_handler(void)
{
	while(1);
}


void HAL_UART_RxCpltCallback(void)
{
	if(read_data == '\r')
	{
		HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);

	}
	else
	{
		buffer[count++] = read_data;
	}

}
