* Lecture 11. One-sample t-test;

* read in data;
DATA birthweight;
INFILE '/home/u47510210/mywork/birthweight.txt';
INPUT id weight;
RUN;

* one-sample t-test;
PROC TTEST DATA=birthweight H0=2800;
VAR weight;
RUN;
