ARG PACKAGE_NAME="latin-checker_1.0_amd64.deb"

FROM ubuntu:latest
ARG PACKAGE_NAME
WORKDIR /tmp
RUN apt-get update
RUN apt-get install -y dpkg-dev
COPY ../$PACKAGE_NAME /tmp/
RUN dpkg -i $PACKAGE_NAME
RUN apt-get -f install -y
# For some AWESOME reason this stuff comes WITHOUT execute permissions so
RUN chmod +x /usr/bin/latin-checker

ENTRYPOINT ["latin-checker"]
