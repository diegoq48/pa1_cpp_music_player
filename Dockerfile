FROM ubuntu:jammy	
WORKDIR /opt 
ADD https://github.com/openframeworks/openFrameworks/releases/download/0.11.2/of_v0.11.2_linux64gcc6_release.tar.gz /opt 
RUN tar -xpvf ./of_v0.11.2_linux64gcc6_release.tar.gz
WORKDIR /opt/of_v0.11.2_linux64gcc6_release/apps/myapps
RUN mkdir project1 && cd ./project1
WORKDIR /opt/of_v0.11.2_linux64gcc6_release/scripts/linux/ubuntu 
RUN ./install_dependencies.sh -y && ./install_codecs.sh -y 
RUN ../compile_of.sh -j4
COPY --exclude=Dockerfile ./* /opt/of_v0.11.2_linux64gcc6_release/apps/myapps/project1
RUN make 
ENTRYPOINT /opt/of_v0.11.2_linux64gcc6_release/apps/myapps/project1/bin/project1




