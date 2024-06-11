# trading_system
This is a self-project aiming to build a high-frequency, high-capacity trading system by taking other open source trading systems in github as reference.

The aim of the project is to learn the basic structure of a quantitative trading system and get hands-on experience on building the system.

The project is initiated by:
Mok Ka Chun, Eric from HKUST Technology and Management Dual Degree Program- Beng COMP BBA Finance

Trading systems references:
Starquant
WonderTrader
Vnpy
PandoraTrader
hikyuu

This trading_system plans to use the interface from FUTU to implement the trade operations, quotings and data.



File Structure explaination:

API
Contains APIs from Brokerage platforms
Futu : 富途牛牛

DataStruct
Definition of all base data structure used in the system

Helper
Definition of all common helper functions

Interface
Interfaces of the system, all classes should inherit from the interface

Log
Log functions used in the system

Trader
Encapuslation of brokerage apis to accomodate the system

System structure:

The system plan to have an API-calling infrastructure

    The core of the system is written in C++, and Manager apis are exposed by pybind. Python then called these APIs to build the system

Structure:

The system is formed by many Managers.
Each managers are running in different threads
Each managers containing all the objects 

