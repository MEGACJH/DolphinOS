#include "io_ASM.h"
#include "../com/types.h"
#include "printk.h"
#include "handler_ASM.h"
#include "pic.h"
#include "io_ASM.h"

void init_pic(){
	io_out8_ASM(PIC0_IMR,  0xff  ); /* Prohibition of all of master PIC's interupt */
	io_out8_ASM(PIC1_IMR,  0xff  ); /* Prohibition of all of slave PIC's interupt */

	io_out8_ASM(PIC0_ICW1, 0x11  ); /* we need ICW4, so many pic series connection*/
	io_out8_ASM(PIC0_ICW2, 0x20  ); /* IRQ0-7, INT 0x20~0x27 accept */
	io_out8_ASM(PIC0_ICW3, 1 << 2); /* PIC1 IRQ2 connect */
	io_out8_ASM(PIC0_ICW4, 0x01  ); /* A model, interupt complete model */

	io_out8_ASM(PIC1_ICW1, 0x11  ); /* we need ICW4, so many pic series connection*/
	io_out8_ASM(PIC1_ICW2, 0x28  ); /* IRQ8-15, INT 0x28~0x2f accept */
	io_out8_ASM(PIC1_ICW3, 2     ); /* PIC1, IRQ2 connect */
	io_out8_ASM(PIC1_ICW4, 0x01  ); /* A model, interupt complete model */

	io_out8_ASM(PIC0_IMR,  0xfb  ); /* 0xfb = 11111011. Prohibition of all of PIC's interupt except PIC1*/
	io_out8_ASM(PIC1_IMR,  0xff  ); /* 0xff = 11111111. Prohibition of all of slave PIC's interupt */
	
}

/*It is very difficult to find this mistake, because the textbook is aslo worry!!!!
 *At the beginning, my os can only accept the interupt once!!!
 *First, I suspicious of the IDT, but the IDT is work. because the os can accept the interupt once.
 *And then, I study the 8259A, but I found it is not 8259A problem. Even you have inform the pic that the interupt has been finished.
 *Finally, I was surprised to find that the Intel 8042. you need read the data from the Intel 8042! beacuse if you haven't read the data, the 8042 still think the interupt hasn't be completed.
 *It cost me about three weeks to solve the problem. OMG!!!
 */
void inthandler21_keyboard(int32_t *esp)
{
	printk("  INT21 (IRQ-1)  ");
	io_out8_ASM(PIC0_OCW2,0x61);
	io_in8_ASM(0x60); //It is very important sentence in the function, if you haven't read the data, the 8042 still think the interupt hasn't be completed.
}
