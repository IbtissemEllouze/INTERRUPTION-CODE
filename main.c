/*----------------------------------------------------------------
LAB EXERCISE: INTERRUPT AND LOW-POWER FEATURES
---------------------------------------
Use interrupt service routine to implement the following function:
The 4 LEDs can be flipped by the joystick
joystick-up flips LED1
joystick-down flips LED2
joystick-left flips LED3
joystick-right flips LED4
joystick-centre flips LED1-4
-----------------------------------------------------------------*/


//Define the address of the interrupt enable register of the nested vectored interrupt controller
#define NVIC_INT_ENABLE			0xE000E100


//Define the structure of the pin multiplexor
typedef struct
{
  volatile  unsigned int    PINSEL0;
  volatile  unsigned int    PINSEL1;
  volatile  unsigned int    PINSEL2;
  volatile  unsigned int    PINSEL3;
  volatile  unsigned int    PINSEL4;
  volatile  unsigned int    PINSEL5;
  volatile  unsigned int    PINSEL6;
  volatile  unsigned int    PINSEL7;
  volatile  unsigned int    PINSEL8;
  volatile  unsigned int    PINSEL9;
  volatile  unsigned int    PINSEL10;
  volatile  unsigned int    RESERVED0[5];
  volatile  unsigned int    PINMODE0;
  volatile  unsigned int    PINMODE1;
  volatile  unsigned int    PINMODE2;
  volatile  unsigned int    PINMODE3;
  volatile  unsigned int    PINMODE4;
  volatile  unsigned int    PINMODE5;
  volatile  unsigned int    PINMODE6;
  volatile  unsigned int    PINMODE7;
  volatile  unsigned int    PINMODE8;
  volatile  unsigned int    PINMODE9;
  volatile  unsigned int    PINMODE_OD0;
  volatile  unsigned int    PINMODE_OD1;
  volatile  unsigned int    PINMODE_OD2;
  volatile  unsigned int    PINMODE_OD3;
  volatile  unsigned int    PINMODE_OD4;
  volatile  unsigned int    I2CPADCFG;
} My_PINCON_TypeDef;


#define My_PINCON_BASE       (0x40000000UL + 0x2C000)
#define My_PINCON            ((My_PINCON_TypeDef    *) My_PINCON_BASE   )


//Define the structure of the GPIO peripheral

typedef struct
{

  volatile  unsigned int   FIODIR;
		
  volatile  unsigned int   RESERVED[3];

  volatile  unsigned int   FIOMASK;

  volatile  unsigned int   FIOPIN;

  volatile  unsigned int   FIOSET;

  volatile  unsigned int   FIOCLR;

} My_GPIO_TypeDef;

#define My_GPIO_BASE         (0x2009C000UL)

#define My_GPIO0_BASE        (My_GPIO_BASE + 0x00000)
#define My_GPIO1_BASE        (My_GPIO_BASE + 0x00020)

#define My_GPIO0             ((My_GPIO_TypeDef      *) My_GPIO0_BASE    )
#define My_GPIO1             ((My_GPIO_TypeDef      *) My_GPIO1_BASE    )


//Define the structure of the GPIO interrupt controller

typedef struct
{
  volatile  unsigned int    IntStatus;
  volatile  unsigned int    IO0IntStatR;
  volatile  unsigned int    IO0IntStatF;
  volatile  unsigned int    IO0IntClr;
  volatile  unsigned int    IO0IntEnR;
  volatile  unsigned int    IO0IntEnF;
  volatile  unsigned int    RESERVED0[3];
  volatile  unsigned int    IO2IntStatR;
  volatile  unsigned int    IO2IntStatF;
  volatile  unsigned int    IO2IntClr;
  volatile  unsigned int    IO2IntEnR;
  volatile  unsigned int    IO2IntEnF;
} My_GPIOINT_TypeDef;

#define My_GPIOINT_BASE      (0x40000000 + 0x28080)
#define My_GPIOINT           ((My_GPIOINT_TypeDef   *) My_GPIOINT_BASE  )


void JoyStick_IRQHandler (void){
	
	int current_bit;
	
	//If interrupt is from P0[23](joystick-up), then flip LED1

	//<Write your code here> 
	 
	//If interrupt is from P0[17](joystick-down), then flip LED2

	//<Write your code here> 
	  
	//If interrupt is from P0[15](joystick-left), then flip LED3 

	//<Write your code here> 
		
	//If interrupt is from P0[24](joystick-right), then flip LED4	
	
	//<Write your code here> 
	
	//If interrupt is from P0[16](joystick-centre), then flip LED1-4	
	
	//<Write your code here> 
	
}

int main()
{	
	
	/*------------------------------------------------------
	Configure the pin multiplexor and GPIO pull-up mode
	PINSEL: enable the external pins to be connected to the GPIO peripheral 
	PINMODE: pin internal pull-up setting
	10: tri-state mode
	11: on-chip pull-down resistor enabled
	-------------------------------------------------------*/
	
	//P0.23 connected to joystick-up -- GPIO, pull-down resistor
	My_PINCON->PINSEL1 &=~((1 <<15)|(1<<14));
	My_PINCON->PINMODE1 |=((1 <<15)|(1<<14));

	//P0.17 connected to joystick-down -- GPIO, pull-down resistor
	My_PINCON->PINSEL1 &=~((1 <<3)|(1<<2));
	My_PINCON->PINMODE1 |=((1 <<3)|(1<<2));

	//P0.15 connected to joystick-left -- GPIO, pull-down resistor
	My_PINCON->PINSEL0 &=~((1 <<31)|(1<<30));
	My_PINCON->PINMODE0 |=((1 <<31)|(1<<30));

	//P0.24 connected to joystick-right -- GPIO, pull-down resistor
	My_PINCON->PINSEL1 &=~((1 <<17)|(1<<16));
	My_PINCON->PINMODE1 |=((1 <<17)|(1<<16));
	
	//P0.16 connected to joystick-centre -- GPIO, pull-down resistor
	My_PINCON->PINSEL1 &=~((1 <<1)|(1<<0));
	My_PINCON->PINMODE1 |=((1 <<1)|(1<<0));

	//P1.18 connected to LED1 -- GPIO, tri-state mode
	My_PINCON->PINSEL3 &=~((1 <<5)|(1<<4));
	My_PINCON->PINMODE3 |=(1 <<4);
	My_PINCON->PINMODE3 &=~(1<<5);

	//P1.20 connected to LED2 -- GPIO, tri-state mode
	My_PINCON->PINSEL3 &=~((1 <<9)|(1<<8));
	My_PINCON->PINMODE3 |=(1 <<9);
	My_PINCON->PINMODE3 &=~(1<<8);

	//P1.21 connected to LED3 -- GPIO, tri-state mode
	My_PINCON->PINSEL3 &=~((1 <<11)|(1<<10));
	My_PINCON->PINMODE3 |=(1 <<11);
	My_PINCON->PINMODE3 &=~(1<<10);

	//P1.23 connected to LED4 -- GPIO, tri-state mode
	My_PINCON->PINSEL3 &=~((1 <<15)|(1<<14));
	My_PINCON->PINMODE3 |=(1 <<15);
	My_PINCON->PINMODE3 &=~(1<<14);
	
	//Turn off all 4 LEDs
	My_GPIO1->FIODIR |=((1<<18)|(1<<20)|(1<<21)|(1<<23));			//direction: input 
	My_GPIO1->FIOMASK &=~((1<<18)|(1<<20)|(1<<21)|(1<<23));		//mask out undesired bits
	My_GPIO1->FIOCLR |=((1<<18)|(1<<20)|(1<<21)|(1<<23));			//write to clear register to clear all four bits
	
	//enable the interrupt from GPIO interrupt controller
  *(unsigned int*) (NVIC_INT_ENABLE) = (1<<21);		
	
	//Enable the interrupt controller to generate an interrupt if any of the five bits (joystick) is set
	My_GPIOINT->IO0IntEnR |= ((1 << 23)|(1 << 17)|(1 << 15)|(1 << 24)|(1 << 16));
	
	//Go to sleep mode and wait for interrupts
	while(1){
		
		//go to sleep	
		//<Write your code here>

	}

}

