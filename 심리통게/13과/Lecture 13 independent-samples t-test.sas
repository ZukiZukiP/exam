* Lecture 13. Indepedent-samples t-test;

* read in data;
DATA speeddata;
INFILE '/home/u47510210/mywork/speed.txt';
INPUT id group speed;
LABEL group = '1:smash,2:hit';
RUN;

* independent-samples t-test;
PROC TTEST DATA=speeddata;
CLASS group;
VAR speed;
RUN;

