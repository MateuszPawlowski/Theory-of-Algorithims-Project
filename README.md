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
