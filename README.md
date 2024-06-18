# trading_system
This is a self-project aiming to build a quantitative trading system by taking other open source trading systems in github as reference.

The aim of the project is to learn the basic structure of a quantitative trading system and get hands-on experience on building the system.

Also, in terms of Computer Science, the project aims to serve as learning material for memory sharing (kungfuyijinjing) and message queue (nanomsg)

**The project is initiated by:**

**Mok Ka Chun, Eric** from HKUST Technology and Management Dual Degree Program- Beng COMP BBA Finance

## Trading systems references:
Starquant (structure)

WonderTrader

Vnpy

PandoraTrader

hikyuu


## Descriptions

This trading_system plans to use the interface from FUTU to implement the trade operations, quotings and data.

### Dependencies

**spdlog**

This is a thread-safe light-weight log lib.

**NNG**

This is a successor of nanomsg. It is a lightweight, broker-less library,offering a simple API to solve common recurring messaging problems. This library is used to achieve the in-system communication as an aid of sharing memory approach.

### File Structure Explaination:

**API**

Contains APIs from Brokerage platforms

Futu : 富途牛牛


**Helper**

Definition of all common helper functions

Log functions used in the system

**Interface**

Interfaces of the system, all classes should inherit from the interface

Data strucutre used in the system


**Trader**

Encapuslation of brokerage apis to accomodate the system

### System structure:

The system plan to have an C-S desgin, where the client is written in Python, server written in C++

### Structure:

The hierarchy of the system is described as below

Trade system engine <- Managers/Components <- individual processes for strategy / data /trader etc

The communication within the server is done by memory sharing(kungfu) and message(nanomsg)



## TODO
1. Define basic data structures (done)
2. Deinfe logger and messager
3. Define trader interfaces
4. Encapsulate Futu api