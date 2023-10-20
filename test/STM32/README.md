# cRingbuf on MCUs

The STM32 cmake test project is from [rxdu/stm32_cmake](https://github.com/rxdu/stm32_cmake).

## Build test

## Test description

## Usage


## Example

```c
#include "cRingbuf.h"

#define RING_BUFFER_SIZE 256 // unit:byte, must be power of two

/* uart1 */
ringbuf_t uart1_rx_ringbuf;
uint8_t uart1_rx_buf[RING_BUFFER_SIZE]={0};
uint8_t *uart1_free_block_ptr;
size_t uart1_free_block_size;

void main(void)
{
    Hardware_Init();

    BSP_Init();

    ringbuf_init(&uart1_rx_ringbuf,uart1_rx_buf,RING_BUFFER_SIZE,RINGBUF_RULE_FILL);
    ringbuf_get_free_continuous_block(&uart1_rx_ringbuf, &free_block_ptr, &uart1_free_block_size);
    DMA_StartTransmit(&hdma1, free_block_ptr, free_block_size);
    DMA_IRQEnable(&hdma1);

    FreeRTOS_Init();

    vTaskSchedulerStart();

    while(1)
    {

    }
}

void DMA_IRQHandler(void)
{
    DMA_Clear_Flags(...);

    ringbuf_get_free_continuous_block(&uart1_rx_ringbuf, &free_block_ptr, &uart1_free_block_size);
    DMA_StartTransmit(&hdma1, free_block_ptr, free_block_size);
    DMA_IRQEnable(&hdma1);
}

void Task_Process_UART1(void * Parameters)
{

}
```




