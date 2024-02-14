# Cameron's Boot & Nuke

Author: camsterrrr (Cameron Oakley), Oakley.CameronJ@gmail.com

CBAN is a Ubuntu CLI utility that allows users to wipe a drives directly from the command line. CBAN's primary use case is to erase drives with sensitive information before e-wasting or selling, this helps keep organizations in compliance with DoD and California DoJ standards of operation.

This utility was inspired by Darik's Boot & Nuke (DBAN), a free (semi open-source) software used to wipe drives. DBAN has been popular throughout the software community for over a decade, and has long since been out of support. The age of the software and lack of support, among other things, inspired me to create my own spin of the software. This project, is aimed to reintroduce the open-source drive wiper.

There were a few issues with DBAN that I have come across while using it for the last several years. These are points in which I hope this software can improve on.
- DBAN has limitations on the hardware it can run on. It will only run on legacy hardware, which makes it a pain to work with at times.
- DBAN runs using a dedicated Linux kernel, meaning you must have a computer solely running this program. 
- Lack of documentation in the GitHub repository. Other than downloading the .ISO file from sourceforge.net, there really isn't any documentation that shows you how to boot up.
    - Machines that I've used DBAN on required running in UEFI mode only.

## Directory structure

This is likely the least complicated open-source repo you've come across. The main directories are as follows, `src` is where you will find any C code that I've written, `bin` is where I will store the binaries,  and `Makefile` may be useful to anyone tweaking the source code. `output` is where this program will output any error or warning log messages.

## Installation

0. Temp text.
1. Temp text.

```bash

```

## How to use




## Best practices

## Disclaimer

This utility will unrecoverably erase drive data. Please ensure that you are using appropriate safety precautions while working with CBAN.

## Feedback

Any feedback is accepted and appreciated! Seriously, if you know how I could better implement the programming, or if there is some edge case bug, please let me know. I aim to make this software reliable and robust. 

For any inquiries, you can contact me at Oakley.CameronJ@gmail.com

## Special thanks

Special thanks to the author of the DBAN software. I began working in IT before I had ever written a line of code, I was always fascinated by your software (truly speaking). Your software inspired me to start this project and for that, I thank you.

## Licensing

Not sure what to put here yet. :\(
