# CompetitionEclipse
Face Recognition competition congifured with Eclipse CDT

###READ ME

In case of architecture incompatibility, object files regarding the algorithm were also attached so that it can be compiled in the target machine.

To generate an executable file in the target machine, open the /obj folder and execute: ./compile2binary.sh.

Note that on non-Linux systems like Solaris, you might have to link to other libraries. For example, I have seen systems where it was also necessary to supply -lnsl or -lsocket options to g++. 

Additionally, the X11 development library isn't installed on Ubuntu by default. So if you require it and are using Ubuntu you can install it by typing: sudo apt-get install libx11-dev
