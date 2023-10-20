# cRingbuf

High performance ring buffer for generic platform, optimized for embeded system.

1. multi-thread safe.
2. optimize memeory copy speed.
3. support fill or discard dataframe when buffer is going to be full.
4. optimize for continuous memory block, DMA-friendly.

---

## Build Test

### test on linux PC

```bash
git clone https://github.com/Pansamic/cRingbuf.git
cd cRingbuf/test/linux_PC
mkdir build && cd build
cmake ..
make
./cRingbuf_test 1024 10
```

### test on STM32 MCU

TODO

## Example


**On PC**
```c
#include "cRingbuf.h"

#define RING_BUFFER_SIZE 1024 //unit:byte, must be power of two

int main(int argc, char* argv[])
{
    ringbuf_t ringbuf;
    unsigned char * buffer = (unsigned char*)malloc(RING_BUFFER_SIZE);
    ringbuf_init(ringbuf, buffer, RING_BUFFER_SIZE, RINGBUF_RULE_FILL);

    ...
}

```

**On MCU**

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

## API

```c
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_init(ringbuf_t *ringbuf, void *buf, size_t capacity, ringbuf_rule_t rule);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_reset(ringbuf_t *ringbuf);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_align_optimize(ringbuf_t *ringbuf);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_write_byte(ringbuf_t *ringbuf, uint8_t data);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_write_block(ringbuf_t *ringbuf, void *data, size_t length);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_get_byte(ringbuf_t *ringbuf, uint8_t *data);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_get_block(ringbuf_t *ringbuf, void *data, size_t length, size_t *read_length);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_peek_byte(ringbuf_t *ringbuf, uint8_t *data);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_peek_block(ringbuf_t *ringbuf, void *data, size_t length, size_t *read_length);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_remove_byte(ringbuf_t *ringbuf);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_remove_block(ringbuf_t *ringbuf, size_t length, size_t *removed_length);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_get_size(ringbuf_t *ringbuf, size_t *size);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_get_capacity(ringbuf_t *ringbuf, size_t *capacity);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_get_free_size(ringbuf_t *ringbuf, size_t *free_size);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_get_free_continuous_block(ringbuf_t *ringbuf, void **data, size_t *length);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_get_stuffed_continuous_block(ringbuf_t *ringbuf, void **data, size_t *length);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_lock(ringbuf_t *ringbuf);
RINGBUF_PUBLIC(ringbuf_ret_t) ringbuf_unlock(ringbuf_t *ringbuf);
```

## TODO

1. add comment.
2. expose function that de/increasing size and retreat/advance head/tail in order to fit the form of DMA transmission.