Rec. Reading
- The Soul of a New Machine
- Death March - Edward Yourdon
---
**.dll** is a collection of functions program can call upon
**Link File** - where in memory your program is going to reside
***Never*** believe an RTOS vendor

Operating system creates the framework for your applications, allowing **portability** and **abstraction**
## Computer Operating Systems
Provides a "virtual machine" for applications
Provides a means for apps to migrate across platforms
Manage HW resources across applications

Benefits of an OS
- Portability - one application can be used on many systems
- Abstraction - Application can be written with limited knowledge of hardware devices

**Virtual Machine** - OS will lie to the programmer and tell the app that it has more resources than it does, so that the app can work on any machine

*Bottom line is **Productivity** - software development is more efficient with an OS*

An OS is broken up into pieces - subsystems - that are related to the hardware
Generally around accessing discs
- Data storage
- Communication
- Graphical displays
- User Input (Peripherals)

Organization often becomes multi level
- Usb Devices - subdivided by hardware function (storage, keyboard, mouse, etc.)
- Ethernet devices - subdivided by comm protocol

Need to decide how to organize the subsystems, user interface, or protocol?

When developing an API, it needs to be user friendly so that anyone can use it easily
W/ an OS API you need to think the same way the developers did
Advantage of an RTOS is it is relatively simple

### Device Drivers
W/ a traditional OS device drivers are considered part of the OS and form part of the API
this is because we don't trust people

Device drivers directly access the hardware and therefore must be part of the "trusted" software

In addition to directly accessing the hardware devices, device drivers must also respond to interrupts from the hardware

Device Driver Architecture is split into top half and bottom half
"Top Half" - Application Interface (Driver API)
Functional Layer between
"Bottom Half" - Hardware Layer 1, 2, etc...

### Kernel Functions
Many API functions are not part of a device driver - these are "Kernel Functions"

They don't have anything to do with hardware
Almost all Kernel Functions do NOT interact with the hardware

Our tasks are going to be functions, so instead of executing a program we will execute a function
This cannot be done with any old function

Tasks in an RTOS will interact with each other unlike tasks/applications in a standard OS ; the tasks in an RTOS all exist in the same memory space

Multiple things executing in parallel w/ complete access to all variables will cause chaos
- We will control that chaos using Kernel functions within the RTOS

Generally the RTOS will contain only kernel functions
- Functions that allow two tasks to interact with the RTOS and with each other
Generally an RTOS does not contain device drivers