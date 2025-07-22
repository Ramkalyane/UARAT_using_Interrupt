#include"stm32f4xx_hal.h"
#include"stm32f4xx_hal_cortex.h"

void HAL_MspInit(void)
{
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef my_gpio;

	__HAL_RCC_USART2_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();

	my_gpio.Pin = GPIO_PIN_2;
	my_gpio.Mode = GPIO_MODE_AF_PP;
	my_gpio.Alternate = GPIO_AF7_USART2;
	my_gpio.Pull = GPIO_NOPULL;
	my_gpio.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &my_gpio);

	my_gpio.Pin = GPIO_PIN_3;
	HAL_GPIO_Init(GPIOA, &my_gpio);

	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);

}
