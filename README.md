# Rasha_Shajahan-SDN-based-Error-Correction-Mechanism-in-Quantum-Key-Distribution-Protocol

###

<h2 align="left">Overview:- </h2>

###
This survey centres around the Post-Quantum Digital Signature Algorithm, a critical subject considering the vulnerability of current public key infrastructure, notably RSA and Diffie-Hellman, to quantum computers. The imperative to secure the Internet's security architecture from potential quantum threats necessitates a quantum-resistant approach. Addressing these security concerns falls within the realm of post-quantum cryptography (PQC), with the National Institute of Standards and Technology (NIST) taking a lead role in standardization. The 3rd round of NIST has identified three finalists (CRYSTALS-Dilithium, Falcon, and Rainbow) and three alternate candidates (GeMSS, Picnic, and SPHINCS+) for PQC digital signatures. This survey assesses these candidates, considering factors such as security, performance, efficiency, and their applicability to diverse real-world scenarios.

<h2 align="left">Quantum Key Distribution:- </h2>

* Quantum Key Distribution (QKD) is a secure communication method that uses quantum mechanics principles to generate a random secret key.
* In QKD, the post-processing stage holds significant importance, as it addresses errors stemming from diverse sources like the presence of eavesdropping, device imperfection, or interference from environmental conditions.

**Steps:**

* Sender sends a sequence of random bits by encoding them into series of polarization states using a series of random bases, through quantum channel. 
* Reciever measures the photon polarization of the received photons using a series of random bases.
    * Due to potential losses in the channel, some of receiver's measurements may yield to null bits.
    * In the case the basis of receiver is different from sender, the measurement result is randomized.
* Receiver reveals the partial information about the basis, used for the measurement. 
* Sender will reveals information regarding the matching bases. 
* Reveiver decode the photon states into binary bits for the matching bases  
* Sender and receiver derive a shared key from the remaining key bits.  
<img width="455" alt="QKD Process" src="https://github.com/AmritaCSN/Rasha_Shajahan-SDN-based-Error-Correction-Mechanism-in-Quantum-Key-Distribution-Protocol/blob/main/Image/QKD-BlockDiagrams/Screenshot%202024-05-16%2017171.png">

<h2 align="left">Error detection and Error Correction Mechanism:- </h2>

<h2 align="left">Methododlogy:- </h2>
![DSA](https://github.com/AmritaCSN/Rasha_Shajahan-A-Survey-on-Post-Quantum-Digital-Signature-Algorithms/assets/75829999/2af0246c-08b5-459c-b7f4-4331af637405)




###
 <h2 align="left">Tools for evaluating PQC digital signature algorithms:- </h2>

 * OpenSSL
 * Cryptographic Libraries: Liboqs, libsodium, Crypto++
 * NIST PQC Benchmarking Tools
 * SUPERCOP Benchmarking suite
   
(Example setup: A virtual machine with 6 processing cores and 6GB of RAM on a computer equipped with a 16-core 32-thread AMD Ryzen 9 3950X processor with 3.5 GHz processor frequency, and 32 GB RAM.)

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
 <h2 align="left">Deployment:- </h2>
 ![System Architecture](https://github.com/AmritaCSN/Rasha_Shajahan-SDN-based-Error-Correction-Mechanism-in-Quantum-Key-Distribution-Protocol/blob/main/Image/QKD-BlockDiagrams/Screenshot%202024-03-29%20132434.png)
 <h3 align="left">Implementation Environment setup:- </h3>
* Apache Tomcat v10 Installation
* Database Setup with PostgreSQL v15 
* Java Environment Configuration
* MAQAN Controller Configuration
* VMware Player 17.5 Setup
* Simulation of NS3 and NetSquid
* Darpan Application Installation
![image](https://github.com/AmritaCSN/Rasha_Shajahan-SDN-based-Error-Correction-Mechanism-in-Quantum-Key-Distribution-Protocol/assets/75829999/0767d478-ac96-4abb-8ad8-a9dcdd1871b8)


 ###
 <h2 align="left">Results:- </h2>

