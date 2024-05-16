# Rasha_Shajahan-SDN-based-Error-Correction-Mechanism-in-Quantum-Key-Distribution-Protocol
This repository has the codes used for the implementation of the project "SDN-based Error Correction Mechanism in Quantum-Key-Distribution".
###

<h2 align="left">Project Overview:- </h2>

###
A new approach using software-defined networking (SDN) is being explored for error detection and correction in quantum key distribution. This method allows controllers to select the most suitable error correction mechanism based on the Quantum Bit Error Rate, resulting in an error-free shared key.

<h2 align="left">Quantum Key Distribution:- </h2>

* Quantum Key Distribution (QKD) is a secure communication method that uses quantum mechanics principles to generate a random secret key.
* In QKD, the post-processing stage holds significant importance, as it addresses errors stemming from diverse sources like the presence of eavesdropping, device imperfection, or interference from environmental conditions.

**Steps:**

* Sender sends a sequence of random bits by encoding them into series of polarization states using a series of random bases, through quantum channel. 
* Reciever measures the photon polarization of the received photons using a series of random bases.
    * Due to potential losses in the channel, some of receiver's measurements may yield to null bits.
    * In the case the basis of receiver is different from sender, the measurement result is randomized.
* Receiver reveals the partial information about the basis, used for the measurement. 
* Sender discloses the information regarding matching bases. 
* Reveiver decode the photon states into binary bits for the matching bases. 
* Sender and receiver derive a shared key from the remaining key bits.  

<h2 align="left">Block Diagram:- </h2>
The block diagram of the proposed system is shown in

###

###
 <h2 align="left">Procedure to be adhered to for execution:- </h2>

* Establish the operating environment for implementing the algorithm.
* Install necessary libraries and performance evaluation tools.
* Choose the PQC algorithm for implementation.
* Set up parameters, security levels, and key sizes according to the selected algorithm.
* Generate key-pair.
* Generate various types of signed documents and perform the verification process.
* Assess the algorithm based on key size, time taken for signing and verification, and the protocol used for file transfer, among other factors.

###
 <h2 align="left">Dependencies:- </h2>
 
 * Darpan Application: Java 
 * MAQAN Controller: C++
 * NS3 Simulator: C++
 * OpenSSL Library
 * A virtual machine:
      * Version: Ubuntu 64-bit
      * Processing cores: 3
      * Hard Disk: 32 GB
      * Memory: 4GB

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
 <h2 align="left">Results:- </h2>

