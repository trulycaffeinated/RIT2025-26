No assembly on Exam 2 - will be on final

Everything from Week 6 - Now
Signal Tap
PWM 
Memory
Address Decoding
Byte Ordering - Little vs Big Endian
Byte Addressable Ram
Cache & Memory hierarchy
Locality Principles
- Spatial
- Temporal
Cache mapping, hits vs misses, thrashing, replacements
- Compulsory
- Conflict
- Capacity
Hardware Acceleration
- Advantages & Disadvantages 
Single vs Multithreaded
Speed up analysis
Custom Instructions vs Custom components
- Where do they exist?
	- **Component sits on Avalon Interface vs Instruction sits in the execute stage inside the NIOS**
- How many can you have?
	- Support up to 256 custom instructions
- Different types and support?
- Custom Instruction is your own special AND gate or bit swap etc. - two different locations in the NIOS (KNEE-O-s) system.
Audio basics
- Nyquist
- Aliasing
- Sampling - how often you're taking samples
- Resolution - how many bits are used to represent data values
Pipelining
- Large combinational area - break up large number of if statements into smaller pieces to pass timing
- Staging using registers.
- Throughput - How many instructions can I push through / second
- Latency - How long does it take for one instruction to make it through the pipeline
- Instruction Time - How long does it take to execute instruction (doesn't change)
- Hazards
	- Data
	- Structural
	- Control
- Branch Prediction and impacts
- Processor stages and what th