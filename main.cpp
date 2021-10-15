/* mbed Microcontroller Library
 * Copyright (c) 2021 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "dwt.h"

DigitalOut  led1(LED1);

// global times for quick an easy access
uint32_t    t1;
uint32_t    t2;

// simple static function and callback
void staticFn()
{
    t2 = getDwtCyccnt();
}

Callback<void()>  cbStatic(staticFn);


// class with member that should be called
class Foo {
public:
    Foo() {};
    void memberFn() { t2 = getDwtCyccnt(); };
};
Foo foo;

Callback<void()>  cbMember(callback(&foo, &Foo::memberFn));



int main()
{
    printf("callback performance test\n");
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
    enableDwtCyccnt();

    t1 = getDwtCyccnt();
    staticFn();
    printf("cyles staticFn          : %lu  %.3f us\n", t2-t1, (t2-t1)/168.0f);

    t1 = getDwtCyccnt();
    cbStatic();
    printf("cyles callback staticFn : %lu  %.3f us\n", t2-t1, (t2-t1)/168.0f);

    t1 = getDwtCyccnt();
    cbMember();
    printf("cyles callback memberFn : %lu  %.3f us\n", t2-t1, (t2-t1)/168.0f);


    while(1) {
        led1 = !led1;
        ThisThread::sleep_for(200ms);
    }
}