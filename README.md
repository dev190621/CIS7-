# CIS7-
This project implements a complete Vigenère Cipher encryption and decryption system using C++. The Vigenère Cipher is a classical polyalphabetic substitution cipher that improves upon simple Caesar ciphers by using multiple shifting alphabets determined by a repeating keyword. The project demonstrates how discrete mathematics concepts—particularly modular arithmetic (mod 26) and cyclic sequences—are applied in practical cryptographic algorithms.

The program allows users to interactively encrypt or decrypt messages through a menu-driven console interface. It accepts full sentences as input, preserves spaces and punctuation for readability, and supports both uppercase and lowercase letters while maintaining their original case in the output. The keyword is automatically repeated and aligned with alphabetic characters in the message, ensuring accurate encryption and decryption.

Encryption is performed using the formula:

Ei = (Pi + Ki) mod 26

Decryption reverses the process using:

Di = (Ei − Ki + 26) mod 26

where plaintext, key, and ciphertext characters are mapped to numeric values between 0 and 25. Input validation ensures the keyword contains at least one alphabetic character, preventing invalid cipher operations.

This project was developed as part of a Discrete Structures / C++ course project and emphasizes algorithm design, mathematical correctness, and clear user interaction. While the Vigenère Cipher is not secure by modern cryptographic standards, this implementation serves as a strong educational example of classical cryptography and discrete mathematics in software development.
