# SDN based Error Correction Mechanism in Quantum Key Distribution
This repository has the codes used for the implementation of the project "SDN-based Error Correction Mechanism in Quantum-Key-Distribution".
###

<h2 align="left">Project Overview:- </h2>

###
Employing software-defined networking (SDN) concept to perform error detection and correction in quantum key distribution process. This approach enables controllers to choose the optimal error correction method based on the Quantum Bit Error Rate, leading to the creation of a flawless shared key.

<h2 align="left">Quantum Key Distribution:- </h2>

Quantum Key Distribution (QKD) is a secure communication method that uses quantum mechanics principles to generate a random secret key between the sender and receiver.

**Steps:**

* Sender sends a sequence of random bits by encoding them into series of polarization states using a series of random bases, through quantum channel. 
* Reciever measures the photon polarization of the received photons using a series of random bases.
    * Due to potential losses in the channel, some of receiver's measurements may yield to null bits.
    * In the case the basis of receiver is different from sender, the measurement result is randomized.
* Receiver reveals the partial information about the basis, used for the measurement. 
* Sender discloses the information regarding matching bases. 
* Reveiver decode the photon states into binary bits for the matching bases. 
* Sender and receiver derive a shared key from the remaining key bits.  

###
 <h2 align="left">Dependencies:- </h2>
 
 * Darpan Application: Java 
 * MAQAN Controller: C++
 * NS3 Simulator: C++
 * A virtual machine:
      * Version: Ubuntu 64-bit
      * Processing cores: 3
      * Hard Disk: 32 GB
      * Memory: 4GB
 * Package: libssl-dev
      * To install: sudo apt-get install libssl-dev

 <h2 align="left">Environment setup:- </h2>
 
* Apache Tomcat v10 Installation
* Database Setup with PostgreSQL v15 
* Java Environment Configuration
* MAQAN Controller Configuration
* VMware Player 17.5 Setup
* Simulation of NS3 and NetSquid
* Darpan Application Installation
<img width="800" alt="System Architecture" src="https://github.com/AmritaCSN/Rasha_Shajahan-SDN-based-Error-Correction-Mechanism-in-Quantum-Key-Distribution-Protocol/blob/main/Image/QKD-BlockDiagrams/Screenshot%202024-03-29%20132434.png">

 ###
 <h2 align="left">Code execution:- </h2>
* To compile the program:

      g++ -o MAIN MAIN.cpp -lssl -lcrypto
* To get output

      ./MAIN

<h2 align="left">Block Diagram:- </h2>
The block diagram of the proposed system is shown in

###
<h2 align="left">Reference:- </h2>

[2D Parity Check](https://www.geeksforgeeks.org/longitudinal-redundancy-check-lrc-2-d-parity-check/)

[Cascade Protocol](https://cascade-python.readthedocs.io/en/latest/protocol.html)

[libssl package](https://packages.debian.org/buster/libssl-dev)

[HMAC](https://en.wikipedia.org/wiki/HMAC)
