# Theory-of-Algorithims-Project
This is my solution to the project that we have gotten for Theory of Algorithims.

## What we needed to do
In this project you must write a program in the C programming language to calculate the SHA512 value of an input file. Your program must take the name or path of the file as a command line argument and output the SHA512 digest of it. The program must be coded from scratch - you cannot use any external libraries other than what is included in the C standard library. Your program must compile using gcc or clang and you must include a Makefile which compiles it upon make being called in the project folder. You must also include tests which run upon make test being called, as will be described in lectures. You should also include in your repository an appropriate .gitignore file and a README.md as described below.

## What is SHA512 ?
SHA512 is a set of set of cryptograpchic hash functions with digest length of 512. 

## Description of the repo
#### Symbols and Operators
Following symbols and operators are used in the secure has algorithim
- <b>AND, OR, XOR</b> are used as <b>^, ⊕, ∨</b>
- <b>Complement, Left-shift, Right-shift</b> are used as <b>~, <<, >></b>
- <b>ROTL n(x)=(x << n) ∨ (x >> w - n)</b> Circular left shift operation, where x is a w-bit word and n is an integer with 0 <= n < w
- <b>ROTR n(x)=(x >> n) ∨ (x << w - n)</b> Circular right shift operation, where x is a w-bit word and n is an integer with 0 <= n < w
- <b>SHR n(x)=x >> n</b> The right shift operation, where x is a w-bit word and n is an integer with 0 <= n < w

#### Defined functions
```C
#define ROTL(_x,_n) ((_x << _n) | (_x >> ((sizeof(_x)*8) - _n)))
#define ROTR(_x,_n) ((_x >> _n) | (_x << ((sizeof(_x)*8) - _n)))
#define SHR(_x,_n) (_x >> _n)

#define CH(_x,_y,_z) ((_x & _y) ^ (~_x & _z))
#define MAJ(_x,_y,_z) ((_x & _y) ^ (_x & _z) ^ (_y & _z))

#define SIG0(_x) (ROTR(_x,28)  ^ ROTR(_x,34) ^ ROTR(_x,39))
#define SIG1(_x) (ROTR(_x,14)  ^ ROTR(_x,18) ^ ROTR(_x,41))
#define Sig0(_x) (ROTR(_x,1)  ^ ROTR(_x,8) ^ SHR(_x,7))
#define Sig1(_x) (ROTR(_x,19) ^ ROTR(_x,61) ^ SHR(_x,6))
```

#### Union Block
SHA512 works on block of 1024 bits
```C
union Block {
    // 8 x 128 = 1024 - dealing with block as bytes
    BYTE bytes[128];
    // 32 x 16 = 512 - dealing with block as words
    WORD words[16];
    // 64 x 16 = 1024 - dealing with the last 64 bits of last block
    uint64_t sixf[16];
};
```
In order to keep track of where we are with the input message
```C
enum Status {
    READ, PAD, END
};
```

K is a sequence of 80 constant 64-bit words. These words represent the first 64 bits of the fractional parts of the cube roots of the first 80 prime numbers.
```C
const WORD K[] = {
    0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
    0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
    0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
    0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
    0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
    0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
    0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
    0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
    0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
    0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
    0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
    0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
    0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
    0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
    0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
    0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
    0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
    0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
    0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
    0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};
```

The initial 8 hash values for SHA512
```C
WORD H[] = {
    0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
    0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
};
```
Main method of the project
```C
int main(int argc, char *argv[]) {
  // Create a File pointer for reading in a file
  // Open file from command line for reading
  // Calculate the SHA512 of f
  // Print the final SHA512 hash
  // Close the file and return 0
}
```


## Instalations
These are the instructions to guide you how to set up this project on your own device. This project was created in Ubuntu.

#### Step 1: Enable WSL
Firstly you will need to enable "Windows Subsystem for Linux" before installing any Linux distributions on Windows. Open up powershell as administrator and type in:
```
dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
```

#### Step 2: Check requirements for WSL2
In order to update to WSL2 you need to be on Windows 10. To check your windows version, press <b>window key + R</b> and type <b>winver</b>.

#### Step 3: Enable VM (Virtual Machine) feature
In order to install WSL2 you need to enable the virtual machine feature. Open up powershell as administrator and type in:
```
dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
```
Make sure to restart your PC after this step.

#### Step 4: Download latest Linux kernel package
1. Donwload the latest package and run the update:
[WSL2 Linux kernel update package for x64 machines](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi)

#### Step 5: Set WSL2 as default version
Open up powershell as administrator and type in:
```
wsl --set-default-version 2
```

#### Step 6: Install your Linux distribution of choice
You can find all the linux distributions on the [Microsoft store](https://aka.ms/wslstore). Pick the Linux distribution you want to work with (Ubuntu in my case). Opening the Linux distribution will take longer as you will be asked to wait for a minute or two for files to de-compress and be stored on your PC. All future launches should take less than a second.
Once completed you will need to create a user and passowrd for login purposes. That is all for downloading Linux distribution on your device.

### Install Windows Terminal (Optional)
- Get windows terminal from [here](https://docs.microsoft.com/en-us/windows/terminal/get-started)
- Set your distribution version, either WSL1 or WSL2. Open up powershell as administrator and type in:
```
wsl --set-version <distribution name> <versionNumber>
```
- To make WSL your default architecture in powershell type in:
```
wsl --set-default-version 2
```

#### Troubleshooting installation
For any troubles please visit microsoft [Troubleshooting installation](https://docs.microsoft.com/en-us/windows/wsl/install-win10#troubleshooting-installation)




# Answers to questions
#### Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?
- It isnt encrypted it is hashed.
- https://crypto.stackexchange.com/questions/45377/why-cant-we-reverse-hashes#:~:text=Bit%20dependency%3A%20A%20hash%20algorithm,of%20the%20output%20hash%20separately.
...
#### Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?
...
#### How difficult is it to find a hash digest beginning with at least twelve zeros?
...
http://www.cryptoswise.com/bitcoin-core-how-difficult-is-it-to-find-a-hash-digest-beginning-with-at-least-twelve-zeros/
