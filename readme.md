# Linux so hijack PoC

```
$ ./dummy
this is original string
$ LD_PRELOAD="./libhijack.so" ./dummy
this is hooooook string
```