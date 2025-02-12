# The Dockerfile is based on the official Ubuntu image for the jammy release. 
# The CONNEXT_VERSION argument is used to specify the version of RTI Connext to install. 
# The RTI_LICENSE_AGREEMENT_ACCEPTED argument is used to accept the RTI license agreement during installation.
# The NDDSHOME environment variable is set to the installation directory of RTI Connext.
#
# The Dockerfile installs the requisite RTI Connext Debian Packages from the official RTI repository. It also installs some build tools and the license file.
#
# The CMD instruction specifies the default command to run when the container starts. In this case, it runs the /bin/bash shell.
#
# To build the Docker image, run the following command from the root repository folder:
#   docker build -t connext:oteladapter -f ./Dockerfile --build-arg RTI_LICENSE_AGREEMENT_ACCEPTED=accepted --build-arg CONNEXT_VERSION=7.3.0 .
#
# To run the Docker container, run the following command:
#   docker run -it --rm --net=host -v $RTI_LICENSE_FILE:/root/rti_license.dat connext:oteladapter 
#
#   The -it option is used to run the container in interactive mode.
#   The --rm option is used to remove the container when it exits.
#
# The container will start and run the /bin/bash shell.

FROM ubuntu:jammy AS install-stage

ARG CONNEXT_VERSION=7.3.0
ARG RTI_LICENSE_AGREEMENT_ACCEPTED

ENV DISPLAY=:0
ENV SHELL=/bin/bash
# CHANGE THE FOLLOWING LINE TO MATCH YOUR TIMEZONE
ENV TZ=Europe/Madrid
ENV NDDSHOME=/opt/rti.com/rti_connext_dds-${CONNEXT_VERSION}

# Install the required packages
RUN export DEBIAN_FRONTEND=noninteractive \
    && apt-get update \
    && apt-get install -y \
    ca-certificates \
    dash \
    tzdata \
    git \
    build-essential \
    cmake \
    curl \
    libcurlpp-dev \
    zlib1g-dev \
    nano \
    tmux \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists

# Install the RTI Connext Debian Package
RUN curl -sSL -o /usr/share/keyrings/rti-official-archive.gpg \
    https://packages.rti.com/deb/official/repo.key

RUN printf -- "deb [arch=%s, signed-by=%s] %s %s main\n" \
    $(dpkg --print-architecture) \
    /usr/share/keyrings/rti-official-archive.gpg \
    https://packages.rti.com/deb/official \
    $(. /etc/os-release && echo ${VERSION_CODENAME}) | tee /etc/apt/sources.list.d/rti-official.list >/dev/null

RUN export DEBIAN_FRONTEND=noninteractive \
    RTI_LICENSE_AGREEMENT_ACCEPTED=${RTI_LICENSE_AGREEMENT_ACCEPTED} \
    && apt-get update \
    && apt-get install -y \
    rti-connext-dds-${CONNEXT_VERSION}-services-routing \
    rti-connext-dds-${CONNEXT_VERSION}-services-routing-dev \
    rti-connext-dds-${CONNEXT_VERSION}-lib-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists

WORKDIR /root

# Copy the source code
RUN mkdir -p /root/opentelemetry-adapter/generator /root/opentelemetry-adapter/resources /root/opentelemetry-adapter/src
COPY generator /root/opentelemetry-adapter/generator
COPY resource /root/opentelemetry-adapter/resource
COPY src /root/opentelemetry-adapter/src
COPY CMakeLists.txt /root/opentelemetry-adapter/

# Clone the opentelemetry-cpp v1.18.0 branch without history and build
RUN git clone --depth 1 --branch v1.18.0 https://github.com/open-telemetry/opentelemetry-cpp.git
WORKDIR /root/opentelemetry-cpp
RUN git submodule update --init --recursive third_party/prometheus-cpp
RUN mkdir -p /root/opentelemetry-cpp/build 
WORKDIR /root/opentelemetry-cpp/build
# Build with ABI version 2 to permit gauge metrics
RUN cmake -DBUILD_TESTING=OFF -DWITH_PROMETHEUS=ON -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DWITH_ABI_VERSION_1=OFF ..
RUN cmake --build .
RUN cmake --install . --prefix /root/opentelemetry-adapter/otel-cpp

WORKDIR /root/opentelemetry-adapter

# Build the source code
RUN mkdir build && cd build && cmake .. && cmake --build .

# Configure licence file
RUN echo "export RTI_LICENSE_FILE=/root/rti_license.dat" >> /root/.bashrc
RUN rm ${NDDSHOME}/rti_license.dat
RUN ln -s /root/rti_licence.dat ${NDDSHOME}/rti_license.dat

# Tweaks
RUN echo "source ${NDDSHOME}/resource/scripts/rtisetenv_*.bash" >> /root/.bashrc
RUN echo 'mkcd() { mkdir -p "$1" && cd "$1"; }' >> /root/.bashrc

FROM scratch AS final-stage

WORKDIR /root

COPY --from=install-stage / /

CMD ["/bin/bash"]
