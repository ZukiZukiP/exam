* Lecture 12. Paired-samples t-test;

* read in data;
DATA sleepdata;
INPUT id calc3 psychstats;
DATALINES;
1 6 2
2 13 10 
3 8 7
4 6 8 
5 19 10
6 10 7
;
RUN;

* paired-samples t-test;
PROC TTEST DATA=sleepdata;
PAIRED calc3*psychstats;
RUN;
