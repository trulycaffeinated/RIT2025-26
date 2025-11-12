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
- Processor stages and what they do
Static Timing Analysis
- TimeQuest
- What determines the max frequency of a synchronous system? - The critical path (Longest/slowest path)
- **Netlist - Is the output of synthesis before the fitter**
	- Fitter takes netlist like instructions
- Setup and Hold
- Modeling timing
- Longest and Shortest Path
- Clock jitter vs Clock Skew
	- Skew is multiple flip flops
	- Jitter is a single flip flop
Bus Structure
- Basic wires
- Some examples
- Async vs Sync
- Bandwidth vs. Effective Bandwidth
- Bus Arbiters and possible strategies
DMA/DMAC
- What does a DMAC do? How is it configured?
- What information does processor provide?
- Advantages and disadvantages
- Bus arbitration schemes