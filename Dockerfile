FROM rhargreaves/gendev:circle-12
RUN apt-get -y update && \
	apt-get -y install \
	build-essential \
	cmake \
	gdb \
	gdbserver
EXPOSE 2345
ENTRYPOINT []
