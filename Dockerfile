FROM ubuntu:22.04
COPY . /workspace/421-bootcamp
VOLUME /workspace/421-bootcamp
RUN cd /workspace/421-bootcamp; echo 'y' | ./packages.sh;
CMD ["sleep","infinity"]
