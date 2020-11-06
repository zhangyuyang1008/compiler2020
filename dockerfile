FROM gcc:10
COPY ./* ./
RUN gcc OPG.c -o OPG
RUN chmod +x OPG
