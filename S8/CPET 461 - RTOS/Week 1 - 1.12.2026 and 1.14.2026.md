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

In addition to directly acc