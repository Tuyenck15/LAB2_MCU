/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int TIMER_CYCLE = 10;
//7 segment display timer setup begins:
int timer0_counter = 0;
int timer0_flag = 0;
void setTimer0(int duration){
	timer0_counter = duration /TIMER_CYCLE;
	timer0_flag = 0;
}
void timer0_run(){
	if(timer0_counter > 0){
		timer0_counter--;
		if(timer0_counter == 0) timer0_flag = 1;
	}
}
//7 segment display timer setup ends

//Hour:minute display timer setup begins:
int timer1_counter = 0;
int timer1_flag = 0;
void setTimer1(int duration){
	timer1_counter = duration /TIMER_CYCLE;
	timer1_flag = 0;
}
void timer1_run(){
	if(timer1_counter > 0){
		timer1_counter--;
		if(timer1_counter == 0) timer1_flag = 1;
	}
}
//Hour:minute display timer setup end

int led_buffer [4];
void updateClockBuffer(int hour, int minute)
{
	if (hour<=9)
	{
		led_buffer [0]=0;
		led_buffer [1]=hour;
	}
	else
	{
		led_buffer [0]=hour/10;
		led_buffer [1]=hour%10;
	}

	if (minute<=9)
	{
		led_buffer [2]=0;
		led_buffer [3]=minute;
	}
	else
	{
		led_buffer [2]=minute/10;
		led_buffer [3]=minute%10;
	}
}

void display7SEG(int num)
	{
		switch (num)
	      {
			case 1:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_SET);
				break;
			case 2:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
				break;
			case 3:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
				break;
			case 4:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
				break;
			case 5:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
				break;
			case 6:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
				break;
			case 7:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_SET);
				break;
			case 8:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
				break;
			case 9:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_SET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_RESET);
				break;
			case 0:
		          HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, GPIO_PIN_RESET);
		          HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, GPIO_PIN_SET);
				break;
			default:
				break;
		}
}
//LED MATRIX display timer setup begins
int timer2_counter = 0;
int timer2_flag = 0;
void setTimer2(int duration){
	timer2_counter = duration /TIMER_CYCLE;
	timer2_flag = 0;
}
void timer2_run(){
	if(timer2_counter > 0){
		timer2_counter--;
		if(timer2_counter == 0) timer2_flag = 1;
	}
}
//LED MATRIX display timer setup end

const int MAX_LED = 4;
int index_led = 0;
void update7SEG ( int index )
{
	switch ( index )
	{
		case 0:
			HAL_GPIO_WritePin ( EN0_GPIO_Port , EN0_Pin ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin ( EN1_GPIO_Port , EN1_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin ( EN2_GPIO_Port , EN2_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin ( EN3_GPIO_Port , EN3_Pin ,GPIO_PIN_SET );
			display7SEG(led_buffer [0]);
			break;
		case 1:
			HAL_GPIO_WritePin ( EN0_GPIO_Port , EN0_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin ( EN1_GPIO_Port , EN1_Pin ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin ( EN2_GPIO_Port , EN2_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin ( EN3_GPIO_Port , EN3_Pin ,GPIO_PIN_SET );
			display7SEG(led_buffer [1]);
			break;
		case 2:
			HAL_GPIO_WritePin ( EN0_GPIO_Port , EN0_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin ( EN1_GPIO_Port , EN1_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin ( EN2_GPIO_Port , EN2_Pin ,GPIO_PIN_RESET );
			HAL_GPIO_WritePin ( EN3_GPIO_Port , EN3_Pin ,GPIO_PIN_SET );
			display7SEG(led_buffer [2]);
			break;
		case 3:
			HAL_GPIO_WritePin ( EN0_GPIO_Port , EN0_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin ( EN1_GPIO_Port , EN1_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin ( EN2_GPIO_Port , EN2_Pin ,GPIO_PIN_SET );
			HAL_GPIO_WritePin ( EN3_GPIO_Port , EN3_Pin ,GPIO_PIN_RESET );
			display7SEG(led_buffer [3]);
			break;
	}
}

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {
	    0x00, // 00000000 (Column 0)
	    0xFC, // 11111100 (Column 1)
	    0xFE, // 11111110 (Column 2)
	    0x33, // 00110011 (Column 3)
	    0x33, // 00110011 (Column 4)
	    0xFE, // 11111110 (Column 5)
	    0xFC, // 11111100 (Column 6)
	    0x00  // 00000000 (Column 7)
};

void updateLEDMatrix(int index)
{
    // Disable all columns first (turn off all columns)
    HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, GPIO_PIN_SET);

    // Set column data (PB8-PB15 for COL0-COL7)

        HAL_GPIO_WritePin(GPIOB, 0xff << 8, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, matrix_buffer[index] << 8, GPIO_PIN_RESET);


    // Enable the column corresponding to "index"
    switch (index) {
        case 0:
            HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, GPIO_PIN_RESET);  // Enable Column 0
            break;
        case 1:
            HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, GPIO_PIN_RESET);  // Enable Column 1
            break;
        case 2:
            HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, GPIO_PIN_RESET);  // Enable Column 2
            break;
        case 3:
            HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, GPIO_PIN_RESET);  // Enable Column 3
            break;
        case 4:
            HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, GPIO_PIN_RESET);  // Enable Column 4
            break;
        case 5:
            HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, GPIO_PIN_RESET);  // Enable Column 5
            break;
        case 6:
            HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, GPIO_PIN_RESET);  // Enable Column 6
            break;
        case 7:
            HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, GPIO_PIN_RESET);  // Enable Column 7
            break;
    }
}
void shiftLeftMatrixBuffer() {
    // Temporary variable to store the left row for wraparound
    uint8_t temp = matrix_buffer[0];

    // Shift all elements to the left
    for (int i = 0; i < MAX_LED_MATRIX - 1; i++) {
        matrix_buffer[i] = matrix_buffer[i + 1]; // Move current move to the left
    }
    matrix_buffer[MAX_LED_MATRIX - 1] = temp;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT (& htim2 );
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int hour = 15, minute = 8, second = 50;
  setTimer0(250);
  setTimer1(1000);
  setTimer2(10);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if( timer0_flag == 1)
	  {
		    update7SEG(index_led++);
		    if (index_led>=MAX_LED)
		    {
			    index_led=0;
		    }
		    setTimer0(250);
	  }

	  if( timer1_flag == 1)
	  {
		    second++;
		    if (second >= 60){
		        second = 0;
		        minute++;
		    }
		    if(minute >= 60){
		        minute = 0;
		        hour++;
		    }
		    if(hour >=24){
		        hour = 0;
		    }
		    updateClockBuffer(hour, minute);
		    setTimer1(1000);
		    HAL_GPIO_TogglePin( DOT_GPIO_Port , DOT_Pin );
	  }

	  if( timer2_flag == 1)
	  {
		  updateLEDMatrix(index_led_matrix++);
		  if (index_led_matrix>=MAX_LED_MATRIX)
		  {
			  shiftLeftMatrixBuffer();  // Shift the character left on the LED matrix
			  index_led_matrix=0;
		  }
		  setTimer2(10); //1/0.01= Hz
	  }
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
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

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, a_Pin|b_Pin|c_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|d_Pin|e_Pin|f_Pin
                          |g_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : a_Pin b_Pin c_Pin R0W2_Pin
                           R0W3_Pin R0W4_Pin R0W5_Pin R0W6_Pin
                           R0W7_Pin d_Pin e_Pin f_Pin
                           g_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = a_Pin|b_Pin|c_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|d_Pin|e_Pin|f_Pin
                          |g_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	timer0_run ();
	timer1_run ();
	timer2_run ();
}
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
