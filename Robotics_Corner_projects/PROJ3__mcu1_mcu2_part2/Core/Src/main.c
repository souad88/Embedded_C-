//MCU1-SEND-[TX(PA9)]
//THE OBJECTIVE HERE IS TO :
//1-CHECK APRESSED_KEY FROM KEY_PAD IN A PORT EX: NUMBER "1"
//2- IF PRESSED KEY IS NUMBER "1" ->SEND FROM MCU1_USART1 TO USART1_MCU2 SEND AN INTEGER
// 	NUMBER "1". //THIS PART PROG ENDED HERE
//3-INTEGER NUMBER "1" IS STORED IN RECEIVE BUFFER IN MCU2.

#include "main.h"

void SystemClock_Config(void);
#define BAUD 9600
#define FOSC 8000000
int main(void)
{

  RCC->APB2ENR  |=(1<<2);
  RCC->APB2ENR  |=(1<<0);
  RCC->APB2ENR  |=(1<<14);
  GPIOA->CRH    |=(0X0B<<4);
  GPIOA->CRH    |=(4<<8);
  ///
  USART1->CR1   |=(1<<13);
  USART1->CR1   |=(1<<3);
  USART1->CR1   |=(1<<2);
  //
  double USART1_BAUD_RATE=FOSC/BAUD;
  USART1->BRR=USART1_BAUD_RATE;
  unsigned int T_BUFFER=USART1->DR&0X00FF; //STORAGE_INTIALIZATION
  HAL_Init();

  SystemClock_Config();

  while (1)
  {

	  //if(gu8_KeyStatesArr[KEY_1] == KEY_PRESSED)
				//{

	         	 	 	 //  while(gu8_KeyStatesArr[KEY_1] == KEY_PRESSED);

	  	  				while(!(USART1->SR&1<<5)); //WHILE RECIEVER_BUFFER IS EMPTY READ DATA AND STORE IT

	  	  				USART1->DR=0XFF&0; //SEND INT 0
	  	  				while(!(USART1->SR&1<<7)) ;

	  //}

  }



}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */