//code begin here
#include "main.h"
#include <stdio.h>
#include <string.h>

void lcd_cmd(char cmd){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0);//RS=0 command register select
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (cmd&0x10));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (cmd&0x20));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (cmd&0x40));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (cmd&0x80));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);//EN=1
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);//EN=0
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ((cmd<<4)&0x10));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ((cmd<<4)&0x20));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ((cmd<<4)&0x40));
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, ((cmd<<4)&0x80));
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);//EN=1
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);//EN=0

}
void lcd_data(char data){
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);//RS=1 data register select
	    //sending higher nibble
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (data&0x10));
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, (data&0x20));
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, (data&0x40));
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, (data&0x80));
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);//EN=1
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);//EN=0
		//sending Lower nibble
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ((data<<4)&0x10));
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ((data<<4)&0x20));
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ((data<<4)&0x40));
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, ((data<<4)&0x80));
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 1);//EN=1
		HAL_Delay(1);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, 0);//EN=0
}
void lcd_string(char *s){
	while(*s!='\0'){
		lcd_data(*s);
		s++;
	}
}
void lcd_init(){
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x01);
	lcd_cmd(0x0C);
}
char arr1[16];
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int check_R1(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		return '1';
	}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '2';
		}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '3';
		}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'A';
		}
}
int check_R2(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		return '4';
	}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '5';
		}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '6';
		}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'B';
		}
}
int check_R3(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		return '7';
	}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '8';
		}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '9';
		}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'C';
		}
}
int check_R4(){
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==1){
		   return '*';
	}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9)==1){
			return '0';
		}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)==1){
			return '#';
		}
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11)==1){
			return 'D';
		}

}

int key_Detect(){

	GPIOB->ODR&=0x00000000;
	GPIOB->ODR|=0x1000;//PB12-PB15 row pins
    if(check_R1()!='\0'){
   return check_R1();

    }HAL_Delay(10);

    GPIOB->ODR&=0x0000;
    GPIOB->ODR|=0x2000;
    if(check_R2()!='\0'){
    	 return check_R2();

        }HAL_Delay(10);

    GPIOB->ODR&=0x0000;
    GPIOB->ODR|=0x4000;
     if(check_R3()!='\0'){
    	 return check_R3();

            }HAL_Delay(10);

     GPIOB->ODR&=0x0000;
     GPIOB->ODR|=0x8000;
       if(check_R4()!='\0'){
    	    return check_R4();

            }HAL_Delay(10);
return 'E';
           	}
unsigned char arr3[4]={'*','0','7','#'};
unsigned char arr2[4]={'9','5','2','0'};

unsigned char input[4]={};//initialize input buffer
unsigned char i=0;
int  count=0;

void checkKeypad(){

	char temp;
	lcd_cmd(0x80);
	repeat:
	lcd_string("Enter Password:");
	lcd_cmd(0xC0);
	while(key_Detect()!='E'){
		while(i<4){
										if(key_Detect()!='E'){
										input[i]=key_Detect();
										Hide_pass();
										HAL_Delay(500);
										i++;
										}
		}


		if(i>3){
			 if(checkcode()){
				 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
				 HAL_Delay(2000);
				 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
							lcd_cmd(0xC0);
							lcd_string("Access Granted");
							HAL_Delay(3000);
							lcd_cmd(0x01);
							for(char cnt =0; cnt < 10; cnt++){
							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
							HAL_Delay(1);
							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 1);
							HAL_Delay(20);
							HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, 0);
							HAL_Delay(100);
							}

						

							i=0;//Reset input Buffer index
						memset(input,0,4);
						}
			 else if (pass_change()){
				lcd_cmd(0x80);
				HAL_Delay(1000);
				lcd_string("Enter old Pass:");
				HAL_Delay(2000);
				lcd_cmd(0x01);
				memset(input,0,4);
				i=0;
				while(i<4){
				if(key_Detect()!='E'){
				input[i]=key_Detect();
				Hide_pass();
				HAL_Delay(700);
				i++;
				}
				}
				for(i=0;i<4;i++){
						 if(input[i]!=arr2[i]){
							HAL_Delay(100);
							lcd_cmd(0x01);
							lcd_cmd(0xC0);
							lcd_string("Wrong Password");
							HAL_Delay(2000);
							lcd_cmd(0x01);
							goto repeat;
						}
						}
				HAL_Delay(100);
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_string(".................");
				HAL_Delay(1000);
				lcd_cmd(0x01);
				lcd_string("Enter New Pass:");
				memset(input,0,4);
				memset(arr2,0,4);
								i=0;
								lcd_cmd(0xC0);
								while(i<4){
								if(key_Detect()!='E'){
								input[i]=key_Detect();
								Hide_pass();
								HAL_Delay(500);
								i++;
								}
								}
				for(i=0;i<4;i++){
					temp=input[i];
					arr2[i]=temp;
					lcd_data(arr2[i]);
					HAL_Delay(100);
					}
				HAL_Delay(1000);
				lcd_cmd(0x01);
				lcd_cmd(0xC0);
				lcd_string("Password Reset!");
				i=0;
				memset(input,0,4);
				HAL_Delay(1000);

				lcd_cmd(0x01);

			}




			else{
				lcd_cmd(0xC0);
				lcd_string("Access Denied!");
				HAL_Delay(2000);
				lcd_cmd(0x01);
				for(int j=0;j<3;j++){
        //buzzer  going to ring  for 3 times indicating wrong password
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
				 HAL_Delay(1000);
				 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 0);
				 HAL_Delay(1000);
				}
				i=0;
				memset(input,0,4);
			}
		}
	}
}
int checkcode(){
	unsigned char i;
	     for(i=0;i<4;i++){

				if(input[i]!=arr2[i]){
					return 0;
				}
				}
	     return 1;
}
int pass_change(){
	 for(i=0;i<4;i++){
		if(input[i]!=arr3[i]) {
			return 0;
		}

	 }
	 return 1;
}
int Hide_pass(){

	lcd_data('*');
}

int main(void)
{


  HAL_Init();


  SystemClock_Config();


  MX_GPIO_Init();
  lcd_init();
  while(1){
	 checkKeypad();
  }

}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA4 PA5 PA6
                           PA7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13
                           PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 PA10 PA11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
