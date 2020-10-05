FROM gcc:10
COPY ./* ./
RUN gcc word_analysis.c -o word_analysis
RUN chmod +x word_analysis