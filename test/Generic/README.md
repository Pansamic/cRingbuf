# cRingbuf on Generic Platform

## Build test

**Build on Linux**

```bash
git clone https://github.com/Pansamic/cRingbuf.git
cd cRingbuf/test/Generic
mkdir build && cd build
cmake ..
make
./cRingbuf_test 1024 10
```

**Build on Windows**

```bash
git clone https://github.com/Pansamic/cRingbuf.git
cd cRingbuf/test/Generic
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
cRingbuf_test 1024 10
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

