# Rasha_Shajahan-SDN-based-Error-Correction-Mechanism-in-Quantum-Key-Distribution-Protocol

###

<h2 align="left">Overview:- </h2>

###
This survey centres around the Post-Quantum Digital Signature Algorithm, a critical subject considering the vulnerability of current public key infrastructure, notably RSA and Diffie-Hellman, to quantum computers. The imperative to secure the Internet's security architecture from potential quantum threats necessitates a quantum-resistant approach. Addressing these security concerns falls within the realm of post-quantum cryptography (PQC), with the National Institute of Standards and Technology (NIST) taking a lead role in standardization. The 3rd round of NIST has identified three finalists (CRYSTALS-Dilithium, Falcon, and Rainbow) and three alternate candidates (GeMSS, Picnic, and SPHINCS+) for PQC digital signatures. This survey assesses these candidates, considering factors such as security, performance, efficiency, and their applicability to diverse real-world scenarios.

<h2 align="left">Quantum Key Distribution:- </h2>

* Quantum Key Distribution (QKD) is a secure communication method that uses quantum mechanics principles to generate a random secret key.
* In QKD, the post-processing stage holds significant importance, as it addresses errors stemming from diverse sources like the presence of eavesdropping, device imperfection, or interference from environmental conditions.
![image](https://github.com/AmritaCSN/Rasha_Shajahan-SDN-based-Error-Correction-Mechanism-in-Quantum-Key-Distribution-Protocol/blob/main/Image/QKD-BlockDiagrams/Screenshot%202024-05-16%2017171.png)

  
<img width="455" alt="Basic_Workflow" src="https://github.com/AmritaCSN/Rasha_Shajahan-A-Survey-on-Post-Quantum-Digital-Signature-Algorithms/assets/75829999/2531d577-4b21-434b-baf5-dd2e592e8bb3">

<h2 align="left">Error detection and Error Correction Mechanism:- </h2>

<h2 align="left">Methododlogy:- </h2>
![DSA](https://github.com/AmritaCSN/Rasha_Shajahan-A-Survey-on-Post-Quantum-Digital-Signature-Algorithms/assets/75829999/2af0246c-08b5-459c-b7f4-4331af637405)


**Steps:**

* Key Generation phase:
  * Private key generation.
  * Public key will be derived from private key.
* Identity protocol phase:
    * To associate an identity with the public key, the entity obtains a digital certificate. This certificate contains the public key and information about the entity, such as its name, organization, and other relevant details.
    * The certificate is signed by a trusted third party called a Certificate Authority (CA). This CA verifies the identity of the entity before issuing the certificate and it will be shared in the network.
* Signing phase:
    * The data intended for signing and the sender's private key are provided as inputs to the Post-Quantum Cryptography (PQC) digital signature algorithm.
    * The signed document will be shared with the reciever through internet.
* Verification phase:
    * The receiver has the ability to examine the signed document using the sender's public key.
    *If the recipient discovers that the message matches the output obtained by inputting the message and the public key into the signature algorithm, they can confirm that the message is genuinely authenticated and has not been corrupted.

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

 ###
 <h2 align="left">Results:- </h2>

