/* Header file with all the essential definitions for a given type of MCU */
#include "MK60DZ10.h"


/* Macros for bit-level registers manipulation */
#define GPIO_PIN_MASK	0x1Fu
#define GPIO_PIN(x)		(((1)<<(x & GPIO_PIN_MASK)))

#define PORT_PCR_ISF(x) (((uint32_t)(((uint32_t)(x))<<PORT_PCR_ISF_SHIFT))&PORT_PCR_ISF_MASK)
#define PORT_PCR_PE(x)  (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PE_SHIFT))&PORT_PCR_PE_MASK)
#define PORT_PCR_PS(x)  (((uint32_t)(((uint32_t)(x))<<PORT_PCR_PS_SHIFT))&PORT_PCR_PS_MASK)

// for snake with size 4
int xsnake[4] = {4, 5, 6, 7};
int ysnake[4] = {0, 0, 0, 0};

// direction of the movement
char direction = 'r';

/* Configuration of the necessary MCU peripherals */
void SystemConfig() {
	/* Turn on all port clocks */
	SIM->SCGC5 = SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTE_MASK;


	/* Set corresponding PTA pins (column activators of 74HC154) for GPIO functionality */
	PORTA->PCR[8] = ( 0|PORT_PCR_MUX(0x01) );  // A0
	PORTA->PCR[10] = ( 0|PORT_PCR_MUX(0x01) ); // A1
	PORTA->PCR[6] = ( 0|PORT_PCR_MUX(0x01) );  // A2
	PORTA->PCR[11] = ( 0|PORT_PCR_MUX(0x01) ); // A3

	/* Set corresponding PTA pins (rows selectors of 74HC154) for GPIO functionality */
	PORTA->PCR[26] = ( 0|PORT_PCR_MUX(0x01) );  // R0
	PORTA->PCR[24] = ( 0|PORT_PCR_MUX(0x01) );  // R1
	PORTA->PCR[9] = ( 0|PORT_PCR_MUX(0x01) );   // R2
	PORTA->PCR[25] = ( 0|PORT_PCR_MUX(0x01) );  // R3
	PORTA->PCR[28] = ( 0|PORT_PCR_MUX(0x01) );  // R4
	PORTA->PCR[7] = ( 0|PORT_PCR_MUX(0x01) );   // R5
	PORTA->PCR[27] = ( 0|PORT_PCR_MUX(0x01) );  // R6
	PORTA->PCR[29] = ( 0|PORT_PCR_MUX(0x01) );  // R7

	/* Set corresponding PTE pins (output enable of 74HC154) for GPIO functionality */
	PORTE->PCR[28] = ( 0|PORT_PCR_MUX(0x01) ); // #EN


	/* Change corresponding PTA port pins as outputs */
	PTA->PDDR = GPIO_PDDR_PDD(0x3F000FC0);

	/* Change corresponding PTE port pins as outputs */
	PTE->PDDR = GPIO_PDDR_PDD( GPIO_PIN(28) );

	/* Set corresponding pins for buttons up, left, down, right*/
	PORTE->PCR[26] = PORT_PCR_ISF(0x01) | PORT_PCR_IRQC(0x0A) | PORT_PCR_MUX(0x01) | PORT_PCR_PE(0x01) | PORT_PCR_PS(0x01);
	PORTE->PCR[10] = PORT_PCR_ISF(0x01) | PORT_PCR_IRQC(0x0A) | PORT_PCR_MUX(0x01) | PORT_PCR_PE(0x01) | PORT_PCR_PS(0x01);
	PORTE->PCR[12] = PORT_PCR_ISF(0x01) | PORT_PCR_IRQC(0x0A) | PORT_PCR_MUX(0x01) | PORT_PCR_PE(0x01) | PORT_PCR_PS(0x01);
	PORTE->PCR[27] = PORT_PCR_ISF(0x01) | PORT_PCR_IRQC(0x0A) | PORT_PCR_MUX(0x01) | PORT_PCR_PE(0x01) | PORT_PCR_PS(0x01);

	NVIC_ClearPendingIRQ(PORTE_IRQn);
	NVIC_EnableIRQ(PORTE_IRQn);
}

/* Conversion of requested column number into the 4-to-16 decoder control.  */
void column_select(unsigned int col_num)
{
	unsigned i, result, col_sel[4];

	for (i =0; i<4; i++) {
		result = col_num / 2;	  // Whole-number division of the input number
		col_sel[i] = col_num % 2;
		col_num = result;

		switch(i) {

			// Selection signal A0
		    case 0:
				((col_sel[i]) == 0) ? (PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(8))) : (PTA->PDOR |= GPIO_PDOR_PDO( GPIO_PIN(8)));
				break;

			// Selection signal A1
			case 1:
				((col_sel[i]) == 0) ? (PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(10))) : (PTA->PDOR |= GPIO_PDOR_PDO( GPIO_PIN(10)));
				break;

			// Selection signal A2
			case 2:
				((col_sel[i]) == 0) ? (PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(6))) : (PTA->PDOR |= GPIO_PDOR_PDO( GPIO_PIN(6)));
				break;

			// Selection signal A3
			case 3:
				((col_sel[i]) == 0) ? (PTA->PDOR &= ~GPIO_PDOR_PDO( GPIO_PIN(11))) : (PTA->PDOR |= GPIO_PDOR_PDO( GPIO_PIN(11)));
				break;

			// Otherwise nothing to do...
			default:
				break;
		}
	}
}

void light(int *x, int *y) {
	for (int i = 3; i >= 0; i--) {
		PTA->PDOR &= ~GPIO_PDOR_PDO(0x3F000280);
		column_select(y[i]);
		switch (x[i]) {
			case 0:
				PTA->PDOR |= GPIO_PDOR_PDO( 1 << 29);
				break;
			case 1:
				PTA->PDOR |= GPIO_PDOR_PDO( 1 << 27);
				break;
			case 2:
				PTA->PDOR |= GPIO_PDOR_PDO( 1 << 7);
				break;
			case 3:
				PTA->PDOR |= GPIO_PDOR_PDO( 1 << 28);
				break;
			case 4:
				PTA->PDOR |= GPIO_PDOR_PDO( 1 << 25);
				break;
			case 5:
				PTA->PDOR |= GPIO_PDOR_PDO( 1 << 9);
				break;
			case 6:
				PTA->PDOR |= GPIO_PDOR_PDO( 1 << 24);
				break;
			case 7:
				PTA->PDOR |= GPIO_PDOR_PDO( 1 << 26);
				break;
		}
	}
}


void change_direction() {
	if (PORTE->ISFR & 1 << 26){
		direction = 'u';
		PORTE->ISFR |= 1 << 26;
	}
	else if (PORTE->ISFR & 1 << 10){
		direction = 'r';
		PORTE->ISFR |= 1 << 10;
	}
	else if (PORTE->ISFR & 1 << 12){
		direction = 'd';
		PORTE->ISFR |= 1 << 12;
	}
	else if (PORTE->ISFR & 1 << 27){
		direction = 'l';
		PORTE->ISFR |= 1 << 27;
	}

}

// if there is interrupt (any button is pressed)
void PORTE_IRQHandler(void)
{
	change_direction();
}

// function for detecting in which direction should the snake move now
void choose_direction(){
	column_select(ysnake[0]);
	switch(direction) {
		case 'd':
			ysnake[0]++;
			if (ysnake[0] > 15) {
				ysnake[0] = 0;
			}
			break;

		case 'l':
			xsnake[0]--;
			if (xsnake[0] < 0) {
				xsnake[0] = 7;
			}
			break;

		case 'r':
			xsnake[0]++;
			if (xsnake[0] > 7) {
				xsnake[0] = 0;
			}
			break;

		case 'u':
			ysnake[0]--;
			if (ysnake[0] < 0) {
				ysnake[0] = 15;
			}
			break;
	}
}

int main(void) {
	SystemConfig();
	while(1){
		for (int i = 3; i > 0; i--) {
			xsnake[i] = xsnake[i-1];
			ysnake[i] = ysnake[i-1];
		}
		choose_direction();
		for (int i = 0; i < 7500; i++){
			light(xsnake, ysnake);
		}
	}


    /* Never leave main */
    return 0;
}
