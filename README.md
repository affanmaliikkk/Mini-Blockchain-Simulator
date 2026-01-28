# **Mini Blockchain Simulator (C++ / Dev-C++)**

### 

### **📌 Project Overview**



This project is a Mini Blockchain Simulator written in C++ (Dev-C++ / C++98 standard). It demonstrates how core blockchain concepts work internally—such as block linking, hashing, immutability, transactions, and tamper detection—without using any external blockchain libraries.



The project is designed for academic learning, university submission, and resume/GitHub showcasing, focusing on clarity and correctness rather than real cryptocurrency networking.





### **🎯 Key Objectives**



Understand blockchain structure at code level



Learn block-to-block hash linking



Simulate account creation and transactions



Detect blockchain tampering



Practice OOP concepts (inheritance, polymorphism, abstraction, encapsulation, file handling etc.)





### **🛠️ Language \& Tools**



**Language:** C++ (C++98 compliant)



**Compiler:** Dev-C++ (MinGW)



**Paradigm:** Object-Oriented Programming



**Platform:** Windows





### **🧱 Blockchain Design Used**



This is a simulated, centralized blockchain with the following logic:



Blocks are stored in a vector<BaseBlock\*>



Each block contains:



Index



Timestamp



Previous hash



Current hash



Data (account or transaction info)





Each new block stores the hash of the previous block



If a block is modified, hash linkage breaks → chain becomes invalid





**⚠️ No networking, mining, consensus, or cryptography libraries are used. This is an educational blockchain model.**





### **🧩 Block Types Implemented**



#### 1️⃣ Account Block



Represents user account creation.



Stores:



Name



Date of Birth



Gmail



Account Number (random)



Initial Balance





First block (Genesis) is a SYSTEM account





#### 2️⃣ Transaction Block



Represents money transfer between accounts.



###### Stores:



Sender



Receiver



Amount





Automatically updates balances logically



Generates a transaction receipt





### **🔐 Hashing \& Security Logic**



Hash is calculated using:



Block index



Timestamp



Block-specific data



Previous block hash





Hashing is done using stringstream (simple simulation)



Tampering modifies block data without updating next blocks



Validation checks if:





**previousHash == previousBlock.currentHash**





If mismatch found → blockchain marked CORRUPTED





### **🚨 Tampering Detection**



User can manually tamper any block



Once tampered:



Block is marked



Chain validation fails



Shows blockchain is no longer trustworthy







This demonstrates immutability, a core blockchain principle.





### **📁 Project Structure (File-by-File)**



MiniBlockchain/

│

├── AbstractBlock.h               # Base abstract class for all blocks

├── BaseBlock.h/.cpp              # Common block functionality

├── AccountBlock.h/.cpp           # Account creation block

├── TransactionBlock.h/.cpp       # Transaction block

├── Blockchain.h/.cpp             # Core blockchain logic

├── TransactionLogger.h/.cpp      # Logs transactions to file

├── main.cpp                      # Menu-driven user interface

├── transactions.txt              # Stored transaction logs

├── Project23.dev                 # Dev-C++ project file







##### ▶️ How to Compile \& Run (Dev-C++)



1\. Open Dev-C++



2\. Click File → Open Project



3\. Open Project23.dev



4\. Click Compile \& Run (F11)



✔ No external libraries required





### **🧪 Sample Usage Flow**



1\. Create accounts (users)



2\. Send transactions between users



3\. View blockchain blocks



4\. Check blockchain validity



5\. Display balances



6\. Tamper a block



7\. Re-check validity → corruption detected





### **🧠 Concepts Used**



##### • Object-Oriented Programming (OOP)



Classes



Objects



Abstraction 



Encapsulation



Constructors



Member functions



##### • Data Structures



Vectors



##### • Blockchain Fundamentals



Hashing concepts



Time handling in C++



Menu-driven program design





### **📚 Learning Outcomes**



Deep understanding of blockchain internals



Practical OOP implementation in C++



Hash linking and immutability concepts



Real-time tamper detection logic



Memory management using pointers





### **🚀 Future Improvements**



Strong cryptographic hashing (SHA-256)



Digital signatures



Proof of Work / Mining simulation



File-based blockchain persistence



GUI interface



Decentralized node simulation





### **🏫 Academic Suitability**



✔ University submission ✔ Viva explanation ready ✔ Resume project ✔ GitHub portfolio ✔ LinkedIn project showcase







#### **👤 Author**



Affan Ahmad Malik,
 Abdul Rehman,
 Muhammad Hassam.

Cyber Security Undergraduate

Mini Blockchain Simulator (C++)





###### **NOTE:**

&nbsp;    This project is for educational purposes only and does not represent a real cryptocurrency system.




