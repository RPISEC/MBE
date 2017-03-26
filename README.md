# Modern Binary Exploitation - CSCI 4968
This repository contains the materials as developed and used by [RPISEC](http://rpis.ec) to
teach Modern Binary Exploitation at [Rensselaer Polytechnic Institute](http://rpi.edu) in
Spring 2015. This was a university course developed and run solely by students to teach
skills in vulnerability research, reverse engineering, and binary exploitation.

<p align="center">
<img width="600px" src="/resources/images/mbe.jpg" alt="MBE"/>
</p>

## About the Course

Vulnerability research & exploit development is something totally outside the bounds of what
you see in a normal computer science curriculum, but central to a lot of what we RPISEC
members find ourselves doing in our free time. We also find that subjects in offensive
security tend to have a stigma around them in university that we would like to help shake
off. These are practical, applied skills that we're excited to share with those interested
in learning.

The question this course posed was _'Can we teach a bunch of programmers how to pwn?'_

**Course website:** http://security.cs.rpi.edu/courses/binexp-spring2015/

**Syllabus:** http://security.cs.rpi.edu/courses/binexp-spring2015/Syllabus.pdf

### Course Abstract

>_Cybersecurity is one of the fastest growing fields in computer science, though its study is rarely covered in academia due to its rapid pace of development and its technical specificity. Modern Binary Exploitation will focus on teaching practical offensive security skills in binary exploitation and reverse engineering. Through a combination of interactive lectures, hands on labs, and guest speakers from industry, the course will offer students a rare opportunity to explore some of the most technically involved and fascinating subjects in the rapidly evolving field of security._

>_The course will start off by covering basic x86 reverse engineering, vulnerability analysis, and classical forms of Linux-based userland binary exploitation. It will then transition into protections found on modern systems (Canaries, DEP, ASLR, RELRO, Fortify Source, etc) and the techniques used to defeat them. Time permitting, the course will also cover other subjects in exploitation including kernel-land and Windows based exploitation._

### Prerequisite Knowledge
This course carried a prereq of
[Computer Organization - CSCI 2500](http://catalog.rpi.edu/preview_course_nopop.php?catoid=10&coid=16571)
at RPI. Computer Organization is RPI's basic computer architecture course that teaches
things like C, MIPS assembly, x86 assembly, Datapaths, CPU Pipelining, CPU Caching,
Memory Mapping, etc.

Our expected demographic for Modern Binary Exploitation was students with zero reverse
engineering or binary exploitation knowledge. That said, to be able to take this course
you will probably need at least the following skills.
* Working knowledge of C/C++
* Any assembly level experience
* Basic Linux command line experience

### Lecture Breakdown
Lecture | Title | Topics
------- | ----- | ------
01 | Syllabus and Review | Linux, C, x86
02 | Introduction to Reverse Engineering | Tools and the VM
03 | Extended Reverse Engineering | GDB & IDA
04 | Intro to Memory Corruption | ELF, the stack, calling conventions, buffer overflows
05 | Shellcoding / Code Injection | Writing shellcode, developing scenario relevant payloads
06 | Format String Vulnerabilities | Format strings, DTOR/GOT overwrites
07 | DEP and ROP | Data Execution Prevention, writing ROP chains, ret2libc
08 | Secure Systems and Game Console Exploitation | OpenBSD, SELinux, GRSEC, Game Console Exploitation
09 | Address Space Layout Randomization (ASLR) | Overview, info leaks, partial overwrites, ASLR closure
10 | Heap Exploitation | Heap structure and concepts, corruption, use after free
11 | Misc Concepts and Stack Cookies | Signed/unsignedness issues, uninitialized data, etc, bypassing stack cookies
12 | C++ Differences and Concepts | C++ basics, structures, vTables, exceptions
13 | Linux Kernel Exploitation | Kernel basics, kernel exploitation, mitigations (mmap_min_addr, kallsyms, SMEP/SMAP), bypassing mitigations
14 | Exploitation on 64bit, ARM, Windows | Exploitation differences on other architectures & platforms
15 | Automation & The Future of Exploitation | Fuzzing, taint analysis, dynamic instrumentation, SMT/SAT solvers

### Lab Breakdown
Lab | Topic | Corresponding Lectures
--- | ----- | ----------------------
[01](/src/lab01) | Reverse Engineering | 01-03
[02](/src/lab02) | Memory Corruption | 04
[03](/src/lab03) | Shellcoding | 05
[04](/src/lab04) | Format Strings | 06
[P1](/src/project1) | Project 1 | 01-06 (Comprehensive)
[05](/src/lab05) | DEP and ROP | 07
**XX** | **ASLR should always be enabled from this point on** | **See VM Information for details**
[06](/src/lab06) | ASLR | 09
[07](/src/lab07) | Heap | 10
[08](/src/lab08) | Misc and Stack Cookies | 11
[09](/src/lab09) | C++ | 12
[P2](/src/project2) | Project 2 | 01-12 (Comprehensive)
[10](/src/lab10) | Linux Kernel | 13

### Repository Breakdown
* [src/](/src) - Source code for labs
* [setup_wargame.sh](/setup_wargame.sh),[external_tools.sh](/external_tools.sh) - Install scripts to setup MBE on an Ubuntu 14.04 32-bit machine
* [MBE_release.tar.gz](https://github.com/RPISEC/MBE/releases/download/v1.1_release/MBE_release.tar.gz) - Binaries for labs and projects
* [MBE_lectures.tar.gz](https://github.com/RPISEC/MBE/releases/download/v1.1_release/MBE_lectures.tar.gz) - PDFs of all lecture slides
* [MBE_VM.vmdk.gz](https://github.com/RPISEC/MBE/releases/download/v1.1_release/MBE_VM.vmdk.gz) - A vmdk (disk image) of a VM that is already setup

## Labs - The RPISEC Warzone

The Warzone is a custom wargame that was built from the ground up for this course. It provided
a complete and consistent learning platform for us to release the labs and projects to the
students. The wargame was built ontop of a vanilla Ubuntu 14.04 32-bit server install, and is
modeled after existing local privilege escalation themed wargames. If you have ever played
the fantastic [IO wargame](https://io.netgarage.org/) (formerly hosted at SmashTheStack), the Warzone has a
somewhat similar structure.

<p align="center">
<img src="/resources/images/warzone.png" alt="RPISEC Warzone"/>
</p>

Some basic tweaks have been made in an attempt to isolate players from each other and create
an individual experience, but it's probably far from perfect. It also comes pre-installed with
some tools, scripts, and configs that can make a beginner's life a bit easier in exploit
development.

You can roll with the Warzone we designed, or you can try to setup your own using our scripts.
___
### Option One - Pre-made Warzone VM
As the years pass, compilers will change, security will improve, and the challenges in this
repo may no longer be solvable. Because of this, we have created a virtual machine disk image
that closely replicates the universal Warzone wargame server we ran for the duration of this
course. The VM has all the tools setup, challenges pre-compiled, and lab accounts ready to go.
Hopefully it will endure the test of time.

#### Virtual Machine Setup

RPISEC is a huge advocate of VMware because of its quality and stability, so we recommend
using our disk image below with VMware Workstation, VMware Fusion, or VMware Player. That
said, it should also work with VirtualBox.

VMware provides a great [2 minute video](https://www.youtube.com/watch?v=I6WfFLQwoPg) on how to setup a virtual machine using an existing disk image.

<p align="center">
<a href="https://www.youtube.com/watch?v=I6WfFLQwoPg"><img src="/resources/images/vmware.png" alt="Final"/></a>
</p>

1. Download [MBE_VM.vmdk.gz](https://github.com/RPISEC/MBE/releases/download/v1.1_release/MBE_VM.vmdk.gz) from our release page
2. Extract the archive to obtain the disk image
3. Using VMware go to `File->New Virtual Machine...` and create a Custom VM
4. When prompted for `Guest Operating System Installation`, select `I will install the operating system later`
5. You can use the default options for almost all the prompts you encounter. For specs, we suggest the following:
  * 1 processor / core
  * 512 MB of RAM
  * NAT Networking
6. When prompted to `Select a Disk`, select `Use an existing virtual disk` and navigate to the .vmdk you extracted
7. In the end your final screen should look something like this. Click Finish and then power on the VM.

<p align="center">
<img src="/resources/images/final.png" alt="Final"/>
</p>


#### How to Play
We tried to keep the course fairly self contained but if you find yourself lost or struggling [OverTheWire's Bandit](http://overthewire.org/wargames/bandit/) is a great intro to Linux wargames. You can also poke people on [IRC](#contact) if you have questions.
* SSH is pre-setup on the VM, but we need an IP. First, sign in through the VMWare or VirtualBox console. To find the IP address type:<br>
  ```$ ip addr```<br>
  <p align="center">
  <img src="/resources/images/ip_addr.png" alt="ip addr"/>
  </p>
  and then SSH using [PuTTY](http://the.earth.li/~sgtatham/putty/latest/x86/putty.exe) or a command line client<br>
  ```$ ssh lab1C@172.16.29.130```<br>
  ```lab1C@172.16.130's password: lab01start```<br>
* Navigate to `/levels/labXX` to begin<br>
  ```$ cd /levels/lab01```
* The Warzone is structured like any local privilege escalation wargame.
You must exploit a challenge to escalate your privileges and gain access to another user (level).
Once you exploit a level and escalate to the next user (confirm with `whoami`), read their password from their home dir<br>
  ```$ cat /home/lab1B/.pass```
* SSH in using the new username and password to continue!

#### VM information
* admin user: `gameadmin:gameadmin`
* lecture user: `lecture:lecture`
* rc files are in `/etc/cfg`
  * All lab/project users have symlinks to these files in their home directories
  * These files are also symlinked in `/etc/skel`
* To begin a lab, login as `labXC:lab0Xstart`
  * e.g. `lab1C:lab01start`
  * Projects are `projectX:projectXstart`
* Levels are in `/levels`
* Passwords are in `/home/$USER/.pass`
* Tools are installed in `/tools` and `/usr/local/bin`
* **ASLR must be enabled after completing the DEP/ROP lab, and stay enabled for the rest of the course**
  * Until reboot: ```# echo 2 > /proc/sys/kernel/randomize_va_space```
  * Persist reboot: ```# echo 'kernel.randomize_va_space = 2' > /etc/sysctl.d/01-disable-aslr.conf```

___
### Option Two - Make a Custom Warzone
We have provided a bash script that will fully setup the exact environment in the provided VM. 

**DO NOT RUN THIS SCRIPT ON YOUR PERSONAL COMPUTER, RUN IT IN A VIRTUAL MACHINE**

1. Download [MBE_release.tar.gz](https://github.com/RPISEC/MBE/releases/download/v1.1_release/MBE_release.tar.gz)
2. Move the archive to your VM or machine and extract it <br>
  **NOTE: It is not recommended to run the script from /tmp, as the sticky bits can screw up wildcards** <br>
  ```$ tar xzvf MBE_release.tar.gz```
3. Modify the configuration variables at the top of [setup_wargame.sh](/setup_wargame.sh) to suit your needs
4. Make the setup script executable and run it with sudo<br>
  ```$ chmod +x ./setup_wargame.sh```<br>```$ sudo ./setup_wargame.sh```<br>
It should take about 10-20 minutes to complete depending on your internet connection and the
number of Ubuntu updates.

## Frequently Asked Questions

#### Why can't I login to lab1c?
Account names are case sensitive, so please check that you're logging in as lab1**C**

#### Why am I getting 'permission denied' errors?
The warzone marks many files as immutable to prevent users from changing them and
ruining the game for other players. For example, we don't want the lab2B user to
delete its `.pass` file or `/levels` files. A few system files, such as `/etc/passwd`,
are also marked immutable. 

If you would like to modify or delete these files simply remove the immutable flag
```bash
chattr -i filename
```
We recommend that you add the flag back when you are done making your changes
```bash
chattr +i filename
```

#### Where are the lab solutions?
Posting solutions spoils the fun and grind of the game, and as an academic resource it is
likely some of these materials may be re-used by other classes in the future. As goes with
most wargames, we would like to ask that you refrain from publicly posting writeups or
exploits to the labs and projects.

If you are ever stuck on a problem or have any questions, you're more than welcome to
ask on [IRC](#contact).

#### Why are the lecture slides for XYZ so sparse?
This was a very hands on course, so almost every lecture we had students slinging GDB commands
or following along with us on screen. The slides were accessory to the lectures and may have
gaps or experience brevity at times. With seven of us creating and giving lectures, the slides
and teaching styles vary a bit. We did our best to keep them consistent. 

#### Do you have videos of the lectures?
Sadly we did not record any of the lectures, maybe next time.

#### Why provide the lab sources to the students?
We're huge fans of reversing / CTF challenges, but reversing is mostly a time problem. With
students juggling other classes and work during the school semester, we'd rather them focus on
learning the exploitation techniques without the overhead of reversing every binary. 

#### These challenges are really easy, what gives?
The 50 students that enrolled had little to no prior computer security experience. The labs 
are not designed to be novel CTF challenges, they're meant to be more academic examples paced
to crystallize the concepts. Seasoned CTF'ers can probably blow through most of these
challenges in a day or two. 

#### Why didn't you cover subject XYZ?
If XYZ is related to vulnerability research, we're all ears. The course is far from perfect
and we are open to hear any feedback for improving it. 

#### Will this course be taught again at RPI?
There's a lot of interest in having it offered again, so it's being considered for Spring
2016. The feedback was almost exclusively positive with the students finding the material
challenging, but engaging. We've got dozens of ideas on how to make it even better next time.

#### Where can I learn more?
Play more wargames:
* [SmashTheStack IO](http://io.smashthestack.org/)
* [Pwnable KR](http://pwnable.kr/)
* [OverTheWire](http://overthewire.org/wargames/)
* [Reversing KR](http://reversing.kr/)
* [W3Challs](http://w3challs.com/)

And when they're happening, play [CTFs](https://ctftime.org/)!

#### <a name="contact"></a>I have a question, how can I get in touch with you?
Our club keeps a pretty active [IRC](http://rpis.ec/irc) presence. Someone there can probably
answer your question.

**Server:** `irc.rpis.ec`
**Port:** `6667`, or `6697` (SSL)


If you would like a more formal means of communication, you can reach us at `contact [at] rpis.ec`


# Licensing
This course was explicitly designed for academic & educational use only. Please keep this
in mind when sharing and distributing our course material. The specific licenses involved
can be found below.

**Lecture Slides**

The lectures are covered by the Creative Commons Attribution-NonCommercial 4.0
International license [CC BY-NC 4.0](https://creativecommons.org/licenses/by-nc/4.0/legalcode).
<p align="center">
<a href="https://creativecommons.org/licenses/by-nc/4.0/"><img src="/resources/images/cc-by-nc.png" alt="CC BY-NC 4.0"/></a>
</p>

**Code**

The code in this repo is covered by the BSD 2-Clause license. You can view this license in [LICENSE](/LICENSE).

# Acknowledgements
Hundreds of hours and countless all nighters went into the production and execution of
this course. This section serves to recognize those who made all of this possible.

## Original Authors
  * Patrick Biernat
  * Jeremy Blackthorne
  * Alexei Bulazel
  * Branden Clark
  * Sophia D'Antoine
  * Markus Gaasedelen
  * Austin Ralls

## Special Thanks
  * The [RPI CS Department](http://www.cs.rpi.edu/) for giving us this opportunity and letting us run with it
  * Professor Bülent Yener for sponsoring such a course
  * Our students who put up with us all semester
