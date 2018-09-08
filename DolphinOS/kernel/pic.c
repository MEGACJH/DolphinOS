#include "io_ASM.h"
#include "../com/types.h"
#include "printk.h"
#include "handler_ASM.h"
#include "pic.h"
#include "io_ASM.h"

void init_pic(){
	io_out8_ASM(PIC0_IMR,  0xff  ); /* 禁止主PIC所有中断 */
	io_out8_ASM(PIC1_IMR,  0xff  ); /* 禁止从PIC所有中断 */

	io_out8_ASM(PIC0_ICW1, 0x11  ); /* 需要ICW4， 多片级联， 边沿触发方式 */
	io_out8_ASM(PIC0_ICW2, 0x20  ); /* IRQ0-7由于INT 0x20~0x27接收 */
	io_out8_ASM(PIC0_ICW3, 1 << 2); /* PIC1由IRQ2连接 */
	io_out8_ASM(PIC0_ICW4, 0x01  ); /* 普通全嵌套 非缓冲 非自动结束中断方式 */

	io_out8_ASM(PIC1_ICW1, 0x11  ); /* 需要ICW4， 多片级联， 边沿触发方式 */
	io_out8_ASM(PIC1_ICW2, 0x28  ); /* IRQ8-15由于INT 0x28~0x2f接收 */
	io_out8_ASM(PIC1_ICW3, 2     ); /* PIC1由IRQ2连接 */
	io_out8_ASM(PIC1_ICW4, 0x01  ); /* 普通全嵌套 非缓冲 非自动结束中断方式 */

	io_out8_ASM(PIC0_IMR,  0xfb  ); /* 11111011 PIC1以外全部禁止 */
	io_out8_ASM(PIC1_IMR,  0xff  ); /* 11111111 禁止从PIC所有中断 */

}

void inthandler21_keyboard(int32_t *esp)
{
	printk("\nINT 21 (IRQ-1) : PS/2 keyboard");
	io_out8_ASM(PIC0_OCW2,0x61);
	//io_out8_ASM(PIC0_OCW2,0x62);
	while(1){
	}
}
