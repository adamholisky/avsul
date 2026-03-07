# A Very Simple Utility Library

A set of OS-agnostic C data structures and algorithms that function well at various levels of OS functionality and interaction. 

## What's Included

The library is broken down into three areas: data structures, algorithms, and utilities. Below is a list of what I'm planning on including, and it's status (or lack there of).

### Data Structures

| Component | Status | Notes | 
| Bit Array | 🔴 |  | 
| Dictionary | 🔴 |  | 
| Doubly Linked List | 🔴 |  | 
| Singularly Linked List | 🔴 |  | 

### Algorithms

| Component | Status | Notes | 
| CRC32 | 🔴 |  | 
| RegEx | 🔴 | Very VERY simple | 
| SHA256 Hash | 🔴 |  | 
| Tokenizer | 🔴 |  |

### Utilities

| Component | Status | Notes | 
| AVSI | 🔴 | A Very Simple Interpreter | 

## Underlying philosophy and goals

There's hundreds upon hundreds of libraries that do this. Why another one? Because my use case in OS development is specific -- something that can run well both when a memory allocator is available or unavailable. Along the same line, a lot of that code that is out there isn't very friendly. Brevity and obscure header file syntax that you only have to use yourself once a year isn't very great for understanding things. I hope to do things different with this!

Goals for the library:
1. **Dynamic memory allocation is optional**. Sometimes malloc isn't very advanced, or isn't something that you want to necessarily use in early stage OS initalization.
2. **Clean code and architecture**. Code can be art when done right, and a clean architecture means the API is easy to understand and integrate.
3. **Safety first**. Given a choice between writing a safe routine and making the routine a few ticks faster, prefer safety.

Personally, I have a few goals with this as well:
- *Full use of standard GNU tools*
- *Nearly complete code coverage in unit tests*
- *Full integrated CICD pipeline*
- *Nothing is under NDA*! Yay! So much of what I've ever written is under lock and key, this is a space for me to show off a high-level of software engineering skills.

