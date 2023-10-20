#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "cRingbuf.h"

#define RINGBUF_HANDLE(fn) \
    {\
        ringbuf_ret_t ret = fn;\
        if(ret == RINGBUF_ERROR)\
        {\
            printf("ring buffer error!\r\n");\
        }\
        else if(ret == RINGBUF_FULL)\
        {\
            printf("ring buffer full!\r\n");\
        }\
        else if(ret == RINGBUF_EMPTY)\
        {\
            printf("ring buffer empty!\r\n");\
        }\
        else if(ret == RINGBUF_LACK_SPACE)\
        {\
            printf("ring buffer lack space!\r\n");\
        }\
        else if(ret == RINGBUF_LOCKED)\
        {\
            printf("ring buffer locked!\r\n");\
        }\
    }

void print_ringbuf_status(ringbuf_t *ringbuf)
{

    printf("-Ring buffer status:\r\n");
    printf("-capacity:%ld\r\n", ringbuf->capacity);
    printf("-size:%ld\r\n", ringbuf->size);
    printf("-head:%ld\r\n", ringbuf->head);
    printf("-tail:%ld\r\n", ringbuf->tail);
    printf("-is_full:%d\r\n", ringbuf->is_full);
    printf("-is_empty:%d\r\n", ringbuf->is_empty);
    printf("-lock:%d\r\n", ringbuf->lock);
    printf("-rule:%d\r\n", ringbuf->rule);
}

int main(int argc, char *argv[])
{
    ringbuf_t ringbuf;
    if (argc != 3)
    {
        printf("Usage: %s <buffer_size> <cycle>\r\n", argv[0]);
        return 0;
    }
    size_t test_buffer_size = atoi(argv[1]);
    size_t test_cycle = atoi(argv[2]);
    unsigned char *buffer = (unsigned char *)malloc(test_buffer_size);
    unsigned char *data = (unsigned char *)malloc(test_buffer_size);
    unsigned char *container = (unsigned char *)malloc(test_buffer_size);
    size_t test_cycle_write_size = 0;
    size_t test_cycle_read_size = 0;
    size_t test_cycle_actual_read_size = 0;

    printf("init ringbuf\r\n");

    RINGBUF_HANDLE(ringbuf_init(&ringbuf, buffer, test_buffer_size, RINGBUF_RULE_OVERWRITE));

    print_ringbuf_status(&ringbuf);

    srand(time(NULL));

    for(int i=0 ; i<test_cycle ; i++)
    {
        printf("---------------------\r\n");
        printf("-------CYCLE %d-------\r\n", i);
        printf("---------------------\r\n");
        test_cycle_write_size = rand() % test_buffer_size;
        test_cycle_read_size = rand() % test_buffer_size;

        memset(data, 0, test_buffer_size);
        memset(container, 0, test_buffer_size);

        for(size_t j=0 ; j<test_cycle_write_size ; j++)
        {
            data[j] = 'A' + rand() % 26;
        }

        printf(">>>Write: length:%ld\r\n",test_cycle_write_size);

        RINGBUF_HANDLE(ringbuf_write_block(&ringbuf, data, test_cycle_write_size));

        print_ringbuf_status(&ringbuf);
        // printf("Buffer data: %s\r\n", ringbuf.buf);

        RINGBUF_HANDLE(ringbuf_get_block(&ringbuf, container, test_cycle_read_size, &test_cycle_actual_read_size));

        printf("<<<Read: target_read_size:%ld ; actual_read_size:%ld\r\n",test_cycle_read_size, test_cycle_actual_read_size);
        print_ringbuf_status(&ringbuf);
    }

    return 0;
}

