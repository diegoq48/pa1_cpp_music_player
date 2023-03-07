FROM ubuntu:22.04
WORKDIR /opt 
ADD https://github.com/UPRM-CIIC4010-S23/pa1-diegoquinones_edyancruz/releases/download/v0.01 /opt
RUN tar -xpvf reactionemAlpha.tar 
ENTRYPOINT /opt/bin/reactionem
