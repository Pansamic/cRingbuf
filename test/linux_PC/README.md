# cRingbuf on Linux PC

This is a simple test on Linux PC

## Build test

```bash
git clone https://github.com/Pansamic/cRingbuf.git
cd cRingbuf/test/linux_PC
mkdir build && cd build
cmake ..
make
./cRingbuf_test 1024 10
```

## Test description

## Usage


## Example

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

