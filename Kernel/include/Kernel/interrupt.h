#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <Kernel/bcm2835.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ARM_EXCEPTION_TABLE_BASE	0x00000000
#define ARM_OPCODE_BRANCH(distance)	(0xEA000000 | (distance))
#define ARM_DISTANCE(from, to)		((uint32 *) &(to) - (uint32 *) &(from) - 2)

#define ARM_IC_IRQ_PENDING(irq)	(  (irq) < ARM_IRQ2_BASE	\
				 ? ARM_IC_IRQ_PENDING_1		\
				 : ((irq) < ARM_IRQBASIC_BASE	\
				   ? ARM_IC_IRQ_PENDING_2	\
				   : ARM_IC_IRQ_BASIC_PENDING))
#define ARM_IC_IRQS_ENABLE(irq)	(  (irq) < ARM_IRQ2_BASE	\
				 ? ARM_IC_ENABLE_IRQS_1		\
				 : ((irq) < ARM_IRQBASIC_BASE	\
				   ? ARM_IC_ENABLE_IRQS_2	\
				   : ARM_IC_ENABLE_BASIC_IRQS))
#define ARM_IC_IRQS_DISABLE(irq) (  (irq) < ARM_IRQ2_BASE	\
				 ? ARM_IC_DISABLE_IRQS_1	\
				 : ((irq) < ARM_IRQBASIC_BASE	\
				   ? ARM_IC_DISABLE_IRQS_2	\
				   : ARM_IC_DISABLE_BASIC_IRQS))
#define ARM_IRQ_MASK(irq)	(1 << ((irq) & (ARM_IRQS_PER_REG-1)))

typedef struct
{
	uint32 Reset;
	uint32 UndefinedInstruction;
	uint32 SVC;
	uint32 PrefetchAbort;
	uint32 DataAbort;
	uint32 Unused;
	uint32 IRQ;
	uint32 FIQ;
} ExceptionTable;

typedef void IRQHandler(void* Param);

void SetupInterrupts();
void InterruptSystemConnectIRQ(unsigned IRQ, IRQHandler* Handler, void* Param);
void InterruptSystemDisconnectIRQ(unsigned IRQ);
void InterruptSystemEnableIRQ(unsigned IRQ);
void InterruptSystemDisableIRQ(unsigned IRQ);
int InterruptSystemCallIRQHandler(unsigned IRQ);

void InterruptHandler(void);
void IRQStub(void);
void SVCStub(void);

#ifdef __cplusplus
}
#endif

#endif
