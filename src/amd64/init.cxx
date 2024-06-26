export module amd64;

import fmt;

import :gdt;
import :idt;

export namespace amd64
{
    void init()
    {
        gdt::init();
        print("GDT initialised\n");
        idt::init();
        print("IDT initialised\n");
    }
}